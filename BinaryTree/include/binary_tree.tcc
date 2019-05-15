#pragma once

namespace AyEDA
{

/*******************************************************************************
*   Base Class Methods
*******************************************************************************/
template<typename T, template<typename> class TNodeType>
void BinaryTree<T, TNodeType>::trim(Node* &node)
{
    if(node == nullptr) return;
    trim(node->left());
    trim(node->right());
    delete node;
}

template<typename T, template<typename> class TNodeType>
std::ostream& BinaryTree<T, TNodeType>::writeInorder(std::ostream& os) const
{
    inorder(os, root_);
    return os;
}

template<typename T, template<typename> class TNodeType>
std::ostream& BinaryTree<T, TNodeType>::writeLevels(std::ostream& os) const
{
    level_order(os, root_);
    return os;
}

template<typename T, template<typename> class TNodeType>
std::ostream& BinaryTree<T, TNodeType>::inorder(std::ostream& os, const Node *node) const
{
    if(node != nullptr)
    {
        inorder(os, node->left());
        os << node << " ";
        inorder(os, node->right());
    }

    return os;
}

template<typename T, template<typename> class TNodeType>
std::ostream& BinaryTree<T, TNodeType>::level_order(std::ostream& os, Node *node) const
{
    std::queue<std::pair<Node*, int>> nodeQueue;
    int level, current_level = 0;
    Node* current_node;

    nodeQueue.emplace(node, 0);

    while (!nodeQueue.empty())
    {
        std::tie(current_node, level) = nodeQueue.front();
        nodeQueue.pop();

        if(level > current_level)
        {
            current_level = level;
            os << std::endl;
        }

        os << current_node << " ";

        if(current_node != nullptr)
        {

            nodeQueue.emplace(current_node->left(), level + 1);
            nodeQueue.emplace(current_node->right(), level + 1);
        }
    }
    return os;
}

/*******************************************************************************
*   Insertion Methods
*******************************************************************************/
template<typename T, template<typename> class TNodeType >
void BinarySearchTree<T, TNodeType>::insert(const T& val)
{
    insert_branch(this->root_, val);
}

template<typename T, template<typename> class TNodeType>
void BinarySearchTree<T, TNodeType>::insert_branch(BSTNode *& node, const T& val)
{
    if(node == nullptr)
    {
        node = new BSTNode(val);
    }
    else if(val < node->get_data())
    {
        insert_branch(node->left(), val);
    }
    else
    {
        insert_branch(node->right(), val);
    }
}


/*******************************************************************************
*   Searching Methods
*******************************************************************************/
template<typename T, template<typename> class TNodeType>
bool BinarySearchTree<T, TNodeType>::search(const T& val) const
{
    return search_branch(this->root_, val);
}

template<typename T, template<typename> class TNodeType>
bool BinarySearchTree<T, TNodeType>::search_branch(const BSTNode *node, const T& val) const
{
    if(node == nullptr)
    {
        return false;
    }
    if(val == node->get_data())
    {
        return true;
    }
    if(val < node->get_data())
    {
        return search_branch(node->left(), val);
    }
    else
    {
        return search_branch(node->right(), val);
    }
}


/*******************************************************************************
*   Removing Methods
*******************************************************************************/
template<typename T, template<typename> class TNodeType>
void BinarySearchTree<T, TNodeType>::remove(const T& val)
{
    remove_branch(this->root_, val);
}

template<typename T, template<typename> class TNodeType>
void BinarySearchTree<T, TNodeType>::remove_branch(BSTNode *& node, const T& val)
{
    if(node == nullptr) return;

    if(val < node->get_data())
    {
        remove_branch(node->left(), val);
    }
    else if(val > node->get_data())
    {
        remove_branch(node->right(), val);
    }
    else
    {
        BSTNode* removed = node;

        if(node->right() == nullptr)
        {
            node = node->left();
        }
        else if(node->left() == nullptr)
        {
            node = node->right();
        }
        else
        {
            replace(removed, node->left());
        }
        delete removed;
    }
}


/*******************************************************************************
*   Auxiliary Methods
*******************************************************************************/
template<typename T, template<typename> class TNodeType>
void BinarySearchTree<T, TNodeType>::replace(BSTNode *& removed, BSTNode *& replacer)
{
    if (replacer->right() != nullptr)
    {
        replace(removed, replacer->right());
    }
    else
    {
        removed->get_data() = replacer->get_data();
        removed = replacer;
        replacer = replacer->left();
    }
}

} //namespace AyEDA