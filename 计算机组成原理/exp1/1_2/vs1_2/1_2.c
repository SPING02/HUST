#include<stdio.h>
int main(void)
{
	unsigned char temp[1000];
	printf("Please Key In:\n");
	scanf("%s", temp);
	printf("\nnational standard code by section position:\n");
	int i;
	for (i = 0; temp[i] != '\0'; i++)
	{
		printf("%.2x", temp[i]);
		if ((i + 1) % 16 == 0) printf("\n");
		else if ((i + 1) % 8 == 0) printf("  ");
		else if ((i + 1) % 2 == 0) printf(" ");
		else continue;
	}
	return 0;
}