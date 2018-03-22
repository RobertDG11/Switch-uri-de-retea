/* DELIU Robert-Gabriel - 312CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define LENS(a) (((ASt)(a))->length)	/*Returneaza lungimea stivei*/

#define EMPTYS(a)	(LENS(a) == 0)	/*Verifica daca stiva e goala*/

#define LENQ(a)  (((AQ)(a))->length)	/*Returneaza lungimea cozii*/

#define EMPTYQ(a)	(LENQ(a) == 0)	/*Verifica daca coada e goala*/

typedef struct celulag
{ 
  void* info;         
  struct celulag *urm; 
} TCelulaG, *TLG, **ALG;

typedef struct
{
	int id;
	char *denumire;
	char *IPv4;
	char *mod_functionare;
	int principal; /* este 0 daca switch-ul este principal si 1 daca este secundar*/
} TSwitch;

typedef struct stiva
{
	TLG vf; //varful stivei
	int length;
} TStiva, *ASt;

typedef struct coada
{
	TLG first, last; /*Extremitatile cozii*/
	int length;
} TCoada, *AQ;

typedef struct vector_stive
{
	ASt *vector;
	int length;
} TVectorStive, *TVS, **AVS;

typedef void (*TFAfi)(void*, char*, FILE*);

/*Initializare stiva*/
ASt InitS();
/*Eliberare stiva*/
void FreeS(ASt s);
/*Introduce un element in stiva*/
void Push(ASt s, void *info);
/*Scoate un element din stiva*/
void *Pop(ASt s, void *info);
/*Initializare coada*/
AQ InitQ();
/*Eliberare coada*/
void FreeCoada(AQ coada);
/*Extrage primul element din coada(c->first)*/
void *PrimQ(AQ c, void *info);
/*Introduce un element in coada*/
void IntrQ(AQ c, void *info);
/*Extrage un element din coada*/
void *ExtrQ(AQ c, void *info);
/*Functie de afisare element generic*/ 
void AfiEntry(void *ae, char *type, FILE *f);
/*Afiseaza stiva*/
void AfisareS(ASt s, TFAfi afiEL, FILE *f);
/*Afiseaza coada*/
void AfisareQ(AQ c, TFAfi afiEL, FILE *f);
/*Aloca un vector de stive*/
TVS AlocaVectorStive(int length);
/*Elibereaza vectorul de stive*/
void FreeVectorStive(TVS vector_stive);
/*Adauga un switch in coada*/
void add_coada(int id, char *denumire, char *IPv4, char *mod_functionare, AQ coada);
/*Adauga un switch in stiva*/
void add_stiva(int id, char *denumire, char *IP, char *mod_functionare, int id_stiva, char *principal, TVS vector_stive);
/*Sterge un element din stiva*/
void del_stiva(int id, TVS vector_stive, AQ coada);
/*Sterge un element din coada*/
void del_coada(int id, AQ coada);
/*Pune elementul de id "id" in stiva*/
void set_stiva(int id, char *mod_functionare, int id_stiva, char *principal, TVS vector_stive, AQ coada);
/*Pune elementul de id "id" in coada*/
void set_coada(int id, char *mod_functionare, TVS vector_stive, AQ coada);
/*Face converia din IP in numar in baza 10*/
unsigned long int convert(char *IPv4);
/*Afiseaza ipul minim din coada(Prim(coada))*/
void ipmin(AQ coada, FILE *f);
/*Afiseaza vectorul de stive si coada*/
void show(TVS vector_stive, AQ coada, FILE *f);