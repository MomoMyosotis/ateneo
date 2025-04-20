#include "implements.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS


Scr* score_head = NULL;  // Variabile globale per la lista degli score

//          COMPLETE    - inizializza le struct per autoatic fill
const char* male_names[20] = {
    "Luca", "Momo", "Papaya", "Andrea", "Matteo",
    "Alessandro", "Francesco", "Paolo", "Stefano", "Antonio",
    "Giorgio", "Federico", "Roberto", "Carlo", "Davide",
    "Michele", "Simone", "Daniele", "Emanuele", "Vincenzo"
};
const char* female_names[20] = {
    "Maria", "Anna", "Giulia", "Francesca", "Sofia",
    "Monika", "Sara", "Chiara", "Gotichisa", "Valentina",
    "Laura", "Giovanna", "Elena", "Simona", "Silvia",
    "Claudia", "Lisa", "Roberta", "Paola", "Selene"
};
const char* degree_programs[10] = {
    "Bioinformatica", "Matematica", "Fisica", "Biologia", "Chimica",
    "Economia", "Psicologia", "Lettere", "Giurisprudenza", "Scienze Politiche"
};
const char* courses[50] = {
    "Programmazione 1", "Matematica Discreta", "Fisica Generale", "Chimica Generale", "Biologia Cellulare",
    "Algebra Lineare", "Statistica", "Diritto Privato", "Economia Aziendale", "Sociologia",
    "Fisica Applicata", "Reti di Calcolatori", "Teoria dei Numeri", "Biochimica", "Genetica",
    "Calcolo Numerico", "Filosofia", "Analisi Matematica", "Microeconomia", "Macroeconomia",
    "Psicologia Generale", "Geometria", "Diritto Costituzionale", "Contabilità e Bilancio", "Informatica Avanzata",
    "Marketing", "Metodi di Ottimizzazione", "Fisica Statistica", "Ecologia", "Sociologia dei Media",
    "Intelligenza Artificiale", "Machine Learning", "Fondamenti di Economia", "Psicologia Clinica", "Neuroscienze",
    "Ingegneria del Software", "Teoria dei Giochi", "Gestione Aziendale", "Psicologia Sociale", "Sistemi Operativi",
    "Microbiologia", "Filosofia della Scienza", "Teorie della Comunicazione", "Sociologia della Cultura", "Didattica",
    "Crittografia", "Matematica per l'Economia", "Storia della Musica", "Economia Politica", "Comunicazione Politica"
};


//          COMPLETE    - per pulire il buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

//          COMPOLETE   - iniizializza una nuova Major
Mjr* init_major(const char* code, const char* name, int tot_c) {
    Mjr* major = malloc(sizeof(Mjr));
    if (!major) {
        printf("\nMemory allocation for Major error.");
        return NULL;
    }

    major->Tot_C = tot_c;
    strncpy(major->M_code, code, 4);
    strncpy(major->M_name, name, 21);

    major->matrix = malloc(tot_c * sizeof(char*));
    major->courses = malloc(tot_c * sizeof(char*));
    if (!major->matrix || !major->courses) {
        free(major->matrix);
        free(major->courses);
        free(major);
        return NULL;
    }

    for (int i = 0; i < tot_c; i++) {
        major->matrix[i] = NULL;
        major->courses[i] = NULL;
    }

    return major;
}

//          COMPLETE    - inizializza un nuovo corso
Crs* init_course(const char* code, const char* name, int cfu) {
    Crs* course = malloc(sizeof(Crs));
    if (!course) {
        printf("\nMemory allocation for Course error.");
        return NULL;
    }

    course->CFU = cfu;
    strncpy(course->C_code, code, 6);
    strncpy(course->C_name, name, 21);

    course->matrix = NULL;
    course->M_code = NULL;

    return course;
}

//          COMPLETE    - inizializza un nuovo studente
Std* init_student(const char* name, const char* surname, const char* matrix, const char* m_code, const char* iscrizione, const char* nascita) {
    Std* student = malloc(sizeof(Std));
    if (!student) {
        printf("\nMemory allocation for Student error.");
        return NULL;
    }

    strncpy(student->S_name, name, 21);
    strncpy(student->S_surname, surname, 21);
    strncpy(student->matrix, matrix, 9);
    strncpy(student->M_code, m_code, 4);
    strncpy(student->D_nascita, nascita, 7);
    strncpy(student->D_iscrizione, iscrizione, 7);


    return student;
}

//          COMPLETE    - inizializza una nuova lista di voti
Scr* init_score(int* cfu, int* voto, const char* c_code, const char* s_code) {
    Scr* score = malloc(sizeof(Scr));
    if (!score) {
        printf("\nError: couldn't allocate memory for struct score.\n");
        return NULL;
    }

    score->CFU = *cfu;
    score->score = *voto;

    // Allocazione memoria per C_code e matrix
    score->C_code = malloc(7 * sizeof(char)); // 6 caratteri + 1 per '\0'
    score->matrix = malloc(10 * sizeof(char)); // 9 caratteri + 1 per '\0'

    if (!score->C_code || !score->matrix) {
        printf("\nError: couldn't allocate memory for C_code or matrix.\n");
        free(score->C_code); // Dealloca memoria in caso di errore
        free(score->matrix);
        free(score);
        return NULL;
    }

    strncpy(score->C_code, c_code, 6);
    score->C_code[6] = '\0';  // Assicura la terminazione della stringa

    strncpy(score->matrix, s_code, 9);
    score->matrix[9] = '\0';   // Assicura la terminazione della stringa

    score->next = NULL;        // Inizializza il puntatore a next node come NULL

    return score;
}

