#pragma once

namespace AyEDA
{

/*******************************************************************************
*   Rotation Methods
*******************************************************************************/
template<typename T>
void AVLTree<T>::rotateLL(AVLNode* &node)
{
    AVLNode* node1 = node->left();
    node->left() = node1->right();
    node1->right() = node;

    if(node1->get_balance() == 1)
    {
        node->set_balance(0);
        node1->set_balance(0);
    }
    else
    {
        node->set_balance(1);
        node1->set_balance(-1);
    }
    node = node1;
}

template<typename T>
void AVLTree<T>::rotateRR(AVLNode* &node)
{
    AVLNode* node1 = node->right();
    node->right() = node1->left();
    node1->left() = node;

    if(node1->get_balance() == -1)
    {
        node->set_balance(0);
        node1->set_balance(0);
    }
    else
    {
        node->set_balance(-1);
        node1->set_balance(1);
    }
    node = node1;
}

template<typename T>
void AVLTree<T>::rotateRL(AVLNode* &node)
{
    AVLNode* node1 = node->right();
    AVLNode* node2 = node1->left();

    node->right() = node2->left();
    node2->left()= node;
    node1->left() = node2->right();
    node2->right() = node1;

    const int balance = node2->get_balance();

    node1->set_balance((balance == 1)? -1 : 0);
    node->set_balance((balance == -1)? 1 : 0);

    node2->set_balance(0);
    node = node2;
}

template<typename T>
void AVLTree<T>::rotateLR(AVLNode* &node)
{
    AVLNode* node1 = node->left();
    AVLNode* node2 = node1->right();

    node->left() = node2->right();
    node2->right() = node;
    node1->right() = node2->left();
    node2->left() = node1;

    const int balance = node2->get_balance();

    node1->set_balance((balance == -1)? 1 : 0);
    node->set_balance((balance == 1)? -1 : 0);

    node2->set_balance(0);
    node = node2;
}


/*******************************************************************************
*   Insertion Methods
*******************************************************************************/
template<typename T>
void AVLTree<T>::insert(const T& val)
{
    auto* new_node = new AVLNode(val);
    bool grow = false;
    insert_balanced(BinaryTree<T, AVLnode_t>::root_, new_node, grow);
}

template<typename T>
void AVLTree<T>::insert_balanced(AVLNode* &node, AVLNode* new_node, bool& grow)
{
    if (node == nullptr)
    {
        node = new_node;
        grow = true;
    }
    else if (new_node->get_data() < node->get_data())
    {
        insert_balanced(node->left(), new_node, grow);
        if(grow)
        {
            insert_rebalanced_left(node, grow);
        }
    }
    else
    {
        insert_balanced(node->right(), new_node, grow);
        if(grow)
        {
            insert_rebalanced_right(node, grow);
        }
    }
}

template<typename T>
void AVLTree<T>::insert_rebalanced_left(AVLNode* &node, bool& grow)
{
    AVLNode* node1 = node->left();

    switch (node->get_balance())
    {
        case -1:
            node->set_balance(0);
            grow = false;
            break;

        case 0:
            node->set_balance(1);
            break;

        case 1:
            if (node1->get_balance() == 1)
            {
                rotateLL(node);
            }
            else
            {
                rotateLR(node);
            }
            grow = false;
            break;
    }
}

template<typename T>
void AVLTree<T>::insert_rebalanced_right(AVLNode* &node, bool& grow)
{
    AVLNode* node1 = node->right();

    switch (node->get_balance())
    {
        case 1:
            node->set_balance(0);
            grow = false;
            break;

        case 0:
            node->set_balance(-1);
            break;

        case -1:
            if(node1->get_balance() == -1)
            {
                rotateRR(node);
            }
            else
            {
                rotateRL(node);
            }
            grow = false;
            break;
    }
}


/*******************************************************************************
*   Removing Methods
*******************************************************************************/
template<typename T>
void AVLTree<T>::remove(const T& val)
{
    bool decrease = false;
    remove_branch(BinaryTree<T, AVLnode_t>::root_, val, decrease);
}

template<typename T>
void AVLTree<T>::remove_branch(AVLNode* &node, const T& val, bool& decrease)
{
    if (node == nullptr) return;
    if (val < node->get_data())
    {
        remove_branch(node->left(), val, decrease);
        if(decrease)
        {
            remove_rebalanced_left(node, decrease);
        }
    }
    else if (val > node->get_data())
    {
        remove_branch(node->right(), val, decrease);
        if(decrease)
        {
            remove_rebalanced_right(node, decrease);
        }
    }
    else
    {
        AVLNode* removed = node;
        if (node->left() == nullptr)
        {
            node = node->right();
            decrease = true;
        }
        else if(node->right() == nullptr)
        {
            node = node->left();
            decrease = true;
        }
        else
        {
            replace(removed, node->left(), decrease);
            if(decrease)
            {
                remove_rebalanced_left(node, decrease);
            }
        }
        delete removed;
    }
}

template<typename T>
void AVLTree<T>::remove_rebalanced_left(AVLNode* &node, bool& decrease)
{
    AVLNode* node1 = node->right();

    switch (node->get_balance())
    {
        case -1:
            if(node1->get_balance() > 0)
            {
                rotateRL(node);
            }
            else
            {
                if(node1->get_balance() == 0)
                {
                    decrease = false;
                }
                rotateRR(node);
            }
            break;

        case 0:
            node->set_balance(-1);
            decrease = false;
            break;

        case 1:
            node->set_balance(0);
            break;
    }
}

template<typename T>
void AVLTree<T>::remove_rebalanced_right(AVLNode* &node, bool& decrease)
{
    AVLNode* node1 = node->left();

    switch (node->get_balance())
    {
        case 1:
            if (node1->get_balance() < 0)
                rotateLR(node);
            else
            {
                if (node1->get_balance() == 0)
                    decrease = false;
                rotateLL(node);
            }
            break;

        case 0:
            node->set_balance(1);
            decrease = false;
            break;

        case -1:
            node->set_balance(0);
            break;
    }
}

template<typename T>
void AVLTree<T>::replace(AVLNode* &removed, AVLNode* &replacer, bool& decrease)
{
    if (replacer->right() != nullptr)
    {
        replace(removed, replacer->right(), decrease);
        if(decrease)
        {
            remove_rebalanced_right(replacer, decrease);
        }
    }
    else
    {
        removed->get_data() = replacer->get_data();
        removed = replacer;
        replacer = replacer->left();
        decrease = true;
    }
}


} //namespace AyEDA
