#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace bananas {

class Node {
  public:
    explicit Node(const std::string&);
    Node* next(char);
    Node* add(char);
    void setValid();

    void print(const std::string&);

  private:
    std::string word_ = "";
    bool valid_ = false;
    std::unordered_map<char, std::unique_ptr<Node>> next_;
};

std::unique_ptr<Node> initializeGraph(const std::string&);

void printGraph(Node*);

} // namespace bananas
