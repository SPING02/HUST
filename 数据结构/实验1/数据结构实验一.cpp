/* 数据结构实验一-----基于顺序存储结构线性表 */
//头文件
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
//预定义的常量 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//类型表达式
typedef int status; //函数返回结果标志 
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100   //线性表存储结构分配的空间 
#define LISTINCREMENT  10  //线性表空间分配增量 
typedef struct {  //顺序表（顺序结构）的定义
    ElemType* elem;
    int length;         //线性表表长 
    int listsize;  //线性表分配空间大小 
}SqList;
typedef struct {  //线性表的管理表定义
    struct {
        char name[30];
        SqList L;
    } elem[10];
    int length;
    int listsize; //线性表集合分配的空间 10
}LISTS;

/*-----------------------------------------------------*/

status InitList(SqList& L);                                 //初始化表
status InitInput(SqList& L);                                //辅助元素  询问初始化后是否需要输入线性表数据 
status DestroyList(SqList& L);                              //销毁表
status ClearList(SqList& L);                                //清空表
status ListEmpty(SqList L);                                 //判定空表
int ListLength(SqList L);                                   //求表长
status GetElem(SqList L, int i, ElemType& e);               //获得元素
status LocateElem(SqList L, ElemType e);                    //查找元素
status PriorElem(SqList L, ElemType cur, ElemType& pre_e);  //获得前驱
status NextElem(SqList L, ElemType cur, ElemType& next_e);  //获得后继
status ListInsert(SqList& L, int i, ElemType e);            //插入元素
status ListDelete(SqList& L, int i, ElemType& e);           //删除元素
status ListTraverse(SqList L);                              //遍历表
status MaxSubArray(SqList L);                               //最大连续子数组和
status SubArrayNum(SqList L, int K);                        //和为K的子数组
status sortList(SqList& L);                                 //顺序表排序
status SaveList(SqList L, char FileName[]);                 //保存文件
status LoadList(SqList& L, char FileName[]);                //读取文件
status AddList(LISTS& Lists, char ListName[]);              //多线性表.添加
status RemoveList(LISTS& Lists, char ListName[]);           //多线性表.移除
int LocateList(LISTS Lists, char ListName[]);               //多线性表.查找

/*------------------------------------------------------------------------*/

