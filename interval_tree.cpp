#include <bits/stdc++.h>
using namespace std;

//struct for interval
struct Interval{
	int low, high;
};

//struct for Node of interval trees
struct Node {
	int data;                               //data shows the value stored in tree(additional information)
	Interval intr;                          //intr is the Interval stored in node
	struct Node *left, *right, *parent;     //pointers to left, right child and parent
};


//class declaration for Interval Tree
class IntervalTree{
    private :
        //A pointer to root stored as a private member
        Node *root;

	public :
	    //constructor
        IntervalTree(Interval interval){
		root = newNode(interval);
		root->parent = NULL;
		}

        //a function to return pointer to root of tree
        Node* getRoot(){return root;}

        //function to initialize a new node
        Node* newNode(Interval interval);

        //function to insert an interval in tree
        void insert(Node* root, Interval interval);

        //function to delete a node(Interval) from tree
        Node* deleteNode(Node* root, Interval interval);

        //function to search for an interval in tree
        Node* searchInterval(Node* root, Interval interval);
};


/*
This method initializes a new node by setting intr value to given interval and all pointers to null
*/
Node* IntervalTree::newNode(Interval interval){
    Node *node = new Node();
    node->intr = interval;
    node->data = interval.high;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/*
This method is used insert an interval in tree.
Pointer to root and interval are passed as arguments
*/
void IntervalTree::insert(Node* root, Interval interval){
    //Initialize the new node
    Node *newNode =  IntervalTree::newNode(interval);

    //If tree is empty then this node is the root
    if (!this->root){
        this->root = newNode;
        this->root->parent = NULL;
    }else{
        root->data = max(root->data, newNode->data);

        //If low interval of new node is less
        //then low interval of root then the new node will go to left of root
        if (newNode->intr.low < root->intr.low ){
            if (!root->left){
                root->left = newNode;
                newNode->parent = root;
            }else{
                insert(root->left, newNode->intr);
            }
        }
        //else new node will go to right of root
        else{
            if(!root->right){
                root->right = newNode;
                newNode->parent = root;
            }else{
                insert(root->right, newNode->intr);
            }
        }
    }
}


/*
This method is used delete an interval/Node from tree.
Pointer to root and interval are passed as arguments
*/
Node* IntervalTree::deleteNode(Node* root, Interval interval){
    //if root is null then element can't be deleted
    if (root == NULL)
        return NULL;

    //if low interval is less than low intr of root then that element should be in left of root
    if (interval.low < root->intr.low)
        root->left = deleteNode(root->left, interval);

    //if low interval is greater than low intr of root then that element should be in right of root
    else if (interval.low > root->intr.low)
        root->right = deleteNode(root->right, interval);

    //if the given interval is equal to the interval of root then we need to delete this element
    else if(interval.low == root->intr.low && interval.high == root->intr.high){

            //if node doesn't have left child then return the right child as root and delete the root
			if(root->left==NULL){
				Node *temp=root->right;
				delete root;
				return temp;
			}

            //if node doesn't have right child then return the left child as root and delete the root
			else if(root->right==NULL){
				Node *temp=root->left;
				delete root;
				return temp;
			}

			//node have both left and right child then temp will be inorder successor of node
            Node *temp = root->right;
            while(temp->left!=NULL)
            {
                temp = temp->left;
            }

            //replace root's values with that of temp's
            root->intr = temp->intr;
            root->data = temp->data;
            root->right = deleteNode(root->right,temp->intr);
		}
		//return pointer to root of the final tree(tree after deletion)
		return root;
   }


/*
This method is used to search an interval in tree.
Pointer to root and interval are passed as arguments
It also considers overlapping intervals
And if more than one interval overlaps then it returns the first one
*/
Node* IntervalTree::searchInterval(Node *root, Interval interval){
        //if root is null return null
        if (root == NULL){
            return NULL;
        }

        //if root itself overlaps the given interval then return pointer to root
        if (root->intr.low <= interval.high && root->intr.high >= interval.low){
            return root;
        }

        //if data of left child of root is greater than low interval then recursively search in left subtree
        if (root->left != NULL && (root->left)->data >= interval.low){
            return searchInterval(root->left, interval);
        }
        //else recursively search in right subtree
        else{
            return searchInterval(root->right, interval);
        }
    }


/*
This function shows the in-order traversal of the tree
pointer to root is passed as argument
*/
void inorder(Node *root) {
	if (!root) return;
    inorder(root->left);
    cout<<"{" << root->intr.low<< " , "<<root->intr.high<<"} , data = "<< root->data<<endl;
    inorder(root->right);
}


int main(){

    //insert given intervals in tree
    Interval intervals[] ={{15, 20}, {10, 30}, {17, 19},{5, 20}, {12, 15}, {30, 40}};
    int size = sizeof(intervals) / sizeof(intervals[0]);

    IntervalTree* intervalTree = new IntervalTree(intervals[0]);

    for(int i=1; i<size; i++){
        intervalTree->insert(intervalTree->getRoot(), intervals[i]);
    }

    cout<<"After insertion, the inorder traversal of tree is -- \n";
    inorder(intervalTree->getRoot());


    // test if given interval overlaps with some element of tree
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


    //delete an element from tree
    cout<<"\nAfter deleting node {17, 19} -- \n";

    intervalTree->deleteNode(intervalTree->getRoot(), {17, 19});
    inorder(intervalTree->getRoot());


    cout<<"\nAfter deleting node {12, 15} -- \n";

    intervalTree->deleteNode(intervalTree->getRoot(), {12, 15});
    inorder(intervalTree->getRoot());


    return 0;
}
