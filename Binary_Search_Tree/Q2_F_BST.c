//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
//이진 탐색 트리의 개별 노드를 나타내는 구조체
//왼쪽 자식은 부모 노드보다 작은 값을, 오른쪽 자식은 부모 노드보다 큰 값을 가지는 특성
typedef struct _bstnode{
	int item;
	struct _bstnode *left; //
	struct _bstnode *right;
} BSTNode;   // BSTNode의 정의를 변경하면 안 됩니다.

//스택 내의 개별 요소를 나타내는 구조체로, 스택은 후입선출 방식으로 작동하는 데이터 구조.
typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // StackNode의 정의를 변경하면 안 됩니다.

//스택의 상태를 관리하기 위한 구조체이다.
//스택은 데이터의 삽입과 삭제가 한 쪽 끝에서만 일어나는 선형 구조로, 주로 임시 데이터 저장.
typedef struct _stack
{
	StackNode *top;
}Stack; // 스택의 정의를 변경하면 안 됩니다.

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void inOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the in-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting in-order traversal of the binary search tree is: ");
			inOrderTraversal(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void inOrderTraversal(BSTNode *root)
{
	// 중위 순회 문제.
	// 스택 초기화
    Stack stack;
    stack.top = NULL;
    BSTNode *current = root;

    // 현재 노드가 NULL이 아니거나 스택이 비어있지 않는 동안 반복합니다.
    while (current != NULL || !isEmpty(&stack)) {

        //왼쪽으로 쭉 이동하면서 스택에 값을 넣는다.
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }

        //스택에서 가장 위에 있는 값 팝하고 
        current = pop(&stack);

        // 바로 출력하기
        printf("%d ", current->item);

        //그 전에서 왼쪽만 돌았기 때문에 팝한거에 오른쪽 노드로 기준점을 바꿔보자.
        current = current->right;
    }
	 
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));// 동적할당

		if (*node != NULL) {// NULL이 아니야? 
			(*node)->item = value; //현재 벨류 값 넣어주고
			(*node)->left = NULL; // 왼, 오 초기화 - 새 노드가 아직 자식 노드를 가지지 않았음
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)// value가 현재 노드의 아이템 보다 작아?
		{
			insertBSTNode(&((*node)->left), value);//왼쪽 서브트리에 삽입
		}
		else if (value >(*node)->item)// value가 현재 노드의 아이템 보다 커?
		{
			insertBSTNode(&((*node)->right), value);// 오른쪽 서브트리에 삽입
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////
//스택 데이터 구조에 새로운 요소를 추가하는 함수
void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode)); //동적 메모리 할당

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)//스택이 비어있어?
	{
		stack->top = temp; //  temp가 새로운 top이됌
		temp->next = NULL; // temp가 스택의 유일한 노드
	}
	else
	{
		temp->next = stack->top; // 업데이트
		stack->top = temp;
	}
}

BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
