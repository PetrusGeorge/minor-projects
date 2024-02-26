#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define NUM_LETRAS 26
#define ASCII_A 65

#define QTDFILES 10 //quantidade de arquivos na pasta senhas
#define QTDSENHASPORFILE 10 //quantidade de senhas em cada arquivo da pasta senhas
#define TAMANHOSENHA 4 //o tamanho da senha sem considera /0 ou /n

typedef struct Passwords{

    char encrypted[QTDSENHASPORFILE][TAMANHOSENHA + 2];//guarda as senha encriptadas lidas do arquivo
    char decrypted[QTDSENHASPORFILE][TAMANHOSENHA + 2];//guarda as senhas decriptadas pelo programa
    //ambas consideram o caractere \n e \0 em seu tamanho inclusive quando não são usadas
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

void remove_newline(char* string){

    int i;
    for(i = 0; string[i] != '\0'; i++);//incrementa i até o final da string
    if(string[i-1] == '\n') string[i-1] = '\0';//remove o \n se ele estiver anterior ao final da string
}

Passwords brute_force(const char* file_name){

    FILE *fencrypted;

    if((fencrypted = fopen(file_name, "r")) == NULL){//tenta abrir o arquivo de senhas

        perror("Could not open encrypted file\n");
        exit(1);
    }

    Passwords passwords;

    for(int i = 0; i < QTDSENHASPORFILE; i++){

        if(fgets(passwords.encrypted[i], TAMANHOSENHA + 2, fencrypted) == NULL) break; //lê cada linha das senhas e caso o arquivo acabe antes do esperado ocorre um break
        remove_newline(passwords.encrypted[i]);
    }

    for(int i = 0; i < QTDSENHASPORFILE; i++){//itera por cada linha do arquivo

        char attempt_password[TAMANHOSENHA + 1]; //guarda a tentativa de brute force atual
        char result[TAMANHOSENHA+1]; //quadar o resultado da função encrypt em formato de string
        char *result_not_formated; //guarda o resultado da função encrypt

        for(int j = 0; j < TAMANHOSENHA;j++) attempt_password[j] = 'A';//preenche a variavel com AAA...A

        attempt_password[TAMANHOSENHA] = '\0'; //coloca \0 na ultima casa para criar uma string

        while(1){
            int aux = 0; //sempre comeca no char menos significativo, o primeiro caracter

            result_not_formated = encrypt(attempt_password, TAMANHOSENHA);
            for(int j = 0; j < TAMANHOSENHA; j++)
                result[j] = result_not_formated[j];
            result[TAMANHOSENHA] = '\0'; //pega o resultado de encrypt e transforma em string
            free(result_not_formated);

            if(strcmp(passwords.encrypted[i], result) == 0){//compara a senha encriptada com o resultado, se for 0 é igual
                strcpy(passwords.decrypted[i], attempt_password); //copia a senha correta para variavel
                break; //sai do while(1) terminando o brute force dessa senha
            }

            //o algoritimo funciona parecido com uma soma binaria
            //caso o incremento chegue ao maximo aquela casa ira para "0"
            //e o proximo ira ser incrementado
            while(attempt_password[aux] == 'Z'){ 
                
                attempt_password[aux] = 'A';
                aux++;
            }

            if(aux >= TAMANHOSENHA){ //caso nenhuma senha passe no teste o resultado sera N/A
                strcpy(passwords.decrypted[i], "N/A");
                break;
            }

            attempt_password[aux]++; //incrementa o char para iterar sobre as possibilidade
        }
    }

    fclose(fencrypted);

    return passwords;
}

int main(){

    pid_t pid_init = getpid();
    int fd[QTDFILES][2];
    
    pid_t pids[QTDFILES];

    int p_index = -1; //index do processo pai
    
    for(int i = 0; i < QTDFILES; i++){

        if(pipe(fd[i]) == -1){//inicia o pipe entre os forks

            perror("Erro no pipe");
            exit(1);
        }


        pids[i] = fork();

        if(getpid() != pid_init){//sai do loop caso seja um fork, as iterações são feitas apenas pelo pai

            p_index = i;
            break;
        }
    }


    if(getpid() == pid_init){//processo pai irá orquestrar os dados dos filhos

        for(int i = 0; i < QTDFILES; i++){

            close(fd[i][1]);//fecha o pipe de escrita

            FILE* fdecrypted;
            char filename[40];

            sprintf(filename, "decrypt/%d", i);
            strcat(filename, ".txt");//o nome do arquivo de saida sera decrypt/'numero'.txt

            if((fdecrypted = fopen(filename, "w")) == NULL){//tenta criar o arquivo e termina o processo caso falhe

                perror("Decrypt file could not be open\n");
                exit(1);
            }

            Passwords results;

            read(fd[i][0], &results, sizeof(results));//recebe os dados do filho

            for(int j = 0; j < QTDSENHASPORFILE; j++){//escreve todas as senhas encontradas no arquivo
                fprintf(fdecrypted,results.decrypted[j]);
                fprintf(fdecrypted,"\n");
            }

            fclose(fdecrypted); //fecha o arquivo
            close(fd[i][0]);//fecha o pipe de leitura
        }

    }else{

        char filename[40];

        sprintf(filename, "senhas/%d", p_index);
        strcat(filename, ".txt");//o nome do arquivo de entrada precisa ser senhas/'numero'.txt

        Passwords results;

        results = brute_force(filename);

        close(fd[p_index][0]);//fecha o pipe de leitura
        write(fd[p_index][1], &results, sizeof(results));//passa os dados para o processo pai
        close(fd[p_index][1]);//fecha o pipe de escrita
        exit(EXIT_SUCCESS);
    }

    return 0;
}
