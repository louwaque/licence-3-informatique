#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int une_globale;
char* alloc;
char* alloc1;
const char* cst = "une-chaine";

/**************************************************
 Afficher la carte mémoire du processus
 fichier /proc/self/maps
 **************************************************/
void dump_maps(void) {
    FILE *f;
    int c;
    
    f = fopen("/proc/self/maps", "r");
    assert(f != NULL);
    while ((c = fgetc(f)) != EOF) {
        putchar(c);
    }
    fclose(f);
    getchar();
}


/**************************************************
 Afficher les adresses de différents objets mémoire
 **************************************************/
int main(int argc, char* argv[]) {
    int une_locale;
    
    alloc = malloc(1024L * 1024L * 10L); /* 10mo */
    printf("PID = %d\n", getpid());
    printf("adresse de une_globale  = %012lx\n", (unsigned long) & une_globale);
    printf("adresse de une_locale   = %012lx\n", (unsigned long) & une_locale);
    printf("adresse de alloc        = %012lx\n", (unsigned long)   alloc);
    printf("adresse de alloc1       = %012lx\n", (unsigned long)   alloc1);
    printf("adresse de une_fonction = %012lx\n", (unsigned long) & main);
    printf("adresse d'une constante = %012lx\n", (unsigned long)   cst);

    /* afficher la carte mémoire */
    dump_maps();

    alloc1 = malloc(1024L * 1024L * 10L); /* 10mo */
	dump_maps();

    return (EXIT_SUCCESS);
}
