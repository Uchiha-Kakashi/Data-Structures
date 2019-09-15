#include "stdio.h"
#include "stdlib.h"

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
	int height;
}node;

void inorder(node *root)
{
	if(root != NULL) {
		inorder(root->left);
		printf("%4d", root->data);
		inorder(root->right);
	}
}

void preorder(node *root)
{
	if(root != NULL) {
		printf("%4d", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(node *root)
{
	if(root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%4d", root->data);
	}
}

void traverse(node *root)
{
	if(root != NULL) {
		inorder(root);
		printf("\n");
		preorder(root);
		printf("\n");
		postorder(root);
		printf("\n");
	}
}

node *search(node *root, int data)
{
	if(root == NULL)
		return NULL;
	if(root->data == data)
		return root;
	else if(root->data > data)
		return search(root->left, data);
	else
		return search(root->right, data);
}

node *createNode(int data)
{
	node *n = (node *)malloc(sizeof(node));
	n->data = data;
	n->left = NULL;
	n->right = NULL;
	n->height = 0;
	return n;
}

int findHeight(node *root)
{
	if(root == NULL)
		return -1;
	int hLeft = findHeight(root->left);
	int hRight = findHeight(root->right);
	return (hLeft >= hRight) ? hLeft+1 : hRight+1;
}

int getBalanceFactor(node *root)
{    if(root == NULL)        return -1;    if(root->left == NULL && root->right == NULL)        return 0;    if(root->left == NULL)        return -1*root->right->height;    if(root->right == NULL)        return root->left->height;
	return root->left->height - root->right->height;
}

node *leftRotate(node *root)
{
	node *r = root->right;
	node *rl =  r->left;

	root->right = rl;
	r->left = root;
	root->height = findHeight(root);
	r->height = findHeight(r);

	return r;
}

node *rightRotate(node *root)
{
	node *l = root->left;
	node *lr =  l->right;

	root->left = lr;
	l->right = root;
	root->height = findHeight(root);
	l->height = findHeight(l);

	return l;
}

node *insertNode(node *root, int data)
{
	if(root == NULL)
		root = createNode(data);
	else if(data < root->data)
		root->left = insertNode(root->left, data);
	else if(data > root->data)
		root->right = insertNode(root->right, data);

	root->height = findHeight(root);

	int balanceFactorRoot = getBalanceFactor(root);

	if(balanceFactorRoot == 2) {
		int balanceFactorLeft = getBalanceFactor(root->left);
		if(balanceFactorLeft == 1) {
			root = rightRotate(root);
		}
		else if(balanceFactorLeft == -1) {
			root->left = leftRotate(root->left);
			root = rightRotate(root);
		}
	}
	else if(balanceFactorRoot == -2) {
		int balanceFactorRight = getBalanceFactor(root->right);

		if(balanceFactorRight == -1) {
			root = leftRotate(root);
		}
		else if(balanceFactorRight == 1) {
			root->right = rightRotate(root->right);
			root = leftRotate(root);
		}
	}
	return root;
}

node *deleteNode(node *root, int data)
{
	if(root == NULL)
		return NULL;
	else if(data < root->data)
		root->left = deleteNode(root->left, data);
	else if(data > root->data)
		root->right = deleteNode(root->right, data);
	else {
		node *temp = NULL;
		if(root->left != NULL && root->right != NULL) {
			temp = root->right;
			while(temp->left != NULL)
				temp = temp->left;
			root->data = temp->data;
			root->right = deleteNode(root->right, temp->data);
			return root;
		}
		temp = (root->left != NULL) ? root->left : root->right;		free(root);
        root = NULL;
		if(temp == NULL)
			return root;
		else            return temp;
	}

	root->height = findHeight(root);

	int balanceFactorRoot = getBalanceFactor(root);

	if(balanceFactorRoot == 2) {
		int balanceFactorLeft = getBalanceFactor(root->left);
		if(balanceFactorLeft == 0 || balanceFactorLeft == 1) {
			root = rightRotate(root);
		}
		else if(balanceFactorLeft == -1) {
			root->left = leftRotate(root->left);
			root = rightRotate(root);
		}
	}
	else if(balanceFactorRoot == -2) {
		int balanceFactorRight = getBalanceFactor(root->right);

		if(balanceFactorRight == 0 || balanceFactorRight == -1) {
			root = leftRotate(root);
		}
		else if(balanceFactorRight == 1) {
			root->right = rightRotate(root->right);
			root = leftRotate(root);
		}
	}
	return root;
}

void main()
{
	int i, size;
	int a[] = {20, 30, 10, 15, 18, 100, 90, 90, 25, 5, 120, 80, 95};
	size = sizeof(a)/sizeof(int);
	node *root = NULL;
	for(i = 0; i < size; i++)	{
            root = insertNode(root, a[i]);
            preorder(root);
            printf("\n");
	}
	while(root != NULL)
		root = deleteNode(root, root->data);
	traverse(root);
}

