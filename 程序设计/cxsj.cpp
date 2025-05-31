#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TRUE 1
#define OK 1
#define FALSE 0
#define ERROR 0
#define INFEASIBLE -1
#define INCREASEMENT 100
#define CLOCKS_PRE_SEC 1000
#define row 9
#define col 9

typedef int status;
int boolCount;  //布尔变元数量
int clauseCount;  //子句数量
char fileName[100]; //文件名
int sudoku1[9][9];
int sudoku2[9][9];
int start1[9][9];
int start2[9][9];
//十字链表结构体
typedef struct SATNode {
    int data;  //数据域
    SATNode* next;
} SATNode;
typedef struct SATList {
    SATNode* head;  //表头
    SATList* next;
} SATList;

//函数声明
status ReadFile(SATList*& cnf);
status SAT(void);
status Sudoku(void);
void destroyClause(SATList*& cnf);
status isUnitClause(SATNode* cnf);
status removeClause(SATList*& cnf, SATList*& root);
status removeNode(SATNode*& cnf, SATNode*& head);
status addClause(SATList* cnf, SATList*& root);
status isemptyClause(SATList* cnf);
status DPLL(SATList*& cnf, int value[]);
void CopyClause(SATList*& a, SATList* b);
status SaveFile(int result, double time, int value[]);
void CreateBinary(void);
void tocnf(char* fileName, int hole);
void print(int a[][9]);
int DFSCreate(int x, int y, int sudoku[][9]);
void CreateSudoku(void);
void Dighole1(int hole);
void Dighole2(int hole);
int Save_sudoku(char* filename, int* val);
void play(int flag, int* val);
status Create(struct SATList*& cnf);
int DPLL0(SATList*& cnf, int value[]);

int main() {
    int op = 1;
    while (op) {
        printf("\n\n");
        printf("                    MENU                        \n");
        printf("-------------------------------------------------\n");
        printf("          1. Sudoku           2. SAT\n");
        printf("          0. exit              \n");
        printf("-------------------------------------------------\n");
        printf("    Please Select[0~2]:");
        scanf("%d", &op);
        switch (op) {
        case 1:
            Sudoku();
            break;
        case 2:
            SAT();
            break;
        case 0:
            printf("Bye Bye! See you Next Time!\n");
            exit(0);
            break;
        }//end of switch
    }//end of while
}

status SAT(void) {
    int op = 1;
    int result, i;
    SATList* CNFList = NULL, * lp;			
    SATNode* tp;						
    int* value;
    double time;
    clock_t start, finish;
    while (op) {
        system("cls"); printf("\n\n");
        printf("                    SAT MENU                      \n");
        printf("-------------------------------------------------------------\n");
        printf("          1.Read cnf File                     2.Transverse clause\n");
        printf("          3.Solve(improved) and Save cnf      4.Solve(not improved)\n");
        printf("          0.exit\n");
        printf("-------------------------------------------------\n");
        printf("    Please Select[0~4]:");
        scanf("%d", &op);
        switch (op) {
        case 1:
            printf("Please key in the name of cnf file to read:");
            scanf("%s", fileName);
            ReadFile(CNFList);
            break;
        case 2:
            if (CNFList == NULL) printf("File not exists\n");
            else {
                printf("cnf clause:\n");
                for (lp = CNFList; lp != NULL; lp = lp->next) {
                    for (tp = lp->head; tp != NULL; tp = tp->next) {
                        printf("\t%d\t", tp->data);
                    }
                    printf("\n");
                }
            }
            printf("Success\n");
            getchar(); getchar();
            break;
        case 3:
            if (CNFList == NULL) printf("File not exists\n");
            else {
                value = (int*)malloc(sizeof(int) * (boolCount + 1));
                for (i = 1; i <= boolCount; i++) value[i] = 1;							
                start = clock();													
                result = DPLL(CNFList, value);
                finish = clock();													
                printf("Result: %d\n", result);
                if (result == 1) {
                    for (i = 1; i <= boolCount; i++) {
                        if (value[i] == 1) printf("\t%d\n", i);
                        else printf("\t%d\n ", -i);
                    }
                    printf("\n");
                }
                time = (double)(finish - start) / CLOCKS_PRE_SEC;
                printf("Operation time=%lfms\n", time * 1000);
                if (SaveFile(result, time, value) == 1)
                    printf("Results are saved to a .txt file with the same namet\n");
                else printf("Failed to Save the file\n");
            }
            getchar(); getchar();
            break;
        case 4:
            value = (int*)malloc(sizeof(int) * (boolCount + 1));
            for (i = 1; i <= boolCount; i++) value[i] = 1;
            start = clock();
            result = DPLL0(CNFList, value);
            finish = clock();
            printf("Result: %d\n", result);
            if (result == 1) {
                for (i = 1; i <= boolCount; i++) {
                    if (value[i] == 1)
                        printf("\t%d\t", i);
                    else printf("\t%d\t", -i);
                }
                printf("\n");
            }
            time = (double)(finish - start) / CLOCKS_PER_SEC;//??????DDê±??
            printf("Operation Time=%lfms\n", time * 1000);//ê?3???DDê±??
            if (SaveFile(result, time, value) == 1)
                printf("Results are saved to a .res file with the same name\n");
            else printf("Failed to Save the file\n");
            getchar(); getchar();
            break;
        case 0:
            printf("Bye Bye! See you Next Time!\n");
            getchar(); getchar();
            exit(0);
            break;
        }//end of switch
    }//end of while
}

