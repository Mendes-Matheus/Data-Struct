#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu_inicial(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int senhaErrada[5], int tentativas[5]);
	/* menu inicial - contem as opcoes de criar e acessar conta */
void criar_conta(char nomeCliente[5][20], int contaSenhaSaldo[5][3]);
	/* oferece ao usuario as opcoes de inserir seu nome, numero da conta e senha */
void acessar_conta(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int senhaErrada[5], int tentativas[5]);
	/* acessa a conta e permite a realizacao de depositos, saques, transferencia e consultas de saldo */
int verificar_senha(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int senhaErrada[5], int tentativas[5], int k);
    /*
        verifica se o usuario digitou a senha correta e bloqueia o cartao caso ele erre a senha 3 vezes seguidas toda vez
        toda vez que ele tentar acessar a conta, sacar ou fazer uma transferencia. Ao acertar a senha, a contagem zera e
        usuario tera mais 3 chances de errar a senha novamente
    */
void depositar(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int k);
void sacar(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int senhaErrada[5], int tentativas[5], int k);
void transferir(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int senhaErrada[5], int tentativas[5], int k);
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
            default:
                printf("Opcao invalida. Tente novamente!\n");
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
    int opcao = -1, i, k, verificaConta, verificaSenha, contaErrada = -1;
    int verifica;

    printf("\nDigite o numero da sua conta: ");
    scanf("%d", &verificaConta);

    for(i = 0; i < 5; i++){
        if(verificaConta == contaSenhaSaldo[i][0]){
            k = i;
            if(senhaErrada[k] < 2){
                verifica = verificar_senha(nomeCliente, contaSenhaSaldo, senhaErrada, tentativas, k);

                if(verifica == 1){
	                printf("\nCliente: %s\t", nomeCliente[i]);
	                printf("Conta: %d\n\n", contaSenhaSaldo[i][0]);
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
								sacar(nomeCliente, contaSenhaSaldo, senhaErrada, tentativas, k);
								break;
							case 3:
								transferir(nomeCliente, contaSenhaSaldo, senhaErrada, tentativas, k);
								break;
							case 4:
								consultar(nomeCliente, contaSenhaSaldo, k);
								break;
							default:
								printf("\nOpcao invalida. Tente novamente!\n");
						}
	                }while(opcao != 0);
	            }
			}
            else
	        	printf("\nSeu cartao foi bloqueado!\n");
        }
        else
            contaErrada++;
    }
    if(contaErrada == 4){
        printf("Essa conta nao existe!\n");
    }
    printf("\n");
}
int verificar_senha(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int senhaErrada[5], int tentativas[5], int k){
    int verificaConta, verificaSenha, contaErrada = -1;

    printf("Digite sua senha: ");
    scanf("%d", &verificaSenha);
    for(int i = 0; i < 5; i++){
        if(verificaSenha == contaSenhaSaldo[k][1]){
            senhaErrada[k] = -1;
            tentativas[k] = 2;
            return 1;
        }
        else if(verificaSenha != contaSenhaSaldo[k][1] && senhaErrada[k] < 1){
            printf("\nAcesso negado, voce tem mais %d tentativa(s)\n", tentativas[k]);
            senhaErrada[k]++; // caso digitar a senha errada mais de 3x bloquear o cartao
            tentativas[k]--;
            return 2;
        }
        else if(verificaSenha != contaSenhaSaldo[k][1] && senhaErrada[k] == 1){
            printf("\nAcesso negado, seu cartao foi bloqueado\n");
            senhaErrada[k]++; // caso digitar a senha errada mais de 3x bloquear o cartao
            menu_inicial(nomeCliente, contaSenhaSaldo, senhaErrada, tentativas);
        }
        else
            return 0;
    }
}
void depositar(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int k){
	int deposito;

	printf("Digite o valor do deposito: ");
	scanf("%d", &deposito);

	contaSenhaSaldo[k][2] = deposito;
}
void sacar(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int senhaErrada[5], int tentativas[5], int k){
	int saque, senha, opcao;
	int verifica;

	printf("\nDigite o valor do saque: ");
	scanf("%d", &saque);

	if(contaSenhaSaldo[k][2] >= saque){
		if(senhaErrada[k] < 2){
            verifica = verificar_senha(nomeCliente, contaSenhaSaldo, senhaErrada, tentativas, k);

            if(verifica == 1){
                do{
                    printf("Deseja sacar RS%d?\n", saque);
                    printf("1. Sim\n2. Nao\n");
                    scanf("%d", &opcao);
                    switch(opcao){
                        case 1:
                            contaSenhaSaldo[k][2] -= saque;
                            break;
                        case 2:
                            printf("Operacao cancelada!\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                }while(opcao != 2 && opcao != 1);
            }
        }
	}
    else
        printf("Saldo insuficiente!\n");
}
void transferir(char nomeCliente[5][20], int contaSenhaSaldo[5][3], int senhaErrada[5], int tentativas[5], int k){
	int senha, opcao, numConta, contaInexistente = -1;
	int verifica;

	printf("\nDigite o numero da conta: ");
	scanf("%d", &numConta);
	for(int w = 0; w < 5; w++){
        if(contaSenhaSaldo[w][0] == numConta){
        	int transferencia, y = w, z = w;
			printf("Digite o valor do transferencia: ");
			scanf("%d", &transferencia);

			if(contaSenhaSaldo[k][2] >= transferencia){
				if(senhaErrada[k] < 2){
                    verifica = verificar_senha(nomeCliente, contaSenhaSaldo, senhaErrada, tentativas, k);

                    if(verifica == 1){
                        do{
                            printf("Deseja transferir RS%d para %s a conta %d?\n", transferencia, nomeCliente[y], contaSenhaSaldo[y][0]);
                            printf("1. Sim\n2. Nao\n");
                            scanf("%d", &opcao);
                            switch(opcao){
                                case 1:
                                    contaSenhaSaldo[k][2] -= transferencia;
                                    contaSenhaSaldo[y][2] += transferencia;
                                    break;
                                case 2:
                                    printf("Operacao cancelada\n");
                                    break;
                                default:
                                    printf("Opcao invalida!\n");
                            }
                        }while(opcao != 2 && opcao != 1);
                    }
				}
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
