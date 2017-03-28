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
} node;

struct node *root = NULL;

bool hasNext(node* node) {
	return (node->next != NULL);
}

bool hasData(node* node) {
	return (node->value->data != NULL);
}

bool exist(node* node) {
	return node != NULL;
}

// initmem()
void initMemory(int memSize) {
	struct bloc *bloc = malloc(sizeof(bloc));
	bloc->size = memSize;
	bloc->offset = 0;
	bloc->data = NULL;

	root = malloc(sizeof(node));
	root->value = bloc;
	root->previous = NULL;
	root->next = NULL;
}

// allouemem()
bloc* allocateMemory(int blocSize) {
    struct node *currentNode = root;
    struct bloc *currentBloc = currentNode->value;

    struct bloc *allocationBloc = NULL;
    while(allocationBloc == NULL) {
        if(currentBloc->data == NULL && currentBloc->size >= blocSize) {
            // Creating our bloc of memory to allocate
            allocationBloc = malloc(sizeof(bloc));
            allocationBloc->size = blocSize;
            allocationBloc->offset = currentNode->value->offset;
            allocationBloc->data = malloc(blocSize);

            // If we are allocating a bloc of memory smaller than the current,
            // we need to create a new empty node
            if(currentBloc->size > blocSize) {
                struct node *emptyNode = malloc(sizeof(node));
                emptyNode->previous = currentNode;
                if(currentNode->next != NULL) {
                    emptyNode->next = currentNode->next;
                    node *rightNode = currentNode->next; // NOT SURE, PLEASE CONFIRM
                    rightNode->previous = emptyNode; 	 // NOT SURE, PLEASE CONFIRM
                    //currentNode->next->previous = emptyNode;
                }

                // We need to fill the empty node with an empty bloc of memory
                struct bloc *emptyBloc = malloc(sizeof(bloc));
                emptyBloc->size = currentBloc->size - blocSize;
                emptyBloc->offset = currentBloc->offset + blocSize;
                emptyBloc->data = NULL;

                emptyNode->value = emptyBloc;
                currentNode->next = emptyNode;
                currentNode->value = allocationBloc;
            } else {
                currentNode->value = allocationBloc;
            }
        } else {
            if(currentNode->next == NULL) {
            	printf("No more memory available\n");
                break;
            }
            printf("allouemem - Going to next node\n");
            currentNode = currentNode->next;
        }
    }
    return allocationBloc;
}

// liberemem()
void freeMemory(node* node, bloc* bloc) {
	if (node->value == bloc)
	{
		// If both previous and next node has data,
		// we only want to empty the node
		if ((exist(node->previous) && !hasData(node->previous)) && (exist(node->next) && !hasData(node->next))) {
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
		freeMemory(node->next, bloc);
	}
}

// nbloclibres()
int nbFreeBlocs() {
	int nbEmptyBloc = 0;
	node *currentNode = root;
	while(currentNode != NULL) {
		bloc *currentBloc = currentNode->value;
		if (currentBloc->data == NULL)
			nbEmptyBloc++;
		currentNode = currentNode->next;
	}
	return nbEmptyBloc;
}

// nblocalloues()
int nbAllocatedBlocs() {
	int nbAllocatedBloc = 0;
	node *currentNode = root;
	while(currentNode != NULL) {
		bloc *currentBloc = currentNode->value;
		if (currentBloc->data != NULL)
			nbAllocatedBloc++;
		currentNode = currentNode->next;
	}
	return nbAllocatedBloc;
}

// memlibre()
int availableMemory() {
	int memAvailable = 0;
	node *currentNode = root;
	while(currentNode != NULL) {
		bloc *currentBloc = currentNode->value;
		if (currentBloc->data == NULL)
			memAvailable += currentBloc->size;
		currentNode = currentNode->next;
	}
	return memAvailable;
}

// mem_pgrand_libre()
int sizeOfLargestBlocOfFreeMemory() {
	// Here we are assuming that the root always has a bloc of memory
	node *currentNode = root;
	int largestSize = currentNode->value->size;
	while(currentNode != NULL) {
		bloc *currentBloc = currentNode->value;
		if (currentBloc->size > largestSize)
			largestSize = currentBloc->size;
		currentNode = currentNode->next;
	}
	return largestSize;
}

// mem_small_free(maxTaillePetit)
int nbFreeBlocsSmallerThan(int blocSize) {
	int nbSmallerFreeBlocs = 0;
	node *currentNode = root;
	while(currentNode != NULL) {
		bloc *currentBloc = currentNode->value;
		if (currentBloc->size < blocSize)
			nbSmallerFreeBlocs++;
		currentNode = currentNode->next;
	}
	return nbSmallerFreeBlocs;
}

// mem_est_alloue(pOctet)
bool byteIsAllocated(int byte) {
	bool byteAllocated = false;
	int currentSize = 0;
	node *currentNode = root;
	while(currentNode != NULL) {
		bloc *currentBloc = currentNode->value;
		currentSize += currentBloc->size;
		if (currentSize > byte) {
			byteAllocated = true;
		}
		else {
			currentNode = currentNode->next;
		}
	}
	return byteAllocated;
}

void printContent() {
	int nodeIndex = 0;
	node *currentNode = root;
	while(currentNode != NULL) {
		printf("Current node : %d\n", nodeIndex);
		printf("Size : %d\n", currentNode->value->size);
		printf("Offset : %d\n", currentNode->value->offset);
		printf("HasData : %d\n", currentNode->value->data != NULL);
		currentNode = currentNode->next;
		nodeIndex++;
	}
}

void main() {
	initMemory(500);
	bloc *allocationBloc = allocateMemory(200);
	printContent();
	printf("MAIN END\n");
	//bloc *allocationBloc1 = allocateMemory(50);
	//allocationBloc = allocateMemory(50);
	//printf("%d\n", allocationBloc->size);
	//allocationBloc = allocateMemory(200);
	//printf("%d\n", allocationBloc->size);
	//allocationBloc = allocateMemory(200);
	//printf("%d\n", allocationBloc->size);
	//printf("%d\n", allocationBloc->size);
	//freeMemory(root, allocationBloc);
	//freeMemory(root, allocationBloc1);
}

