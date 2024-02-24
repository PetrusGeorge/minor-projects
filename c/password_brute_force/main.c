#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define NUM_LETRAS 26
#define ASCII_A 65

#define QTDFILES 10
#define QTDSENHASPORFILE 10
#define TAMANHOSENHA 4

typedef struct Passwords{

    char strings[QTDSENHASPORFILE][TAMANHOSENHA + 1];
}Passwords;

char* encrypt(const char* str, int tamanho) {
    char* str_result = (char*) malloc(sizeof(char)*tamanho);
    for (int i = 0; i < tamanho; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            int chave = str[i] - ASCII_A;
            str_result[i] = (str[i] - ASCII_A + chave) % NUM_LETRAS + ASCII_A;
        }
    }
    return str_result;
}

Passwords brute_force(const char* file_name){

    Passwords passwords;

    for(int i = 0; i < QTDSENHASPORFILE; i++){

        strcpy(passwords.strings[i], "HGDK");
    }

    return passwords;
}

int main(){

    pid_t pid_init = getpid();
    int fd[QTDFILES][2];
    
    pid_t pids[QTDFILES];

    int p_index = -1;
    
    for(int i = 0; i < QTDFILES; i++){

        if(pipe(fd[i]) == -1){

            perror("Erro no pipe");
            exit(1);
        }


        pids[i] = fork();

        if(getpid() != pid_init){

            p_index = i;
            break;
        }
    }


    if(getpid() == pid_init){

        for(int i = 0; i < QTDFILES; i++){

            close(fd[i][1]);

            Passwords results;

            read(fd[i][0], &results, sizeof(results));

            for(int j = 0; j < QTDSENHASPORFILE; j++){
                printf(results.strings[j]);
                printf("\n");
            }

            close(fd[i][0]);
        }

    }else{

        char filename[10];

        sprintf(filename, "%d", p_index);
        strcat(filename, ".txt");

        Passwords results;

        results = brute_force(filename);

        close(fd[p_index][0]);
        write(fd[p_index][1], &results, sizeof(results));
        close(fd[p_index][1]);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
