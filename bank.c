#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// o numero da conta, a senha e o nome do cliente estao em variaveis do tipo char, e o saldo esta em varivel do tipo float

void menu_inicial(float saldo[5], char nome[5][20], char conta[5][13], char senha[5][13], int senhaErrada[5], int tentativas[5]);
	/* funcao menu inicial: contem as opcoes de criar e acessar conta */
void criar_conta(char nome[5][20], char conta[5][13], char senha[5][13]);
	/* funcao criar conta: oferece ao usuario as opcoes de inserir seu nome, numero da conta e senha */
void acessar_conta(float saldo[5], char nome[5][20], char conta[5][13], char senha[5][13], int senhaErrada[5], int tentativas[5]);
	/* acessa a conta e permite a realizacao de depositos, saques, transferencia e consultas de saldo */
int verificar_senha(float saldo[5], char nome[5][20], char conta[5][13], char senha[5][13], int senhaErrada[5], int tentativas[5], int k);
    /*
        funcao verifica senha: verifica se o usuario digitou a senha correta e bloqueia a conta caso ele erre a senha 3
        vezes seguidas toda vez toda vez que ele tentar acessar a conta, sacar ou fazer uma transferencia. Ao acertar
        a senha, a contagem zera e usuario tera mais 3 chances de errar a senha novamente
    */
void depositar(float saldo[5], char nome[5][20], char conta[5][13], char senha[5][13], int k);
void sacar(float saldo[5], char nome[5][20], char conta[5][13], char senha[5][13], int senhaErrada[5], int tentativas[5], int k);
void transferir(float saldo[5], char nome[5][20], char conta[5][13], char senha[5][13], int senhaErrada[5], int tentativas[5], int k);
void consultar(float saldo[5], char nome[5][20], char conta[5][13], char senha[5][13], int k);

