#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define len 60000000 //�ڴ濽������Ϊ 60000000
char src[len], dst[len]; //Դ��ַ��Ŀ�ĵ�ַ
long int len1 = len; extern void memorycopy(char* dst, char* src, long int len1); //�����ⲿ����
int main()
{
    struct timespec t1, t2; //�����ʼ�����ʱ��
    int i, j;
    //Ϊ��ʼ��ַ�θ�ֵ���Ա�����Ӹõ�ַ�ζ�ȡ���ݿ���
    for (i = 0; i < len - 1; i++)
    {
        src[i] = 'a';
    }
    src[i] = 0;
    clock_gettime(CLOCK_MONOTONIC, &t1); //���㿪ʼʱ�䡣
    memorycopy(dst, src, len1); //�����ã�ִ����Ӧ����Ρ�
    clock_gettime(CLOCK_MONOTONIC, &t2); //�������ʱ�䡣
    //�ó�Ŀ�����ε�ִ��ʱ�䡣
    printf("memorycopy time is %11u ns\n", t2.tv_nsec - t1.tv_nsec);
    return 0;
}