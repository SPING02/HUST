/*数据结构实验二—----基于链式存储结构线性表*/
//头文件
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
//预定义常量
#define TRUE 1  
#define FALSE 0  
#define OK 1  
#define ERROR 0  
#define INFEASIBLE -1  
#define OVERFLOW -2
//类型表达式
typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100  
#define LISTINCREMENT  10  
typedef int ElemType;
typedef struct LNode {  //单链表（链式结构）结点的定义  
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;
/*---------------------------------------------------*/

status InitList(LinkList& L);                               //线性表的创建
status DestroyList(LinkList& L);                            //销毁线性表
status ClearList(LinkList& L);                              //清空线性表
status ListEmpty(LinkList L);                               //线性表判空
int ListLength(LinkList L);                                 //线性表长度
status GetElem(LinkList L, int i, ElemType& e);             //获取元素
status LocateElem(LinkList L, ElemType e);                  //查找元素
status PriorElem(LinkList L, ElemType e, ElemType& pre);    //获取前驱元素
status NextElem(LinkList L, ElemType e, ElemType& next);    //获取后继元素
status ListInsert(LinkList& L, int i, ElemType e);          //插入元素
status ListDelete(LinkList& L, int i, ElemType& e);         //删除元素
status ListTraverse(LinkList L);                            //遍历线性表
status SaveList(LinkList L, char FileName[]);               //储存线性表
status LoadList(LinkList& L, char FileName[]);              //读取线性表

/*main*/
int main(void) {
    LinkList L; 
    L = NULL;
    int op = 1;
    int p, i, j, ch, e, n, f, v;
    ElemType pre, next;
    FILE* fp = NULL;
    char name[30];          //add
    char ListName[50];      //delete 
    char FileName[50];    //filename 
    /*MENU*/
    while (op) {
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("          1.  InitList       7.  LocateElem\n");
        printf("          2.  DestroyList    8.  PriorElem\n");
        printf("          3.  ClearList      9.  NextElem \n");
        printf("          4.  ListEmpty      10. ListInsert\n");
        printf("          5.  ListLength     11. ListDelete\n");
        printf("          6.  GetElem        12. ListTranverse\n");
        printf("          13. Linear table read and write files\n");
        printf("          Press 0 to exit\n");
        printf("-------------------------------------------------\n");
        printf("    Please Select[0~13]:\n");  
        scanf("%d", &op);
        switch (op) {
        case 1:
            //InitList
            j = InitList(L);
            if (j == OK) {
                printf("The Linear Table Create Successfully!\n");
            }
            else if (j == ERROR) {
                printf("The Linear Table Create Failed!\n");
            }
            else if (j == INFEASIBLE) {
                printf("The Linear Table already exist!\n");
            }
            getchar();
            break;
        case 2:
            //Destroy List
            j = DestroyList(L);
            if (j == OK) {
                printf("The Linear Table Destroy Successfully!\n");
            }
            else if (j == ERROR) {
                printf("The Linear Table Destroy Failed!\n");
            }
            else if (j == INFEASIBLE) {
                printf("The Linear Table does not exist!\n");
            }
            getchar();
            break;
        case 3:
            //ClearList。
            if (ClearList(L) == OK)
                printf("The Linear Table Was emptied successfully!\n");
            else
                printf("The Linear Table does NOT exist!\n");
            getchar();
            break;
        case 4:
            //ListEmpty
            j = ListEmpty(L);
            if (j == TRUE)
                printf("Linear table is empty!\n");
            else if (j == FALSE)
                printf("Linear table is not empty!\n");
            else if (j == INFEASIBLE)
                printf("The Linear Table does NOT exist!\n");
            getchar();
            break;
        case 5:
            //ListLength
            j = ListLength(L);
            if (j >= 0)
                printf("The linear table length is %d !\n", j);
            else
                printf("The linear table does not exist, the table length cannot be calculated!\n");
            getchar();
            break;
        case 6:
            //GetElem
            printf("Please enter the location to find the element:\n");
            scanf("%d", &i);
            j = GetElem(L, i, e);
            if (j == OK)
                printf("The element at position %d in the linear table is %d\n", i, e);
            else if (j == ERROR)
                printf("The selected element position is invalid (may be less than 1 or greater than the linear table length)!\n");
            else if (j == INFEASIBLE)
                printf("Linear table does not exist, element acquisition cannot be performed!\n");
            getchar();
            break;
        case 7:
            //LocateElem
            printf("Please enter the location to find the element:\n");
            scanf("%d", &e);
            j = LocateElem(L, e);
            if (j > 0)
                printf("Element to find %d in the linear table %d place!\n", e, j);
            else if (j == ERROR)
                printf("Failed to find element, the element is not in the linear table!\n");
            else if (j == INFEASIBLE)
                printf("Linear table does not exist, element acquisition cannot be performed!\n");
            getchar();
            break;
        case 8:
            //PriorElem；
            printf("Please enter the element to find to get its predecessor element:\n");
            scanf("%d", &e);
            j = PriorElem(L, e, pre);
            if (j == OK)
                printf("The predecessor element of element %d is %d !\n", e, pre);
            else if (j == ERROR)
                printf("Element %d has no predecessor (the element is in the table header or the element is not in the table)!\n", e);
            else if (j == INFEASIBLE)
                printf("Linear table does not exist, cannot get element!\n");
            getchar();
            break;
        case 9:
            //NextElem
            printf("Please enter the element to find to get its successor:\n");
            scanf("%d", &e);
            j = NextElem(L, e, next);
            if (j == OK)
                printf("The successor element of this element %d is %d!\n", e, next);
            else if (j == ERROR)
                printf("The element %d has no successor (the element is at the end of the list or the element is not in the list)!\n", e);
            else if (j == INFEASIBLE)
                printf("Linear table does not exist, cannot get element!\n");
            getchar();
            break;
        case 10:
            //ListInsert   
            printf("Please enter the element to be inserted:\n");
            scanf("%d", &e);
            printf("Please enter the element number after the insertion position:\n");
            scanf("%d", &i);
            j = ListInsert(L, i, e);
            if (j == OK)
                printf("Element inserted successfully!\n");
            else if (j == ERROR)
                printf("Inaccurate insertion position;i invalid value!\n");
            else if (j == INFEASIBLE)
                printf("The linear table does not exist and cannot be inserted!\n");
            getchar();
            break;
        case 11:
            //ListDelete
            printf("Please enter the position of the element to be removed:\n");
            scanf("%d", &i);
            j = ListDelete(L, i, e);
            if (j == OK)
                printf("Element removed successfully，The removed element is %d!\n", e);
            else if (j == ERROR)
                printf("Incorrect delete location!\n");
            else if (j == INFEASIBLE)
                printf("Linear table does not exist, delete operation cannot be performed!\n");
            getchar();
            break;
        case 12:
            //ListTraverse 
            j = ListTraverse(L);
            if (j == OK)
                printf("\nLinear table traversal succeeded!\n");
            else if (j == ERROR)
                printf("\nThe linear table is an empty table with no elements!\n");
            else if (j == INFEASIBLE)
                printf("\nLinear tables do not exist!\n");
            getchar();
            break;
        case 13:
            //save
            printf("-------- Sub Menu ——The linear table already exists, and direct writing will cause the original data in the table to be lost!--------------------\n");
            printf("-------------------------------------------------\n");
            printf("          1. SaveList  2.LoadList\n");
            printf("    Please Select[1~2]:       ");
            scanf("%d", &ch);
            if (ch == 1)
                //SaveList
            {
                printf("Please enter the name of the file to be operated:\n");
                scanf("%s", FileName);
                j = SaveList(L, FileName);
                if (j == OK)
                    printf("The data in the linear table has been successfully written to the specified file!\n");
                else if (j == INFEASIBLE)
                    printf("Linear tables do not exist!\n");
                getchar();
                break;
            }
            else if (ch == 2)
                //LoadList
            {
                printf("Please enter the name of the file to be operated:\n");
                scanf("%s", FileName);
                j = LoadList(L, FileName);
                if (j == OK)
                    printf("The data in the file has been successfully written to the linear table!\n");
                else if (j == INFEASIBLE)
                    printf("The linear table already exists, and direct writing will cause the original data in the table to be lost!\n");
            }
            getchar();
        case 0:
            break;
        }//end of switch
        printf("-----Press any key to continue-----\n");
        getchar();
    }//end of while
    printf("Thanks for Using, See U Next Time\n");
 }//end of main

/*sub*/
status InitList(LinkList& L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    /********** Begin *********/
    if (L) {
        return INFEASIBLE;
    }

    L = (LinkList)malloc(sizeof(struct LNode));
    if (!L) {
        //fail
        exit(OVERFLOW);
    }
    L->next = NULL;//指针领域为空
    return OK;
    /********** End **********/
}

status DestroyList(LinkList& L)    
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    /********** Begin *********/
    if (!L) {
        return INFEASIBLE;
    }

    LinkList q;
    while (L) {
        q = L->next;
        free(L);
        L = q;
    }
    return OK;
    /********** End **********/
}

