/* DELIU Robert-Gabriel - 312CB */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tema2.h"

ASt InitS() 
{
	ASt S = (ASt)malloc(sizeof(TStiva)); //alocare memorie
	S->vf = NULL;
	S->length = 0;
	return S;
} 

void FreeS(ASt s) 
{	
	if(EMPTYS(s)) {
		free(s); /*Daca stiva este goala elibereaza memoria alocata
					pentru un element de tip ASt*/
		return;
	}

	while(!EMPTYS(s)) {
		TSwitch *aux = Pop(s, aux); /*Extrage cate un element
											si il elibereaza*/

		free(aux->denumire);
		free(aux->IPv4);
		free(aux->mod_functionare);

		free(aux);
	}
	s->vf = NULL;
	free(s);

}

void Push(ASt s, void *info) 
{
	TLG aux = (TLG)malloc(sizeof(TCelulaG)); /*Initializeaza o celula*/
	aux->info = malloc(sizeof(TSwitch));
	TSwitch *data = (TSwitch*)info; /*Casteaza informatia la tipul TSwitch*/
	TSwitch *p = (TSwitch*)aux->info;

	p->id = data->id;
	p->denumire = strdup(data->denumire);  /*Copiaza informatiile*/
	p->IPv4 = strdup(data->IPv4);
	p->mod_functionare = strdup(data->mod_functionare);
	p->principal = data->principal;

	aux->urm = s->vf; /*Ataseaza celula la stiva,
						modifica varful stivei si
						creste lungimea*/
	s->vf = aux;
	s->length++;

}

void *Pop(ASt s, void *info) 
{
	if(!EMPTYS(s)) {
		TLG aux = s->vf;
		TSwitch *p = (TSwitch*)aux->info;
		TSwitch *data = (TSwitch*)info;
		data = malloc(sizeof(TSwitch));

		data->id = p->id;
		data->denumire = strdup(p->denumire);
		data->IPv4 = strdup(p->IPv4);
		data->mod_functionare = strdup(p->mod_functionare);
		data->principal = p->principal;

		s->vf = aux->urm;
		free(p->denumire); /*elibereaza pointerul alocat pentru a 
							extrage informatia din varful stivei*/
		free(p->IPv4);
		free(p->mod_functionare);
		free(p);
		free(aux);


		s->length--;
		return data;
	}
	return 0;
}

void AfiEntry(void * ae, char *type, FILE *f)  
{
	TSwitch *p = (TSwitch*)ae;
	if(strcmp(type, "stiva") == 0) {
		fprintf(f, "%d %s %s\n", p->id, p->IPv4, p->denumire);
 	}
 	else {
 		fprintf(f, "%d ", p->id);
 	}
}

void AfisareS(ASt s, TFAfi afiEL, FILE *f) 
{
	ASt s_aux = InitS();

	if(EMPTYS(s)) {
		free(s_aux);
		return;
	}

	while(!EMPTYS(s)) {
		TSwitch *aux = Pop(s, aux); /*Extrage un element, il pune intr-o stiva 
									auxiliara si apoi il afiseaza in fiser 
									folosind AfiEntry*/
		afiEL(aux, "stiva", f);
		Push(s_aux, aux);

		free(aux->denumire);
		free(aux->IPv4);
		free(aux->mod_functionare);
		free(aux);
	}

	while(!EMPTYS(s_aux)) {
		TSwitch *aux = Pop(s_aux, aux);

		Push(s, aux);
		free(aux->denumire);
		free(aux->IPv4);
		free(aux->mod_functionare);
		free(aux);

		
	}
	FreeS(s_aux);
}

AQ InitQ()
{
	AQ C = (AQ)malloc(sizeof(TCoada)); //Aloca memorie

	C->first = NULL;
	C->last = NULL;
	C->length = 0;

	return C;
}

void FreeCoada(AQ coada)
{
	if(EMPTYQ(coada)) {
		free(coada);
		return;
	}

	while(!EMPTYQ(coada)) {
		TSwitch *aux = ExtrQ(coada, aux);

		free(aux->denumire);
		free(aux->IPv4);
		free(aux->mod_functionare);

		free(aux);
	}
	coada->first = NULL;
	coada->last = NULL;
	free(coada);
}

