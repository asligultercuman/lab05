// 152120221095 Özge Erarslan
// 152120221123 Elif Fatma Cebeci
// 152120231104 Aslıgül Tercuman
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
void ThreadedBST::remove(int key) {// Asligul
    BSTNode* current = root;
    BSTNode* parent = nullptr;

    // Find the node to be deleted and its parent
    while (current != nullptr && current->key != key) {
        parent = current;
        if (key < current->key) {
            if (current->leftLinkType == CHILD) {
                current = current->left;
            }
            else
                return;  // Key not found
        }
        else {
            if (current->rightLinkType == CHILD) {
                current = current->right;
            }
            else
                return;  // Key not found
        }
    }

    // If the node is not found
    if (current == nullptr) {
        return;
    }

    // Case 1: Node has two children
    if (current->leftLinkType == CHILD && current->rightLinkType == CHILD) {
        // Find the in-order successor and its parent
        BSTNode* succParent = current;
        BSTNode* successor = current->right;
        while (successor->leftLinkType == CHILD) {
            succParent = successor;
            successor = successor->left;
        }

        // Copy the successor's key to the current node
        current->key = successor->key;

        // Adjust pointers to remove the successor node
        current = successor;
        parent = succParent;
    }

    // Case 2 & 3: Node with one or zero children
    BSTNode* child;
    if (current->leftLinkType == CHILD) {
        child = current->left;
    }
    else if (current->rightLinkType == CHILD) {
        child = current->right;
    }
    else {
        child = nullptr;  // Leaf node
    }

    // Adjust the parent's pointers to bypass the deleted node
    if (parent == nullptr) {  // Deleting the root node
        root = child;
    }
    else if (current == parent->left) {
        parent->left = child;
        if (child && current->leftLinkType == THREAD) {
            parent->leftLinkType = THREAD;
            parent->left = current->left;  // Maintain thread to predecessor
        }
    }
    else {
        parent->right = child;
        if (child && current->rightLinkType == THREAD) {
            parent->rightLinkType = THREAD;
            parent->right = current->right;  // Maintain thread to successor
        }
    }

    // Clean up
    delete current;
}//end remove

///-----------------------------------------------
/// Searches a given key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode *ThreadedBST::find(int key) {
	BSTNode* current = root;//baslangic
    while (current != NULL) {
        if (key == current->key)
            return current;

        if (key > current->key && current->rightLinkType == CHILD)
            current = current->right;
        else if (key < current->key && current->leftLinkType == CHILD)
            current = current->left;
        else
            break;
    }
    return NULL;//key not found
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
BSTNode* ThreadedBST::previous(BSTNode* node) {//Asligul
    if (node->leftLinkType == THREAD)
        return node->left;

    node = node->left;//If leftLinkType is CHILD, move to the left subtree
    while (node->rightLinkType == CHILD)//find the max node
        node = node->right;

    return node;
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
