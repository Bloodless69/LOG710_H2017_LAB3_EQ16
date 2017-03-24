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

bool exist(node* node) {
	return node != NULL;
}

bloc* alloumem(int blocSize) {
    struct node *currentNode = root;
    struct bloc *newBlock = NULL;
    while(newBlock == NULL) {
        if(currentNode->value->data == NULL && currentNode->value->size >= blocSize) {
            newBlock = malloc(sizeof(bloc));
            newBlock->size = blocSize;
            newBlock->offset = currentNode->value->offset;
            newBlock->data = malloc(blocSize);

            if(currentNode->value->size > blocSize) {
            	printf("LALAL\n");
                struct node *newEmptyNode = malloc(sizeof(node));
                newEmptyNode->previous = currentNode;
                if(currentNode->next != NULL) {
                	printf("TATATATA\n");
                    newEmptyNode->next = currentNode->next;
                    currentNode->next->previous = newEmptyNode;
                }
	printf("LAL11AL\n");
                struct bloc *newEmptyBloc = malloc(sizeof(bloc));
                newEmptyBloc->size = currentNode->value->size - blocSize;
                newEmptyBloc->offset = currentNode->value->offset + blocSize;
                newEmptyBloc->data = NULL;
	printf("LAL121231211AL\n");
                newEmptyNode->value = newEmptyBloc;
                currentNode->next = newEmptyNode;
                currentNode->value = newBlock;
                	printf("1231231231AL\n");
            } else {
                currentNode->value = newBlock;
            }
        } else {
            if(currentNode->next == NULL) {
            	printf("NO MORE MEMORY\n");
                break;
            }
            printf("change!\n");
            currentNode = currentNode->next;
        }
    }
    return newBlock;
}

void liberemem(node* node, bloc* bloc) {
	printf("YOOOO");
	if (node->value == bloc)
	{
		// If both previous and next node has data,
		// we only want to empty the node
		if ((exist(node->previous) && !hasData(node->previous)) && (exist(node->next) && !hasData(node->next))) {
			printf("YOOO!");
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
		} else if (exist(node->previous) && !hasData(node->previous)) {
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
		} else if(exist(node->next) && !hasData(node->next)){
				printf("YOOOO111");
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
		} else {
			node->value->data = NULL;
		}
	} else {
		liberemem(node->next, bloc);
	}
}

void printContent() {
	printf("hey\n");
	node *currentNode = root;
	while(currentNode != NULL) {
		//printf("IS IN");
		printf("size: %d\n", currentNode->value->size);
		printf("offset: %d\n", currentNode->value->offset);
		printf("haveData: %d\n", currentNode->value->data != NULL);

		if(currentNode->next != NULL && currentNode->next->previous != NULL)
			printf("GOOD NEXT/PREVIOUS: %p %p \n", currentNode->next, currentNode->next->previous);
		currentNode = currentNode->next;
	}
}

void main() {
	initmem(500);
	printf("Patate\n");
	bloc *block = alloumem(200);
//	printf("%d\n", block->size);
	//bloc *block1 = alloumem(50);
	//printContent();
	 /*block = alloumem(50);
	 printf("%d\n", block->size);
	 block = alloumem(200);
	 printf("%d\n", block->size);
	 block = alloumem(200);
	 printf("%d\n", block->size);
	printf("%d\n", block->size);*/

//	liberemem(root, block);
//	liberemem(root, block1);
	printf("\n\n\n");
printContent();

	printf("Bob\n");
}

