// #include "btree.h"
/**
 * @file btree.cpp
 * Implementation of a B-tree class which can be used as a generic dictionary
 * (insert-only). Designed to take advantage of caching to be faster than
 * standard balanced binary search trees.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

using std::vector;

/**
 * Finds the value associated with a given key.
 * @param key The key to look up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const K& key) const
{
    return (root == nullptr) ? V() : find(root, key);
}

/**
 * Private recursive version of the find function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param key The key we are looking up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const BTreeNode* subroot, const K& key) const
{
    size_t idx = insertion_idx(subroot->elements, key);
    // std::cout << "finding:" << idx << '\n';
    try {
        if (subroot->elements.at(idx) == key)
            return subroot->elements[idx].value;
    } catch (std::out_of_range e) {}

    if (subroot->is_leaf)
        return V();
    else
        return find(subroot->children[idx], key);
}

/**
 * Inserts a key and value into the BTree. If the key is already in the
 * tree do nothing.
 * @param key The key to insert.
 * @param value The value to insert.
 */
template <class K, class V>
void BTree<K, V>::insert(const K& key, const V& value)
{
    /* Make the root node if the tree is empty. */
    if (root == nullptr) {
        root = new BTreeNode(true, order);
    }
    insert(root, DataPair(key, value));
    /* Increase height by one by tossing up one element from the old
     * root node. */
    if (root->elements.size() >= order) {
        BTreeNode* new_root = new BTreeNode(false, order);
        new_root->children.push_back(root);
        split_child(new_root, 0);
        root = new_root;
    }

    // print(root);
    // std::cout << "\n---------------------------------------------\n";
}

/**
 * Splits a child node of a BTreeNode. Called if the child became too
 * large.
 * @param parent The parent whose child we are trying to split.
 * @param child_idx The index of the child in its parent's children
 * vector.
 */
template <class K, class V>
void BTree<K, V>::split_child(BTreeNode* parent, size_t child_idx)
{
    BTreeNode* child = parent->children[child_idx];

    auto newChildIt = parent->children.emplace(parent->children.begin() + child_idx + 1);
    *newChildIt = new BTreeNode(child->is_leaf, order);

    auto midElemIt = child->elements.begin() + (child->elements.size() - 1) / 2;
    parent->elements.insert(parent->elements.begin() + child_idx, *midElemIt);

    (*newChildIt)->elements.assign(midElemIt + 1, child->elements.end());
    auto midChildIt = child->children.begin() + child->children.size() / 2;
    (*newChildIt)->children.assign(midChildIt, child->children.end());

    child->elements.erase(midElemIt, child->elements.end());
    child->children.erase(midChildIt, child->children.end());
}

/**
 * Private recursive version of the insert function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param pair The DataPair to be inserted.
 * Note: Original solution used std::lower_bound, but making the students
 * write an equivalent seemed more instructive.
 */
template <class K, class V>
void BTree<K, V>::insert(BTreeNode* subroot, const DataPair& pair)
{
    /* There are two cases to consider.
     * If the subroot is a leaf node and the key doesn't exist in subroot, we
     * should simply insert the pair into subroot.
     * Otherwise (subroot is not a leaf and the key doesn't exist in subroot)
     * we need to figure out which child to insert into and call insert on it.
     * After this call returns we need to check if the child became too large
     * and thus needs to be split to maintain order.
     */
    // std::cout << pair.key << ',' << pair.value <<  std::endl;
    size_t idx = insertion_idx(subroot->elements, pair);

    try {
        if (subroot->elements.at(idx) == pair){
            // std::cout << "case1" <<  std::endl;
            return;
        }
    } catch (std::out_of_range e) {}

    if (subroot->is_leaf) {
        // std::cout << "case2:"<< idx << '\n';
        subroot->elements.insert(subroot->elements.begin() + idx, pair);
    } else {
        // std::cout << "case3:"<< idx << '\n';
        insert(subroot->children[idx], pair);
    }

    if (!subroot->is_leaf) {
        for (auto c : subroot->children) {
            if (c->elements.size() >= order) {
                // std::cout << "spliting" << '\n';
                split_child(subroot, idx);
            }
        }
    }
}
