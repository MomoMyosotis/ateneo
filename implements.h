#ifndef IMPLEMENTS_H
#define IMPLEMENTS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 260 righe (implements.h e main.c)

#define CFU_TOT 180
#define INIT_AVG 0

typedef struct Scores {		// relazione tra studente e voto in un corso
	int CFU;				// 12 || 6 || 3
	int score;				// voto in 30esimi
	char* C_code;			// codice del corso
	char* matrix;			// matricola dello studente1
	struct Score* next;		// puntatore al prossimo elemento della lista

} Scr;

typedef struct Major {
	int Tot_C;		// n corsi totali
	char M_code[4];
	char M_name[21];
	char** matrix;  // array dinamico della lista delle matricole iscritte
	char** courses; // Array dinamico di stringhe (codici dei corsi)
} Mjr;

typedef struct Course {

	int CFU;
	char C_code[6];
	char C_name[21];
	char** matrix; 	// array dinamico della lista delle matricole iscritte
	char** M_code;	// più Major possono avere lo stesso corso

} Crs;

typedef struct Student {

	char D_nascita[7];
	char D_iscrizione[7];
	char matrix[9];			// 8 + terminatore di stringa
	char S_name[21];
	char S_surname[21];
	char M_code[4];			// 5 + terminatore di stringa major code
} Std;


//______________________________________________

extern const char* male_names[];
extern const char* female_names[];
extern const char* degree_programs[];
extern const char* courses[];

//______________________________________________

void Print_Menu();
void clear_input_buffer();
void REGISTER(char type);
void SEARCH(char type);
void SEARCH_ENGINE(char type, char search_type, void* data);
void RM(char type);
void C_DATA(char type);
void Score(char type);
void LIST(char type);
void INIT(char type, void* data);
void V_DATA(char type, void* data);
void SAVE_DATA(char type, void* data);
void LOAD_DATA(char type, void* data);

// Funzioni per inizializzare strutture
Mjr* init_major(const char* code, const char* name, int tot_c);
Crs* init_course(const char* code, const char* name, int cfu);
Std* init_student(const char* name, const char* surname, const char* matrix, const char* m_code, const char* iscrizione, const char* nascita);
Scr* init_score(int* cfu, int* voto, const char* c_code, const char* s_code);

#endif /* IMPLEMENTS_H */