int main(){
    char nome[5][20], conta[5][13], senha[5][13], confere[] = "";
    float saldo[5];
    int senhaErrada[5], tentativas[5];

    for(int i = 0; i < 5; i++){
        strcpy(nome[i], confere);
    }
    for(int i = 0; i < 5; i++){
        strcpy(conta[i], confere);
    }
    for(int i = 0; i < 5; i++){
        strcpy(senha[i], confere);
    }
    for(int i = 0; i < 5; i++){
        saldo[i] = 0;
    }
    for(int i = 0; i < 5; i++){
        senhaErrada[i] = -1;
    }
    for(int i = 0; i < 5; i++){
        tentativas[i] = 2;
    }
    printf("\n");
    menu_inicial(saldo, nome, conta, senha, senhaErrada, tentativas);

    return 0;
}
void menu_inicial(float saldo[5], char nome[5][20], char conta[5][13], char senha[5][13], int senhaErrada[5], int tentativas[5]){
    int opcao;
    do{
        printf("\nBanco Imaginario\n\nSelecione uma opcao\n");
        printf("1. Criar conta\n2. Acessar conta\n0. Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 0:
                printf("Saindo...\n");
                break;
            case 1:
                criar_conta(nome, conta, senha);
                break;
            case 2:
                acessar_conta(saldo, nome, conta, senha, senhaErrada, tentativas);
                break;
            default:
                printf("Opcao invalida. Tente novamente!\n");
        }
    }while(opcao != 0);
}
void criar_conta(char nome[5][20], char conta[5][13], char senha[5][13]){

    for(int i = 0; i < 5; i++){
        if(strlen(nome[i]) == 0){
            printf("Digite seu nome: ");
            scanf(" %[^\n]", nome[i]);
            break;
        }
    }
    for(int i = 0; i < 5; i++){
        if(strlen(conta[i]) == 0){
            printf("Digite o numero da conta: ");
            scanf(" %[^\n]", conta[i]);
            break;
        }
    }
    for(int i = 0; i < 5; i++){
        if(strlen(senha[i]) == 0){
            printf("Digite sua senha: ");
            scanf(" %[^\n]", senha[i]);
            break;
        }
    }
}
void acessar_conta(float saldo[5], char nome[5][20], char conta[5][13], char senha[5][13], int senhaErrada[5], int tentativas[5]){
    int opcao = -1, i, k, contaErrada = -1;
    int verifica;
    char verificaConta[13];

    printf("\nDigite o numero da sua conta: ");
    scanf(" %[^\n]", verificaConta);

    for(i = 0; i < 5; i++){
        if(strcmp(conta[i], verificaConta)  == 0){
            k = i;
            if(senhaErrada[k] < 2){
                verifica = verificar_senha(saldo, nome, conta, senha, senhaErrada, tentativas, k);

                if(verifica == 1){
	                printf("\nCliente: %s\t", nome[i]);
	                printf("Conta: %s\n\n", conta[i]);
	                do{
	                	printf("\nSelecione um opcao: \n1. Deposito\n2. Saque\n3. Transferencia\n4. Consultar saldo\n0. Voltar\n");
		                scanf("%d", &opcao);
		                switch(opcao){
		                	case 0:
		                		break;
		                	case 1:
								depositar(saldo, nome, conta, senha, k);
								break;
							case 2:
								sacar(saldo, nome, conta, senha, senhaErrada, tentativas, k);
								break;
							case 3:
								transferir(saldo, nome, conta, senha, senhaErrada, tentativas, k);
								break;
							case 4:
								consultar(saldo, nome, conta, senha, k);
								break;
							default:
								printf("\nOpcao invalida. Tente novamente!\n");
						}
	                }while(opcao != 0);
	            }
			}
            else
	        	printf("\nSua conta foi bloqueada!\n");
        }
        else
            contaErrada++;
    }
    if(contaErrada == 4){
        printf("Essa conta nao existe!\n");
    }
    printf("\n");
}
int verificar_senha(float saldo[5], char nome[5][20], char conta[5][13], char senha[5][13], int senhaErrada[5], int tentativas[5], int k){
    char verificaSenha[13];

    printf("Digite sua senha: ");
    scanf(" %[^\n]", verificaSenha);

    for(int i = 0; i < 5; i++){
        if(strcmp(senha[k], verificaSenha)  == 0){
            senhaErrada[k] = -1;
            tentativas[k] = 2;
            return 1;
        }
        else if(senhaErrada[k] < 1){
            printf("\nAcesso negado, voce tem mais %d tentativa(s)\n", tentativas[k]);
            senhaErrada[k]++; // caso digitar a senha errada mais de 3x bloquear a conta
            tentativas[k]--;
            return 2;
        }
        else if(senhaErrada[k] == 1){
            printf("\nAcesso negado, sua conta foi bloqueada\n");
            senhaErrada[k]++; // caso digitar a senha errada mais de 3x bloquear a conta
            menu_inicial(saldo, nome, conta, senha, senhaErrada, tentativas);
        }
        else
            return 0;
    }
}
void depositar(float saldo[5], char nome[5][20], char conta[5][13], char senha[5][13], int k){
	float deposito;

	printf("Digite o valor do deposito: ");
	scanf("%f", &deposito);

	saldo[k] = deposito;
}
void sacar(float saldo[5], char nome[5][20], char conta[5][13], char senha[5][13], int senhaErrada[5], int tentativas[5], int k){
	float saque;
	int verifica, opcao;

	printf("\nDigite o valor do saque: ");
	scanf("%f", &saque);

	if(saldo[k] >= saque){
		if(senhaErrada[k] < 2){
            verifica = verificar_senha(saldo, nome, conta, senha, senhaErrada, tentativas, k);

            if(verifica == 1){
                do{
                    printf("Deseja sacar RS%.2f?\n", saque);
                    printf("1. Sim\n2. Nao\n");
                    scanf("%d", &opcao);
                    switch(opcao){
                        case 1:
                            saldo[k] -= saque;
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
void transferir(float saldo[5], char nome[5][20], char conta[5][13], char senha[5][13], int senhaErrada[5], int tentativas[5], int k){
	int verifica, opcao, contaInexistente = -1;
    char numConta[13];
    float transferencia;

	printf("\nDigite o numero da conta: ");
	scanf(" %[^\n]", numConta);

	for(int w = 0; w < 5; w++){
        if(strcmp(conta[w], numConta) == 0){
        	int y = w;
        	if(senhaErrada[w] >= 2){
                printf("A conta informada esta bloqueada\n");
        	}
        	else{
                printf("Digite o valor do transferencia: ");
                scanf("%f", &transferencia);

                if(saldo[k] >= transferencia){
                    if(senhaErrada[k] < 2){
                        verifica = verificar_senha(saldo, nome, conta, senha, senhaErrada, tentativas, k);

                        if(verifica == 1){
                            do{
                                printf("Deseja transferir RS%.2f para %s, conta %s?\n", transferencia, nome[y], conta[y]);
                                printf("1. Sim\n2. Nao\n");
                                scanf("%d", &opcao);
                                switch(opcao){
                                    case 1:
                                        saldo[k]-= transferencia;
                                        saldo[y] += transferencia;
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

        }
        else
        	contaInexistente++;
    }
	if(contaInexistente == 4){
		printf("A conta informada nao existe\n");
	}

}
void consultar(float saldo[5], char nome[5][20], char conta[5][13], char senha[5][13], int k){
	printf("\nNome: %s\t", nome[k]);
	printf("Conta: %s\t", conta[k]);
	printf("Saldo: %.2f\n", saldo[k]);
}