status Sudoku(void) {
    int op = 1;
    int result, i;
    SATList* CNFList = NULL, * lp;			
    SATNode* tp;					
    int* value;
    double time;
    char s[111111];
    clock_t start, finish;
    while (op) {
        system("cls"); printf("\n\n");
        printf("                    Twodoku                       \n");
        printf("-------------------------------------------------\n");
        printf("          1.Twodoku\n");
        printf("          0. exit\n");
        printf("-------------------------------------------------\n");
        printf("    Please Select[0~1]:");
        scanf("%d", &op);
        switch (op) {
        case 1:
            CreateSudoku();
            printf("Sudoku final game is generated!\n");
            int hole1, hole2;
            printf("Please enter the number of spaces in the top left Sudoku\n");
            scanf("%d", &hole1);
            Dighole1(hole1);
            printf("Please enter the number of spaces in the bottom right Sudoku\n");
            scanf("%d", &hole2);
            Dighole2(hole2);
            printf("top left sudoku\n");
            print(start1);
            printf("\nbottom right sudoku\n");
            print(start2);
            printf("Please enter the required cnf file name");
            scanf("%s", fileName);
            tocnf(fileName, hole1 + hole2);
            printf("Suceessfully created cnf, FileName is %s\n", fileName);
            Create(CNFList);
            value = (int*)malloc(sizeof(int) * (boolCount * 3 + 1));
            for (i = 1; i <= boolCount; i++) value[i] = 1;	
            start = clock();
            if (DPLL(CNFList, value) == 1) {
                finish = clock();
                printf("Double Sudoku solved successfully\n");
                printf("Operation hours%fms\n", (double)(finish - start) / CLK_TCK * 1000);
                if (Save_sudoku(fileName, value)) {
                    printf("The solution is saved successfully, the file name is %s\n", fileName);
                    printf("Do you want to start the game? YES or NO\n");
                    scanf("%s", s);
                    if (strcmp(s, "YES") == 0) play(1, value);
                }
                else printf("Failed to save\n");
            }
            else printf("solve failed\n");
            getchar(); getchar();
            break;
        case 0:
            printf("Bye Bye! See You Next Time!\n");
            getchar(); getchar();
            exit(0);
            break;
        }//end of switch
    }//end of while
}

status ReadFile(struct SATList*& cnf) {
    FILE* fp;
    char ch;
    int nodenumber, i;
    SATList* lp;
    SATNode* tp;
    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Error\n");
        getchar(); getchar();
        return ERROR;
    }
    while ((ch = getc(fp)) != 'p');
    getc(fp); getc(fp); getc(fp); getc(fp);			
    fscanf(fp, "%d", &boolCount);
    fscanf(fp, "%d", &clauseCount);
    cnf = (SATList*)malloc(sizeof(SATList));
    cnf->next = NULL;
    cnf->head = (SATNode*)malloc(sizeof(SATNode));
    cnf->head->next = NULL;
    lp = cnf;
    tp = cnf->head;

    for (i = 0; i < clauseCount; i++, lp = lp->next, tp = lp->head) {
        fscanf(fp, "%d", &nodenumber);
        for (; nodenumber != 0; tp = tp->next) {
            tp->data = nodenumber;		
            tp->next = (SATNode*)malloc(sizeof(SATNode));
            fscanf(fp, "%d", &nodenumber);
            if (nodenumber == 0) tp->next = NULL;
        }
        lp->next = (SATList*)malloc(sizeof(SATList));
        lp->next->head = (SATNode*)malloc(sizeof(SATNode));
        if (i == clauseCount - 1) {
            lp->next = NULL;
            break;
        }
    }
    fclose(fp);
    return OK;
}