//          COMPLETE    - register a student || course || major
void REGISTER(char type) {
    printf("\nREGISTER() is running...\n");

    if (type == 'm') {
        char code[4], name[21];
        int tot_c = 0;

        // Input del codice della major
        printf("\nInsert major's code (max 3): ");
        if (scanf("%3s", code) != 1) {
            printf("Input error for major code.\n");
            clear_input_buffer();
            return;
        }
        clear_input_buffer();

        // Input del nome della major
        printf("\nInsert major's name (max 20): ");
        if (scanf(" %20[^\n]", name) != 1) {
            printf("Input error for major name.\n");
            clear_input_buffer();
            return;
        }
        clear_input_buffer();

        // Input del numero di corsi
        printf("\nInsert the total number of courses for this major: ");
        if (scanf("%d", &tot_c) != 1 || tot_c <= 0) {
            printf("\nError in filling tot_c. Please enter a valid positive number.\n");
            clear_input_buffer();
            return;
        }
        clear_input_buffer();

        // Inizializza la struttura Major
        Mjr* new_major = init_major(code, name, tot_c);
        if (!new_major) {
            printf("\nMajor's init error.\n");
            return;
        }

        // Alloca memoria per i corsi
        new_major->courses = (char**)malloc(tot_c * sizeof(char*));
        if (!new_major->courses) {
            printf("\nMemory allocation for courses failed.\n");
            free(new_major);
            return;
        }

        // Inserisci i codici dei corsi
        for (int waw = 0; waw < tot_c; waw++) {
            char course_code[6];
            printf("\nInsert the code for course %d of the major \"%s\": ", waw + 1, name);
            if (scanf("%5s", course_code) != 1) {
                printf("Input error for course code.\n");
                clear_input_buffer();

                // Libera memoria allocata
                for (int j = 0; j < waw; j++) {
                    free(new_major->courses[j]);
                }
                free(new_major->courses);
                free(new_major);
                return;
            }
            clear_input_buffer();

            new_major->courses[waw] = _strdup(course_code);
            if (!new_major->courses[waw]) {
                printf("\nMemory allocation failed for course code %d.\n", waw + 1);

                // Libera memoria allocata
                for (int j = 0; j < waw; j++) {
                    free(new_major->courses[j]);
                }
                free(new_major->courses);
                free(new_major);
                return;
            }
        }

        // Input del numero di studenti
        int iscritti_major_temp = 0;
        do {
            printf("\nHow many people are in this major? (min = 10): ");
            if (scanf("%d", &iscritti_major_temp) != 1 || iscritti_major_temp < 10) {
                printf("Invalid input. Please enter a number greater than or equal to 10.\n");
                clear_input_buffer();
            }
        } while (iscritti_major_temp < 10);

        // Alloca memoria per le matricole
        new_major->matrix = malloc(iscritti_major_temp * sizeof(char*));
        if (!new_major->matrix) {
            printf("\nMemory allocation for matrix failed.\n");
            for (int j = 0; j < tot_c; j++) {
                free(new_major->courses[j]);
            }
            free(new_major->courses);
            free(new_major);
            return;
        }

        // Inserisci le matricole
        for (int waw = 0; waw < iscritti_major_temp; waw++) {
            char m_iscritto[9];
            printf("\nInsert the matrix for student %d of the major \"%s\": ", waw + 1, name);
            if (scanf("%8s", m_iscritto) != 1) {
                printf("Input error for matrix.\n");
                clear_input_buffer();

                // Libera memoria allocata
                for (int j = 0; j < waw; j++) {
                    free(new_major->matrix[j]);
                }
                for (int j = 0; j < tot_c; j++) {
                    free(new_major->courses[j]);
                }
                free(new_major->matrix);
                free(new_major->courses);
                free(new_major);
                return;
            }
            clear_input_buffer();

            new_major->matrix[waw] = _strdup(m_iscritto);
            if (!new_major->matrix[waw]) {
                printf("\nMemory allocation failed for student matrix %d.\n", waw + 1);

                // Libera memoria allocata
                for (int j = 0; j < waw; j++) {
                    free(new_major->matrix[j]);
                }
                for (int j = 0; j < tot_c; j++) {
                    free(new_major->courses[j]);
                }
                free(new_major->matrix);
                free(new_major->courses);
                free(new_major);
                return;
            }
        }
        clear_input_buffer();
        // Salva i dati della major
        SAVE_DATA('m', new_major);
        printf("\nMajor '%s' registered successfully!\n", name);

        // Libera memoria allocata
        for (int i = 0; i < tot_c; i++) {
            free(new_major->courses[i]);
        }
        for (int i = 0; i < iscritti_major_temp; i++) {
            free(new_major->matrix[i]);
        }
        free(new_major->courses);
        free(new_major->matrix);
        free(new_major);
    }
    // ##########################################################################

    else if (type == 'c') {
        //gestione register di un course
        int cfu;
        char code[6], name[21];
        printf("\nInsert course's name: ");
        if (!scanf(" %[^\n]", name)) {
            printf("\nerror in filing name.");
            return;
        }
        printf("\nInsert course's CFU (usually 3-6-12): ");
        if (!scanf("%i", &cfu)) {
            printf("\nerror in filling CFU.\n");
            return;
        }
        printf("\nInsert course's code: ");
        if (!scanf("%5s", code)) {
            printf("\nerror in filling course code.");
            return;
        }


        Crs* new_course = init_course(code, name, cfu);
        if (!new_course) {
            printf("\nCourse's init error.\n");
            return;
        }

        // riempio codici delle major (1 min)
        int n_m_temp = 1; // numero minimo major
        do {
            printf("\nhow many majors teach this course?(min = 1)\nnum: ");
            if (!scanf("%i", &n_m_temp)) {
                printf("\nerror in filling n_m_temp.\n");
                return;
            }
        } while (n_m_temp < 1);


        new_course->M_code = (char**)malloc(n_m_temp * sizeof(char*));
        // libera memoria allocata se errore avviene
        if (!new_course->M_code) {
            printf("\nMemory allocation error for M_code.");
            free(new_course->M_code);
            free(new_course);
            return;
        }


        for (int waw = 0; waw < n_m_temp; waw++) {
            char majorID[4]; //major code
            printf("\nInsert the code of the Major %i: ", waw + 1);

            if (!scanf("%3s", majorID)) {
                printf("\nerror in filling mc");
                return;
            }
            majorID[3] = '0';

            new_course->M_code[waw] = _strdup(majorID);
            if (!new_course->M_code[waw]) {
                printf("\nMemory allocation error M_code in courses.");
                for (int boop = 0; boop < waw; boop++) {
                    free(new_course->M_code[boop]);
                }
                free(new_course->M_code);
                free(new_course);
                return;
            }
        }

        // riempio codici delle matricole
        int n_s_temp = 10; // numero minimo student
        do {
            printf("\nhow many students in this course?(min = 10)\nnum: ");
            if (!scanf("%i", &n_s_temp)) {
                printf("\nerror in filling m_s_temp.\n");
                return;
            }
        } while (n_s_temp < 10);


        new_course->matrix = (char**)malloc(n_s_temp * sizeof(char*)); // min 10 std per corso
        // studenti da Major diverse possono frequentare lo stesso corso

        // libera memoria allocata se errore avviene
        if (!new_course->matrix) {
            printf("\nMemory allocation error either for M_code or for matrix.");
            free(new_course->M_code);
            free(new_course->matrix);
            free(new_course);
            return;
        }

        for (int waw = 0; waw < n_s_temp; waw++) {
            char sc[9]; //students matrix
            printf("\nInsert student's %i matrix: ", waw + 1);
            if (!scanf("%8s", sc)) {
                printf("\nerror in filling sc.\n");
                return;
            }

            new_course->matrix[waw] = _strdup(sc);
            if (!new_course->matrix[waw]) {
                printf("\nMemory allocation error matrix in courses.");
                for (int boop = 0; boop < waw; boop++) {
                    free(new_course->matrix[boop]);
                }
                free(new_course->M_code);
                free(new_course->matrix);
                free(new_course);
                return;
            }
        }

        SAVE_DATA('c', &new_course);

    }
    // #########################################################################

    else if (type == 's') {

        char m_code[4], name[21], surname[21], matrix[9], nascita[7], iscrizione[7];
        clear_input_buffer();
        printf("\nInsert student's Name: ");
        if(!scanf(" %[^\n]", name)){
            printf("\nerror in filling name.\n");
            return;
        }
        clear_input_buffer();

        printf("\nInsert student's Surename: ");
        if(!scanf(" %[^\n]", surname)) {
            printf("\nerror in filling surname.\n");
            return;
        }
        clear_input_buffer();

        printf("\nInsert Student's matrix: ");
        if(!scanf(" %[^\n]", matrix)){
            printf("\nerror in filling matrix.\n");
            return;
        }
        clear_input_buffer();

        printf("\nInsert Student's B-day (format: DD\\MM\\AA): ");
        if (!scanf(" %6[^\n]", nascita)) {
            printf("\nerror in filling nascita.\n");
            
        }
        clear_input_buffer();

        printf("\nInsert Student's registration date: (format: DD\\MM\\AA): ");
        if (!scanf(" %6[^\n]", iscrizione)){
            printf("\nerror in filling iscrizione.\n");
            
        }
        clear_input_buffer();

        printf("\nWhich major is the student in: ");
        if(!scanf(" %6[^\n]", m_code)) {
            printf("\nerror in filling m_code.\n");
            
        }
        clear_input_buffer();

        Std* new_student = init_student(name, surname, matrix, m_code, nascita, iscrizione);
        if (!new_student) {
            printf("\nErorr in creation of struct Student.\n");
        }

        printf("\nStudent '%s %s' has been registerd in the major with code %s", new_student->S_name, new_student->S_surname, new_student->M_code);
        SAVE_DATA('s', &new_student);
    }

    // ########################################################################
    else if (type == 'v') {

        int cfu = 0;
        int score = -1;
        char C_code[6];
        char matrix[9];

        printf("\nwhat's the code of the course?\ncode: ");
        if(!scanf("%5s", C_code)) {
            printf("\nerror in filling C_code.\n");
            return;
        }
        printf("\nwhat's the matrix of the student?\ncode: ");
        if(!scanf("%8s", matrix)){
            printf("\nerror in filling matrix.\n");
            return;
        }

        // ciclo per i crediti
        do {
            printf("\nhow many CFU does this course give? (12-6-3)\ncfu: ");
            if(!scanf("%i", &cfu)) {
                printf("\nerror in filling cfu.\n");
                return;
        }
        } while (cfu != 12 && cfu != 6 && cfu != 3);

        // ciclo per i voti
        do {
            printf("\nwhat1 score did %s get in %s?\nscore: ", matrix, C_code);
            if(!scanf("%i", &score)){
                printf("\nerror in filling score.\n");
                return;
        }
        } while (0 > score || score < 33);

        Scr* new_score = init_score(&cfu, &score, &C_code, &matrix);
        if (!new_score) {
            printf("\nErorr. couldn't allocate memory for the score.\n");
            return;
        }

        new_score->next = score_head;       // il nuovo nodo punta al nodo in testa
        score_head = new_score;             // il nuovo nodo diventa la testa

        SAVE_DATA('v', &new_score);

        printf("\nthe result of the course %s has been added to the studen %s.\n", new_score->C_code, new_score->matrix);

    }

    //#########################################################################
    else {
        printf("\ninvalid input, termintaing.");
        return;
    }

    printf("\nREGISTER() terminating...\n");
}

