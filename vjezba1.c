#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define FILE_DIDNT_OPEN (-1)
#define PROGRAME_FINISHED (0)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define MAX_NAME (50)

typedef struct {
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int bodovi;
}student;

int CountStudentsFromFile(char *filename);
int CountPointsFromFile(char* filename, student *s);
void GetStudentsInformation(char* filename, student* s, int n, int Maxbr);

int main(void) {

	char filename[MAX_FILE_NAME] = { 0 };
	student* s;
	int Maxbr=0, Brstud=0;

	printf("Insert filename > ");
	scanf(" %s", filename);

	s = (student*)malloc(CountStudentsFromFile(filename) * sizeof(student));

	printf("Broj studenata u datoteci %s je %d.\n", filename, CountStudentsFromFile(filename));
	
	Brstud = CountStudentsFromFile(filename);
	Maxbr = CountPointsFromFile(filename, s);

	GetStudentsInformation(filename, s, Brstud, Maxbr);
	
	return PROGRAME_FINISHED;
}

int CountStudentsFromFile(char *filename) {

	FILE* fp = NULL;
	int count = 0;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen(filename, "r");

	if (fp == NULL) {

		printf("Dear costumer, the file %s did not open!\r\n", filename);
		exit( FILE_DIDNT_OPEN);
	}

	while (!feof(fp)) {

		fgets(buffer, MAX_LINE, fp);

		if (strcmp("\n", buffer) != 0) {
			count++;
		}
	}

	fclose(fp);

	return count;
}

int CountPointsFromFile(char* filename, student* s) {

	FILE* fp;
	int i, points = 0;

	fp = fopen(filename, "r");

	for (i = 0; i < CountStudentsFromFile(filename); i++) {

		fscanf(fp, "%s %s %d", s[i].ime, s[i].prezime, &s[i].bodovi);
		points += s[i].bodovi;
	}

	fclose(fp);

	return points;
}

void GetStudentsInformation(char* filename, student* s, int n, int Maxbr) {

	FILE* fp;
	int i;
	float relativni_bodovi;
	
	fp = fopen(filename, "r");
	
	for (i = 0; i < n; i++) {

		fscanf(fp, "%s %s %d", s[i].ime, s[i].prezime, &s[i].bodovi);
	}

	for (i = 0; i < n; i++) {

		relativni_bodovi = ((float)s[i].bodovi / Maxbr) * 100;
		printf("Ime: %s\tPrezime: %s\t Broj bodova: %d\tBroj relativnih bodova: %.2f", s[i].ime, s[i].prezime, s[i].bodovi, relativni_bodovi);
		printf("\n");
	}

	fclose(fp);
}
