#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 148

//Daired Almeida Cruz,Rishardson,Victor Cortat,Thiago de Jesus,Rafael Andrade

typedef struct{//dados de um cliente
		
			char nomepassageiro[100];
			int rg;
			float valorpago;
			char email[100];
			char telefonepassageiro[20];
			char telefoneurgencia[20];
			char nomeurgencia[100];
			int cod;
			int poltrona;
		}dados;

typedef struct{//lista de clientes
	
			dados numero[N];
			int quantidade;
			int numerovoo;
			int horarioembarque;
			int horariochegada;
		}passageiros;
	
int main(){
	
	void menu();
	void cadastro(dados *pd);
	void dados_cliente(passageiros mostrar,int c);
	void relacao_clientes(passageiros relacao);
	void controle_vendas(passageiros relacao);
	void emissao_passagem(passageiros passagem,int c, int n, int ida, int chegada);
	void horarios(passageiros *pp,int f);
	void dar_dados(passageiros *pp);
	void salvar_dados(dados *pd);
	
	int opcao;
	int proximo;
	int contador=0;
	int e;
	
	dados *d = (dados *) malloc(sizeof(dados));
	
	if(d==NULL){
		printf("ERRO AO ALOCAR DADOS\n");
		return 0;
	}
	
	passageiros *p = (passageiros *) malloc(sizeof(passageiros));
	
	if(p==NULL){
		printf("ERRO AO ALOCAR DADOS\n");
		return 0;
	}
	
	p->quantidade=0;
	
	dar_dados(p);
	
	if(p->numerovoo!=p->horariochegada/2 || p->numerovoo>=13 || p->numerovoo<=0 || p->horarioembarque>=24 || p->horarioembarque<0 || p->horariochegada>=24 || p->horariochegada<0 || p->horarioembarque%2!=0 || p->horariochegada%2!=0){
		horarios(p,1);
	}
	
	printf("\n*****OLA BOM DIA BEM VINDO AO PROGRAMA DE AVIOES*****\n");
	
	do{
		printf("\nVOCE ESTA NO VOO %i COM EMBARQUE AS %i:00h E CHEGADA AS %i:00h\n\n",p->numerovoo,p->horarioembarque,p->horariochegada);
		menu();
		
		scanf("%i",&opcao);
		getchar();
		
		switch(opcao){

			case 1:	if(p->quantidade>=N){printf("OPCAO AINDA NAO DESPONIVEL, MAXIMO DE CLIENTES ATINGIDO PARA ESSE VOO\n\n");break;}
					
					cadastro(d);
					p->quantidade++;
					d->cod=(p->quantidade);
					printf("Esse cliente tem codigo: %i\nE poltrona: %i\n\n",d->cod,d->cod+1);
					salvar_dados(d);
					p->numero[p->quantidade] = *d;
					
					break;
					
			case 2:	if(p->quantidade<=-1){printf("OPCAO AINDA NAO DESPONIVEL, POR FAVOR CADASTRE UM CLIENTE NA OPCAO 1\n\n");break;}
			
					while(1){
						printf("Pesquisar pelo codigo do passageiro ou poltrona?\n\nDIGITE 1 PARA COM CODIGO ou DIGITE 2 PARA COM POLTRONA:");
						scanf("%i",&contador);
						getchar();
						
						if(contador==1){
							printf("\nDigite o codigo do passageiro:");
							scanf("%i",&contador);
							getchar();
							if(contador>p->quantidade){printf("\n***Codigo invalido, nenhum cliente associado a esse codigo***\n\n");}
							else{dados_cliente(*p,contador);break;}
						}
						if(contador==2){
							printf("\nDigite a poltrona do passageiro:");
							scanf("%i",&contador);
							getchar();
							if(contador-1>p->quantidade){printf("\n***Poltrona invalido, nenhum cliente associado a esse poltrona***\n\n");}
							else{dados_cliente(*p,contador-1);break;}
						}
					}
						
					break;
					
			case 3:	relacao_clientes(*p);
					break;
					
			case 4:	controle_vendas(*p);
					break;
					
			case 5:	if(p->quantidade<=-1){printf("OPCAO AINDA NAO DESPONIVEL, POR FAVOR CADASTRE UM CLIENTE NA OPCAO 1\n\n");break;}
			
					while(1){
						printf("Digite o codigo do passageiro: ");
						scanf("%i",&contador);
						if(contador>p->quantidade){printf("Codigo invalido, nenhum cliente associado a esse codigo\n\n");}
						else{break;}
					}
						emissao_passagem(*p,contador,p->numerovoo,p->horarioembarque,p->horariochegada);
					break;
					
			case 6:	while(1){
						printf("TEM CERTEZA QUE DESEJA IR PARA O PROXIMO VOO ?\n\n");
						printf("(1)-Sim\n");
						printf("(2)-Nao\n\n");
						printf("OPCAO: ");
						
						scanf("%i",&proximo);
						
						if(proximo==1){e=1;break;}
						else if(proximo==2){e=2;break;}
						else{printf("NUMERO INVALIDO, POR FAVOR DIGITE UM NUMERO VALIDO\n\n");}
					}
					
					if(e==2){break;}
					
					horarios(p,0);
					remove("dados.txt");
					p->quantidade=-1;
					
					printf("\nOPERACAO FEITA COM SUSCESSO\n\n");
					getchar();
					break;
					
			case 7:	printf("\n*****OBRIGADO POR UTILIZAR O PROGRAMADE AVIOES*****\n\n");
					break;
					
			default: printf("NUMERO INVALIDO, POR FAVOR DIGITE UM NUMERO VALIDO\n\n");
					break;
		}
		
		printf("aperte enter para continuar");
		getchar();
		
		system("cls");//isso aqui e para lipar a tela do terminal no windows
		//system("clear");//isso aqui e para lipar a tela do terminal no linux
		
	}while(opcao!=7);
	
	free(d);
	free(p);
	
	return 0;
}

