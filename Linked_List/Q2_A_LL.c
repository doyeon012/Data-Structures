//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item; //노드가 저장할 데이터를 나타낸다.
	struct _listnode *next; // 다음 ListNode를 가리킨다.
	//이는 링크드리스트의 연결 구조를 만들기 위해 사용되며
	//다음 노드로의 연결을 의미한다.
} ListNode;			//ListNode의 정의를 변경하면 안 됩니다.

typedef struct _linkedlist
{
	int size; // 리스트에 현재 저장된 노드의 개수를 나타낸다.
	ListNode *head; // 리스트의 첫 번째 노드, 즉 헤드 노드를 가리킨다.
	// 이 포인터를 통해 리스트의 모든 노드에 접근할 수 있다.
} LinkedList;			// LinkedList의 정의를 변경하면 안 됩니다.


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2) {
	
	ListNode *Node1 = ll1 -> head;
	ListNode *Node2 = ll2 -> head;
	int idx =1;
	int count = 0;

	// ll1과 ll2중에 더 작은 값이 기준이 되어서 절반으로 나눈다.
	// ll1이 더 커 그러면 더 작은 ll2의 size 값이 기준이 됌.
	if(ll1->size >= ll2->size)
	{
		count = ll2->size;
		
	}

	else if(ll1->size <= ll2->size)
	{
		count = ll1->size;
	}

	// count 사라질때까지 돌아
	while(count){
		
		// idx가 홀수 일때
		if(idx%2==1)
		{

			//ll1에 위치에 Node2의 아이템을 넣고, ll2에서 0번째 인덱스 지워
			insertNode(ll1, idx, Node2->item);
			removeNode(ll2, 0);
			Node2 = ll2 -> head;
			count --; // 카운트 -1하고 왜? while 문 끝나는 기준이 되니깐
		}
		idx++;

	}

}

///////////////////////////////////////////////////////////////////////////////////

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


ListNode *findNode(LinkedList *ll, int index){

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

	// 빈 목록이거나 첫 번째 노드를 삽입하는 경우 헤드 포인터를 업데이트해야 합니다.
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode)); // 새 노드를 동적 할당한다.
		ll->head->item = value;
		ll->head->next = cur; // 새 노드의  다음 노드를 이전의 헤드로 설정한다.
		ll->size++;
		return 0;
	}

	// 목표 위치 앞의 노드와 위치의 노드를 찾습니다.
	// 새 노드를 생성하고 링크를 다시 연결합니다.
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value; // 새 노드의 값 설정
		pre->next->next = cur; // 새 노드의 다음 노드를 cur로 설정한다.
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	
	// 제거할 수 있는 가장 높은 인덱스는 크기 1입니다.
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// 첫 번째 노드를 제거하는 경우 헤드 포인터를 업데이트해야 합니다.
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;	
	}

	// 목표 위치 전후의 노드를 찾습니다.
  	// 대상 노드를 해제하고 링크를 다시 연결합니다.
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