int main(void) {
    SqList L;
    L.elem = NULL;
    int op = 1;
    int K;
    int i, j, ch, e, n, f, v;
    ElemType pre, next;
    LISTS Lists;
    Lists.length = 0;
    Lists.listsize = 10;
    FILE* fp = NULL;
    char name[30];          //add
    char ListName[50];      //delete 
    char FileName[50];      //filename 
    while (op) {
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("          1.  InitList       7.  LocateElem\n");
        printf("          2.  DestroyList    8.  PriorElem\n");
        printf("          3.  ClearList      9.  NextElem \n");
        printf("          4.  ListEmpty      10. ListInsert\n");
        printf("          5.  ListLength     11. ListDelete\n");
        printf("          6.  GetElem        12. ListTrabverse\n");
        printf("          13. MaxSubArray    14. SubArrayNum   \n");
        printf("          15. sortList       16. The file format of the linear table is saved\n");
        printf("          17. Multiple linear table management   0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    Please Select [0~17]:       \n");
        scanf("%d", &op);
        switch (op) {
        case 1:
            //InitList
            j = InitList(L);
            if (j == OK) {
                printf("Link Create Successfully!\n");
                InitInput(L);
            }
            else if (j == ERROR) {
                printf("List Create Failed!\n");
            }
            else if (j == INFEASIBLE) {
                printf("List already exist!\n");
            }
            getchar();
            break;
        case 2:
            //DestroyList
            j = DestroyList(L);
            if (j == OK)
                printf("The linear table is destroyed successfully!\n");
            else if (j == INFEASIBLE)
                printf("The linear table does not exist, and the linear table destruction operation cannot be performed!\n");
            getchar();
            break;
        case 3:
            //ClearList。
            if (ClearList(L) == OK)
                printf("The linear table is emptied successfully!\n");
            else
                printf("The linear table does not exist, and the linear table clearing operation cannot be performed!\n");
            getchar();
            break;
        case 4:
            //ListEmpty
            j = ListEmpty(L);
            if (j == TRUE)
                printf("The linear table is empty!\n");
            else if (j == FALSE)
                printf("The linear table is not empty!\n");
            else if (j == INFEASIBLE)
                printf("The linear table does not exist, and the linear table null judgment operation cannot be performed!\n");
            getchar();
            break;
        case 5:
            //ListLength
            j = ListLength(L);
            if (j >= 0)
                printf("Linear table length is %d !\n", j);
            else
                printf("The linear table does not exist, the table length cannot be calculated!\n");
            getchar();
            break;
        case 6:
            //GetElem
            printf("Please enter where to find the element:\n");
            scanf("%d", &i);
            j = GetElem(L, i, e);
            if (j == OK)
                printf("The element at position %d in the linear table is %d\n", i, e);
            else if (j == ERROR)
                printf("The selected element position is invalid (may be less than 1 or greater than the linear table length)\n");
            else if (j == INFEASIBLE)
                printf("Linear table does not exist, element acquisition cannot be performed!\n");
            getchar();
            break;
        case 7:
            //LocateElem
            printf("Please enter where to find the element:\n");
            scanf("%d", &e);
            j = LocateElem(L, e);
            if (j > 0)
                printf("The element %d to find is at position %d in the linear table!\n", e, j);
            else if (j == ERROR)
                printf("Failed to find element, the element is not in the linear table!\n");
            else if (j == INFEASIBLE)
                printf("Linear table does not exist, element lookup is not possible!\n");
            getchar();
            break;
        case 8:
            //PriorElem；
            printf("Please enter the element to find to get its predecessor:\n");
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
            printf("Enter the element to find to get its successor:\n");
            scanf("%d", &e);
            j = NextElem(L, e, next);
            if (j == OK)
                printf("The successor element of this element %d is %d !\n", e, next);
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
                printf("Insert element successfully!\n");
            else if (j == ERROR)
                printf("Insert position is inaccurate; i value is invalid!\n");
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
                printf("The element was removed successfully, the removed element is %d !\n", e);
            else if (j == ERROR)
                printf("The deletion location is incorrect!\n");
            else if (j == INFEASIBLE)
                printf("The linear table does not exist and cannot be deleted!\n");
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
                printf("\nThe linear table does not exist!\n");
            getchar();
            break;
        case 13:
            //MaxSubArray
            j = MaxSubArray(L);
            if (j == -1)
                printf("The linear table does not exist!!\n");
            else if (j == 0)
                printf("Linear tables are empty tables! ! !\n");
            getchar();
            break;
        case 14:
            //SubArrayNum
            printf("Now to ask for the number of consecutive subarrays whose sum is K, please enter your K value:\n");
            scanf("%d", &K);
            j = SubArrayNum(L, K);
            if (j == -1)
                printf("The linear table does not exist!!\n");
            else if (j == 0)
                printf("Linear tables are empty tables! !\n");
            getchar();
            break;
        case 15:
            //sortList
            j = sortList(L);
            if (j == OK)
                printf("Sorted successfully\n");
            else if (j == INFEASIBLE)
                printf("The linear table L does not exist, the sorting operation cannot be performed\n");
            getchar();
            break;
        case 16:
            //The file format of the linear table is saved
            printf("------------------ Sub-Menu --------------------\n");
            printf("--- realize the file save of the linear table---\n");
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
            break;
        case 17:
            //Multiple linear table management
            printf("-------------------Sub Menu——Multiple linear table management------------------\n");
            printf("          1. AddList            2.RemoveList\n");
            printf("          3. LocateList         4.ListTraverse\n");
            printf("-------------------------------------------------\n");
            printf("    Please Select[1~4]:      ");
            scanf("%d", &ch);
            if (ch == 1)
            //AddList
            {
                printf("Please enter n linear tables, where the value of n is:\n");
                scanf("%d", &n);
                while (n)
                {
                    printf("Please enter a linear table name, and data elements, ending with 0, excluding 0\n");
                    scanf("%s", name);
                    AddList(Lists, name);
                    scanf("%d", &f);
                    while (f)
                    {
                        ListInsert(Lists.elem[Lists.length - 1].L, Lists.elem[Lists.length - 1].L.length + 1, f);
                        scanf("%d", &f);
                    }
                    n--;
                }
                printf("Do I need to print all the linear tables now? \n1: print 0: not required\n");
                scanf("%d", &v);
                if (v == 1)
                {
                    printf("\n\nPrint all linear tables as follows:\n ");
                    for (n = 0; n < Lists.length; n++)
                    {
                        printf("          The %dth linear table name is %s", n + 1, Lists.elem[n].name);
                        ListTraverse(Lists.elem[n].L);
                        putchar('\n');
                    }
                }
            }
            else if (ch == 2)
            //RemoveList
            {
                printf("Please enter the name of the linear table to be deleted: \n");
                scanf("%s", ListName);
                j = RemoveList(Lists, ListName);
                if (j == ERROR)
                    printf("Delete failed, no linear table with this name\n");
                else if (j == -1)
                    printf("failed to delete! ! ! The linear table set is empty\n");
                else
                {
                    printf("successfully deleted!\n");
                    printf("Do need to print all linear tables? \n1: print 0: not required\n");
                    scanf("%d", &v);
                    if (v == 1)
                    {
                        int   flag = 1;
                        if (Lists.length == 0)
                        {
                            printf("Error! ! ! The linear table set is empty\n ");
                            flag = 0;
                        }
                        if (flag == 1)
                        {
                            printf("\n\nPrint all linear tables as follows:\n ");
                            for (n = 0; n < Lists.length; n++)
                            {
                                printf("          The %dth linear table name is %s ", n + 1, Lists.elem[n].name);
                                ListTraverse(Lists.elem[n].L);
                                putchar('\n');
                            }
                        }
                    }
                }
            }
            else if (ch == 3)
            //LocateList
            {
                int   flag = 1;
                if (Lists.length == 0)
                {
                    printf("Error! ! ! The linear table set is empty\n ");
                    flag = 0;
                }
                if (flag == 1)
                {
                    printf("Please enter the name of the linear table you are looking for \n");
                    scanf("%s", ListName);
                    j = LocateList(Lists, ListName);
                    if (!j)
                        printf("There is no linear table of this name in the linear table collection \n\n");
                    else if (j == -1)
                        printf("Error! ! ! The linear table set is empty\n\n");
                    else
                    {
                        printf("After investigation, the logical serial number of the linear table is: %d \n", j);
                        printf("The linear table is named %s ", Lists.elem[j - 1].name);
                        ListTraverse(Lists.elem[j - 1].L);
                        putchar('\n');
                    }
                }
            }
            else if (ch == 4)
            //ListTraverse
            {
                int   flag = 1;
                if (Lists.length == 0)
                {
                    printf("Error! ! ! The linear table set is empty\n ");
                    flag = 0;
                }
                if (flag == 1)
                {
                    printf("\n\nPrint all linear tables as follows:\n ");
                    for (n = 0; n < Lists.length; n++)
                    {
                        printf("The %dth linear table name is %s ", n + 1, Lists.elem[n].name);
                        ListTraverse(Lists.elem[n].L);
                        putchar('\n');
                    }
                }
            }
            else
            {
                printf("Select typo! ! ! ! Please enter again\n");
                continue;
            }
            getchar();
            break;
        case 0:
            break;
        }//end of switch
        printf("-----Press any key to continue-----\n");
        getchar();
    }//end of while
    printf("Thanks for Using, See U Next Time\n");
}//end of main()