status ClearList(LinkList& L)       
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    /********** Begin *********/
    if (!L) {
        return INFEASIBLE;
    }

    LinkList p, q;
    p = L->next;//p point to first node
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;//Pointer field of first Node is empty
    return OK;
    /********** End **********/
}

status ListEmpty(LinkList L) 
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/
    if (!L) {
        return INFEASIBLE;
    }

    if (L->next) {
        //not empty
        return FALSE;
    }
    else {
        return TRUE;
    }

    /********** End **********/
}

int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    /********** Begin *********/
    if (!L) {
        return INFEASIBLE;
    }

    int i = 0;
    LinkList p = L->next;//p point to the First Node
    while (p) {
        //not til the end
        i++;
        p = p->next;
    }
    return i;

    /********** End **********/
}

status GetElem(LinkList L, int i, ElemType& e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/
    if (!L) {
        return INFEASIBLE;
    }

    int count = 1;
    LinkList p = L->next; //p point to the first Node
    while (p && count < i) {
        //Look backwards clockwise until p points to the ith element or p is empty
        p = p->next;
        count++;
    }

    if (!p || count > i) {
        //i-th element does not exist
        return ERROR;
    }
    e = p->data;//get the i-th element
    return OK;
    /********** End **********/
}

status LocateElem(LinkList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    /********** Begin *********/
    if (!L) {
        return INFEASIBLE;
    }

    int i = 0;
    LinkList p = L;
    for (i = 0; p; p = p->next, i++) {
        if (e == p->data) {
            return i;
        }
    }

    if (!p) {
        return ERROR;
    }

    /********** End **********/
}