void *PrimQ(AQ c, void *info)
{
	if(!EMPTYQ(c)) {
		TLG aux = c->first;
		TSwitch *p = (TSwitch*)aux->info;
		TSwitch *data = (TSwitch*)info;
		data = malloc(sizeof(TSwitch));

		data->id = p->id;
		data->denumire = strdup(p->denumire);
		data->IPv4 = strdup(p->IPv4);
		data->mod_functionare = strdup(p->mod_functionare);
		data->principal = p->principal;

		return data;
	}

	return 0;
}

void IntrQ(AQ c, void *info)
{
	TLG aux = (TLG)malloc(sizeof(TCelulaG)); /*Initializeaza o celula*/
	aux->info = malloc(sizeof(TSwitch));
	TSwitch *data = (TSwitch*)info;  /*Casteaza informatia la tipul TSwitch*/
	TSwitch *p = (TSwitch*)aux->info;

	p->id = data->id;
	p->denumire = strdup(data->denumire);
	p->IPv4 = strdup(data->IPv4);	/*Copiaza informatia in celula*/
	p->mod_functionare = strdup(data->mod_functionare);
	p->principal = data->principal;
	/*Modifica extremitatile cozii*/
	if(EMPTYQ(c)) {
		c->first = aux;
	}
	else {
		c->last->urm = aux;
	}

	c->last = aux;
	c->length++;

}

void *ExtrQ(AQ c, void *info)
{
	if(!EMPTYQ(c)) {
		TLG aux = c->first;
		TSwitch *p = (TSwitch*)aux->info;
		TSwitch *data = (TSwitch*)info;
		data = malloc(sizeof(TSwitch));

		data->id = p->id;
		data->denumire = strdup(p->denumire);
		data->IPv4 = strdup(p->IPv4);
		data->mod_functionare = strdup(p->mod_functionare);
		data->principal = p->principal;

		c->first = aux->urm;
		free(p->denumire);
		free(p->IPv4);
		free(p->mod_functionare);
		free(p);
		free(aux);
		
		c->length--;
		

		return data;
	}

	return 0;
}

void AfisareQ(AQ c, TFAfi afiEL, FILE *f)
{
	AQ c_aux = InitQ();
	fprintf(f, "{");

	while(!EMPTYQ(c)) {
		TSwitch *aux = ExtrQ(c, aux);
		afiEL(aux, "coada", f);
		IntrQ(c_aux, aux);

		free(aux->denumire);
		free(aux->IPv4);
		free(aux->mod_functionare);

		free(aux);
	} 

	while(!EMPTYQ(c_aux)) {
		TSwitch *aux = ExtrQ(c_aux, aux);
		
		IntrQ(c, aux);
		free(aux->denumire);
		free(aux->IPv4);
		free(aux->mod_functionare);

		free(aux);
	} 

	FreeCoada(c_aux);

	fprintf(f, "}\n");
}	

void show(TVS vector_stive, AQ coada, FILE *f)
{
	AfisareQ(coada, AfiEntry, f);
	int i, l = vector_stive->length;

	for(i = 0; i < l; i++) {
		ASt stiva = vector_stive->vector[i];
		fprintf(f, "%d:\n", i);
		AfisareS(stiva, AfiEntry, f);	

	}

	fprintf(f, "\n");

}

TVS AlocaVectorStive(int length)
{
	TVS vector_stive = NULL;
	int i;

	vector_stive = (TVS)malloc(sizeof(TVectorStive)); /*Aloca memorie pentru structura*/
	vector_stive->length = length;
	vector_stive->vector = malloc(sizeof(ASt) * length);/*Aloca memorie pentru
														 campul vector*/

	for(i = 0; i < length; i++) {
		vector_stive->vector[i] = InitS();
	}

	return vector_stive;

}

void FreeVectorStive(TVS vector_stive)
{
	int i, length = vector_stive->length;
	for(i = 0; i < length; i++) {
		FreeS(vector_stive->vector[i]);
	}

	free(vector_stive->vector);
	free(vector_stive);
	vector_stive = NULL;
}


