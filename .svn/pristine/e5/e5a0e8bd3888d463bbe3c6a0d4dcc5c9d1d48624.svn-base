
// #include "avltree.h"
/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    Node* origRC = t->right;
    t->right = origRC->left;
    origRC->left = t;
    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    origRC->height = max(heightOrNeg1(origRC->left),heightOrNeg1(origRC->right)) + 1;
    t = origRC;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    Node* origLC = t->left;
    t->left = origLC->right;
    origLC->right = t;
    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    origLC->height = max(heightOrNeg1(origLC->left),heightOrNeg1(origLC->right)) + 1;
    t = origLC;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (balance == -2) {
        int lBalance = heightOrNeg1(subtree->left->right) -
            heightOrNeg1(subtree->left->left);
        if (lBalance == -1 )
            rotateRight(subtree);
        else
            rotateLeftRight(subtree);
    } else if (balance == 2) {
        int rBalance = heightOrNeg1(subtree->right->right) -
            heightOrNeg1(subtree->right->left);
        if (rBalance == 1)
            rotateLeft(subtree);
        else
            rotateRightLeft(subtree);
    } else {
        subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
    }
    // cout << subtree->key << " " << heightOrNeg1(subtree) << endl;
    // cout << "L " << heightOrNeg1(subtree->left) << endl;
    // cout << "R " << heightOrNeg1(subtree->right) << endl;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (!subtree)
        subtree = new Node(key, value);
    else if (key < subtree->key)
        insert(subtree->left, key, value);
    else
        insert(subtree->right, key, value);
    rebalance(subtree);
    // this->print();
    // cout << endl;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;
    // std::cout << subtree->key <<  endl;
    if (key < subtree->key) {
        remove(subtree->left, key);
        // std::cout << "blaneing!!!" <<  endl;
        rebalance(subtree);
        // this->print();
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        // std::cout << "blaneing!!!" <<  endl;
        rebalance(subtree);
        // this->print();
    } else {
        // std::cout << "removing" <<  endl;
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node* t = subtree->left;
            Node* tParent = subtree;
            while (t->right) {
                tParent = t;
                t = t->right;
            }
            swap(t, subtree);
            remove(tParent, key);
        } else {
            /* one-child remove */
            Node* t = subtree;
            if (!subtree->left)
                subtree = subtree->right;
            else
                subtree = subtree->left;
            delete t;
        }
        // this->print();
        // cout << endl;
    }

}