status PriorElem(LinkList L, ElemType e, ElemType& pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) {
        return INFEASIBLE;
    }
    int i;
    LinkList p = L;//first node p point to

    for (i = 0; p->next; p = p->next, i++) {
        if (e == p->next->data && i != 0) {
            pre = p->data;
            return OK;
        }
    }
    return ERROR;

    /********** End **********/
}

status NextElem(LinkList L, ElemType e, ElemType& next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/
    if (!L) {
        return INFEASIBLE;
    }

    int i;
    LinkList p = L; //p point to the first Node
    for (i = 0; p->next; p = p->next, i++) {
        //The node pointed to by p has a successor
        if (p->data == e) {
            next = p->next->data;
            return OK;
        }
    }
    return ERROR;

    /********** End **********/
}

status ListInsert(LinkList& L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/
    if (!L) {
        return INFEASIBLE;
    }

    int j = 0;
    LinkList p = L, s;
    while (p && j < i - 1) {
        //find i-1 th node
        p = p->next;
        j++;
    }

    if (!p || j > i - 1) {
        //i smaller than 1 or bigger than length
        return ERROR;
    }

    s = (LinkList)malloc(sizeof(struct LNode));//build new Node
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;

    /********** End **********/
}

status ListDelete(LinkList& L, int i, ElemType& e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/
    if (!L) {
        return INFEASIBLE;
    }

    int j = 0;
    LinkList p = L, q;
    while (p->next && j < i - 1) {
        //find i th node, Let p point to its predecessor
        p = p->next;
        j++;
    }

    if (!p->next || j > i - 1) {
        //delete illegal location
        return ERROR;
    }

    q = p->next; // delete and release Node
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;

    /********** End **********/
}

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/
    if (!L) {
        return INFEASIBLE;
    }

    LinkList p = L->next;
    for (; p; p = p->next) {
        if (p->next) {
            printf("%d ", p->data);
        }
        else {
            printf("%d", p->data);
        }

    }
    return OK;

    /********** End **********/
}

status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    /********** Begin 1 *********/
    if(!L){
        return INFEASIBLE;
    }

    LinkList p=L->next;
    FILE *fp;
    fp=fopen(FileName,"wb");
    while(p){
        //Traverse the linear table with the p pointer, writing the linear table elements to the file
        fprintf(fp,"%d ",p->data);
        p=p->next;
  }
        fclose(fp);
        return OK;
    /********** End 1 **********/
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    /********** Begin 2 *********/
    if(L){
        return INFEASIBLE;
    }

    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
    FILE *fp;
    LinkList p;
    if((fp=fopen(FileName,"rb"))!=NULL){
        //Use a first-in, first-out singly linked list to read the data elements in the file into a linear list
        L->next=(LinkList)malloc(sizeof(LNode));
        p=L->next;
        p->next=NULL;
        while((fscanf(fp,"%d ",&p->data))!=EOF){
            if(!feof(fp)){
                p->next=(LinkList)malloc(sizeof(LNode));
                p=p->next;
            }
        }
        p->next=NULL;
        fclose(fp);
    }
    return OK;

    /********** End 2 **********/
}