void add_stiva(int id, char *denumire, char *IP, char *mod_functionare, int id_stiva, char *principal, TVS vector_stive)
{
	ASt stiva = vector_stive->vector[id_stiva];

	TSwitch *elem = malloc(sizeof(TSwitch)); /*Initializeaza elementul care
												trebuie inserat*/
		elem->id = id;
		elem->denumire = strdup(denumire);
		elem->IPv4 = strdup(IP);
		elem->mod_functionare = strdup(mod_functionare);
		elem->principal = 0;

	if(EMPTYS(stiva)) { /*Cazul 1, daca stiva este goala il insereaza
						pe prima pozitie, deci este baza*/

		Push(stiva, elem);

		free(elem->denumire);
		free(elem->IPv4);
		free(elem->mod_functionare); /*Elibereaza memoria folosita pentru
										a extrage un element*/
		free(elem);
			
		return;
	}
	/*Cazul 2, daca stiva are doar un element(baza) si este introdus un
	  element secundar il pune in continuarea stivei. Daca este introdus
	  un alt switch principal, il pune pe acesta la baza, iar vechea baza
	  devine urmatorul element in stiva*/
	else if(stiva->length == 1) {
		if(strcmp(principal, "NON_BASE") == 0) {
			
			elem->principal = 1;
				
			Push(stiva, elem);
			free(elem->denumire);
			free(elem->IPv4);
			free(elem->mod_functionare);
			free(elem);
			return;
		}	

		else {
			TSwitch *aux = Pop(stiva, aux);

			Push(stiva, elem);

			free(elem->denumire);
			free(elem->IPv4);
			free(elem->mod_functionare);
			free(elem);

			aux->principal = 1;

			Push(stiva, aux);

			free(aux->denumire);
			free(aux->IPv4);
			free(aux->mod_functionare);
			free(aux);

			return;
		}
	}
	/*Cazul 3: stiva are cel putin 2 elemente. Aici sunt inca 2 cazuri:
	A, este introdus un switch principal, in cazul acesta switchul este
	pus in stiva la locul lui(ordonat descrescator dupa id de la baza spre
	varf) si cazul B in care switchul care trebuie introdus este principal.
	In acest caz se inlocuieste baza stivei si vechea baza va fi pusa inapoi
	in stiva dupa regula descrisa mai sus*/
	else if(stiva->length > 1) {
		ASt s_aux = InitS();
		if(strcmp(principal, "NON_BASE") == 0) {
			
			int found = 0;

			while(stiva->length > 1) { /*Scoate toate elementele din stiva
										mai putin baza */
				TSwitch *aux = Pop(stiva, aux);

				Push(s_aux, aux);

				free(aux->denumire);
				free(aux->IPv4);
				free(aux->mod_functionare);
				free(aux);
			}

			elem->principal = 1; 

			while(!EMPTYS(s_aux)) {
				TSwitch *temp = Pop(s_aux, temp);

				if(elem->id > temp->id && found != 1) {
					/*Daca switchul care trebuie inserat are id-ul mai mare
						decat switchul scos din stiva auxiliara il pune pe
						acesta in stiva principala, iar pe cel din urma
						inapoi in stiva auxiliara*/
					Push(stiva, elem);
					Push(s_aux, temp);

					found = 1;
				}

				else {
					Push(stiva, temp);
				}

				free(temp->denumire);
				free(temp->IPv4);
				free(temp->mod_functionare);
				free(temp);
				
			}
			/*Daca elementul care trebuie inserat in stiva este mai mic
				decat toate celelalte elemente deja existente, il pune
				pe acesta in varful stivei*/
			if(found == 0) {
				Push(stiva, elem);
				
			}

			free(elem->denumire);
			free(elem->IPv4);
			free(elem->mod_functionare);
			free(elem);
			FreeS(s_aux);
			
			return;

		}

		else {
			
			int gasit = 0;

			while(!EMPTYS(stiva)) {
				TSwitch *aux = Pop(stiva, aux);

				Push(s_aux, aux);
				free(aux->denumire);
				free(aux->IPv4);
				free(aux->mod_functionare);
				free(aux);
			}

			Push(stiva, elem);
			free(elem->denumire);
			free(elem->IPv4);
			free(elem->mod_functionare);
			free(elem);

			TSwitch *old_base = Pop(s_aux, old_base);
			old_base->principal = 1;

			while(!EMPTYS(s_aux)) {
				TSwitch *temp = Pop(s_aux, temp);

				if(old_base->id > temp->id && gasit != 1) {

					Push(stiva, old_base);
					Push(s_aux, temp);

					gasit = 1;
					
				}
				else {
					Push(stiva, temp);

				}
				free(temp->denumire);
				free(temp->IPv4);
				free(temp->mod_functionare);
				free(temp);
			}
			
			if(gasit == 0) {
				Push(stiva, old_base);
				
			}

			free(old_base->denumire);
			free(old_base->IPv4);
			free(old_base->mod_functionare);
			free(old_base);

			FreeS(s_aux);
		}
	} 
}