void menu(){
	
	printf("---------- MENU ----------\n\n");
	
	printf("DIGITE O NUMERO DA OPCAO DESEJADA\n\n");
	
	printf("(1)-Cadastar novo cliente\n");
	printf("(2)-Dados de um cliente\n");
	printf("(3)-Relacao de todos os clientes\n");
	printf("(4)-Controle de valores adquiridos da venda das passagens\n");
	printf("(5)-Emissao de passagem\n");
	printf("(6)-Ir para o proximo voo\n");
	printf("(7)-Sair do programa\n\n");
	printf("OPCAO: ");
}

void cadastro(dados *pd){
	
	printf("Digite o nome do passageiro: ");
	while(1){
	fgets(pd->nomepassageiro,100,stdin);
	if(pd->nomepassageiro[0]!='\n'){break;}}
	
	printf("\nDigite o RG do passageiro: ");
	scanf("%i",&pd->rg);
	getchar();
	
	printf("\nDigite o valor pago pelo passageiro da passagem: ");
	scanf("%f",&pd->valorpago);
	getchar();
	
	printf("\nDigite o email do passageiro: ");
	while(1){
	fgets(pd->email,100,stdin);
	if(pd->email[0]!='\n'){break;}}
	
	printf("\nDigite o telofone do passageiro: ");
	while(1){
	fgets(pd->telefonepassageiro,100,stdin);
	if(pd->telefonepassageiro[0]!='\n'){break;}}
	
	printf("\nDigite o nome de uma pessoa para avisar em caso de acidentes: ");
	while(1){
	fgets(pd->nomeurgencia,100,stdin);
	if(pd->nomeurgencia[0]!='\n'){break;}}
	
	printf("\nTelofone dessa pessoa: ");
	while(1){
	fgets(pd->telefoneurgencia,100,stdin);
	if(pd->telefoneurgencia[0]!='\n'){break;}}
	
	printf("\n");
}

