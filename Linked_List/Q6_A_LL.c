//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 6 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j=insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head));  // You need to code this function
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

int moveMaxToFront(ListNode **ptrHead)
{	
	ListNode *Node1 = *ptrHead;

	ListNode *Node2 = *ptrHead;
	int max = 0;
	int idx = 0;
	int i = 0;
	ListNode *Maxnode = Node1;
	ListNode *new =  0;


	//max값의 인덱스를 찾는 용도
	while (Node1 != NULL) // Node가 NULL이라는 뜻은 끝에 까지 도달했다는 뜻
	{
		if(max < Node1->item )
		{
			max = Node1->item; //max 변수에 max값을 넣고
			idx = i; // idx에 인덱스를 저장한다.
		}
		Node1 = Node1->next; // 다음껄로 바꿔주면서 전체 탐색o
		i ++;
	}

	Node1 = *ptrHead; // 그 전에 Node1값을 계속해서 바꿔주면서 썻으니, 다시 처음부터 돌아야 하니깐 헤드값으로 업데이트
	

	//처음부터 돌면서 idx가 max에 index니깐 그전에꺼에서 멈추게끔
	for (int j = 0; j <= idx; j++)
	{	
		//max 전꺼
		if(j == idx-1)
		{
			new = Node1->next; // max 전의 next니깐 max의 Node의 값 미리 저장해놈
			Node1->next = Node1->next->next; // 현재의 next는 일반적으로 max인데 max의 위치가 맨 처음으로 이동하기 때문에 next의 next로 그다음꺼 연결o
			j++; //이거 해주면 자연스래 다음 로직으로 들어감
		}

		//max 일때
		if(j==idx)
		{
			new->next = Node2; //좀 전에 저장해놓은 new라는 값의 next를 현재 head 값인 즉 깔끔한 Node2의 값으로 연결해줌
			Maxnode = new; // ll의 head 값을 바꿔주기 위해 
			break; // 할거 다했으니 끝내.
		}
		
		Node1 = Node1->next; // max전의 값을 찾기 전까지 Node값을 next로 바꿔주면서 탐색o
	}

	*ptrHead = Maxnode;  //결국 printList에서 헤드부터 도니깐 헤드에 max의 노드를 넣어준다.
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}