status Create(struct SATList*& cnf) {
    FILE* fp;
    char ch;
    int nodenumber, i;
    SATList* lp;
    SATNode* tp;
    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("???t′ò?a′í?ó\n");
        getchar(); getchar();
        return ERROR;
    }
    while ((ch = getc(fp)) != 'p');
    getc(fp); getc(fp); getc(fp); getc(fp);
    fscanf(fp, "%d", &boolCount);
    fscanf(fp, "%d", &clauseCount);
    cnf = (SATList*)malloc(sizeof(SATList));
    cnf->next = NULL;
    cnf->head = (SATNode*)malloc(sizeof(SATNode));
    cnf->head->next = NULL;
    lp = cnf;
    tp = cnf->head;

    //′′?¨×ó???ˉ 
    for (i = 0; i < clauseCount; i++, lp = lp->next, tp = lp->head) {
        fscanf(fp, "%d", &nodenumber);
        for (; nodenumber != 0; tp = tp->next) {
            tp->data = nodenumber;		//êy?Y?3?μ
            tp->next = (SATNode*)malloc(sizeof(SATNode));//?a±ùD??áμ?
            fscanf(fp, "%d", &nodenumber);
            if (nodenumber == 0) tp->next = NULL;
        }
        lp->next = (SATList*)malloc(sizeof(SATList));//?a±ùD?×ó??±í
        lp->next->head = (SATNode*)malloc(sizeof(SATNode));//?a±ùD??áμ?
        if (i == clauseCount - 1) {
            lp->next = NULL;
            break;
        }
    }
    return OK;
}

