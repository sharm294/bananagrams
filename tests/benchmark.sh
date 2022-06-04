#!/usr/bin/env bash

# This script evaluates the memory and runtime of the bananagram solver in 
# some scenarios for comparison purposes

set -e

# build the project under a config type
compile(){
    cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
        -DCMAKE_BUILD_TYPE:STRING=$1 -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc \
        -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ \
        -S/home/sharm294/bananagrams -B/home/sharm294/bananagrams/build -G "Unix Makefiles"

    cmake --build /home/sharm294/bananagrams/build --config $1 --target all -j 6 --
}

# usage: avg_time n command ...
# https://stackoverflow.com/a/54920339
avg_time() {
    n=$1; shift
    filename="./tests/board_${1}.out"; shift
    (($# > 0)) || return                   # bail if no command given
    for ((i = 0; i < n; i++)); do
        # ignore the output of the command but collect time's output in stdout
        { time -p "$@" &> ${filename}; } 2>&1
    done | awk '
        /real/ { real = real + $2; nr++ }
        /user/ { user = user + $2; nu++ }
        /sys/  { sys  = sys  + $2; ns++}
        END    {
                 if (nr>0) printf("    real %f\n", real/nr);
                 if (nu>0) printf("    user %f\n", user/nu);
                 if (ns>0) printf("    sys %f\n",  sys/ns)
               }'
}

compile RelWithDebInfo

programs=(
    # this takes ~1s
    "./build/src/main ./dictionaries/en_0.txt castearbail"
    # this takes ~1s
    "./build/src/main ./dictionaries/en_1.txt aksdhfoweroweounsdkfnaweyuruewliuoiiioi"
    # this takes ~1s
    "./build/src/main --freq-min 99 ./dictionaries/en_1.txt aksdhfoweroweounsdkfnaweyuruewliuoiiioi"
    # this takes ~ 30s
    "./build/src/main --freq-min 99 --len-min 3 ./dictionaries/en_1.txt aksdhfoweroweounsdkfnaweyuruewliuoiiioi"
    # this takes ~ 2-3min
    "./build/src/main --freq-min 99 --len-min 3 --len-max 6 ./dictionaries/en_1.txt aksdhfoweroweounsdkfnaweyuruewliuoiiioi"
    # this takes >hours? have not seen it end. Is it in a cycle?
    # "./build/src/main --freq-min 99 --len-min 4 --len-max 6 ./dictionaries/en_1.txt aksdhfoweroweounsdkfnaweyuruewliuoiiioi"
)

data_file="./tests/benchmark.out"
rm -f $data_file
touch $data_file

index=0
for program in "${programs[@]}"; do
    echo "Running $program"
    echo "$index: $program" >> $data_file

    # runtime
    echo "  Getting program runtime"
    # run_time=$(/usr/bin/time --format "%E" $program)
    echo "  Runtimes:" >> $data_file
    avg_time 1 $index $program >> $data_file

    # memory usage
    echo "  Getting memory usage with massif"
    valgrind --tool=massif --pages-as-heap=yes --massif-out-file=massif_${index}.out $program &> /dev/null
    peak_mem=$(grep mem_heap_B massif.out | sed -e 's/mem_heap_B=\(.*\)/\1/' | sort -g | tail -n 1)
    echo "  Peak memory: $peak_mem" >> $data_file

    # profiling
    echo "  Getting profiling data with callgrind"
    valgrind --tool=callgrind --callgrind-out-file=callgrind_${index}.out $program &> /dev/null
    # callgrind_annotate --tree=both callgrind_${index}.out > tmp.txt  

    index=$((index+1))
done