void add_coada(int id, char *denumire, char *IP, char *mod_functionare, AQ coada)
{

	TSwitch *elem = malloc(sizeof(TSwitch));
	elem->id = id;
	elem->denumire = strdup(denumire);
	elem->IPv4 = strdup(IP);
	elem->mod_functionare = strdup(mod_functionare);
	elem->principal = 0;

	if(EMPTYQ(coada)) { /*Daca este goala, pune direct elementul in coada*/

		IntrQ(coada, elem);

		free(elem->denumire);
		free(elem->IPv4);
		free(elem->mod_functionare);
		free(elem);

		return;
	}
	/*Daca are cel putin un element, scoate elementele din coada,
	le pune intr-o noua coada si apoi le insereaza inapoi in vechea
	coada, crescator in functie de IP*/
	else {
		AQ c_aux = InitQ();
		int found = 0;
		while(!EMPTYQ(coada)) {
			TSwitch *temp = ExtrQ(coada, temp);
			IntrQ(c_aux, temp);

			free(temp->denumire);
			free(temp->IPv4);
			free(temp->mod_functionare);
			free(temp);

		}

		while(!EMPTYQ(c_aux)) {
			TSwitch *temp = ExtrQ(c_aux, temp);

			if(convert(elem->IPv4) < convert(temp->IPv4) && found != 1) {
				IntrQ(coada, elem);
				IntrQ(coada, temp);

				found = 1;
					
			}
			else {
				IntrQ(coada, temp);
				
			}

			free(temp->denumire);
			free(temp->IPv4);
			free(temp->mod_functionare);
			free(temp);

		}
		
		if(found == 0) {
			IntrQ(coada, elem);
		}

		free(elem->denumire);
		free(elem->IPv4);
		free(elem->mod_functionare);
		free(elem);

		FreeCoada(c_aux);
	}

}

void del_stiva(int id, TVS vector_stive, AQ coada)
{
	int i, found = 0;
	int length = vector_stive->length;
	ASt s_aux = InitS();
	for(i = 0; i < length; i++) {
		ASt stiva = vector_stive->vector[i];
		
		if(EMPTYS(stiva)) {
			continue;
		}
		/*Scoate toate elementele din stiva, mai putin baza, le verifica 
		idul si daca acesta NU este egal cu "id", il insereaza in 
		lista auxiliara*/
		while(stiva->length > 1) {
			TSwitch *aux = Pop(stiva, aux);

			if(aux->id != id) {
				Push(s_aux, aux);
			}
			else {
				found = 1;

			}

			free(aux->denumire);
			free(aux->IPv4);
			free(aux->mod_functionare);
			free(aux);

		}		
		TSwitch *aux = Pop(stiva, aux); /*Scoate baza din stiva*/

		if(aux->id == id) { /*Daca idul bazei nu este egal cu "id",
							insereaza baza in stiva auxiliara*/
			
			found = 1;
		}

		else {
			Push(s_aux, aux);
		}
		/*La final pune inapoi in stiva toate elementele, mai putin cel eliminat*/
		while(!EMPTYS(s_aux)) {
			TSwitch *temp = Pop(s_aux, temp);

			Push(stiva, temp);
			free(temp->denumire);
			free(temp->IPv4);
			free(temp->mod_functionare);
			free(temp);

		}
		free(aux->denumire);
		free(aux->IPv4);
		free(aux->mod_functionare);
		free(aux);

		
		/*Daca a gasit switchul in stiva curenta nu mai cata si in celelalte*/
		if(found == 1) {
			break;
			
		}

	}
	FreeS(s_aux);

}

