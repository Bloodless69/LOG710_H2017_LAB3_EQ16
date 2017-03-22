#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct bloc {
	int size;
	int offset;
	void *data;
} bloc;

typedef struct node {
	struct bloc *value;
	struct node *previous;
	struct node *next;
} node;

node *root = NULL;

void initmem(int memSize) {
	struct bloc *bloc;
	bloc->size = memSize;
	bloc->offset = 0;
	bloc->data = NULL;

	root = malloc(sizeof(node));
	root->value = bloc;
	root->previous = NULL;
	root->next = NULL;
}

boolean hasNext(node* node) {
	return (node->next != NULL);
}

void liberemem(bloc* bloc) {
	node* currentNode = root;

	// If we are trying to free the root, 
	// we need to check the next node only
	if (currentNode->value == bloc)
	{
		// Checking next node
		if (hasNext(currentNode)) {
			// Root offset
			currentOffset = currentNode->value->offset;
			// Next node offset
			nextOffset = currentNode->next->value->offset;
		} else {
			currentNode->value->data = NULL;
		}
	// We are tying to free another node in the linked list	
	} else {
		while (hasNext(currentNode)) {
			// Switching to next node
			currentNode = currentNode->next;
		}
	}
}

void liberemem2(bloc* bloc) {
	node* currentNode = root;

	while (hasNext(currentNode)) {
			// Switching to next node
			currentNode = currentNode->next;


	}
}

void main() {
	initmem(500);
}

