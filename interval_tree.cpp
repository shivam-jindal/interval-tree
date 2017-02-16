#include <bits/stdc++.h>
using namespace std;

struct Node {
	int data;
	int highInterval, lowInterval;
	struct Node *left, *right, *parent;
};

void inorder(Node *x) {
	if (!x) return;
    inorder(x->left);
    cout<<"{" << x->lowInterval<< " , "<<x->highInterval<<"}";
    inorder(x->right);
}


class IntervalTree{
    private :
        Node *root;

	public :
        IntervalTree(int lowIntr, int highIntr){
		root = newNode(lowIntr, highIntr);
		root->parent = NULL;
		}

        Node* newNode(int lowIntr, int highIntr);
        void insert(Node* root, int lowIntr, int highIntr);

};


Node* IntervalTree::newNode(int lowIntr, int highIntr){
    Node *node = new Node();
    node->lowInterval = lowIntr;
    node->highInterval = highIntr;
    node->data = highIntr;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void IntervalTree::insert(Node* root, int lowIntr, int highIntr){
    Node *newNode =  IntervalTree::newNode(lowIntr, highIntr);
    if (!this->root){
        this->root = newNode;
        this->root->parent = NULL;
    }else{
        root->data = max(root->data, newNode->data);
        if (newNode->lowInterval < root->lowInterval){
            if (!root->left){
                root->left = newNode;
                newNode->parent = root;
            }else{
                insert(root->left, newNode->lowInterval, newNode->highInterval);
            }
        }else{
            if(!root->right){
                root->right = newNode;
                newNode->parent = root;
            }else{
                insert(root->right, newNode->lowInterval, newNode->highInterval);
            }
        }
    }
}




int main(){
}