/* 函数名称: destroyClause*/
status destroyClause(SATList*& cnf)
{
    SATList* lp1, * lp2;
    SATNode* tp1, * tp2;
    for (lp1 = cnf; lp1 != NULL; lp1 = lp2)
    {
        lp2 = lp1->next;
        for (tp1 = lp1->head; tp1 != NULL; tp1 = tp2)
        {
            tp2 = tp1->next;
            free(tp1);
        }
        free(lp1);
    }
    cnf = NULL;
}
/*函数名称: isUnitClause*/
status isUnitClause(SATNode* cnf)
{
    if (cnf != NULL && cnf->next == NULL)
        return 1;
    else
        return 0;
}
/*函数名称: removeClause*/
int removeClause(SATList*& cnf, SATList*& root)
{
    SATList* lp = root;
    if (lp == cnf) root = root->next;  //删除为头
    else
    {
        while (lp != NULL && lp->next != cnf) lp = lp->next;
        lp->next = lp->next->next;
    }
    free(cnf);
    cnf = NULL;
    return 1;
}
/*函数名称: removeNote*/
status removeNode(SATNode*& cnf, SATNode*& head)
{
    SATNode* lp = head;
    if (lp == cnf) head = head->next;  //删除为头
    else
    {
        while (lp != NULL && lp->next != cnf) lp = lp->next;
        lp->next = lp->next->next;
    }
    free(cnf);
    cnf = NULL;
    return 1;
}
/*函数名称: addClause*/
status addClause(SATList* cnf, SATList*& root)
{
    //直接插入在表头
    if (cnf != NULL)
    {
        cnf->next = root;
        root = cnf;
        return 1;
    }
    return 0;
}
/*函数名称: emptyClause*/
status isemptyClause(SATList* cnf)
{
    SATList* lp = cnf;
    while (lp != NULL)
    {
        if (lp->head == NULL) return 1;
        lp = lp->next;
    }
    return 0;
}
/*函数名称: CopyClause*/
void CopyClause(SATList*& a, SATList* b)
{
    SATList* lpa, * lpb;
    SATNode* tpa, * tpb;
    a = (SATList*)malloc(sizeof(SATList));
    a->head = (SATNode*)malloc(sizeof(SATNode));
    a->next = NULL;
    a->head->next = NULL;
    for (lpb = b, lpa = a; lpb != NULL; lpb = lpb->next, lpa = lpa->next)
    {
        for (tpb = lpb->head, tpa = lpa->head; tpb != NULL; tpb = tpb->next, tpa = tpa->next)
        {
            tpa->data = tpb->data;
            tpa->next = (SATNode*)malloc(sizeof(SATNode));
            tpa->next->next = NULL;
            if (tpb->next == NULL)
            {
                free(tpa->next);
                tpa->next = NULL;
            }
        }
        lpa->next = (SATList*)malloc(sizeof(SATList));
        lpa->next->head = (SATNode*)malloc(sizeof(SATNode));
        lpa->next->next = NULL;
        lpa->next->head->next = NULL;
        if (lpb->next == NULL)
        {
            free(lpa->next->head);
            free(lpa->next);
            lpa->next = NULL;
        }
    }
}
/*函数名称: DPLL*/
status DPLL(SATList*& cnf, int value[])
{
    SATList* tp = cnf, * lp = cnf, * sp;
    SATNode* dp;
    int* count, i, MaxWord, max, re; //count记录每个文字出现次数,MaxWord记录出现最多次数的文字
    count = (int*)malloc(sizeof(int) * (boolCount * 2 + 1));
FIND:
    while (tp != NULL && isUnitClause(tp->head) == 0) tp = tp->next;  //找到表中的单子句
    if (tp != NULL)
    {
        //单子句规则简化
        if (tp->head->data > 0) value[tp->head->data] = 1;
        else value[-tp->head->data] = 0;
        re = tp->head->data;
        for (lp = cnf; lp != NULL; lp = sp)
        {
            sp = lp->next;
            //查找含有核心文字的句子
            for (dp = lp->head; dp != NULL; dp = dp->next)
            {
                if (dp->data == re)
                {
                    removeClause(lp, cnf);  //删除子句，简化式子
                    break;
                }
                if (dp->data == -re)
                {
                    removeNode(dp, lp->head);  //删除文字，简化子句
                    break;
                }
            }
        }
        //极简化规则简化后
        if (cnf == NULL)
        {
            free(count);
            return 1;
        }
        else if (isemptyClause(cnf))
        {
            free(count);
            destroyClause(cnf);
            return 0;
        }
        tp = cnf;
        goto FIND;  //继续简化
    }
    for (i = 0; i <= boolCount * 2; i++) count[i] = 0;  //初始化
    //计算子句中各文字出现次数
    for (lp = cnf; lp != NULL; lp = lp->next)
    {
        for (dp = lp->head; dp != NULL; dp = dp->next)
        {
            if (dp->data > 0) count[dp->data]++;
            else count[boolCount - dp->data]++;
        }
    }
    max = 0;
    //找到出现次数最多的正文字
    for (i = 2; i <= boolCount; i++)
    {
        if (max < count[i])
        {
            max = count[i];
            MaxWord = i;
        }
    }
    if (max == 0)
    {
        //若没有出现正文字,找到出现次数最多的负文字
        for (i = boolCount + 1; i <= boolCount * 2; i++)
        {
            if (max < count[i])
            {
                max = count[i];
                MaxWord = -i;
            }
        }
    }
    free(count);
    lp = (SATList*)malloc(sizeof(SATList));
    lp->head = (SATNode*)malloc(sizeof(SATNode));
    lp->head->data = MaxWord;
    lp->head->next = NULL;
    lp->next = NULL;
    CopyClause(tp, cnf);
    addClause(lp, tp);
    if (DPLL(tp, value) == 1) return 1;  //在第一分支中搜索
    destroyClause(tp);
    lp = (SATList*)malloc(sizeof(SATList));
    lp->head = (SATNode*)malloc(sizeof(SATNode));
    lp->head->data = -MaxWord;
    lp->head->next = NULL;
    lp->next = NULL;
    addClause(lp, cnf);
    re = DPLL(cnf, value); //回溯到执行分支策略的初态进入另一分支
    destroyClause(cnf);
    return re;
}