void dados_cliente(passageiros mostrar, int c){
	
	printf("Nome do passageiro: %s\n",mostrar.numero[c].nomepassageiro);
	
	printf("RG do passageiro: %i\n\n",mostrar.numero[c].rg);
	
	printf("Valor pago pelo passageiro da passagem: %f\n\n",mostrar.numero[c].valorpago);
	
	printf("Email do passageiro: %s\n",mostrar.numero[c].email);
	
	printf("Telofone do passageiro: %s\n",mostrar.numero[c].telefonepassageiro);
	
	printf("Nome da pessoa para avisar em caso de acidentes: %s\n",mostrar.numero[c].nomeurgencia);
	
	printf("Telofone dessa pessoa: %s\n",mostrar.numero[c].telefoneurgencia);
	
	printf("Telofone dessa pessoa: %s\n",mostrar.numero[c].telefoneurgencia);
}

void relacao_clientes(passageiros relacao){
	
	int num=0,x,y=0;
	if(relacao.quantidade<0){printf("\nSem clientes no momento\n\n");}
	
	else{
	while(1){
		
		printf("================================================================================================================================\n");
		printf("| RG: %i | ",relacao.numero[num].rg);
		printf("Codigo: %i | ",relacao.numero[num].cod);
		printf("Poltrona: %i | ",relacao.numero[num].cod+1);
		printf("Nome do passageiro: ");
		
		if(relacao.numero[num].nomepassageiro[0]==' '){y=1;}
		
		for(x=0;relacao.numero[num].nomepassageiro[x]!='\n';x++){
			
			if(y==0)printf("%c",relacao.numero[num].nomepassageiro[x]);
			else{y=0;}
		}
		printf(" |\n");
		if(num == relacao.quantidade){break;}
		num++;
	}
	
	printf("================================================================================================================================\n\n");}
	
}

void controle_vendas(passageiros relacao){
	
	int num=0;
	double soma=0;
	int x,y=0;
	
	if(relacao.quantidade < 0){printf("Sem clientes no momento\n\n");}
	
	else{
		do{
		
			printf("================================================================================================================================\n");
			printf("| RG: %i | ",relacao.numero[num].rg);
			printf("Codigo: %i | ",relacao.numero[num].cod);
			printf("Poltrona: %i | ",relacao.numero[num].cod);
			printf("Nome do passageiro: ");
			
			if(relacao.numero[num].nomepassageiro[0]==' '){y=1;}
			
			for(x=0;relacao.numero[num].nomepassageiro[x]!='\n';x++){
				if(y==0)printf("%c",relacao.numero[num].nomepassageiro[x]);
				else{y=0;}
			}
			printf(" | ");
		
			printf("Valor pago: %.2f |\n",relacao.numero[num].valorpago);
		
			soma = soma + relacao.numero[num].valorpago;
		
			num++;
		
		}while(num-1!= relacao.quantidade);
	
		printf("================================================================================================================================\n\n");
	}
	printf("Dinheiro total arrecadado: %.2lf\n\n",soma);
	soma=0;
}

void emissao_passagem(passageiros passagem,int c, int n, int ida, int chegada){
	
	FILE *file;
	file = fopen("passagem.txt","w");
	
	if(file==NULL){
		printf("ERRO AO IMPRIMIR A PASSAGEM\n\n");
		return;
	}
	
	else{printf("\nIMPRIMINDO\n\n");}
	
	fprintf(file,"*Numero do voo: %i\n\n*Horario de embarque: %i:00h\n*Horario de chegada: %i:00h\n\n*Numero da poltrona: %i\n\n",n,ida,chegada,passagem.numero[c].cod+1);
	
	fclose(file);
	
	getchar();
}

