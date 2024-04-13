#pragma once
#include <memory>
#include <iostream>

namespace spbu {

template<typename TVal>
class BTSetNode {
public:
    BTSetNode(TVal value)
        : value_(value) { }

    TVal getValue() {
        return value_;
    }

    std::shared_ptr<BTSetNode<TVal>> getLeft() {
        return left_;
    }


    std::shared_ptr<BTSetNode<TVal>> getRight() {
        return right_;
    }

    void setLeft(std::shared_ptr<BTSetNode<TVal>> node) {
        left_ = node;
    }


    void setRight(std::shared_ptr<BTSetNode<TVal>> node) {
        right_ = node;
    }

private:
    std::shared_ptr<BTSetNode<TVal>> left_ = nullptr;
    std::shared_ptr<BTSetNode<TVal>> right_ = nullptr;
    TVal value_;
};

template <typename TVal>
class BTSet {
public:
    BTSet() {

    }

    void add(const TVal& value) {
        if (root == nullptr) {
            root = std::shared_ptr<BTSetNode<TVal>>(new BTSetNode(value));
            return;
        }

        insert_(root, value);
    }

    bool contains(const TVal& value) {
        if (root == nullptr) {
            return false;
        }

        return find_(root, value);
    }

    void remove(const TVal& value) {
        if (root == nullptr) {
            return;
        }

        remove_(root, value);
    }

private:
    void insert_ (std::shared_ptr<BTSetNode<TVal>> node, const TVal& value) {
        if (value < node->getValue()) {
            if (node->getLeft() != nullptr) {
                insert_(node->getLeft(), value);
            } else {
                node->setLeft(std::shared_ptr<BTSetNode<TVal>>(new BTSetNode<TVal>(value)));
            }
        }

        if (value > node->getValue()) {
            if (node->getRight() != nullptr) {
                insert_(node->getRight(), value);
            } else {
                node->setRight(std::shared_ptr<BTSetNode<TVal>>(new BTSetNode<TVal>(value)));
            }
        }

        // при равенстве ничего не нужно делать
    }

    bool find_(std::shared_ptr<BTSetNode<TVal>> node, const TVal& value) {
        if (node == nullptr) {
            return false;
        }

        if (value < node->getValue()) {
            return find_(node->getLeft(), value);
        }

        if (value > node->getValue()) {
            return find_(node->getRight(), value);
        }

        return value == node->getValue();
    }

    std::shared_ptr<BTSetNode<TVal>> remove_(std::shared_ptr<BTSetNode<TVal>> node, const TVal& value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->getValue()) {
            node->setLeft(remove_(node->getLeft(), value));
            return node;
        }

        if (value > node->getValue()) {
            node->setRight(remove_(node->getRight(), value));
            return node;
        }

        if (node->getLeft() == nullptr) {
            return node->getRight();
        }

        if (node->getRight() == nullptr) {
            return node->getLeft();
        }

        // подвесим левое поддерево в самую левую точку правого поддерева
        // это можно делать, так как все элементы левого поддерева меньше всех элементов правого
        auto cur = node->getRight();
        while (cur->getLeft() != nullptr) {
            cur = cur->getLeft();
        }
        cur->setLeft(node->getLeft());
        return node->getRight();
    }

    std::shared_ptr<BTSetNode<TVal>> root = nullptr;
};

}