//          COMPLETE   - search engine interace
void SEARCH(char type) {
    printf("\nSEARCH() is running...\n");

    if (type == 'm') {
        char search_type = 'a';
        printf("\nHow do you want to search for the Major?\nOptions:\n- n = name\n- m = code\nChoice: ");
        if (!scanf(" %c", &search_type)) {
            printf("\nError in filling search_type.\n");
            clear_input_buffer();
            return;
        }

        clear_input_buffer();

        if (search_type == 'n') {
            char temp_name[21];
            printf("\nSearch by Major's name selected.\nInsert name: ");
            if (!scanf("%20s", temp_name)) {
                printf("\nError in filling temp_name.\n");
                clear_input_buffer();
                return;
            }
            printf("\nThe name you're looking for is: %s\n", temp_name);
            SEARCH_ENGINE(type, search_type, temp_name);
        }
        else if (search_type == 'm') {
            char temp_code[4];
            printf("\nSearch by Major's code selected.\nInsert code: ");
            if (!scanf("%3s", temp_code)) {
                printf("\nError in filling temp_code.\n");
                clear_input_buffer();
                return;
            }
            printf("\nThe code you're looking for is: '%s'\n", temp_code);
            SEARCH_ENGINE(type, search_type, temp_code);
        }
        else {
            printf("\nInvalid input. Terminating.\n");
            return;
        }
    }
    //##################################################

    else if (type == 'c') {
        char search_type = 'a';
        printf("\nHow do you want to search for the Course?\nOptions:");
        printf("\n- n = course name\n- c = course code\n- m = major code\n- u = CFU\nChoice: ");
        if (!scanf(" %c", &search_type)) {
            printf("\nError in filling search_type.\n");
            clear_input_buffer();
            return;
        }

        clear_input_buffer();

        if (search_type == 'n') {
            char temp_name[21];
            printf("\nSearch by Course's name selected.\nInsert name: ");
            if (!scanf("%20s", temp_name)) {
                printf("\nError in filling temp_name.\n");
                clear_input_buffer();
                return;
            }
            printf("\nThe name you're looking for is: %s\n", temp_name);
            SEARCH_ENGINE(type, search_type, temp_name);
        }
        else if (search_type == 'u') {
            int credits;
            printf("\nSearch by Course's CFU selected.\nHow many: ");
            if (!scanf("%i", &credits)) {
                printf("\nError in filling credits.\n");
                clear_input_buffer();
                return;
            }
            printf("\nThe course you're looking for has: %i CFU\n", credits);
            SEARCH_ENGINE(type, search_type, &credits);
        }
        else {
            printf("\nInvalid input. Terminating.\n");
            return;
        }
    }
    //###################################################

    else if (type == 's') {

        clear_input_buffer();
        printf("\nhow you want to search for the student?\noptinos:");
        printf("\nn = student name.\ns = student surname.\nm = student's matrix.\nl = major code.\nc = course code.\nb = birth day.\nr = registration day.\nchoice: ");
        char search_type = 'a';
        if (!scanf("%c", &search_type)) {
            printf("\nerror in filling search_type\n");
            return;
        }

        switch (search_type) {
        case 'n':
            printf("\nyou're searching a student by it's name.");
            char dude_name[21];
            printf("\nhow's called?\nname: ");
            if (!scanf(" %[^\n]", dude_name)) {
                printf("\nerror in filling dude_name.\n");
                return;
            }
            printf("\nthe name you're looking for is: %s", dude_name);
            SEARCH_ENGINE(type, search_type, dude_name);
            break;
        case 's':
            printf("\nyou're searching a student by it's surname.");
            char dude_surname[21];
            printf("\nhow's called?\nname: ");
            if (!scanf(" %[^\n]", dude_surname)) {
                printf("\nerror in filling dude_surname.\n");
                return;
            }
            printf("\nthe surname you're looking for is: %s", dude_surname);
            SEARCH_ENGINE(type, search_type, dude_surname);
            break;
        case 'm':
            printf("\nyou're searching for a student by it's matrix.");
            char dude_matrix[9];
            printf("\nwhat's the matrix?\nmatrix: ");
            if (!scanf(" %[^\n]", dude_matrix)) {
                printf("\nerror in filling dude_matrix.\n");
                return;
            }
            printf("\nthe matrix you're looking for is: %s", dude_matrix);
            SEARCH_ENGINE(type, search_type, dude_matrix);
            break;
        case 'l':
            printf("\nyou're searching a student by the major it's enrolled in.");
            char dude_major[4];
            printf("\what's the major's code?\ncode: ");
            if (!scanf(" %[^\n]", dude_major)) {
                printf("\nerror in filling dude_majro.\n");
                return;
            }
            printf("\nthe code of the major you're looking for is: %s", dude_major);
            SEARCH_ENGINE(type, search_type, dude_major);
            break;
        case 'c':
            printf("\nyou're searching a student by a course he's in.");
            char dude_course[6];
            printf("\nhow's the course called?\nname: ");
            if (!scanf(" %[^\n]", dude_course)) {
                printf("\nerror in filling dude_course.\n");
                return;
            }
            printf("\nthe code of the course you're looking for is: %s", dude_course);
            SEARCH_ENGINE(type, search_type, dude_course);
            break;
        case 'b':
            printf("\nyou're searching a student by his birth day.");
            char dude_bday[7];
            printf("\nwhen he was born? (format: DD\\MM\\YY)\ndate: ");
            if (!scanf(" %6[^\n]", dude_bday)) {
                printf("\nerror in filling dude_bday.\n");
                return;
            }
            printf("\nthe studen you're looking for was born: %s", dude_bday);
            SEARCH_ENGINE(type, search_type, dude_bday);
            break;
        case 'r':
            printf("\nyou're searching for a student by it's enrollment day.");
            char dude_enrollment[7];
            printf("\nwhen did it register? format (DD\\MM\\YY)\nname: ");
            if (!scanf(" %[^\n]", dude_enrollment)) {
                printf("\nerror in filling dude_enrollment.\n");
                return;
            }
            printf("\nthe student you're looking for has enrolled in: %s", dude_enrollment);
            SEARCH_ENGINE(type, search_type, dude_enrollment);
            break;
        default:
            printf("\ninvalid input.");
            clear_input_buffer();
            break;
        }

    }
    //###################################################

    else if (type == 'v') {
        char search_type = 'a';

        printf("\noptions:\n- I -> course code\n- M -> matrix\n- C -> cfu\nchoice: ");
        if (!scanf("%c", &search_type)) {
            printf("\nerror in filling search_type.\n");
            return;
        }

        switch (search_type) {
        case 'I':
            printf("\nsearching by the course's code\n");

            char CourseCode[5];
            printf("insert the course's name: ");
            if (!scanf("%5s", &CourseCode)) {
                printf("\nerror in filling CourseCode.\n");
                return;
            }
            printf("\ncourse code is: %s", CourseCode);

            SEARCH_ENGINE(type, search_type, CourseCode);
            break;
        case 'M':
            printf("\nsearching by the student's matrix\n");

            char MatricolaStudente[9];
            printf("\nstudent's matrix: ");
            if (!scanf("%s", &MatricolaStudente)) {
                printf("\nerror in filling MatricolaStudente.\n");
                return;
            }
            printf("\nthe matrix you gave is: %s", MatricolaStudente);

            SEARCH_ENGINE(type, search_type, MatricolaStudente);
            break;
        case 'C':
            printf("\nsearching by the number of credits\n");

            int crediti;
            printf("\nInsert course's CFU: ");
            if (!scanf("%i", &crediti)) {
                printf("\nerror in filling crediti.\n");
                return;
            }
            printf("\nthe course gives %i CFU", crediti);

            SEARCH_ENGINE(type, search_type, crediti);
            break;
        default:
            printf("\ninvalid input, terminating.");
            return;
        }

    }
    //###################################################

    else {
        printf("\nInvalid input for SEARCH. Terminating.\n");
        return;
    }
    //###################################################
    printf("\nSEARCH() terminating...\n");
}