int DPLL0(SATList*& cnf, int value[]) {
    SATList* lp = cnf, * sp = cnf, * dp;
    SATNode* tp;
    int* count, i, MaxWord, max, ret;										//count??????????×?3???′?êy￡?MaxWord????3???×??à′?êyμ???×?
    count = (int*)malloc(sizeof(int) * (boolCount * 2 + 1));
Cycle: while (lp != NULL && isUnitClause(lp->head) == 0) lp = lp->next;		//?òμ?μ￥×ó??
    if (lp != NULL) {
        if (lp->head->data > 0) value[lp->head->data] = 1;
        else value[-lp->head->data] = 0;
        ret = lp->head->data;
        for (sp = cnf; sp != NULL; sp = dp) {
            dp = sp->next;
            for (tp = sp->head; tp != NULL; tp = tp->next) {
                if (tp->data == ret) {
                    removeClause(sp, cnf);								//é?3y×ó??￡??ò?ˉ·?ê? 
                    break;
                }
                if (tp->data == -ret) {
                    removeNode(tp, sp->head);							//é?3y??×?￡??ò?ˉ×ó?? 
                    break;
                }
            }
        }
        if (cnf == NULL) {
            return OK;
        }
        else if (isemptyClause(cnf)) {
            destroyClause(cnf);
            return ERROR;
        }
        lp = cnf;
        goto Cycle;														//?-?·?ˉ?ò 
    }

    lp = (SATList*)malloc(sizeof(SATList));
    lp->head = (SATNode*)malloc(sizeof(SATNode));
    lp->head->data = cnf->head->data;
    lp->head->next = NULL;
    lp->next = NULL;
    CopyClause(sp, cnf);
    addClause(lp, sp);
    if (DPLL0(sp, value) == OK) return OK;										//?úμúò?·??§?DDPLL 
    destroyClause(sp);
    lp = (SATList*)malloc(sizeof(SATList));
    lp->head = (SATNode*)malloc(sizeof(SATNode));
    lp->head->data = -cnf->head->data;
    lp->head->next = NULL;
    lp->next = NULL;
    addClause(lp, cnf);
    ret = DPLL0(cnf, value);													//???Y￡???è?áíò?·??§ 
    destroyClause(cnf);
    return ret;
}
/*函数名称: WriteFile*/
status SaveFile(int result, double time, int value[]) 
{
    FILE* fp;
    int i;
    for (i = 0; fileName[i] != '\0'; i++)
    {
        //修改拓展名
        if (fileName[i] == '.' && fileName[i + 4] == '\0')
        {
            fileName[i + 1] = 'r';
            fileName[i + 2] = 'e';
            fileName[i + 3] = 's';
            break;
        }
    }
    fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("Failed to open file!\n");
        return 0;
    }
    fprintf(fp, "s %d\nv ", result);  //求解结果
    if (result == 1)
    {
        //保存解值
        for (i = 1; i <= boolCount; i++)
        {
            if (value[i] == 1) fprintf(fp, "%d ", i);
            else fprintf(fp, "%d ", -i);
        }
    }
    fprintf(fp, "\nt %lf", time * 1000);  //运行时间/毫秒
    fclose(fp);
    return 1;
}

void print(int a[][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int DFSCreate(int x, int y, int sudoku[][9]) {
    if (x < 9 && y < 9) {
        if (sudoku[x][y] != 0) {
            return DFSCreate(x, y + 1, sudoku);
        }
        int i, j;
        char check[10];
        memset(check, 0, 10);
        for (i = 0; i < y; i++) check[sudoku[x][i]] = 1;
        for (i = 0; i < x; i++) check[sudoku[i][y]] = 1;
        for (i = x / 3 * 3; i <= x; i++) {
            if (i == x) for (j = y / 3 * 3; j < y; j++) check[sudoku[i][j]] = 1;
            else for (j = y / 3 * 3; j < y / 3 * 3 + 3; j++) check[sudoku[i][j]] = 1;
        }
        int flag = 0;
        for (i = 1; i <= 9 && flag == 0; i++) {
            if (check[i] == 0) {
                flag = 1;
                sudoku[x][y] = i;
                if (y == 8 && x != 8) {
                    if (DFSCreate(x + 1, 0, sudoku)) return 1;
                    else flag = 0;
                }
                else if (y != 8) {
                    if (DFSCreate(x, y + 1, sudoku)) return 1;
                    else flag = 0;
                }
            }
        }
        if (flag == 0) {
            sudoku[x][y] = 0;
            return 0;
        }
    }
    return 1;
}

void CreateSudoku(void) {
    memset(sudoku1, 0, sizeof(sudoku1));
    memset(sudoku2, 0, sizeof(sudoku2));
    int i, j;
    srand((unsigned)time(NULL));
    for (i = 0; i < 9; i++) {
        sudoku1[0][i] = rand() % 9 + 1;
        for (j = 0; j < i;) {
            if (sudoku1[0][j] == sudoku1[0][i]) {
                sudoku1[0][i] = rand() % 9 + 1;
                j = 0;
            }
            else j++;
        }
    }
    DFSCreate(1, 0, sudoku1);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            sudoku2[i][j] = sudoku1[i + 6][j + 6];
        }
    }
    DFSCreate(0, 3, sudoku2);
}

