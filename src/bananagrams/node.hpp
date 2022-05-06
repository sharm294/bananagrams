#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>

namespace bananas {

class Node;

using NodeMap = std::unordered_map<char, std::unique_ptr<Node>>;

class Node {
  public:
    explicit Node(const std::string&);
    Node* next(char);
    Node* add(char);

    std::string getWord() const;
    
    void setValid();
    bool isValid() const;

    void print(const std::string&, std::ostream&);

    NodeMap::iterator begin();
    NodeMap::iterator end();
    NodeMap::const_iterator cbegin() const;
    NodeMap::const_iterator cend() const;

  private:
    std::string word_ = "";
    bool valid_ = false;
    NodeMap next_;
};

} // namespace bananas