//          COMPLETE    - deep searching
void SEARCH_ENGINE(char type, char search_type, void* data) {

    FILE* file = NULL;
    // per i casi specifici di ricerca
    if (type == 'm') {
        file = fopen("major.bin", "rb");
        if (!file) {
            printf("\nERROR: cannot open file major.bin.\n");
            return;
        }

        Mjr major;
        while (fread(&major, sizeof(Mjr), 1, file) == 1) {
            if (search_type == 'n' && strcmp((char*)data, major.M_name) == 0) {
                printf("\nMatch found!\n");
                V_DATA('m', &major);
                fclose(file);
                return;
            }
            else if (search_type == 'm' && strcmp((char*)data, major.M_code) == 0) {
                printf("\nMatch found!\n");
                V_DATA('m', &major);
                fclose(file);
                return;
            }
        }
        printf("\nNo matches found.\n");
        fclose(file);
    }
    //###################################################

    else if (type == 'c') {
        file = fopen("course.bin", "rb");
        if (!file) {
            printf("\nERROR: cannot open file course.bin.\n");
            return;
        }

        Crs course;
        while (fread(&course, sizeof(Crs), 1, file) == 1) {
            if (search_type == 'n' && strcmp((char*)data, course.C_name) == 0) {
                printf("\nMatch found!\n");
                V_DATA('c', &course);
                fclose(file);
                return;
            }
            else if (search_type == 'c' && strcmp((char*)data, course.C_code) == 0) {
                printf("\nMatch found!\n");
                V_DATA('c', &course);
                fclose(file);
                return;
            }
        }
        printf("\nNo matches found.\n");
        fclose(file);
    }
    //###################################################

    else if (type == 's') {
        file = fopen("student.bin", "rb");
        if (!file) {
            printf("\nERROR: cannot open file student.bin.\n");
            return;
        }

        Std student;
        while (fread(&student, sizeof(Std), 1, file) == 1) {
            if (search_type == 'n' && strcmp((char*)data, student.S_name) == 0) {
                printf("\nMatch found!\n");
                V_DATA('s', &student);
                fclose(file);
                return;
            }
            else if (search_type == 's' && strcmp((char*)data, student.S_surname) == 0) {
                printf("\nMatch found!\n");
                V_DATA('s', &student);
                fclose(file);
                return;
            }
            else if (search_type == 'm' && strcmp((char*)data, student.matrix) == 0) {
                printf("\nMatch found!\n");
                V_DATA('s', &student);
                fclose(file);
                return;
            }
            else if (search_type == 'l' && strcmp((char*)data, student.M_code) == 0) {
                printf("\nMatch found!\n");
                V_DATA('s', &student);
                fclose(file);
                return;
            }
        }
        printf("\nNo matches found.\n");
        fclose(file);
    }
    //###################################################

    else if (type == 'v') {
        file = fopen("score.bin", "rb");
        if (!file) {
            printf("\nERROR: cannot open file score.bin.\n");
            return;
        }

        Scr score;
        while (fread(&score, sizeof(Scr), 1, file) == 1) {
            if (search_type == 'm' && strcmp((char*)data, score.matrix) == 0) {
                printf("\nMatch found!\n");
                V_DATA('v', &score);
                fclose(file);
                return;
            }
            else if (search_type == 'c' && strcmp((char*)data, score.C_code) == 0) {
                printf("\nMatch found!\n");
                V_DATA('v', &score);
                fclose(file);
                return;
            }
        }
        printf("\nNo matches found.\n");
        fclose(file);
    }
    //###################################################

    else {
        printf("\nInvalid type for SEARCH_ENGINE.\n");
    }
    //###################################################

}