void Dighole1(int hole) {
    int i, j, k, l, flag;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            start1[i][j] = sudoku1[i][j];
        }
    }
    int a[hole][2];
    srand((unsigned)time(NULL));
    for (i = 0; i < hole; i++) {
        j = rand() % 9;
        k = rand() % 9;
        flag = 0;
        for (l = 0; l < i; l++) {
            if (j == a[l][0] && k == a[l][1]) {
                flag = 1;
            }
        }
        if (flag == 0) {
            start1[j][k] = 0;
            a[i][0] = j;
            a[i][1] = k;
        }
        else i--;
    }
}

void Dighole2(int hole) {
    int i, j, k, l, flag, num = 0;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            start2[i][j] = sudoku2[i][j];
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            start2[i][j] = start1[i + 6][j + 6];
            if (start2[i][j] == 0) num++;
        }
    }
    int a[hole - num][2];
    srand((unsigned)time(NULL));
    for (i = 0; i < hole - num; i++) {
        do {
            j = rand() % 9;
            k = rand() % 9;
        } while (j <= 2 && k <= 2);
        flag = 0;
        for (l = 0; l < i; l++) {
            if (j == a[l][0] && k == a[l][1]) {
                flag = 1;
            }
        }
        if (flag == 0) {
            start2[j][k] = 0;
            a[i][0] = j;
            a[i][1] = k;
        }
        else i--;
    }
}