void horarios(passageiros *pp,int f){
	
	FILE *fi;
	
	fi = fopen("horario.txt","w");
	
	if(fi==NULL){
		printf("ERRO AO SALVAR OS HORARIOS DAS VIAGENS\n\n");
		return;
	}
	
	if(f==1){
		
		//if(fscanf(fi,"%i",&pp->numerovoo)==EOF){
			
		pp->numerovoo=1;
		pp->horarioembarque=0;
		pp->horariochegada=2;
	}
	
	else{
		pp->numerovoo++;
		if(pp->numerovoo>=13){pp->numerovoo=1;}
	
		pp->horarioembarque = pp->horarioembarque + 2;
		if(pp->horarioembarque>=24){pp->horarioembarque=0;}
		pp->horariochegada = pp->horarioembarque + 2;
		if(pp->horariochegada>=24){pp->horariochegada=0;}
	}
	
	fprintf(fi,"%i ",pp->numerovoo);
	fprintf(fi,"%i ",pp->horarioembarque);
	fprintf(fi,"%i ",pp->horariochegada);
	
	fclose(fi);
}

void salvar_dados(dados *pd){
	
	FILE *file;
	file = fopen("dados.txt","a");
	
	if(file==NULL){
		printf("ERRO AO SALVAR OS DADOS DOS PASSAGEIROS\n\n");
		return;
	}
	
	fprintf(file,"%s",pd->nomepassageiro);
	fprintf(file,"%i ",pd->rg);
	fprintf(file,"%f ",pd->valorpago);
	fprintf(file,"%s",pd->email);
	fprintf(file,"%s",pd->telefonepassageiro);
	fprintf(file,"%s",pd->nomeurgencia);
	fprintf(file,"%s",pd->telefoneurgencia);
	fprintf(file,"%i ",pd->cod);
	
	fclose(file);
}

void dar_dados(passageiros *pp){
	
	FILE *file,*file2;
	int x,y=0,z=0;
	
	file = fopen("dados.txt","r");
	
	pp->quantidade=0;
	
	if(file==NULL){
		//printf("ERRO AO RECEBER OS DADOS DOS PASSAGEIROS\n\n");
		y=1;
	}
	
	while(fgets(pp->numero[pp->quantidade].nomepassageiro,100,file)!=NULL){
		
		if(fscanf(file,"%i",&pp->numero[pp->quantidade].rg)== EOF){break;}
		
		fscanf(file,"%f",&pp->numero[pp->quantidade].valorpago);
		
		fgets(pp->numero[pp->quantidade].email,100,file);
		
		fgets(pp->numero[pp->quantidade].telefonepassageiro,100,file);
		
		fgets(pp->numero[pp->quantidade].nomeurgencia,100,file);
	
		fgets(pp->numero[pp->quantidade].telefoneurgencia,100,file);
		
		fscanf(file,"%i",&pp->numero[pp->quantidade].cod);
		
		z++;
		pp->quantidade++;
	}
	
	pp->quantidade--;
	
	
	//printf("%i",pp->quantidade);
	//getchar();
	
	fclose(file);
	
	file2 = fopen("horario.txt","r");
	
	if(file2==NULL){
		//printf("ERRO AO RECEBER OS DADOS DOS PASSAGEIROS\n\n");
		return;
	}
	
	fscanf(file2,"%i",&pp->numerovoo);
	fscanf(file2,"%i",&pp->horarioembarque);
	fscanf(file2,"%i",&pp->horariochegada);
	
	fclose(file2);
}

/*

nome do passageiro,
RG, 
valor pago,
e-mail, 
telefone pra contato, 
telefone e nome de uma pessoa para avisar em caso de acidentes

deverá mostrar os dados de um respectivo passageiro quando solicitado
a relação de todos passageiros mostrando RG e seu respectivo nome

Controle de valores adquiridos da venda das passagens

O Avião deverá ter 37 fileiras sendo que em cada fileira teremos as cadeiras AB CD, onde as cadeiras A e D são janelas e as demais corredores

A emissão de passagem deverá constar o número do voo,horário de embarque e horário de chegada além do numero da poltrona entre outras informações que acreditarem necessárias. 

*/