//                      - remove the data
void RM(char type) {
    printf("\nRM() is running...\n");

    char choice = 'a';
    printf("\nrm a data or a whole struct? (D/S).\nchoice: ");
    if(!scanf("%c", &choice)){
        printf("\nerror in filling choice.\n");
        return;
        }

    if (type == 'm') {

        if (choice == 'D') {

            printf("\nyou choose to delite a single data from the struct");
            C_DATA('m');

        }
        else if (choice == 'S') {



        }
        else {
            printf("\ninvalid input.\n");
            return;
        }

    }
    //###########################################################
    else if (type == 'c') {

        if (choice == 'D') {

            printf("\nyou choose to delite a single data from the struct");
            C_DATA('c');

        }
        //######################################################

        else if (choice == 'S') {



        }
        //#######################################################

        else {
            printf("\ninvalid input.\n");
            return;
        }
        //#######################################################

    }
    //###########################################################

    else if (type == 's') {

        if (choice == 'D') {

            printf("\nyou choose to delite a single data from the struct");
            C_DATA('s');

        }
        //###########################################################

        else if (choice == 'S') {



        }
        //###########################################################

        else {
            printf("\ninvalid input.\n");
            return;
        }
        //############################################################
    }
    //#############################################################

    else {
        printf("\ninvalid input.\n");
        return;
    }
    printf("\nRM() terminating...\n");
}

//          COMPLETE    - change the data
void C_DATA(char type) {
    printf("\nC_DATA() is running...\n");

    /*
    a questo punto è come una register solo che prima
    search
    crea e cambia una copia change()
    register()
    */

    if (type == 's') {

        printf("\nyou choose to change the data of a student.\n");
        SEARCH('s');
        printf("the idea is to rewrite the new data having the old ones in sight.\n");
        REGISTER('s');
    }
    else if (type == 'c') {

        printf("\nyou choose to change the data of a course.\n");
        SEARCH('c');
        printf("the idea is to rewrite the new data having the old ones in sight.\n");
        REGISTER('c');

    }
    else if (type == 'm') {

        printf("\nyou choose to change the data of a major.\n");
        SEARCH('m');
        printf("the idea is to rewrite the new data having the old ones in sight.\n");
        REGISTER('m');

    }
    else if (type == 'v') {

        printf("\nyou choose to change the data of a score.\n");
        SEARCH('v');
        printf("the idea is to rewrite the new data having the old ones in sight.\n");
        REGISTER('v');

    }
    else {
        printf("Invalid input, terminating...");
        return;
    }

    printf("\nC_DATA() terminating...\n");
}