void del_coada(int id, AQ coada)
{
	AQ c_aux = InitQ();
	/*Algoritmul este identic ca la cel de stergere din stiva*/
	if(EMPTYQ(coada)) {
		FreeCoada(c_aux);
		return;
	}

	while(!EMPTYQ(coada)) {
		TSwitch *aux = ExtrQ(coada, aux);
	
		if (aux->id != id)
		{
			IntrQ(c_aux, aux);
		}

		free(aux->denumire);
		free(aux->IPv4);
		free(aux->mod_functionare);
		free(aux);
	}

	while(!EMPTYQ(c_aux)) {
		TSwitch *temp = ExtrQ(c_aux, temp);

		IntrQ(coada, temp);

		free(temp->denumire);
		free(temp->IPv4);
		free(temp->mod_functionare);
		free(temp);

	}

	FreeCoada(c_aux);
	return;
}

void set_stiva(int id, char *mod_functionare, int id_stiva, char *principal, TVS vector_stive, AQ coada)
{
	int i, found = 0, caz = 0, id_s = 0;
	int length = vector_stive->length;
	TSwitch *elem = malloc(sizeof(TSwitch));
	AQ c_aux = InitQ();
	ASt s_aux = InitS();
	
	for(i = 0; i < length; i++) {
		ASt stiva = vector_stive->vector[i];
		
		if(EMPTYS(stiva)) {
			continue;
		}
		/*Cauta switchul care are idul "id" si daca il gaseste
		pastreaza informatia din el in "elem"*/
		while(!EMPTYS(stiva)) {
			TSwitch *aux = Pop(stiva, aux);

			if(aux->id == id) {
				found = 1;
				id_s = i; //idul stivei in care a fost gasit switchul
				
				elem->denumire = strdup(aux->denumire);
				elem->IPv4 = strdup(aux->IPv4);
				elem->principal = aux->principal;
			}

			Push(s_aux, aux);

			free(aux->denumire);
			free(aux->IPv4);
			free(aux->mod_functionare);
			free(aux);

		}
		while(!EMPTYS(s_aux)) {
			TSwitch *aux = Pop(s_aux, aux);

			Push(stiva, aux);

			free(aux->denumire);
			free(aux->IPv4);
			free(aux->mod_functionare);
			free(aux);

		}
		
		if(found == 1) {
			break;	
		}
		
	}
	FreeS(s_aux);
	/*Cauta switchul si in coada doar daca nu il gaseste in stiva
		(pentru a evita niste alocari si operatii inuile)*/
	if (found == 0) {
		while(!EMPTYQ(coada)) {
			TSwitch *aux = ExtrQ(coada, aux);

			if(aux->id == id) {
				found = 2;

				elem->denumire = strdup(aux->denumire);
				elem->IPv4 = strdup(aux->IPv4);
				elem->principal = aux->principal;
			
			}

			IntrQ(c_aux, aux);

			free(aux->denumire);
			free(aux->IPv4);
			free(aux->mod_functionare);
			free(aux);
		}


		while(!EMPTYQ(c_aux)) {
			TSwitch *aux = ExtrQ(c_aux, aux);
			IntrQ(coada, aux);

			free(aux->denumire);
			free(aux->IPv4);
			free(aux->mod_functionare);
			free(aux);

		}
	}
	/*Cazurile posibile de mutare in stiva, din stiva*/
	if(id_stiva == id_s && strcmp(principal, "BASE") == 0) {
		caz = 1;
	}
	else if(id_stiva == id_s && strcmp(principal, "BASE") != 0) {
		caz = 2;
	}
	else if(id_stiva != id_s && strcmp(principal, "BASE") == 0) {
		caz = 3;
	}
	else if(id_stiva != id_s && strcmp(principal, "BASE") != 0) {
		caz = 4;
	}

	if(found == 1) {
		/*Daca switchul a fost gasit in stiva*/
		if(caz == 1) {
			/*Daca nu era deja element principal il insereaza la locul lui
			si il sterge din vechea pozitie*/
			if(elem->principal != 0) {
				del_stiva(id, vector_stive, coada);
				add_stiva(id, elem->denumire, elem->IPv4, "STACK", id_s, "BASE", vector_stive);
			}
		}
		else if(caz == 2) {
			if(elem->principal != 1) { 
			/*Daca nu era deja element secundar il insereaza la locul lui
			si il sterge din vechea pozitie */
				del_stiva(id, vector_stive,coada);
				add_stiva(id, elem->denumire, elem->IPv4, "STACK", id_s, "NON_BASE", vector_stive);
			}
		}
		else if(caz == 3) {
			/*Muta elementul in noua stiva si si il sterge din vechea stiva*/
			del_stiva(id, vector_stive,coada);
			add_stiva(id, elem->denumire, elem->IPv4, "STACK", id_stiva, "BASE", vector_stive);
		}
		else {
			/*Muta elementul in noua stiva si il sterge din vechea stiva*/
			del_stiva(id, vector_stive, coada);
			add_stiva(id, elem->denumire, elem->IPv4, "STACK", id_stiva, "NON_BASE", vector_stive);
		}

	}
	else {
		/*Daca switchl a fost gasit in coada il sterge de acolo si il muta in stiva*/
		del_coada(id, coada);
		add_stiva(id, elem->denumire, elem->IPv4, "STACK", id_stiva, principal, vector_stive);

		}
	free(elem->denumire);
	free(elem->IPv4);
	free(elem);
	FreeCoada(c_aux);
}