status InitList(SqList& L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    /********** Begin *********/
    if (L.elem) {
        return INFEASIBLE;
    }

    L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));

    if (!L.elem) {
        //fail
        exit(OVERFLOW);
    }
    L.length = 0;//length of array =0
    L.listsize = LIST_INIT_SIZE;//reset volume
    return OK;

    /********** End **********/
}

status InitInput(SqList& L)
// 选择是否向线性表中输入数据，是则由用户输入以0为结束标志的一组数据，返回OK，否则返回0。
{
    int ord, temp;
    printf("Choose 1 for input data, otherwise choose 0:\n");
    scanf("%d", &ord);
    if (ord == 0)  //以0为结束标志
        return 0;
    else
    {
        printf("Please enter a set of data, 0 is the end mark:\n");
        scanf("%d", &temp);
        while (temp != 0)    //元素输入截止的标志
        {
            ListInsert(L, L.length + 1, temp);  //调用插入函数在线性表尾部增加元素
            scanf("%d", &temp);
        }
        printf("Entered successfully!\n");
        return OK;
    }
}

status DestroyList(SqList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;

    /********** End **********/
}

status ClearList(SqList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    /********** Begin *********/
    if (!L.elem) {
        return INFEASIBLE;
    }
    L.length = 0;
    return OK;

    /********** End **********/
}