void tocnf(char* fileName, int hole) {
    FILE* fp;
    fp = fopen(fileName, "w");
    int i, j, k, l, m, share = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (start2[i][j] == 0) share++;
        }
    }
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            fprintf(fp, " %d ", sudoku1[i][j]);
        }
        fprintf(fp, "        ");
        for (j = 0; j < 9; j++) {
            fprintf(fp, " %d ", sudoku2[i][j]);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "\n");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            fprintf(fp, " %d ", start1[i][j]);
        }
        fprintf(fp, "        ");
        for (j = 0; j < 9; j++) {
            fprintf(fp, " %d ", start2[i][j]);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "\n");
    fprintf(fp, "p cnf 2999 %d\n", 24300 - hole);
    for (i = 1; i <= 9; i++) {
        for (j = 1; j <= 9; j++) {
            if (start1[i - 1][j - 1] != 0) {
                fprintf(fp, "%d 0\n", 1000 + i * 100 + j * 10 + start1[i - 1][j - 1]);
            }
            if (start2[i - 1][j - 1] != 0) {
                fprintf(fp, "%d 0\n", 2000 + i * 100 + j * 10 + start2[i - 1][j - 1]);
            }
        }
    }
    for (l = 1; l <= 9; l++) {
        for (i = 1; i <= 9; i++) {
            for (k = 1; k <= 9; k++) {
                for (j = i + 1; j <= 9; j++) {
                    fprintf(fp, "-%d -%d 0\n", 1000 + ((l - 1) / 3 * 3 + (i - 1) / 3 + 1) * 100 + ((l - 1) % 3 * 3 + (i - 1) % 3 + 1) * 10 + k, 1000 + ((l - 1) / 3 * 3 + (j - 1) / 3 + 1) * 100 + ((l - 1) % 3 * 3 + (j - 1) % 3 + 1) * 10 + k);
                    fprintf(fp, "-%d -%d 0\n", 2000 + ((l - 1) / 3 * 3 + (i - 1) / 3 + 1) * 100 + ((l - 1) % 3 * 3 + (i - 1) % 3 + 1) * 10 + k, 2000 + ((l - 1) / 3 * 3 + (j - 1) / 3 + 1) * 100 + ((l - 1) % 3 * 3 + (j - 1) % 3 + 1) * 10 + k);
                }
            }
        }
    }
    for (i = 7; i <= 9; i++) {
        for (j = 7; j <= 9; j++) {
            for (k = 1; k <= 9; k++) {
                fprintf(fp, "-%d %d 0\n", 1000 + i * 100 + j * 10 + k, 2000 + (i - 6) * 100 + (j - 6) * 10 + k);
                fprintf(fp, "%d -%d 0\n", 1000 + i * 100 + j * 10 + k, 2000 + (i - 6) * 100 + (j - 6) * 10 + k);
            }
        }
    }
    for (i = 1; i <= 9; i++) {
        for (j = 1; j <= 9; j++) {
            for (k = 1; k <= 9; k++) {
                for (l = j + 1; l <= 9; l++) {
                    fprintf(fp, "-%d -%d 0\n", 1000 + i * 100 + j * 10 + k, 1000 + i * 100 + l * 10 + k);
                    fprintf(fp, "-%d -%d 0\n", 1000 + j * 100 + i * 10 + k, 1000 + l * 100 + i * 10 + k);
                    fprintf(fp, "-%d -%d 0\n", 2000 + i * 100 + j * 10 + k, 2000 + i * 100 + l * 10 + k);
                    fprintf(fp, "-%d -%d 0\n", 2000 + j * 100 + i * 10 + k, 2000 + l * 100 + i * 10 + k);
                }
            }
        }
    }
    for (i = 1; i <= 9; i++) {
        for (k = 1; k <= 9; k++) {
            for (j = 1; j <= 9; j++) {
                fprintf(fp, "%d ", 1000 + i * 100 + j * 10 + k);
            }
            fprintf(fp, "0\n");
            for (j = 1; j <= 9; j++) {
                fprintf(fp, "%d ", 1000 + j * 100 + i * 10 + k);
            }
            fprintf(fp, "0\n");
            for (j = 1; j <= 9; j++) {
                fprintf(fp, "%d ", 2000 + i * 100 + j * 10 + k);
            }
            fprintf(fp, "0\n");
            for (j = 1; j <= 9; j++) {
                fprintf(fp, "%d ", 2000 + j * 100 + i * 10 + k);
            }
            fprintf(fp, "0\n");
        }
    }
    for (l = 1; l <= 9; l++) {
        for (i = 1; i <= 3; i++) {
            for (j = 1; j <= 3; j++) {
                for (k = 1; k <= 9; k++) {
                    fprintf(fp, "%d ", 1000 + ((l - 1) / 3 * 3 + i) * 100 + ((l - 1) % 3 * 3 + j) * 10 + k);
                }
                fprintf(fp, "0\n");
                for (k = 1; k <= 9; k++) {
                    fprintf(fp, "%d ", 2000 + ((l - 1) / 3 * 3 + i) * 100 + ((l - 1) % 3 * 3 + j) * 10 + k);
                }
                fprintf(fp, "0\n");
            }
        }
    }
    for (i = 1; i <= 9; i++) {
        for (j = 1; j <= 9; j++) {
            for (k = 1; k <= 9; k++) {
                fprintf(fp, "%d ", 1000 + i * 100 + j * 10 + k);
            }
            fprintf(fp, "0\n");
            for (k = 1; k <= 9; k++) {
                fprintf(fp, "%d ", 2000 + i * 100 + j * 10 + k);
            }
            fprintf(fp, "0\n");
        }
    }
    for (i = 1; i <= 9; i++) {
        for (j = 1; j <= 9; j++) {
            for (k = 1; k <= 9; k++) {
                for (l = k + 1; l <= 9; l++) {
                    fprintf(fp, "-%d -%d 0\n", 1000 + i * 100 + j * 10 + k, 1000 + i * 100 + j * 10 + l);
                    fprintf(fp, "-%d -%d 0\n", 2000 + i * 100 + j * 10 + k, 2000 + i * 100 + j * 10 + l);
                }
            }
        }
    }
    fclose(fp);
}

