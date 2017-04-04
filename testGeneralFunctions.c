#include "main.c"
#include <assert.h>

/////////////////////////////////////////////////////
void testInitMemory() {
	initMemory(500);
	assert(root->value->size == 500);
	assert(root->value->offset == 0);
	assert(root->value->data == NULL);
}
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
void testBlocDoesntExist() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(500);
	assert(freeMemory(NULL) == false);
}

void testFreeOnlyBloc() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(500);
	freeMemory(bloc);

	assert(root->value->size == 500);
	assert(root->value->offset == 0);
	assert(root->value->data == NULL);
}

void testFreeMemoryWithEmptyRightBloc1() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(100);
	struct bloc *nextBloc = allocateMemory(100);
	freeMemory(nextBloc);

	assert(root->value->size == 100);
	assert(root->value->offset == 0);
	assert(root->value->data != NULL);

	struct node *nextNode = root->next;

	assert(nextNode->value->size == 400);
	assert(nextNode->value->offset == 100);
	assert(nextNode->value->data == NULL);
}

void testFreeMemoryWithEmptyRightBloc2() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(100);
	struct bloc *nextBloc = allocateMemory(100);
	struct bloc *thirdBloc = allocateMemory(100);
	struct bloc *forthBloc = allocateMemory(100);
	freeMemory(thirdBloc);
	freeMemory(nextBloc);

	assert(root->value->size == 100);
	assert(root->value->offset == 0);
	assert(root->value->data != NULL);

	struct node *nextNode = root->next;

	assert(nextNode->value->size == 200);
	assert(nextNode->value->offset == 100);
	assert(nextNode->value->data == NULL);

	struct node *thirdNode = nextNode->next;

	assert(thirdNode->value->size == 100);
	assert(thirdNode->value->offset == 300);
	assert(thirdNode->value->data != NULL);

	struct node *emptyNode = thirdNode->next;

	assert(emptyNode->value->size == 100);
	assert(emptyNode->value->offset == 400);
	assert(emptyNode->value->data == NULL);
}

void testFreeMemoryWithEmptyRightBloc3() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(100);
	freeMemory(bloc);

	assert(root->value->size == 500);
	assert(root->value->offset == 0);
	assert(root->value->data == NULL);
}

void testFreeMemoryWithEmptyRightBloc4() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(100);
	struct bloc *secondBloc = allocateMemory(100);
	struct bloc *thirdBloc = allocateMemory(100);
	freeMemory(secondBloc);
	freeMemory(bloc);

	assert(root->value->size == 200);
	assert(root->value->offset == 0);
	assert(root->value->data == NULL);

	struct node *nextNode = root->next;

	assert(nextNode->value->size == 100);
	assert(nextNode->value->offset == 200);
	assert(nextNode->value->data != NULL);

	struct node *emptyNode = nextNode->next;

	assert(emptyNode->value->size == 200);
	assert(emptyNode->value->offset == 300);
	assert(emptyNode->value->data == NULL);
}

void testFreeMemoryWithEmptyLeftBloc1() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(100);
	struct bloc *secondBloc = allocateMemory(100);
	struct bloc *thirdBloc = allocateMemory(100);
	freeMemory(bloc);
	freeMemory(secondBloc);

	assert(root->value->size == 200);
	assert(root->value->offset == 0);
	assert(root->value->data == NULL);

	struct node *nextNode = root->next;

	assert(nextNode->value->size == 100);
	assert(nextNode->value->offset == 200);
	assert(nextNode->value->data != NULL);

	struct node *emptyNode = nextNode->next;

	assert(emptyNode->value->size == 200);
	assert(emptyNode->value->offset == 300);
	assert(emptyNode->value->data == NULL);
}

void testFreeMemoryWithEmptyLeftBloc2() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(100);
	struct bloc *secondBloc = allocateMemory(400);
	freeMemory(bloc);
	freeMemory(secondBloc);

	assert(root->value->size == 500);
	assert(root->value->offset == 0);
	assert(root->value->data == NULL);
}

