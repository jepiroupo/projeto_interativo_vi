#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>

//variaveis
char *ip = "127.0.0.1";
int localsock, conector, porta = 7886;
struct sockaddr_in serv_end;

void *recebe(){
	//printf("Thread 'recebe' em execussao\n");	
	char *data;	
	while(1){			
		if( (recv(localsock, &data,1,0)) ==-1){
			perror("Thread 'recebe' encerrada!");
			return 0;
		}
		else{
			printf("%s\n",(char *)&data);
		}
	}
		
}

void *envia(){	
	//printf("Thread 'envia' em execussao\n");	
	char data[12];	
	char leitura[10];
	int primeiro = 1;

	while(1){		

		scanf("%s",leitura);		

		if(primeiro == 1)
		{
			strcpy(data, "0|");
			primeiro = 0;
		}
		else
		{
			strcpy(data, "1|");
		}
		strcat(data, leitura);

		if(send(localsock, &data, strlen((char *)&data), 0) < 0){
			perror("Thread 'envia' encerrada!");
			return 0;
		}
		else{
			//printf("%s\n",(char *) &data, strlen((char *)&data));
		}
	}
}



void conexao(){
	printf("Estabelecendo conexão...\n");	
	//printf("Digite a Porta\n");
    //scanf("%d",&porta);
	
	//estrutura com dados do servidor	
	serv_end.sin_family=AF_INET;
	serv_end.sin_port = htons(porta);
	serv_end.sin_addr.s_addr = inet_addr(ip);	

	//cria socket	
	localsock = socket(AF_INET, SOCK_STREAM, 0);
	
	//verifica se socket foi criado com sucesso
	if(localsock < -1)
		perror("Socket");

	//cria conexao;
	conector = connect(localsock, (struct sockaddr *)&serv_end, sizeof(serv_end));

	//verifica se conexao foi criada com sucesso
	if(conector <0)
		perror("connect");
	

	printf("conectado\n");
}


void thread(){	
	printf("Iniciando threads...\n");	
	pthread_t proc[2];
	pthread_create( &proc[0], NULL, envia, NULL);
	pthread_create( &proc[1], NULL, recebe, NULL);	
}

int main(int argc){
		
	conexao();
	
	thread();

	pthread_exit(NULL);
	close(localsock);
}
