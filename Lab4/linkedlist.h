#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER

//ref https://github.com/skorks/c-linked-list/blob/master/linkedlist.h for structure
//ref https://stackoverflow.com/questions/26439354/error-incomplete-type-is-not-allowed
typedef struct Node {
	int key;
	char firstName[64];
	char lastName[64];
	char major[64];
	float GPA;

	struct Node* next;
} Node; 

typedef struct LinkedList{
	Node* head;
} LinkedList;


struct Node* CreateNode(int key, char *firstName, char *lastName, char *major, float GPA);
struct LinkedList* CreateList();
struct Node* LookUpByIndex(struct Node** start, int index);
struct Node* LookUpByKey(struct Node** start, int key);
int GetKeyByIndex(struct Node** start, int index);
int GetIndexByKey(struct Node** start, int key);
int GetListLength(struct Node** start);
void ReverseString(char* str, int len);
int IntToStr(int x, char str[], int d);
int ftoa(float n, char* res, int afterpoint);
int ToCsv(struct Node* node, char *string);
int ToString(struct Node* node, char *string);
void PrintNode(struct Node* node);
void PrintList(struct Node** start);
void PrintSearch(struct Node** start, char* searchRequest);
void FreeList(struct Node** start);
int InsertFront(struct Node** start, struct Node* nodeToInsert);
int InsertEnd(struct Node** start, struct Node* nodeToInsert);
int InsertMiddle(struct Node** start, int index, struct Node* nodeToInsert);
int ToComparisonString(struct Node* node, char* string);
int InsertByGPA(struct Node** start, struct Node* nodeToInsert);
int DeleteFront(struct Node** start);
int DeleteEnd(struct Node** start);
int DeleteMiddle(struct Node** start, int index);



#endif