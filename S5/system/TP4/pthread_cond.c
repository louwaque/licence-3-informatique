#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/**********************************************************************
** Outils de synchronisation.
**********************************************************************/
pthread_mutex_t mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition = PTHREAD_COND_INITIALIZER;

/**********************************************************************
** Définition des couleurs et du nombre de peintres
**********************************************************************/
typedef enum {RED, BLUE} COLOR;
char* colors_name[] = {"RED", "BLUE"};

COLOR color = RED;
int nbPainters = 0;
int nbColors[2] = {0, 0};

/**********************************************************************
** Chaque peintre va récupérer un numéro unique et une couleur
** et peindre trois fois en alternant les couleurs.
**********************************************************************/
void* painter (void* _unused) {
    COLOR my_color;
    int my_number;
    int i;

    /* Chaque peintre prend un numéro et une couleur. */
    pthread_mutex_lock(&mutex);
    my_number = (++nbPainters);
    my_color = ((my_number % 2) ? RED : BLUE);
	++nbColors[my_color];
	printf("init numéro=%d, couleur=%s\n", my_number, colors_name[my_color]);
    pthread_mutex_unlock(&mutex);
	
	sleep(1);

    /* il y a trois zones à peindre */
    for(i=0; (i < 3); i++) {
    
        /* il faut attendre pour alterner les couleurs */
        pthread_mutex_lock(&mutex);
        while (color != my_color) {
            /* je m'endors car la condition est fausse */
            pthread_cond_wait(&condition, &mutex);
        }
        
        printf("numéro=%d, couleur=%s\n", my_number, colors_name[my_color]);
        sleep(1);
        
        /* je passe a la couleur suivante */
		do {
        	color = ((color == RED) ? BLUE : RED);
		} while (nbColors[color] == 0);

        pthread_cond_broadcast(&condition);
        pthread_mutex_unlock(&mutex);
    }

	pthread_mutex_lock(&mutex);
	--nbColors[my_color];
    pthread_mutex_unlock(&mutex);
 
    /* pas de résultat */
    return NULL;
}

/**********************************************************************
** Initialiser les peintres et attendre la fin du travail.
**********************************************************************/

#define NB_PAINTERS  (3)

int main (void) {
    pthread_t peintres[NB_PAINTERS];
    int i;
    
    for(i=0; (i < NB_PAINTERS); i++) {
        if (pthread_create(&peintres[i], NULL, painter, NULL)) {
            perror("thread");
            return (EXIT_FAILURE);
        }
    }

    for(i=0; (i < NB_PAINTERS); i++) {
        if (pthread_join(peintres[i], NULL)) {
            perror("pthread_join");
            return (EXIT_FAILURE);
        }
    }

    printf("Fin du pere\n") ;
    return (EXIT_SUCCESS);
}