//          COMPLETE    - add a score to a student || see AVG of student || course result || highest AVG
void Score(char type) {
    printf("\nScore() is running...\n");

    char operation = 'z';
    printf("\nmenù:\n- A -> add a score\n- C -> change a score\n- V -> see a Score\n\nchoice: ");
    if(!scanf("%c", &operation)){
        printf("\nerror in filling operation.\n");
        return;
        }
    printf("\nyou choose to ");

    switch (operation) {
    case 'A':
        printf("add a score.\n");
        // legge la lista per vedere se già esiste il valore che sto cercando
        SEARCH('v');
        if (!SEARCH) {
            REGISTER('v');
        }
        else {
            printf("\nscore already existent.\n");
            return;
        }
        break;
    case 'C':
        printf("change a score.\n");
        SEARCH('v');
        if (!SEARCH) {
            printf("\nscore not found.\n");
            return;
        }
        else {
            C_DATA('v');
        }
        break;
    case 'V':
        printf("see a score.\n");
        SEARCH('v');
        if (!SEARCH) {
            printf("\nscore not found.\n");
            return;
        }
        break;
    }

    printf("\nScore() terminating...\n");
}

//          COMPLETE    - LIST OF ALL students || courses || majors
void LIST(char type) {
    printf("\nLIST() is running...\n");


    printf("\nsearching...");
    SEARCH(type);

    printf("\nresults:\n");

    if (type == 's') {  // Lista degli studenti
        FILE* file = fopen("student.bin", "rb");
        if (file == NULL) {
            printf("Error: could not open 'student.bin'.\n");
            return;
        }

        Std student;
        while (fread(&student, sizeof(Std), 1, file) == 1) {
            // Passa la struct alla funzione V_DATA per stampare solo la matricola
            printf("\n");
            V_DATA(type, &student);  // V_DATA stampa solo il campo "matrix"
        }
        fclose(file);
    }
    //##############################################################

    else if (type == 'c') {  // Lista dei corsi
        FILE* file = fopen("course.bin", "rb");
        if (file == NULL) {
            printf("Error: could not open file 'course.bin'.\n");
            return;
        }

        Crs course;
        while (fread(&course, sizeof(Crs), 1, file) == 1) {
            // Passa la struct alla funzione V_DATA per stampare solo il codice del corso
            printf("\n");
            V_DATA(type, &course);  // V_DATA stampa solo il campo "C_code"
        }
        fclose(file);
    }
    //##############################################################

    else if (type == 'm') {  // Lista delle major
        FILE* file = fopen("major.bin", "rb");
        if (file == NULL) {
            printf("Error: could not open file 'major.bin'.\n");
            return;
        }

        Mjr major;
        while (fread(&major, sizeof(Mjr), 1, file) == 1) {
            // Passa la struct alla funzione V_DATA per stampare solo il nome della major
            printf("\n");
            V_DATA(type, &major);  // V_DATA stampa solo il campo "M_name"
        }
        fclose(file);
    }
    //##############################################################

    else if (type == 'v') {

        FILE* moon = fopen("score.bin", "rb");
        if (!moon) {
            printf("\nError: couldn't open score.bin");
            return;
        }

        Scr score;

        while (fread(&score, sizeof(Scr), 1, moon) == 1) {
            //passa la struct alla funzione V_DATA
            printf("\n");
            V_DATA(type, &score);
        }
        fclose(moon);

    }
    //##############################################################

    else {
        printf("\ninvalid input.\n");
        return;
    }
    //##############################################################

    printf("\nLIST() terminating...\n");
}

//          COMPLETE    - initialize the stucts Mjr || Crs || Std
void INIT(char type, void* data) {

    if (type == 'm') {
        Mjr* major = (Mjr*)data;
        memset(major, 0, sizeof(Mjr)); // Inizializza a zero tutti i campi
        strcpy(major->M_name, "");     // Nome vuoto
        major->Tot_C = 12;             // Imposta Tot_C con un valore predefinito
    }
    //#############################################################

    else if (type == 'c') {
        Crs* course = (Crs*)data;
        memset(course, 0, sizeof(Crs));
        strcpy(course->C_code, "");    // Codice corso vuoto
        strcpy(course->C_name, "");    // Nome corso vuoto
        strcpy(course->M_code, "");    // Codice major vuoto
        course->CFU = 0;               // CFU inizializzato a 0
    }
    //##############################################################

    else if (type == 's') {
        Std* student = (Std*)data;
        memset(student, 0, sizeof(Std));
        strcpy(student->S_name, "");      // Nome studente vuoto
        strcpy(student->S_surname, "");  // Cognome studente vuoto
        strcpy(student->matrix, "");     // Matricola vuota
        memset(student->D_iscrizione, 0, sizeof(student->D_iscrizione)); // Data iscrizione azzerata
        memset(student->D_nascita, 0, sizeof(student->D_nascita));       // Data nascita azzerata
    }
    //##############################################################

    else if (type == 'v') {
        Scr* score = (Scr*)data;
        memset(score, 0, sizeof(Scr));   // Reset della struct a 0
        score->C_code[0] = '\0';         // Codice corso vuoto
        score->matrix[0] = '\0';         // Matricola vuota
        score->score = -1;               // Punteggio inizializzato a -1
        score->CFU = 0;                  // CFU inizializzato a 0
        score->next = NULL;              // Puntatore 'next' nullo
    }
    //###############################################################

    else {
        printf("Unknown type: %c\n", type);
        return;
    }
    //##############################################################
}

