#include "stdio.h"
#include "stdlib.h"

#define DEBUG 0

typedef struct tnode {
	char ch;
	struct tnode *next;
	struct tnode *child;
	int isWord;
}tnode;

tnode *createTrieNode(char ch)
{
	tnode *tn = (tnode *)malloc(sizeof(tnode));
	tn->ch = ch;
	tn->isWord = 0;
	tn->next = NULL;
	tn->child = NULL;
	return tn;
}

tnode *insertChar(tnode *temp, char ch)
{
	tnode *curr = temp->child;
	if(curr == NULL)
		return createTrieNode(ch);
	if(ch < curr->ch) {
		tnode *tn = createTrieNode(ch);
		tn->next = curr;
		return tn;
	}
    tnode *prev = NULL;
	while(curr != NULL && curr->ch < ch) {
		prev = curr;
		curr = curr->next;
	}
	if(curr == NULL) {
		curr = createTrieNode(ch);
		prev->next = curr;
		return temp->child;
	}
	if(curr->ch == ch)
		return temp->child;
	tnode *tn = createTrieNode(ch);
	tn->next = curr;
	prev->next = tn;
	return temp->child;
}

tnode *insert(tnode *root, char *key)
{
    if(key[0] == '\0')
        return root;
	tnode *temp = root;
    temp->child = insertChar(temp, key[0]);
    temp = temp->child;
    while(temp->ch != key[0])
        temp = temp->next;
    temp = insert(temp, key+1);
    if(key[1] == '\0')
        temp->isWord = 1;
    return root;
}

int search(tnode *root, char *key)
{
    char ch = key[0];
    tnode *temp = root->child;
    if(ch == '\0' || temp == NULL)
        return 0;
	while(temp != NULL && temp->ch < ch)
		temp = temp->next;
	if(temp == NULL)
		return 0;
	if(temp->ch == ch) {
		    if(key[1] == '\0' && temp->isWord == 1) {
                return 1;
		    }
		    if(key[1] == '\0' && temp->isWord == 0) {
                return 0;
		    }
		    else {
                return search(temp, key+1);
		    }
	}
    return 0;
}

tnode *deleteChar(tnode *root, char key)
{
    tnode *temp = root;
    if(temp->ch == key)
        root = root->next;
    else {
        tnode *prev = NULL;
        while(temp->ch != key){
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
    }
    free(temp);
    temp = NULL;
    return root;
}

tnode *delete(tnode *root, char *key)
{
    char ch = key[0];
    tnode *temp = root->child;
    if(ch == '\0' || temp == NULL)
        return root;
	while(temp != NULL && temp->ch < ch)
		temp = temp->next;
	if(temp == NULL)
		return root;
	if(temp->ch == ch) {
        if(key[1] == '\0')
            temp->isWord = 0;
        else
            temp = delete(temp, key+1);

        if(temp->isWord == 0 && temp->child == NULL)
            root->child=deleteChar(root->child, key[0]);
        return root;
	}
    return root;
}



int main()
{
	int i, size;

	tnode *root = createTrieNode('\0');

	char keys[][10] = {"the", "a", "there", "answer", "any", "by", "bye", "their", "abuse", "abusal", "dogmatic", "dog", "an"};

	char output[][32] = {"not present in trie", "present in trie"};

	size = sizeof(keys)/sizeof(keys[0]);

	if(DEBUG)
		printf("number of words = %d\n", size);

	for (i = 0; i < size; i++)
		root = insert(root, keys[i]);

	for (i = 0; i < size; i++)
		printf("%10s is %s\n", keys[i],   output[search(root, keys[i])] );


	printf("%10s is %s\n", "these", output[search(root, "these")] );
	printf("%10s is %s\n", "thaw", output[search(root, "thaw")] );

	printf("\n");



    //root = delete(root, "dog");
    root = delete(root, "dogmatic");
    root = delete(root, "an");
    root = delete(root, "abuse");
    root = delete(root, "abuse");
    root = delete(root, "abusal");
    root = delete(root, "there");
    root = delete(root, "their");
    root = delete(root, "the");
    root = delete(root, "by");
    root = delete(root, "bye");
    root = delete(root, "any");
    root = delete(root, "answer");
    //root = delete(root, "a");

    for (i = 0; i < size; i++)
		printf("%10s is %s\n", keys[i],   output[search(root, keys[i])] );

	return 0;
}

