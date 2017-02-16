#include <bits/stdc++.h>
using namespace std;

struct Interval{
	int low, high;
};

struct Node {
	int data;
	Interval intr;
	struct Node *left, *right, *parent;
};


void inorder(Node *x) {
	if (!x) return;
    inorder(x->left);
    cout<<"{" << x->intr.low<< " , "<<x->intr.high<<"}";
    inorder(x->right);
}


class IntervalTree{
    private :
        Node *root;

	public :
        IntervalTree(Interval interval){
		root = newNode(interval);
		root->parent = NULL;
		}

        Node* newNode(Interval interval);
        void insert(Node* root, Interval interval);
};


Node* IntervalTree::newNode(Interval interval){
    Node *node = new Node();
    node->intr = interval;
    node->data = interval.high;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void IntervalTree::insert(Node* root, Interval interval){
    Node *newNode =  IntervalTree::newNode(interval);
    if (!this->root){
        this->root = newNode;
        this->root->parent = NULL;
    }else{
        root->data = max(root->data, newNode->data);
        if (newNode->intr.low < root->intr.low ){
            if (!root->left){
                root->left = newNode;
                newNode->parent = root;
            }else{
                insert(root->left, newNode->intr);
            }
        }else{
            if(!root->right){
                root->right = newNode;
                newNode->parent = root;
            }else{
                insert(root->right, newNode->intr);
            }
        }
    }
}




int main(){
}