status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }

    if (L.length == 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }

    /********** End **********/
}

status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    /********** Begin *********/
    if(L.elem==NULL){
        return INFEASIBLE; 
    }

    return L.length;

    /********** End **********/
}

status GetElem(SqList L, int i, ElemType& e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }

    if (i<1 || i>L.length) {
        return ERROR;
    }

    e = *(L.elem + i - 1);
    return OK;

    /********** End **********/
}

int LocateElem(SqList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }

    int i, flag = 1;
    for (i = 0; i < L.length; i++)
    {
        if (e == L.elem[i])
        {
            flag = 0;
            return i + 1;
        }
    }
    if (flag)
        return ERROR;

    /********** End **********/
}

status PriorElem(SqList L, ElemType e, ElemType& pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }

    int i = 2;
    ElemType* p = L.elem + 1;
    while (i <= L.length && *p != e) {
        p++;
        i++;
    }
    if (i > L.length) {
        return ERROR;
    }
    else {
        pre = *--p;
        return OK;
    }
    /********** End **********/
}

status NextElem(SqList L, ElemType e, ElemType& next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }

    for (int i = 0; i < L.length - 1; i++) {
        if (L.elem[i] == e) {
            next = L.elem[i + 1];
            return OK;
        }
    }
    return ERROR;

    /********** End **********/
}

status ListInsert(SqList& L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }

    ElemType* newbase, * q, * p;
    if (i<1 || i>L.length + 1) {
        //illegal
        return ERROR;
    }
    if (L.length >= L.listsize) {
        //full
        if (!(newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType)))) {
            //fail
            exit(OVERFLOW);
        }
        L.elem = newbase; //new address
        L.listsize += LISTINCREMENT;//extra volume
    }

    q = L.elem + i - 1; //q stand for insert places
    for (p = L.elem + L.length - 1; p >= q; --p) {
        //element after new place move to right
        *(p + 1) = *p;
    }
    *q = e; //insert e
    ++L.length;//insert length
    return OK;

    /********** End **********/
}

status ListDelete(SqList& L, int i, ElemType& e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }

    ElemType* p, * q;
    if (i<1 || i>L.length) {
        //illegal
        return ERROR;
    }

    p = L.elem + i - 1; //p stand for delete place
    e = *p; //e is given the value of deleted element
    q = L.elem + L.length - 1; //last element place

    for (++p; p <= q; ++p) {
        //element after deleted element move to left
        *(p - 1) = *p;
    }
    L.length--;
    return OK;

    /********** End **********/
}

status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }

    for (int i = 0; i < L.length; i++) {
        if (i != L.length - 1) {
            printf("%d ", L.elem[i]);
        }
        else {
            printf("%d", L.elem[i]);
        }
    }
    return OK;

    /********** End **********/
}

status MaxSubArray(SqList L)
//初始条件是线性表L已存在且非空，
//找出一个具有最大和的连续子数组（子数组最少包含一个元素），操作结果是其最大和；
{
    if (!L.elem) {
        return -1;
    }
    if (!L.length) {
        return 0;
    }
    int SUM = L.elem[0];
    for (int i = 0; i < L.length; i++){
        if (SUM > L.elem[i]) {
            SUM = L.elem[i];
        }
    }

    for (int i = 0; i < L.length; i++){
        int subOfArr = 0;  //temporary maximum
        for (int j = i; j < L.length; j++){
            subOfArr += L.elem[j];

            if (subOfArr > SUM) {
                SUM = subOfArr;
            }
        }
    }
    printf("The linear table L already exists and is not empty and meets the condition!\n");
    printf("The operation is successful, and the maximum sum of consecutive subarrays sought is %d\n", SUM);
}

