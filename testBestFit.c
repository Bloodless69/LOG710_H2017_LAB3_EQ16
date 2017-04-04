#include "manageMemoryPart2.c"
#include <assert.h>

/////////////////////////////////////////////////////
void testAlloueAllMemory() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(bestFitStrategy, 500);

	assert(root->value->size == 500);
	assert(root->value->offset == 0);
	assert(root->value->data != NULL);
}

void testAlloueMemoryWithLeftOver() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(bestFitStrategy, 100);

	assert(root->value->size == 100);
	assert(root->value->offset == 0);
	assert(root->value->data != NULL);

	struct node *emptyNode = root->next;
	assert(emptyNode->value->size == 400);
	assert(emptyNode->value->offset == 100);
	assert(emptyNode->value->data == NULL);
}

void testAlloueMemoryGotNext() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(bestFitStrategy, 100);
	struct bloc *nextBloc = allocateMemory(bestFitStrategy, 100);
	freeMemory(bloc);
	struct bloc *newNextBloc = allocateMemory(bestFitStrategy, 50);

	assert(root->value->size == 50);
	assert(root->value->offset == 0);
	assert(root->value->data != NULL);

	node *afterRoot = root->next;

	assert(afterRoot->value->size == 50);
	assert(afterRoot->value->offset == 50);
	assert(afterRoot->value->data == NULL);

	node *afterNext = afterRoot->next;

	assert(afterNext->value->size == 100);
	assert(afterNext->value->offset == 100);
	assert(afterNext->value->data != NULL);

	node *lastNode = afterNext->next;

	assert(lastNode->value->size == 300);
	assert(lastNode->value->offset == 200);
	assert(lastNode->value->data == NULL);
}

void testNotEnoughMemory() {
	initMemory(500);
	assert(allocateMemory(bestFitStrategy, 600) == NULL);
}
/////////////////////////////////////////////////////

void main() {
	testAlloueAllMemory();
	testAlloueMemoryWithLeftOver();
	testAlloueMemoryGotNext();
	testNotEnoughMemory();
}