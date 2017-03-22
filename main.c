#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef enum { false, true } bool;

typedef struct bloc {
	int size;
	int offset;
	void *data;
} bloc;

typedef struct node {
	struct bloc *value;
	struct node *previous;
	struct node *next;
	bool isRoot;
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

bool hasNext(node* node) {
	return (node->next != NULL);
}

bool hasData(node* node) {
	return (node->value->data != NULL);
}

bloc* alloumem(int blocSize) {
    node *currentNode = root;

    bloc *newBlock = NULL;
    while(newBlock == NULL) {
        if(currentNode->value->data == NULL && currentNode->value->size >= blocSize) {
            node *newNode = malloc(sizeof(node));
            if(currentNode->previous)
                currentNode->previous->next = newNode;

            newNode->previous = currentNode->previous;

            newBlock = malloc(sizeof(bloc));
            newBlock->size = blocSize;
            newBlock->offset = currentNode->offset;
            newBlock -> malloc(blocSize);
            newNode->value = newBlock;

            if(currentNode->value->size > blocSize) {
                node *newEmptyNode = malloc(sizeof(node));
                newEmptyNode->previous = newNode;
                if(currentNode->next)
                    newEmptyNode->next = currentNode->next;


                struct bloc *newEmptyBloc;
                newEmptyBloc->size = currentNode->block->size - blocSize;
                newEmptyBloc->offset = currentNode->value->offset + blocSize;
                newEmptyBloc->data = NULL;

                newEmptyNode->value = newEmptyBloc;
                newNode->next = newEmptyNode;
            } else {
                if(currentNode->next)
                    newNode->next = currentNode->next;
            }
        } else {
            if(currentNode->next == NULL)
                break;
            currentNode = currentNode->next;
        }
    }
    return newBlock;
}

void liberemem(node* node, bloc* bloc) {
	
	if (node->value == bloc)
	{
		// If both previous and next node has data,
		// we only want to empty the node
		if (hasData(node->previous) && hasData(node->next)) {
			node->value->data = NULL;
		}

		// If both previous and next node has no data,
		// we want to merge current node with the both nodes
		if (!(hasData(node->previous) && hasData(node->next))) {
			node* leftNode = node->previous->previous;
			node* rightNode = node->next->next;

			bloc* previousBloc = node->previous->value;
			bloc* nextBloc = node->next->value;
			bloc currentBloc = node->value;

			bloc* newBloc;
			newBloc->size = previousBloc->size + currentBloc->size + nextBloc->size;
			newBloc->offset = node->previous->previous->value->offset;
			newBloc->data = NULL;

			node* newNode;
			newNode->value = newBloc;
			newNode->previous = leftNode;
			newNode->next = rightNode;

			leftNode->next = newNode;
			rightNode->previous = newNode;
		}

		// If previous node only has no data,
		// we want to merge current node with the previous one
		if (!hasData(node->previous) && hasData(node->next)) {

		}

		// If next node only has no data,
		// we want to merge current node with the next one
		if (hasData(node->previous) && !hasData(node->next)) {

		}
		}
	} else {
		liberemem(node->next, bloc);
	}
}

void main() {
	initmem(500);
}