status SubArrayNum(SqList L, int K)
//初始条件是线性表L已存在且非空, 
//操作结果是该数组中和为k的连续子数组的个数；
{
    if (!L.elem) {
        return -1;
    }
    if (!L.length) {
        return 0;
    }
    int ans = 0;
    for (int i = 0; i < L.length; i++){
        int subOfArr = 0;  //temporary maximum
        for (int j = i; j < L.length; j++){
            subOfArr += L.elem[j];
            if (subOfArr == K) {
                ans++;
            }
        }
    }
    printf("The number of consecutive subarrays obtained as K is %d!\n", ans);
    return OK;
}

status  sortList(SqList& L)
//初始条件是线性表L已存在；操作结果是将L由小到大排序
{
    if (!L.elem) {
        return -1;
    }
    int temp, i, j;
    for (i = 0; i < L.length - 1; i++){
        int lmin = i;                  //The first element defaults to the smallest value and records the smallest value;
        for (j = i + 1; j < L.length; j++){
            // access unsorted elements
            if (L.elem[j] < L.elem[lmin]){
                //find the current minimum
                lmin = j;    //record minimum
            }
        }
        if (lmin != i){
            temp = L.elem[lmin];  // exchange
            L.elem[lmin] = L.elem[i];
            L.elem[i] = temp;
        }
    }
    return OK;
}

status  SaveList(SqList L, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }

    FILE* fp;
    int i = 0;
    fp = fopen(FileName, "wb");

    if (!fp) {//file open fail
        return ERROR;
    }
    while (i < L.length) {
        fprintf(fp, "%d ", L.elem[i]);    //write in 
        i++;
    }
    fclose(fp);
    return OK;
    /********** End **********/
}

status  LoadList(SqList& L, char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    /********** Begin *********/
    if (L.elem) {
        return INFEASIBLE;
    }
    FILE* fp;
    int i = 0;
    L.elem = (ElemType*)malloc(sizeof(ElemType) * LIST_INIT_SIZE); //initialization
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    if ((fp = fopen(FileName, "rb")) != NULL) {
        while ((fscanf(fp, "%d ", &L.elem[i])) != EOF) {
            //cant read file
            if (L.length < L.listsize - 1) {
                //read element when array not complete
                L.length++;
                i++;
            }
            else {//reallocate space when its full
                L.elem = (ElemType*)realloc(L.elem, sizeof(ElemType) * (L.listsize + LISTINCREMENT));
                L.listsize += LISTINCREMENT;
                L.length++;
                i++;
            }
        }
    }
    fclose(fp);
    return OK;

    /********** End **********/
}

status AddList(LISTS& Lists, char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    /********** Begin *********/
    strcpy(Lists.elem[Lists.length].name, ListName);

    Lists.elem[Lists.length].L.elem = NULL;
    InitList(Lists.elem[Lists.length].L);
    Lists.length++;
    return OK;

    /********** End **********/
}

status RemoveList(LISTS& Lists, char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    /********** Begin *********/
    if (!Lists.length) {
        return ERROR;
    }
    for (int i = 0; i < Lists.length; i++) {
        if (!(strcmp(Lists.elem[i].name, ListName))) {
            free(Lists.elem[i].L.elem);
            for (int j = i; j < Lists.length; j++) {
                Lists.elem[j] = Lists.elem[j + 1];
            }
            Lists.length--;
            return OK;
        }
    }
    return ERROR;

    /********** End **********/
}

int LocateList(LISTS Lists, char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    /********** Begin *********/
    for (int i = 0; i < Lists.length; i++) {
        if (!(strcmp(Lists.elem[i].name, ListName))) {
            return i + 1;
        }
    }
    return 0;

    /********** End **********/
}