#include "node.hpp"

namespace bananas {

Node::Node(const std::string& word_so_far) : word_(word_so_far) {}

Node* Node::next(char c) {
    auto iterator = next_.find(c);
    if (iterator != next_.end()) {
        return iterator->second.get();
    }
    return nullptr;
}

Node* Node::add(char c) {
    auto new_node = std::make_unique<Node>(word_ + c);
    next_.insert({c, std::move(new_node)});
    return next_.at(c).get();
}

void Node::setValid() { valid_ = true; }

bool Node::isValid() const { return valid_; }

std::string Node::getWord() const { return word_; }

NodeMap::iterator Node::begin() { return next_.begin(); }

NodeMap::iterator Node::end() { return next_.end(); }

NodeMap::const_iterator Node::cbegin() const { return next_.cbegin(); }

NodeMap::const_iterator Node::cend() const { return next_.cend(); }

void Node::print(const std::string& indent, std::ostream& stream) {
    if (!word_.empty()) {
        stream << indent << word_.back();
        if (valid_) {
            stream << "*";
        }
        stream << "\n";
    }
    for (const auto& [c, next] : next_) {
        next->print(indent + " ", stream);
    }
}

}  // namespace bananas
