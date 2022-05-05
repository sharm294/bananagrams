#include "database.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

namespace bananas {

Node::Node(const std::string& word_so_far) : word_(word_so_far) {}

Node* Node::next(char c){
    auto iterator = next_.find(c);
    if(iterator != next_.end()){
        return iterator->second.get();
    }
    return nullptr;
}

Node* Node::add(char c){
    auto new_node = std::make_unique<Node>(word_ + c);
    next_.insert({c, std::move(new_node)});
    return next_.at(c).get();
}

void Node::setValid(){
    valid_ = true;
}

void Node::print(const std::string& indent){
    std::cout << indent << word_.back();
    if(valid_){
        std::cout << "*";
    }
    std::cout << "\n";
    for(const auto& [c, next] : next_){
        next->print(indent + " ");
    }
}

std::unique_ptr<Node> initializeGraph(const std::string& word_list_file){
    auto root = std::make_unique<Node>("");

    std::ifstream word_file(word_list_file);
    std::string word;
    while(word_file >> word){
        auto* current_node = root.get();
        for(const auto& c : word){
            Node* next = current_node->next(c);
            if(next == nullptr){
                next = current_node->add(c);
            }
            current_node = next;
        }
        current_node->setValid();
    }
    
    return root;
}

void printGraph(Node* root){
    root->print("");
}

} // namespace bananas
