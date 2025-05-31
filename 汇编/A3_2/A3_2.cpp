#include <stdio.h>
#include <string.h>

struct SAMPLES {
	int SDA;
	int SDB;
	int SDC;
	int SF;
	char SAMID[9];
};

//paste data
extern "C" void pdata(SAMPLES * ss) {
	SAMPLES * cls = (SAMPLES*) ss;
	printf_s("123");
	scanf_s("%s", cls->SAMID, 9);
	scanf_s("%d%d%d", &(cls->SDA), &(cls->SDB), &(cls->SDC));
}

//exit option
//R=redo
//Q=quit
//m=input data
//default=prompt warning
extern "C" void exitop(SAMPLES * ss, int* n) {
	char exitop;
	printf_s("Press \"R\" to repeat or Press \"Q\" to exit.\n");
	scanf_s("%c", &exitop, 1);
	switch (exitop) {
	case'Q':
		*n = 0;
		break;
	case'R':
		*n = 1;
		break;
	case'M':
		pdata(ss);
		*n = -1;
		break;
	default:
		*n = -1;
		break;
	}
}

extern "C" void printMID(SAMPLES * ss, int n) {
	n /= 25;
	for (int i = 0; i <= n; i++) {
		printf("SAMID: %s\n", ss[i].SAMID);
		printf("SDA: %d\n", ss[i].SDA);
		printf("SDB: %d\n", ss[i].SDB);
		printf("SDC: %d\n", ss[i].SDC);
		printf("SF: %d\n", ss[i].SF);
	}
}

extern "C" void stringcmp(char* value1, char* value2, char* n) {
	for (int i = 0; i < 3; i++) {
		printf_s("USERNAME (not more than 10 words):\n");
		scanf_s("%s", value1, 11);
		printf("PASSWORD (not more than 10 words):\n");
		scanf_s("%s", value2, 11);
		int username = strcmp(value1, "HUST");
		int password = strcmp(value2, "hust");
		if (username == 0 && password == 0) {
			*n = -1;
			return;
		}
		printf_s("Incorrect input, Please Try Again!'");
	}
	*n = 0;
}