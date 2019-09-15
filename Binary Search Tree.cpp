
/* This code contains following Functions
	All of them are not called by main as some of them contain use of STL
	1. Inorder  2. Preorder  3. Postorder  4. LevelOrder  5. ReverseLevelOrder 
	6. Nodes at a distance d from root  7. Mirror Tree of given Tree  8. All paths from root to leaf
	9. Common Ancestors of two numbers  10. Inorder Successor  11. Height of the tree e
	*/
	
#include <bits/stdc++.h>

using namespace std;

int inor[100];
int k=0;

typedef struct element{
	int num;
	element *l;
	element *r;
}element;

element *createnode(int a,element *root)
{
	element *t;
	t=(element *)malloc(sizeof(element));
	t->num=a;
	t->l=NULL;
	t->r=NULL;
	return t;
}

void insert(int a,element *root){
	if(a>root->num){
		if(root->r==NULL){
			root->r=createnode(a,root->r);
			return ;
		}
		else {
			insert(a,root->r);
		}
	}
	else{
		if(root->l==NULL){
			root->l=createnode(a,root->l);
			return ;
		}
		else {
			insert(a,root->l);
		}
	}
}

//This Function works  but needs to use STL deque
void ReverseLevelorder(element *root)
{
	element *it;
	deque <element *> dq;
	dq.push_back(root);
	deque <element *> :: iterator t;
	for(t=dq.begin();t!=dq.end();t++){
		it=*t;
		if(it->l!=NULL){
			dq.push_back(it->l);	
		}
		if(it->r!=NULL){
			dq.push_back(it->r);	
		}
	}
	while(!dq.empty()){
		it=dq.back();
		cout << it->num << " ";
		dq.pop_back();
	}
	return ;
}

void preorder(element *root)
{
	if(root!=NULL){
		cout << root->num << " ";
		preorder(root->l);
		preorder(root->r);
	}	
	else {
		return ;
	}
}

void inorder(element *root)
{
	if(root!=NULL){
		inorder(root->l);
		cout << root->num << " ";
		inor[k]=root->num;
		k++;
		inorder(root->r);
	}
	else {
		return ;
	}
}

void postorder(element *root)
{
	if(root!=NULL){
		postorder(root->l);
		postorder(root->r);
		cout << root->num << " ";
	}
	else {
		return ;
	}
}

// This function shows the numbers at distance d  from root node
void nodeatd(element *root,int d)
{
	if(d==0){
		cout << root->num << " ";
		return ;
	}
	if(root->l!=NULL){
		nodeatd(root->l,d-1);	
	}
	if(root->r!=NULL){
		nodeatd(root->r,d-1);	
	}
}

// This Function uses STL hence may be used using IDEONE
void levelorder(element *root)
{
	queue <element *> q;
	q.push(root);
	element *u;
	while(!q.empty()){
		if(root->l!=NULL){
			q.push(root->l);
		}
		if(root->r!=NULL){
			q.push(root->r);
		}
		u=q.front();
		cout << u->num << " ";
		q.pop();
		root=q.front();
	}
	return ;
}

void allpaths(element *root,int i,int *path)
{
	int k;
	if(root->l!=NULL){
		path[i]=root->num;
		allpaths(root->l,i+1,path);
	}
	if(root->r!=NULL){
		path[i]=root->num;
		allpaths(root->r,i+1,path);
	}
	if(root->l==NULL && root->r==NULL){
		path[i]=root->num;
		i++;
		for(k=0;k<i;k++){
			cout << path[k] << " ";
		}
		cout << endl;
		return ;
	}
}

void swapnodes(element *a,element *b)
{
	element *t;
	t=a;
	a=b;
	b=t;
}

int ancestor(element *root,int a,int b,int CA)
{
	element *t;
	if(a>CA && b>CA){
		t=root->r;
		ancestor(root->r,a,b,t->num);
	}
	else if(a<CA && b<CA){
		t=root->l;
		ancestor(root->l,a,b,t->num);
	}
	else {
		return CA;    
	}
}

void inarray(element *root)
{
	if(root!=NULL){
		inarray(root->l);
		inor[k]=root->num;
		k++;
		inarray(root->r);
	}
	else {
		return ;
	}
}

void successor(element *root)
{
	int i,key;
	cout << "Enter the key\n";
	cin >> key;
	inarray(root);
	for(i=0;i<k;i++){
		if(inor[i]==key){
			if(i==k-1){
				cout << "The inorder successor of " << key << " is NULL\n";
				break;
			}
			else {
				cout << "The inorder successor of " << key << " is " << inor[i+1] << endl;
				break;
			}
		}
		else{
			continue;
		}
	}	
}

int height(element *root)
{
	int h=0;
	int lh=0,rh=0;
	if(root->r==NULL && root->l==NULL){
        return h;
    }
	else{
		if(root->l!=NULL){
			lh+=height(root->l);
		}
		if(root->r!=NULL){
			rh+=height(root->r);
		}
		h=max(lh,rh);
		return h;
	}
}

void swapnode(element *a)
{
	element *t;
	t=a->l;
	a->l=a->r;
	a->r=t;
}


int main()
{
	int n,i,j,a,b,CA,q=0;
	element *root;
	root=NULL;
	cout << "Enter the number of elements in the tree\n";
	cin >> n;
	cout << "Enter the elements in the tree such that each number should be distinct\n";
	int A[n];
	for(i=0;i<n;i++){
		cin >> A[i];
	}
	root=createnode(A[0],root);
	for(i=1;i<n;i++){
		insert(A[i],root);
	}
	
	while(q!=8){
		cout << "\nWhat you want to do with the tree\n";
		cout << "\n1.Preorder Traversal\n2.Inorder Traversal\n3.Postorder Traversal\n4.Level-order Traversal\n";
		cout << "5.Print all paths from root to leaf\n6.Find Common Ancestor\n7.Find Inorder Successor\n8.Quit\n";	
		cin >> q;
		
		if(q==1){
			cout << "\nPreorder Traversal is done in the following way :- ";
			preorder(root);
			cout << "\n";
		}
		if(q==2){
			cout << "\nInorder Traversal is done in the following way :- ";
			inorder(root);
			cout << "\n";
		}
		if(q==3){
			cout << "\nPostorder Traversal is done in the following way :- ";
			postorder(root);
			cout << "\n";
		}
		if(q==4){
			cout << "\nLevelorder Traversal is done in the following way :- " << root->num << " ";
			levelorder(root);
			cout << "\n";
		}	
		if(q==5){ 
			cout << "\nFollowing are all the paths from root to leaf nodes\n";
			int path[n];
			allpaths(root,0,path);
			cout << endl;
		}
		if(q==6){
			cout <<"\nEnter the two numbers whose common ancestor you want to find\n";
			cin >> a >> b;
			CA=root->num;
			cout << "\nThe ancestor of " << a << " and " << b << " is " << ancestor(root,a,b,CA) << endl;
			cout << "\n";
		}
	}
	return 0;
}

/*


*/
