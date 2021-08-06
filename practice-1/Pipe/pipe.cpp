#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <string.h>
#include <sstream>

using namespace std;

//Função para gerar um número aleatório entre 1 e 100
int randomNumberBetween1And100()
{
    srand(time(NULL));
    return rand() % 100 + 1;
}

//Função para incrementar um numero passado por um número aleatório entre 1 e 100
int incrementByDelta(int number)
{
    return number + randomNumberBetween1And100();
}

//Função para checar se o número pode ser dividido em duas partes iguais
bool isEvenlyDivisible(int numerator, int denominator)
{
    return (numerator % denominator) == 0;
}

//Função que verifica se o numero passado é primo
bool isPrimeNumber(int number)
{
    for (int i = 2; i <= sqrt(number); i++)
    {
        if (isEvenlyDivisible(number, i))
        {
            return false;
        }
    }
    return true;
}

//Função main
int main(int argc, char const *argv[])
{
		//Variavel de escrita e leitura do pipe
    int fd[2];

		//Variável que pega o argumento passado ao sistema como parametro da quantidade de numeros a serem incrementados
    int QTD_DE_NUM = stoi(argv[1]);

    char input_str[100];

		//variavel para identificação de processo
    pid_t p;

		//Cria o pipe e verifica se foi criado corretamente
    if(pipe(fd)==-1){
        cout<<"Pipe Failed";
        return 1;
    }

		//Faz o fork do processo para criar um processo filho
    p=fork();

		//Verifica se o fork foi bem sucedido
    if(p<0){
        cout<<"Fork Failed";
        return 1;
    }

    //Parent Process
    // Produtor
    if (p>0){
				//Fecha a ponta do pipe de leitura
        close(fd[0]);
				//Variavel para enviar ao pipe
        char num[20];
				//variavel a ser incrementada
        int incrementalNumber = 1;
        for (int i =0; i< QTD_DE_NUM; i++){
					//Cast de int para string
            sprintf(num, "%d", incrementalNumber);
						//Escreve a variavel no pipe
            write(fd[1], num, 50);
						//Incrementa a variavel 
            incrementalNumber = incrementByDelta(incrementalNumber);
        }
				//Envia "0" para encerrar o programa
        sprintf(num, "%d", 0);
        write(fd[1], num, 20);
				//Fecha o pipe de escrita
        close(fd[1]);
				//Encerra o processo
        exit(EXIT_SUCCESS);
    }
    //Child Process
		//Processo consumidor
    else{
				//Variavel de leitura
        char readNumber[20];
				//Variavel a receber o valor de leitura em inteiro
        int intReadNumber = 0;
				//Fecha a ponta do pipe de escrita
        close(fd[1]);
        for (int i = 0; i < QTD_DE_NUM + 1; i++)
        {
						//Lê a variavel enviada pelo pipe
            read(fd[0], readNumber, 50);
						//Cast da variavel para inteiro
            intReadNumber = stoi(readNumber);
						//Verifica se o valor passado no pipe é primo
            if (isPrimeNumber(intReadNumber) && intReadNumber != 0)
								//Caso seja primo e diferente de zero, é printado
                cout << readNumber << "\n";
						//Se o valor passado pelo pipe for zero, sai do loop
            if(intReadNumber == 0) break;
        }
				//Fecha o pipe de leitura
        close(fd[0]);
				//Encerra o processo
        exit(EXIT_SUCCESS);
    }
    return 0;
}