int Save_sudoku(char* fileName, int* val) {
    FILE* fp;
    int i, j, k;
    for (i = 0; fileName[i] != '\0'; i++) {
        if (fileName[i] == '.') {
            fileName[i + 1] = 'r';
            fileName[i + 2] = 'e';
            fileName[i + 3] = 's';
            break;
        }
    }
    fp = fopen(fileName, "w");
    fprintf(fp, "Answer:\n");
    for (i = 1; i <= 9; i++) {
        if (i < 7) {
            for (j = 1; j <= 9; j++) {
                if (start1[i - 1][j - 1] != 0) fprintf(fp, "%d ", start1[i - 1][j - 1]);
                else {
                    for (k = 1; k <= 9; k++) {
                        if (val[1000 + i * 100 + j * 10 + k] == 1) fprintf(fp, "%d ", k);
                    }
                }
                if (j % 3 == 0) fprintf(fp, "   ");
            }
            fprintf(fp, "\n");
        }
        else {
            for (j = 1; j < 7; j++) {
                if (start1[i - 1][j - 1] != 0) fprintf(fp, "%d ", start1[i - 1][j - 1]);
                else {
                    for (k = 1; k <= 9; k++) {
                        if (val[1000 + i * 100 + j * 10 + k] == 1) fprintf(fp, "%d ", k);
                    }
                }
                if (j % 3 == 0) fprintf(fp, "   ");
            }
            for (j = 1; j <= 9; j++) {
                if (start2[i - 7][j - 1] != 0) fprintf(fp, "%d ", start2[i - 7][j - 1]);
                else {
                    for (k = 1; k <= 9; k++) {
                        if (val[2000 + i * 100 + j * 10 + k] == 1) fprintf(fp, "%d ", k);
                    }
                }
                if (j % 3 == 0) fprintf(fp, "   ");
            }
            fprintf(fp, "\n");
        }
        if (i % 3 == 0) fprintf(fp, "\n");
    }
    for (i = 4; i <= 9; i++) {
        fprintf(fp, "                        ");
        for (j = 1; j <= 9; j++) {
            if (start2[i - 1][j - 1] != 0) fprintf(fp, "%d ", start2[i - 1][j - 1]);
            else {
                for (k = 1; k <= 9; k++) {
                    if (val[2000 + i * 100 + j * 10 + k] == 1) fprintf(fp, "%d ", k);
                }
            }
            if (j % 3 == 0) fprintf(fp, "   ");
        }
        fprintf(fp, "\n");
        if (i % 3 == 0) fprintf(fp, "\n");
    }
    fclose(fp);
    return 1;
}

void play(int flag, int* val) {
    int i, j, k, x, num;
    char s[10];
    while (flag) {
        system("cls");
        flag = 0;
        for (i = 1; i <= 9; i++) {
            if (i < 7) {
                for (j = 1; j <= 9; j++) {
                    printf("%d ", start1[i - 1][j - 1]);
                    if (j % 3 == 0) printf("  ");
                    if (start1[i - 1][j - 1] == 0) flag = 1;
                }
                printf("\n");
            }
            else {
                for (j = 1; j < 7; j++) {
                    printf("%d ", start1[i - 1][j - 1]);
                    if (j % 3 == 0) printf("  ");
                    if (start1[i - 1][j - 1] == 0) flag = 1;
                }
                for (j = 1; j <= 9; j++) {
                    printf("%d ", start2[i - 7][j - 1]);
                    if (j % 3 == 0) printf("  ");
                    if (start2[i - 7][j - 1] == 0) flag = 1;
                }
                printf("\n");
            }
            if (i % 3 == 0) printf("\n");
        }
        for (i = 4; i <= 9; i++) {
            printf("                ");
            for (j = 1; j <= 9; j++) {
                printf("%d ", start2[i - 1][j - 1]);
                if (j % 3 == 0) printf("  ");
                if (start2[i - 1][j - 1] == 0) flag = 1;
            }
            printf("\n");
            if (i % 3 == 0) printf("\n");
        }
        printf("Please enter the Sudoku serial number (1 in the upper left and 2 in the lower right), row sequence, column sequence, and fill in the numbers:\n");
        scanf("%d%d%d%d", &k, &i, &j, &x);
        if (k != 1 && k != 2 && (i < 1 || i>9) && (j < 1 || j>9) || (x < 1 || x>9)) printf("Error\n");
        num = k * 1000 + i * 100 + j * 10 + x;
        if (k == 1 && start1[i - 1][j - 1] != 0) {
            printf("Cannot be empty!\n");
            continue;
        }
        if (k == 2 && start2[i - 1][j - 1] != 0) {
            printf("Cannot be empty!\n");
            continue;
        }
        if (val[num] == 1) {
            printf("Correct\n");
            if (k == 1) start1[i - 1][j - 1] = x;
            else start2[i - 1][j - 1] = x;
        }
        else {
            printf("Wrong\n");
        }
        printf("Continue to play? YES or NO\n");
        scanf("%s", s);
        if (strcmp(s, "NO") == 0) return;
    }
    printf("End! Good Game!\n");
}
