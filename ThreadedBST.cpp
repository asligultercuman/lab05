#include "ThreadedBST.h"

///-----------------------------------------------
/// Erases all nodes in the tree
/// 
void ThreadedBST::eraseTreeNodes(BSTNode* node) {
	BSTNode *curr = this->min();

	while (curr != NULL){
		BSTNode *n = this->next(curr);
		delete curr;
		curr = n;
	} // end-while
	
} //end-eraseTreeNodes

///-----------------------------------------------
/// Adds a given key to the BST
/// 
void ThreadedBST::add(int key) {//elif
    // create new node
    BSTNode* newNode = new BSTNode(key);

    // if tree is empty
    if (root == nullptr) {
        root = newNode;
        return;}

    // finding correct node
    BSTNode* current = root;
    BSTNode* parent = nullptr;

    while (current != nullptr) {
        parent = current;

        if (key < current->key) {
            if (current->leftLinkType == THREAD)
                break; 
            current = current->left;
        } else {
            if (current->rightLinkType == THREAD)
                break; 
            current = current->right;
        }}

   
    if (key < parent->key) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->left = newNode;
        parent->leftLinkType = CHILD; 
    } else {
        newNode->right = parent->right;
        newNode->left = parent;
        parent->right = newNode;
        parent->rightLinkType = CHILD; }
}

// end-add

///-----------------------------------------------
/// Removes a given key from the BST (if it exists)
/// 
void ThreadedBST::remove(int key) {
	// Fill this in
} // end-remove

///-----------------------------------------------
/// Searches a given key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode *ThreadedBST::find(int key) {
	// Fill this in
	return NULL;
} // end-find

///-----------------------------------------------
/// Returns the minimum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::min() {//elif
    if (root == nullptr) {
        return nullptr; }

    BSTNode* current = root;
    while (current->left != nullptr && current->leftLinkType != THREAD) {
        current = current->left;}

    return current; 
}


///-----------------------------------------------
/// Returns the maximum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::max() {//özge
	if (root == NULL) return NULL;
	
	BSTNode* p = root;
	while (p->rightLinkType == CHILD) p = p->right;
	
	return p;
} // end-max
///-----------------------------------------------
/// Given a valid pointer to a node in ThreadedBST,
/// returns a pointer to the node that contains the inorder predecessor
/// If the inorder predecessor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::previous(BSTNode* node) {
	// Fill this in
	return NULL;
} // end-previous

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::next(BSTNode* node) {//özge
	if (node->rightLinkType == THREAD)
		return node->right;

	node = node->right;
	while (node->leftLinkType == CHILD)
		node = node->left;
	return node;
} // end-next
