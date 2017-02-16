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
        Node* deleteNode(Node* root, Interval interval);
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



Node* IntervalTree::deleteNode(Node* root, Interval interval){
    if (root == NULL)
        return root;
    if (interval.low < root->intr.low)
        root->left = deleteNode(root->left, interval);
    else if (interval.low > root->intr.low)
        root->right = deleteNode(root->right, interval);
    else{
        Node *p = root->parent;
        int maxleft = (root->left)->data;
        int maxright = (root->right)->data;
        if (root->left == NULL){
            Node *temp = root->right;
            p->data = max(p->data, temp->data);
            return temp;
        }
        else if (root->right == NULL){
            Node *temp = root->left;
            p->data = max(p->data, temp->data);
            return temp;
        }
        p->data = max(p->data, max((root->left)->data, (root->right)->data));
        Node *temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        root->intr = temp->intr;
        root->data =  max(maxleft, maxright);
        root->right = deleteNode(root->right, temp->intr);
    }
    return root;
}



int main(){
}