void testFreeMemoryWithEmptyLeftBloc3() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(100);
	struct bloc *secondBloc = allocateMemory(100);
	struct bloc *thirdBloc = allocateMemory(100);
	struct bloc *forthBloc = allocateMemory(100);
	freeMemory(secondBloc);
	freeMemory(thirdBloc);

	assert(root->value->size == 100);
	assert(root->value->offset == 0);
	assert(root->value->data != NULL);

	struct node *secondNode = root->next;

	assert(secondNode->value->size == 200);
	assert(secondNode->value->offset == 100);
	assert(secondNode->value->data == NULL);

	struct node *thirdNode = secondNode->next;

	assert(thirdNode->value->size == 100);
	assert(thirdNode->value->offset == 300);
	assert(thirdNode->value->data != NULL);

	struct node *emptyNode = thirdNode->next;

	assert(emptyNode->value->size == 100);
	assert(emptyNode->value->offset == 400);
	assert(emptyNode->value->data == NULL);
}

void testFreeMemoryWithEmptyRightLeft1() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(100);
	struct bloc *secondBloc = allocateMemory(100);
	struct bloc *thirdBloc = allocateMemory(300);
	freeMemory(bloc);
	freeMemory(thirdBloc);
	freeMemory(secondBloc);

	assert(root->value->size == 500);
	assert(root->value->offset == 0);
	assert(root->value->data == NULL);
}

void testFreeMemoryWithEmptyRightLeft2() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(100);
	struct bloc *secondBloc = allocateMemory(100);
	struct bloc *thirdBloc = allocateMemory(100);
	struct bloc *forthBloc = allocateMemory(100);
	struct bloc *fifthBloc = allocateMemory(100);
	freeMemory(secondBloc);
	freeMemory(forthBloc);
	freeMemory(thirdBloc);

	assert(root->value->size == 100);
	assert(root->value->offset == 0);
	assert(root->value->data != NULL);

	struct node* secondNode = root->next;

	assert(secondNode->value->size == 300);
	assert(secondNode->value->offset == 100);
	assert(secondNode->value->data == NULL);

	struct node* thirdNode = secondNode->next;

	assert(thirdNode->value->size == 100);
	assert(thirdNode->value->offset == 400);
	assert(thirdNode->value->data != NULL);
}
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
void testNbFreeBloc() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(100);
	struct bloc *secondBloc = allocateMemory(100);
	assert(nbFreeBlocs() == 1);
}

void testNbBlocAllocated() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(100);
	struct bloc *secondBloc = allocateMemory(100);
	assert(nbAllocatedBlocs() == 2);
}

void testAvailableFreeMemory() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(100);
	struct bloc *secondBloc = allocateMemory(100);
	assert(availableMemory() == 300);
}

void testSizeOfLargestBloc() {
	initMemory(500);
	struct bloc *firstBloc = allocateMemory(100);
	allocateMemory(111);
	struct bloc *secondBloc = allocateMemory(90);
	allocateMemory(120);
	struct bloc *thirdBloc = allocateMemory(3);

	freeMemory(firstBloc);
	freeMemory(secondBloc);
	freeMemory(thirdBloc);
	assert(sizeOfLargestBlocOfFreeMemory() == 100);
}

void testNbFreeBlocSmallerThanX() {
	initMemory(500);
	struct bloc *firstBloc = allocateMemory(100);
	allocateMemory(111);
	struct bloc *secondBloc = allocateMemory(97);
	allocateMemory(120);
	struct bloc *thirdBloc = allocateMemory(3);

	freeMemory(firstBloc);
	freeMemory(secondBloc);
	freeMemory(thirdBloc);

	assert(nbFreeBlocsSmallerThan(98) == 2);
}

void testIsByteAllocatedTRUE() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(100);
	struct bloc *secondBloc = allocateMemory(100);
	assert(byteIsAllocated(125) == true);
}

void testIsByteAllocatedFALSE() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(100);
	struct bloc *secondBloc = allocateMemory(100);
	assert(byteIsAllocated(212) == false);
}
/////////////////////////////////////////////////////

void main() {
	testInitMemory();
	testBlocDoesntExist();
	testFreeOnlyBloc();
	testFreeMemoryWithEmptyRightBloc1();
	testFreeMemoryWithEmptyRightBloc2();
	testFreeMemoryWithEmptyRightBloc3();
	testFreeMemoryWithEmptyRightBloc4();

	testFreeMemoryWithEmptyLeftBloc1();
	testFreeMemoryWithEmptyLeftBloc2();
	testFreeMemoryWithEmptyLeftBloc3();

	testFreeMemoryWithEmptyRightLeft1();
	testFreeMemoryWithEmptyRightLeft2();

	testNbFreeBloc();
	testNbBlocAllocated();
	testAvailableFreeMemory();
	testSizeOfLargestBloc();
	testNbFreeBlocSmallerThanX();
	testIsByteAllocatedTRUE();
	testIsByteAllocatedFALSE();
}