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


class IntervalTree{
    private :
        Node *root;

	public :
        IntervalTree(Interval interval){
		root = newNode(interval);
		root->parent = NULL;
		}

        Node* getRoot(){return root;}
        Node* newNode(Interval interval);
        void insert(Node* root, Interval interval);
        Node* deleteNode(Node* root, Interval interval);
        Node* searchInterval(Node* root, Interval interval);
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
        return NULL;
    if (interval.low < root->intr.low)
        root->left = deleteNode(root->left, interval);
    else if (interval.low > root->intr.low)
        root->right = deleteNode(root->right, interval);
    else if(interval.low == root->intr.low && interval.high == root->intr.high){
			if(root->left==NULL){
				Node *temp=root->right;
				delete root;
				return temp;
			}
			else if(root->right==NULL){
				Node *temp=root->left;
				delete root;
				return temp;
			}
            Node *temp = root->right;
            while(temp->left!=NULL)
            {
                temp = temp->left;
            }

            root->intr = temp->intr;
            root->data = temp->data;
            root->right = deleteNode(root->right,temp->intr);
		}
		return root;
   }


Node* IntervalTree::searchInterval(Node *root, Interval interval){
        if (root == NULL){
            return NULL;
        }
        if (root->intr.low <= interval.high && root->intr.high >= interval.low){
            return root;
        }
        if (root->left != NULL && (root->left)->data >= interval.low){
            return searchInterval(root->left, interval);
        }
        else{
            return searchInterval(root->right, interval);
        }
    }


void inorder(Node *x) {
	if (!x) return;
    inorder(x->left);
    cout<<"{" << x->intr.low<< " , "<<x->intr.high<<"} \n";
    inorder(x->right);
}


int main(){
    Interval intervals[] ={{15, 20}, {10, 30}, {17, 19},{5, 20}, {12, 15}, {30, 40}};
    int size = sizeof(intervals) / sizeof(intervals[0]);

    IntervalTree* intervalTree = new IntervalTree(intervals[0]);

    for(int i=1; i<size; i++){
        intervalTree->insert(intervalTree->getRoot(), intervals[i]);
    }

    cout<<"After insertion, the inorder traversal of tree is -- \n";
    inorder(intervalTree->getRoot());


    Interval test1 = {14, 16};
    cout<<"\nSearching for interval {"<<test1.low <<" , "<< test1.high <<"} ---\n";

    Node *result1 = intervalTree->searchInterval(intervalTree->getRoot(), test1);
    if (result1 == NULL)
        cout << "No matching interval found\n";
    else
        cout << "Overlaps with {" << result1->intr.low << "," << result1->intr.high << "} \n";


    Interval test2 = {21, 23};
    cout<<"\nSearching for interval  {"<<test2.low <<" , "<< test2.high <<"}  ---\n";

    Node *result2 = intervalTree->searchInterval(intervalTree->getRoot(), test2);
    if (result2 == NULL)
        cout << "No matching interval found! \n";
    else
        cout << "Overlaps with {" << result2->intr.low << "," << result2->intr.high << "} \n";



    cout<<"\nAfter deleting node {17, 19} -- \n";

    intervalTree->deleteNode(intervalTree->getRoot(), {17, 19});
    inorder(intervalTree->getRoot());


    cout<<"\nAfter deleting node {12, 15} -- \n";

    intervalTree->deleteNode(intervalTree->getRoot(), {12, 15});
    inorder(intervalTree->getRoot());


    return 0;
}
