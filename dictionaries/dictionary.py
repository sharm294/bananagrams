import argparse
import json

"""
Given a dictionary and some set of frequency lists, combine the two to create
a dictionary with attached frequency data
"""


def parser_0(path_to_file, data: dict):
    """
    Parse the data in format 0:
        word
    """

    with open(path_to_file) as f:
        for line in f:
            read_line = line.split()
            word = read_line[0].strip().lower()
            if word not in data:
                data[word] = 0


def parser_1(path_to_file, data: dict):
    """
    Parse the data in format 1:
        word word_count
    """

    with open(path_to_file) as f:
        for line in f:
            read_line = line.split()
            word = read_line[0].strip().lower()
            frequency = read_line[1].strip()
            if word in data:
                data[word] += int(frequency)
            else:
                data[word] = int(frequency)


def combine(words: dict, freqs: dict, out_file: str):
    """
    If words is non empty, filter the frequencies with the chosen words, convert
    the frequencies to percentages, and save the dictionary
    """

    if len(words) != 0:
        # delete all frequencies that aren't present in our dictionary if it exists
        filtered_freqs = {k: freqs[k] for k in freqs.keys() if k in words}
    else:
        # construct a new word dictionary if none is specified with empty frequencies
        words = {k: 0 for k in freqs.keys()}
        filtered_freqs = freqs

    frequency_len = len(filtered_freqs)
    print(frequency_len)
    sorted_freqs = dict(
        sorted(filtered_freqs.items(), key=lambda item: item[1], reverse=True)
    )
    index = 0
    for key in sorted_freqs.keys():
        sorted_freqs[key] = 100 - (index / frequency_len * 100)
        index += 1
        if index < 5:
            print(key, sorted_freqs[key])

    with open(out_file, "w") as f:
        for word, freq in words.items():
            if word in sorted_freqs:
                freq += sorted_freqs[word]
            f.write(f"{word} {freq}\n")


def add_help(command_group):
    command_group.add_argument(
        "-h", "--help", action="help", help="show this help message and exit"
    )


class Build:
    @staticmethod
    def parse(args):
        print(args)

        freq = {}
        if args.f1 is not None:
            for file in args.f1:
                parser_1(file, freq)

        words = {}
        if args.d0 is not None:
            for file in args.d0:
                parser_0(file, words)

        combine(words, freq, args.output_file)

    @classmethod
    def add(cls, parser):
        subparser = parser.add_parser(
            "build", help="Build a dictionary file with frequency data", add_help=False
        )

        command_group = subparser.add_argument_group("Options")
        add_help(command_group)

        command_group.add_argument(
            "-d0",
            dest="d0",
            action="append",
            help=f"path to dictionary file (format 0)",
        )

        command_group.add_argument(
            "-f1",
            dest="f1",
            action="append",
            help=f"path to frequency file (format 1)",
        )

        command_group.add_argument(
            "-o",
            dest="output_file",
            action="store",
            help=f"output file name. Defaults to out.txt",
            default="out.txt",
        )

        subparser.set_defaults(func=cls.parse)


def get_parser():
    parser = argparse.ArgumentParser(
        prog="dictionary",
        description="Script to build and validate dictionaries for use with bananagrams",
        add_help=False,
    )

    subparser = parser.add_subparsers(
        title="Commands", metavar="command", dest="subparser_name"
    )

    Build.add(subparser)

    command_group = parser.add_argument_group("Options")
    add_help(command_group)

    return parser


if __name__ == "__main__":
    parser = get_parser()

    args = parser.parse_args()
    args.func(args)