//          COMPLETE    - printf all info of a struct
void V_DATA(char type, void* data) {
    printf("\nV_DATA() is running...\n");

    INIT(type, data);

    if (type == 'm') {
        Mjr* major = (Mjr*)data;
        printf("\nMajor's name: %s", major->M_name);
        printf("\nMajor's code: %s", major->M_code);

        // Stampa i nomi dei corsi della laurea
        FILE* file = fopen("course.bin", "rb");
        if (file == NULL) {
            printf("Error: could not open file 'course.bin'.\n");
            return;
        }

        Crs course;
        printf("\nList of courses for Major %s:\n", major->M_name);
        int course_found = 0;
        while (fread(&course, sizeof(Crs), 1, file) == 1) {
            if (strcmp(course.M_code, major->M_code) == 0) {
                // Il codice della major corrisponde, quindi stampiamo il nome del corso
                printf("Course Name: %s\n", course.C_name);
                course_found = 1;
            }
        }

        if (!course_found) {
            printf("No courses found for this major.\n");
        }

        fclose(file);

        // Stampa le matricole iscritte alla laurea
        FILE* wawati = fopen("student.bin", "rb");
        if (wawati == NULL) {
            printf("Error: could not open 'student.bin'.\n");
            return;
        }

        Std student;
        int student_found = 0;
        printf("\nList of all matricules enrolled in the major %s:\n", major->M_name);
        while (fread(&student, sizeof(Std), 1, wawati) == 1) {
            if (strcmp(student.M_code, major->M_code) == 0) {
                printf("Matrix: %s\n", student.matrix);
                student_found = 1;
            }
        }

        if (!student_found) {
            printf("No students found for this major.\n");
        }

        fclose(wawati);
    }
    //#####################################################

    else if (type == 'c') {
        Crs* course = (Crs*)data;

        printf("\nCourse's name: %s", course->C_name);
        printf("\nCourse's code: %s", course->C_code);
        printf("\nCourse's CFU: %i", course->CFU);

        printf("\nMajors that offer this course:\n");
        FILE* file = fopen("major.bin", "rb");
        if (file == NULL) {
            printf("Error: cannot open file 'major.bin'.\n");
            return;
        }

        Mjr major;
        int major_counter = 0;
        while (fread(&major, sizeof(Mjr), 1, file) == 1) {
            for (int i = 0; i < major.Tot_C; i++) {
                if (strcmp(major.courses[i], course->C_code) == 0) {
                    printf("Major: %s\n", major.M_name);
                    major_counter++;
                    break;
                }
            }
        }
        fclose(file);

        if (major_counter == 0) {
            printf("No majors offer this course.\n");
        }
        else {
            printf("Total number of majors offering this course: %i\n", major_counter);
        }

        printf("\nList of students enrolled in this course:\n");
        FILE* stfile = fopen("student.bin", "rb");
        if (stfile == NULL) {
            printf("Error: cannot open file 'student.bin'.\n");
            return;
        }

        Std student;
        int student_enrolled = 0;
        while (fread(&student, sizeof(Std), 1, stfile) == 1) {
            if (strcmp(student.M_code, course->M_code) == 0) {
                printf("Matrix: %s\n", student.matrix);
                student_enrolled = 1;
            }
        }

        if (!student_enrolled) {
            printf("No students enrolled in this course.\n");
        }

        fclose(stfile);
    }
    //###################################################

    else if (type == 's') {
        Std* student = (Std*)data;
        printf("\nStudent's matrix: %s", student->matrix);
        printf("\nStudent's full name: %s %s", student->S_name, student->S_surname);
        printf("\nStudent's birth date: %s", student->D_nascita);
        printf("\nStudent's registration date: %s", student->D_iscrizione);

        printf("\nStudent is enrolled in the major: ");

        FILE* file = fopen("major.bin", "rb");
        if (file == NULL) {
            printf("Error: cannot open 'major.bin'.\n");
        }

        Mjr major;
        int major_found = 0;
        while (fread(&major, sizeof(Mjr), 1, file) == 1) {
            if (strcmp(major.M_code, student->M_code) == 0) {
                printf("%s\n", major.M_name);
                major_found = 1;
            }
        }

        if (!major_found) {
            printf("This student is not enrolled in any major.\n");
        }

        fclose(file);
    }
    //#####################################################

    else if (type == 'v') {
        Scr* score = (Scr*)data;

        // Stampo il nome del corso
        FILE* corsi = fopen("course.bin", "rb");
        if (corsi == NULL) {
            printf("Error: cannot open 'course.bin'.\n");
            return;
        }

        Crs course;
        int course_found = 0;
        while (fread(&course, sizeof(Crs), 1, corsi) == 1) {
            if (strcmp(score->C_code, course.C_code) == 0) {
                printf("\nCourse: %s", course.C_name);
                course_found = 1;
                break;
            }
        }
        fclose(corsi);

        if (!course_found) {
            printf("No course found for this score.\n");
        }

        printf("\nMatrix - Score\n%s - %d/30\n", score->matrix, score->score);
    }
    //#####################################################

    else {
        printf("Invalid input.\n");
        return;
    }

    //######################################################
    printf("\nV_DATA() terminating...\n");
}

