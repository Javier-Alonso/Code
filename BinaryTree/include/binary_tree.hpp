#pragma once

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

#include "node_t.hpp"

namespace AyEDA
{

template<typename T, template<typename> class TNodeType = node_t>
class BinaryTree
{
    static_assert(std::is_base_of<node_t<T>, TNodeType<T>>::value, "node_t required has TNodeType base.");

    protected:

        using Node = TNodeType<T>;
        Node* root_ = nullptr;

    public:

        BinaryTree() = default;
        virtual ~BinaryTree() { trim(root_); }

        bool empty(Node* node) const { return node == nullptr; }
        bool leaf(Node* node)  const { return !node->right() && !node->left(); }

        virtual std::ostream& writeInorder(std::ostream& os) const;
        virtual std::ostream& writeLevels(std::ostream& os) const;

    private:

        void trim(Node* &node);

        std::ostream& inorder(std::ostream& os, const Node *node) const;
        std::ostream& level_order(std::ostream& os, Node *node) const;
};



template<typename T, template<typename> class TNodeType = node_t>
class BinarySearchTree : public BinaryTree<T, TNodeType>
{
    protected:

        using BSTNode = typename BinaryTree<T, TNodeType>::Node;

    public:

        BinarySearchTree() = default;
        ~BinarySearchTree() override = default;

        virtual void insert(const T& val);
        bool search(const T& val) const;
        virtual void remove(const T& val);

    private:

        bool search_branch(const BSTNode *node, const T& val) const;
        void insert_branch(BSTNode *& node, const T& val);
        void remove_branch(BSTNode *& node, const T& val);

        void replace(BSTNode *& removed, BSTNode *& replacer);
};



template<typename T>
class AVLTree : public BinarySearchTree<T, AVLnode_t>
{
    private:

        using AVLNode = typename BinarySearchTree<T, AVLnode_t>::BSTNode;

    public:

        ~AVLTree() override = default;

        void insert(const T& val) override;
        void remove(const T& val) override;

    private:

        void rotateLL(AVLNode* &node);
        void rotateRR(AVLNode* &node);

        void rotateLR(AVLNode* &node);
        void rotateRL(AVLNode* &node);

        void insert_balanced(AVLNode* &node, AVLNode* new_node, bool& grow);
        void insert_rebalanced_left(AVLNode* &node, bool& grow);
        void insert_rebalanced_right(AVLNode* &node, bool& grow);

        void remove_branch(AVLNode* &node, const T& val, bool& decrease);
        void remove_rebalanced_left(AVLNode* &node, bool& decrease);
        void remove_rebalanced_right(AVLNode* &node, bool& decrease);

        void replace(AVLNode* &removed, AVLNode* &replacer, bool& decrease);

};


} //namespace AyEDA

#include "binary_tree.tcc"
#include "avl_tree.tcc"

