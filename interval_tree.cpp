#include <bits/stdc++.h>
using namespace std;

#define RED		1
#define BLACK	2

struct node {
	int key;
	int highInterval, lowInterval;
	struct node *left, *right, *p;
	int color;
};

typedef struct node *NODEPTR;
struct node NIL;
NODEPTR NILPTR = &NIL;

int main(){
}
