#include <stdio.h>
#include <stdlib.h>

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

struct node *root = NULL;

void initmem(int memSize) {
	struct bloc *bloc = malloc(sizeof(bloc));
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
    struct node *currentNode = root;

    struct bloc *newBlock = NULL;
    while(newBlock == NULL) {
        if(currentNode->value->data == NULL && currentNode->value->size >= blocSize) {
        	printf("BAM\n");
            struct node *newNode = malloc(sizeof(node));
            if(currentNode->previous != NULL) {
                currentNode->previous->next = newNode;
            	newNode->previous = currentNode->previous;
            }

            newBlock = malloc(sizeof(bloc));
            newBlock->size = blocSize;
            newBlock->offset = currentNode->value->offset;
            newBlock->data = malloc(blocSize);
            newNode->value = newBlock;

            printf("BOM\n");

            if(currentNode->value->size > blocSize) {
                struct node *newEmptyNode = malloc(sizeof(node));
                newEmptyNode->previous = newNode;
                if(currentNode->next != NULL) {
                	printf("IM IN\n");
                    newEmptyNode->next = currentNode->next;
                    currentNode->next->previous = newEmptyNode;
                }

                printf("BIM\n");

                struct bloc *newEmptyBloc;
                newEmptyBloc->size = currentNode->value->size - blocSize;
                newEmptyBloc->offset = currentNode->value->offset + blocSize;
                newEmptyBloc->data = NULL;

                newEmptyNode->value = newEmptyBloc;
                newNode->next = newEmptyNode;

                printf("BUM\n");
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
		// If both previous and next node has no data,
		// we want to merge current node with the both nodes
		} else if (!(hasData(node->previous)) && !(hasData(node->next))) {
			struct node* leftNode = node->previous->previous;
			struct node* rightNode = node->next->next;

			struct bloc* previousBloc = node->previous->value;
			struct bloc* nextBloc = node->next->value;
			struct bloc* currentBloc = node->value;

			struct bloc* newBloc;
			newBloc->size = previousBloc->size + currentBloc->size + nextBloc->size;
			newBloc->offset = previousBloc->offset;
			newBloc->data = NULL;

			struct node* newNode;
			newNode->value = newBloc;
			newNode->previous = leftNode;
			newNode->next = rightNode;

			if (leftNode != NULL) {
				leftNode->next = newNode;
			}

			if (rightNode != NULL) {
				rightNode->previous = newNode;
			}
			
		// If previous node only has no data,
		// we want to merge current node with the previous one
		} else if (!hasData(node->previous)) {
			struct node* leftNode = node->previous->previous;
			struct node* rightNode = node->next;

			struct bloc* previousBloc = node->previous->value;
			struct bloc* currentBloc = node->value;

			struct bloc* newBloc;
			newBloc->size = previousBloc->size + currentBloc->size;
			newBloc->offset = previousBloc->offset;
			newBloc->data = NULL;

			struct node* newNode;
			newNode->value = newBloc;
			newNode->previous = leftNode;
			newNode->next = rightNode;

			leftNode->next = newNode;
			
			if (leftNode != NULL) {
				leftNode->next = newNode;
			}
			rightNode->previous = newNode;
		// If next node only has no data,
		// we want to merge current node with the next one
		} else {
			struct node* leftNode = node->previous;
			struct node* rightNode = node->next->next;

			struct bloc* currentBloc = node->value;
			struct bloc* nextBloc = node->next->value;

			struct bloc* newBloc;
			newBloc->size = currentBloc->size + nextBloc->size;
			newBloc->offset = leftNode->value->offset;
			newBloc->data = NULL;

			struct node* newNode;
			newNode->value = newBloc;
			newNode->previous = leftNode;
			newNode->next = rightNode;

			leftNode->next = newNode;
			if (rightNode != NULL) {
				rightNode->previous = newNode;
			}
		}
	} else {
		liberemem(node->next, bloc);
	}
}

void main() {
	initmem(500);
	printf("Patate\n");
	alloumem(250);
	printf("Bob\n");
}