//          COMPLETE    - self explicative
void SAVE_DATA(char type, void* data) {
    printf("\nSAVE_DATA() is running...\n");

    if (type == 'm') {
        system("cls");
        printf("\nsaving the major's data...\n");
        Mjr* major = (Mjr*)data;


        FILE* file = fopen("major.bin", "rb+");

        if (!file) {
            // Il file non esiste lo creo
            file = fopen("major.bin", "wb");
            if (!file) {
                perror("Errore nella creazione del file major.bin");
                return;
            }
        }

        // Scrivi la struttura Major senza matrix e courses
        fwrite(major, sizeof(Mjr), 1, file);

        // Scrivi la lunghezza di 'matrix' e 'courses' e i loro contenuti
        for (int i = 0; i < major->Tot_C; i++) {
            if (major->courses[i]) {
                size_t len = strlen(major->courses[i]) + 1;
                fwrite(&len, sizeof(size_t), 1, file);
                fwrite(major->courses[i], sizeof(char), len, file);
            }
        }

        for (int i = 0; i < major->Tot_C; i++) {
            if (major->matrix[i]) {
                size_t len = strlen(major->matrix[i]) + 1;
                fwrite(&len, sizeof(size_t), 1, file);
                fwrite(major->matrix[i], sizeof(char), len, file);
            }
        }

        fclose(file);
        printf("\nsaving completed =)\n");

        system("cls");
        printf("Here's a recap of what got saved: \n");
        LOAD_DATA('m', data);
    }
    //#############################################################

    else if (type == 'c') {
        system("cls");
        printf("\nsaving the course's data...\n");

        Crs* course = (Crs*)data;
        FILE* file = fopen("course.bin", "rb+");

        if (!file) {
            file = fopen("course.bin", "wb");
            if (!file) {
                printf("\nerror in courses.bin creation.");
                return;
            }
        }

        Crs temp_course;
        while (fread(&temp_course, sizeof(Crs), 1, file) == 1) {
            if (strcmp(temp_course.C_code, course->C_code) == 0) {

                // esiste già il corso -> aggiorno i dati

                fseek(file, sizeof(Crs), SEEK_CUR);
                fwrite(course, sizeof(Crs), 1, file);
                fclose(file);
                return;
            }
        }


        fseek(file, 0, SEEK_END);
        fwrite(course, sizeof(Crs), 1, file);
        fclose(file);

        printf("\nsaving completed =)\n");
        system("cls");
        printf("Here's a recap of what got saved: \n");
        LOAD_DATA('c', &temp_course);
    }
    //#############################################################

    else if (type == 's') {

        printf("\nSaving the student's data...\n");

        Std* student = (Std*)data;
        FILE* file = fopen("student.bin", "rb+");

        // Se non esiste il file, lo creiamo
        if (!file) {
            file = fopen("student.bin", "wb");
            if (!file) {
                printf("\nError in creating student.bin.\n");
                return;
            }
        }

        Std temp_student;
        int found = 0;

        // Leggi il file per vedere se lo studente esiste già
        while (fread(&temp_student, sizeof(Std), 1, file) == 1) {
            if (strcmp(temp_student.matrix, student->matrix) == 0) {
                // Lo studente esiste già, quindi aggiorna i suoi dati
                fseek(file, sizeof(Std), SEEK_CUR);  // Torna indietro di una struttura Std
                fwrite(student, sizeof(Std), 1, file);
                found = 1;
                break;
            }
        }

        // Se lo studente non è stato trovato, aggiungilo alla fine del file
        if (!found) {
            fseek(file, 0, SEEK_END);  // Vai alla fine del file
            fwrite(student, sizeof(Std), 1, file);
        }

        fclose(file);
        printf("\nSaving completed =)\n");

        // Visualizza un riepilogo dei dati salvati
        printf("Here's a recap of the saved data:\n");
        LOAD_DATA('s', student);
    }
    //#############################################################

    else if (type == 'v') {

        Scr* current_score = (Scr*)data;

        FILE* nooty = fopen("score.bin", "rb+");
        if (!nooty) {
            nooty = fopen("score.bin", "wb");
            if (!nooty) {
                printf("\nerror in score.bin creation.\n");
                return;
            }
        }

        Scr temp_score;

        // ciclo itinera tutta la lista
        while (fread(&temp_score, sizeof(Scr), nooty, 1) == 1) {

            // vede se il record esiste
            if (strcmp(temp_score.C_code, current_score->C_code) == 0
                && strcmp(temp_score.matrix, current_score->matrix) == 0) {

                // se il nodo esistelo aggiorno
                fseek(nooty, sizeof(Scr*), SEEK_CUR);       // torno in dietro di Scr
                fwrite(current_score, sizeof(Scr), 1, nooty);
                fclose(nooty);
                printf("\nupdate successfull.\n");
                break;
            }
        }

        // se il nodo non viene trovato, lo creo e lo aggiungo in testa
        fseek(nooty, 0, SEEK_END);
        fwrite(current_score, sizeof(Scr), 1, nooty);
        fclose(nooty);

        printf("\nhere's a recap of what you've just saved.\n");
        LOAD_DATA('v', &current_score);

    }

    //##############################################################à
    else {
        printf("\ninvalid input.\n");
        return;
    }

    printf("\nSAVE_DATA() terminating.... \n");
}

//          COMPLETE    - self explicative
void LOAD_DATA(char type, void* data) {
    printf("\nLOAD_DATA() is running...\n");

    if (type == 'm') {
        Mjr* major = (Mjr*)data;
        FILE* file = fopen("major.bin", "rb");
        if (file == NULL) {
            printf("Error: could not open file 'major.bin'.\n");
            return;
        }

        // Leggi la parte della struttura Mjr senza matrix e courses
        if (fread(major, sizeof(Mjr), 1, file) != 1) {
            printf("Error: failed to read major data.\n");
            fclose(file);
            return;
        }

        // Leggi i corsi
        for (int i = 0; i < major->Tot_C; i++) {
            size_t len;
            if (fread(&len, sizeof(size_t), 1, file) != 1) {
                printf("Error: failed to read course length.\n");
                fclose(file);
                return;
            }
            major->courses[i] = malloc(len);
            if (major->courses[i] == NULL) {
                printf("Memory allocation failed for courses.\n");
                fclose(file);
                return;
            }
            if (fread(major->courses[i], sizeof(char), len, file) != len) {
                printf("Error: failed to read course data.\n");
                fclose(file);
                return;
            }
        }

        // Leggi le matricole
        for (int i = 0; i < major->Tot_C; i++) {
            size_t len;
            if (fread(&len, sizeof(size_t), 1, file) != 1) {
                printf("Error: failed to read matrix length.\n");
                fclose(file);
                return;
            }
            major->matrix[i] = malloc(len);
            if (major->matrix[i] == NULL) {
                printf("Memory allocation failed for matrix.\n");
                fclose(file);
                return;
            }
            if (fread(major->matrix[i], sizeof(char), len, file) != len) {
                printf("Error: failed to read matrix data.\n");
                fclose(file);
                return;
            }
        }

        V_DATA("m", major);  // Visualizza i dati caricati
        fclose(file);
    }
    //#######################################################

    else if (type == 'c') {
        Crs* course = (Crs*)data;
        FILE* file = fopen("course.bin", "rb");
        if (file == NULL) {
            printf("Error: could not open file 'course.bin'.\n");
            return;
        }

        if (fread(course, sizeof(Crs), 1, file) != 1) {
            printf("Error: failed to read course data.\n");
            fclose(file);
            return;
        }

        V_DATA("c", course);  // Visualizza i dati caricati
        fclose(file);
    }
    //#######################################################

    else if (type == 's') {
        Std* student = (Std*)data;
        FILE* file = fopen("student.bin", "rb");
        if (file == NULL) {
            printf("Error: could not open file 'student.bin'.\n");
            return;
        }

        while (fread(student, sizeof(Std), 1, file) == 1) {
            // Visualizza i dati del singolo studente
            V_DATA("s", student);  // Supponendo che V_DATA stampi i dati dello studente
        }

        fclose(file);
    }
    //#######################################################

    else if (type == 'v') {
        Scr* score = (Scr*)data;
        FILE* moon = fopen("score.bin", "rb");
        if (!moon) {
            printf("Error: could not open file 'score.bin'.\n");
            return;
        }

        if (fread(score, sizeof(Scr), 1, moon) != 1) {
            printf("Error: failed to read score data.\n");
            fclose(moon);
            return;
        }

        V_DATA("v", score);  // Visualizza i dati caricati
        fclose(moon);
    }
    //#######################################################

    else {
        printf("\nInvalid input.\n");
        return;
    }

    printf("\nLOAD_DATA() is terminating...\n");
}
// last line