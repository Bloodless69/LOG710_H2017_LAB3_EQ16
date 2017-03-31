#include "manageMemoryPart2.c"
#include <assert.h>

/////////////////////////////////////////////////////
void testAlloueAllMemory() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(firstFitWithLoopingStrategy, 500);

	assert(root->value->size == 500);
	assert(root->value->offset == 0);
	assert(root->value->data != NULL);
}

void testAlloueMemoryWithLeftOver() {
	initMemory(500);
	struct bloc *bloc = allocateMemory(firstFitWithLoopingStrategy, 100);

	assert(root->value->size == 100);
	assert(root->value->offset == 0);
	assert(root->value->data != NULL);

	struct node *emptyNode = root->next;
	assert(emptyNode->value->size == 400);
	assert(emptyNode->value->offset == 100);
	assert(emptyNode->value->data == NULL);
}

void testAlloueMemoryGotNext() {
	// to fix. to lazy to do it
	initMemory(500);
	struct bloc *bloc = allocateMemory(firstFitWithLoopingStrategy, 100);
	struct bloc *nextBloc = allocateMemory(firstFitWithLoopingStrategy, 100);
	freeMemory(bloc);
	struct bloc *newNextBloc = allocateMemory(firstFitWithLoopingStrategy, 50);

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
	assert(allocateMemory(firstFitWithLoopingStrategy, 600) == NULL);
}
/////////////////////////////////////////////////////

void main() {
	testAlloueAllMemory();
	testAlloueMemoryWithLeftOver();
	testAlloueMemoryGotNext();
	testNotEnoughMemory();
}