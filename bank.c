#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	/* Commit */
void menu_inicial(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int senhaErrada[5], int tentativas[5]);
	/* menu inicial - contem as opcoes de criar e acessar conta */
void criar_conta(char nomeCliente[5][20], int contaSenhaSaldo[5][3]);
	/* oferece ao usuario as opcoes de inserir seu nome, numero da conta e senha */
void acessar_conta(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int senhaErrada[5], int tentativas[5]);
	/* acessa a conta e permite a realizacao de depositos, saques, transferencia e consultas de saldo */
void depositar(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int k);
void sacar(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int k);
void transferir(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int k);
void consultar(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int k);

int main(){
    char nomeCliente[5][20], confere[] = "";
    int contaSenhaSaldo[5][3], senhaErrada[5], tentativas[5];

    for(int i = 0; i < 5; i++){
        strcpy(nomeCliente[i], confere);
    }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 3; j++){
            contaSenhaSaldo[i][j] = 0;
        }
    }
    for(int i = 0; i < 5; i++){
        senhaErrada[i] = -1;
    }
    for(int i = 0; i < 5; i++){
        tentativas[i] = 2;
    }
    printf("\n");
    menu_inicial(nomeCliente, contaSenhaSaldo, senhaErrada, tentativas);

    return 0;
}
void menu_inicial(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int senhaErrada[5], int tentativas[5]){
    int opcao;
    do{
        printf("1. Criar conta\n2. Acessar conta\n0. Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 0:
                printf("Saindo...\n");
                break;
            case 1:
                criar_conta(nomeCliente, contaSenhaSaldo);
                break;
            case 2:
                acessar_conta(nomeCliente, contaSenhaSaldo, senhaErrada, tentativas);
                break;
        }
    }while(opcao != 0);
}
void criar_conta(char nomeCliente[5][20], int contaSenhaSaldo[5][3]){

    for(int i = 0; i < 5; i++){
        if(strlen(nomeCliente[i]) == 0){
            printf("Digite seu nome[%d]: ", i);
            scanf(" %[^\n]", nomeCliente[i]);
            break;
        }
    }
    for(int i = 0, j = 0; i < 5; i++){
        if(contaSenhaSaldo[i][j] == 0){
            printf("Digite o numero da conta[%d][%d]: ", i, j);
            scanf("%d", &contaSenhaSaldo[i][j]);
            break;
        }
    }
    for(int i = 0, j = 1; i < 5; i++){
        if(contaSenhaSaldo[i][j] == 0){
            printf("Digite sua senha[%d][%d]: ", i, j);
            scanf("%d", &contaSenhaSaldo[i][j]);
            break;
        }
    }
}
void acessar_conta(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int senhaErrada[5], int tentativas[5]){
    char verifica[20];
    int i, k, verificaConta, verificaSenha, contaErrada = -1;

    printf("Digite o numero da sua conta: ");
    scanf("%d", &verificaConta);

    for(i = 0; i < 5; i++){
        if(verificaConta == contaSenhaSaldo[i][0]){
            k = i;
            if(senhaErrada[k] < 2){
            	printf("Digite sua senha: ");
	            scanf("%d", &verificaSenha);

            	if(verificaSenha == contaSenhaSaldo[i][1]){
            		int opcao;
	            	senhaErrada[k] = -1;
	            	tentativas[k] = 2;
	                printf("\nCliente: %s\t", nomeCliente[i]);
	                printf("Conta: %d\t", contaSenhaSaldo[i][0]);
	                do{
	                	printf("\nSelecione um opcao: \n1. Deposito\n2. Saque\n3. Transferencia\n4. Consultar saldo\n0. Voltar\n");
		                scanf("%d", &opcao);
		                switch(opcao){
		                	case 0:
		                		break;
		                	case 1:
								depositar(nomeCliente, contaSenhaSaldo, k);
								break;
							case 2:
								sacar(nomeCliente, contaSenhaSaldo, k);
								break;
							case 3:
								transferir(nomeCliente, contaSenhaSaldo, k);
								break;
							case 4:
								consultar(nomeCliente, contaSenhaSaldo, k);
								break;
							default:
								printf("Opcao invalida. Tente novamente!\n");
						}
	                }while(opcao != 0);
	            }
	            else if(verificaSenha != contaSenhaSaldo[i][1] && senhaErrada[k] < 1){
	                printf("Acesso negado, voce tem mais %d tentativa(s)\n", tentativas[k]); // aviso de tentativas restantes
	                senhaErrada[k]++; // caso digitar a senha errada mais de 3x bloquear o cartao
	                tentativas[k]--;
	                break;
	            }
	            else if(verificaSenha != contaSenhaSaldo[i][1] && senhaErrada[k] == 1){
	                printf("Acesso negado, seu cartao foi bloqueado\n");
	                senhaErrada[k]++; // caso digitar a senha errada mais de 3x bloquear o cartao
	                break;
	            }
			}
            else
	        	printf("Seu cartao foi bloqueado!\n");
        }
        else
            contaErrada++;
    }
    if(contaErrada == 4){
        printf("Essa conta nao existe!\n");
    }
    printf("\n");
}
void depositar(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int k){
	int deposito;

	printf("Digite o valor do deposito: ");
	scanf("%d", &deposito);

	contaSenhaSaldo[k][2] = deposito;
}
void sacar(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int k){
	int saque, senha, opcao;

	printf("Digite o valor do saque: ");
	scanf("%d", &saque);

	if(contaSenhaSaldo[k][2] >= saque){
		printf("Digite sua senha: ");
		scanf("%d", &senha);

		if(contaSenhaSaldo[k][1] == senha){
			printf("Deseja sacar RS%d?\n", saque);
			printf("1. Sim\n2. Nao\n");
			scanf("%d", &opcao);

			if(opcao == 1){
				contaSenhaSaldo[k][2] -= saque;
			}
			else
				printf("Operacao cancelada\n");
		}
		else
			printf("Senha invalida. Tente novamente!\n");
	}
	else
		printf("Saldo insuficiente!\n");
}
void transferir(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int k){
	int senha, opcao, numConta, contaInexistente = -1;

	printf("Digite o numero da conta: ");
	scanf("%d", &numConta);
	for(int w = 0; w < 5; w++){
        if(contaSenhaSaldo[w][0] == numConta){
        	int transferencia, y = w, z = w;
			printf("Digite o valor do transferencia: ");
			scanf("%d", &transferencia);

			if(contaSenhaSaldo[k][2] >= transferencia){
				printf("Digite sua senha: ");
				scanf("%d", &senha);

				if(contaSenhaSaldo[k][1] == senha){
					printf("Deseja transferir RS%d para %s a conta %d?\n", transferencia, nomeCliente[y], contaSenhaSaldo[y][0]);
					printf("1. Sim\n2. Nao\n");
					scanf("%d", &opcao);

					if(opcao == 1){
						contaSenhaSaldo[k][2] -= transferencia;
						contaSenhaSaldo[y][2] += transferencia;
					}
					else
						printf("Operacao cancelada\n");
				}
				else
					printf("Senha invalida. Tente novamente!\n");
			}
			else
				printf("Saldo insuficiente!\n");
        }
        else
        	contaInexistente++;
    }
	if(contaInexistente == 4){
		printf("A conta informada nao existe\n");
	}

}
void consultar(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int k){
	printf("\nNome: %s\t", nomeCliente[k]);
	printf("Conta: %d\t", contaSenhaSaldo[k][0]);
	printf("Saldo: %d\n", contaSenhaSaldo[k][2]);
}