void set_coada(int id, char *mod_functionare, TVS vector_stive, AQ coada)
{
	int i, found = 0;
	int length = vector_stive->length;
	TSwitch *elem = malloc(sizeof(TSwitch));
	ASt s_aux = InitS();
	/*Cauta switchul de id "id"*/
	for(i = 0; i < length; i++) {
		ASt stiva = vector_stive->vector[i];
		
		if(EMPTYS(stiva)) {
			continue;
		}

		while(!EMPTYS(stiva)) {
			TSwitch *aux = Pop(stiva, aux);

			if(aux->id == id) {
				found = 1;
				
				elem->denumire = strdup(aux->denumire);
				elem->IPv4 = strdup(aux->IPv4);
				
			}

			Push(s_aux, aux);

			free(aux->denumire);
			free(aux->IPv4);
			free(aux->mod_functionare);
			free(aux);
		}
		while(!EMPTYS(s_aux)) {
			TSwitch *aux = Pop(s_aux, aux);

			Push(stiva, aux);

			free(aux->denumire);
			free(aux->IPv4);
			free(aux->mod_functionare);
			free(aux);
		}

		if(found == 1) {
			break;	
		}
	}

	FreeS(s_aux);

	if(found == 1) {
		/*Daca il gaseste in stiva, il insereaza in coada si il
			sterge din stiva*/
		del_stiva(id, vector_stive, coada);
	
		add_coada(id, elem->denumire, elem->IPv4, mod_functionare, coada);
		
		free(elem->denumire);
		free(elem->IPv4);
	
	}
	free(elem);
	
}

unsigned long int convert(char *IPv4) 
{

	int a[4], count = 0;
	unsigned long int number = 0;
	char *tok, *dup;
	dup = strdup(IPv4); /*duplicheaza IP-ul pentru a nu-l pierde
						in urma prelucrarii cu strtok*/
	tok = strtok(dup, ".");
	/*Separa stringul in 4 tokene, dupa fiecare punct*/
	while(tok != NULL) {
		a[count] = atoi(tok); /*transforma stringul in integer*/
		count++;
		tok = strtok(NULL, ".");
	}
	/*Calculeaza numarul aferent ip-ului*/
	number = a[0]*256*256*256 + a[1]*256*256 + a[2]*256 + a[3];
	free(dup);
	free(tok);

	return number;

}

void ipmin(AQ coada, FILE *f)
{
	if(EMPTYQ(coada)) {
		fprintf(f, "ipmin=0\n");
		return;
	}
	TSwitch *prim = PrimQ(coada, prim); /*Scoate primul element din coada*/
	unsigned long int number = convert(prim->IPv4); /*Face conversia*/

	free(prim->denumire);
	free(prim->IPv4);
	free(prim->mod_functionare);
	free(prim);

	fprintf(f, "ipmin=%lu\n", number);
}

