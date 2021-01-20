#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#define broj 30
#define size 11

typedef struct student* pokStudent;

typedef struct student
{
	char ime[broj];
	char prezime[broj];
	char mat_broj[broj];
	pokStudent next;

}Student;

typedef struct tablica* pokHash;

typedef struct tablica
{
	pokStudent niz[size];
}Tablica;

int hashFja(char prezime[])
{
	int key=0;
	for (int i = 0; i < 5; i++)
	{
		key = key + prezime[i];
	}
	key = key % size;
	return key;
}

void Izbornik()
{
	printf("--------------------------------\n");
	printf("1.Unos studenta.\n");
	printf("2.Ispis tablice.\n");
	printf("3.Ispis mat. broja.\n");
	printf("0. izlaz\n");
	printf("--------------------------------\n");
}

void Alokacija(pokHash table)
{
	for (int i = 0; i < size; i++)
	{
		table->niz[i] = (pokStudent)malloc(sizeof(Student));
		table->niz[i]->next = NULL;
		strcpy(table->niz[i]->ime, "");
		strcpy(table->niz[i]->prezime, "");
		strcpy(table->niz[i]->mat_broj, "");
	}
}

bool Provjeri(pokHash table, int key)
{
	if (!(strcmp(table->niz[key]->ime, "") && strcmp(table->niz[key]->prezime, "") && strcmp(table->niz[key]->mat_broj, "")))
		return true;
	else
		return false;
}

void UnesiStudenta(pokHash table, char Ime[], char Prezime[], char matBr[], int key)
{
	if (Provjeri(table, key) && table->niz[key]->next == NULL)
	{
		strcpy(table->niz[key]->ime, Ime);
		strcpy(table->niz[key]->prezime, Prezime);
		strcpy(table->niz[key]->mat_broj, matBr);
	}
	else
	{
		pokStudent temp = (pokStudent)malloc(sizeof(Student));
		temp->next = table->niz[key];
		table->niz[key] = temp;
		bool test = false;
		while (temp->next != NULL && !test)
		{
			if (strcmp(temp->next->prezime, Prezime) > 0)
			{
				pokStudent buff = (pokStudent)malloc(sizeof(Student));
				strcpy(buff->ime, Ime);
				strcpy(buff->prezime, Prezime);
				strcpy(buff->mat_broj, matBr);
				buff->next = temp->next;
				temp->next = buff;
				test = true;
			}
			else if (strcmp(temp->next->prezime, Prezime) == 0)
			{
				if (strcmp(temp->next->ime, Ime) >= 0)
				{
					pokStudent buff = (pokStudent)malloc(sizeof(Student));
					strcpy(buff->ime, Ime);
					strcpy(buff->prezime, Prezime);
					strcpy(buff->mat_broj, matBr);
					buff->next = temp->next;
					temp->next = buff;
					test = true;
				}
				else
					temp = temp->next;
			}
			else
				temp = temp->next;
		}
		if (!test)
		{
			pokStudent buff = (pokStudent)malloc(sizeof(Student));
			strcpy(buff->ime, Ime);
			strcpy(buff->prezime, Prezime);
			strcpy(buff->mat_broj, matBr);
			temp->next = buff;
			buff->next = NULL;
		}
		table->niz[key] = table->niz[key]->next;
	}
}

void Ispis(pokHash table)
{
	for (int i = 0; i < size; i++)
	{
		printf("Kljuc %d: \n", i);
		if (!Provjeri(table, i))
		{
			pokStudent temp = (pokStudent)malloc(sizeof(Student));
			temp = table->niz[i];
			while (temp->next != NULL)
			{
				printf("\t%s\t\t%s\n", temp->ime, temp->prezime);
				temp = temp->next;
			}
			printf("\t%s\t\t%s\n", temp->ime, temp->prezime);
		}
		else
		{
			printf("-------------------------------------\n");
		}
	}
}

void IspisiMatBr(pokHash table, char Ime[], char Prezime[])
{
	int key = hashFja(Prezime);
	pokStudent temp = (pokStudent)malloc(sizeof(Student));
	temp = table->niz[key];

	if (Provjeri(table, key) && temp->next == NULL)
		printf("Trazeni student ne postoji!!!\n");
	else
	{
		while (temp->next != NULL)
		{
			if (!(strcmp(temp->ime, Ime) || strcmp(temp->prezime, Prezime)))
			{
				printf("\nStudent %s   %s ima maticni broj %s\n", temp->ime, temp->prezime, temp->mat_broj);
			}
			temp = temp->next;
		}
		if (!(strcmp(temp->ime, Ime) || strcmp(temp->prezime, Prezime)))
			printf("\nStudent %s   %s ima maticni broj %s\n", temp->ime, temp->prezime, temp->mat_broj);
	}

}

int main()
{
	pokHash tablica = (pokHash)malloc(sizeof(Tablica));
	char Ime[broj]="", Prezime[broj]="", mat[broj]="";
	int izbor, key;
	Alokacija(tablica);

	do
	{
		Izbornik();
		scanf("%d", &izbor);
		switch (izbor)
		{
		case 1:
			printf("Unesite ime studenta: ");
			scanf("%s", Ime);
			printf("Unesite prezime studenta: ");
			scanf("%s", Prezime);
			printf("Unesite maticni broj studenta: ");
			scanf("%s", mat);
			key = hashFja(Prezime);
			UnesiStudenta(tablica, Ime, Prezime, mat, key);
			break;
		case 2:
			Ispis(tablica);
			break;
		case 3:
			printf("Unesite ime: ");
			scanf("%s", Ime);
			printf("Unesite prezime: ");
			scanf("%s", Prezime);
			IspisiMatBr(tablica, Ime, Prezime);
			break;
		case 0:
			printf("Dovidenja!!!\n");
			break;
		default:
			printf("Unijeli ste krivi broj!!!\n");
			break;
		}
	} while (izbor!=0);
	

	

	return 0;
}