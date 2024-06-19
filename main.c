#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 200
#define MAX_PHONE_LENGTH 15
#define MAX_STATUS_LENGTH 15

typedef struct {
    int codigo;
    char nome[MAX_NAME_LENGTH];
    char endereco[MAX_ADDRESS_LENGTH];
    char telefone[MAX_PHONE_LENGTH];
} Cliente;

typedef struct {
    int codigo;
    char nome[MAX_NAME_LENGTH];
    char telefone[MAX_PHONE_LENGTH];
    char funcao[MAX_NAME_LENGTH];
    double salario;
} Funcionario;

typedef struct {
    int numeroQuarto;
    int capacidadeHospedes;
    double taxaDiaria;
    char status[MAX_STATUS_LENGTH]; // "ocupado" ou "vago"
} Quarto;

typedef struct {
    int codigo;
    char dataCheckIn[11]; // DD/MM/YYYY
    char dataCheckOut[11]; // DD/MM/YYYY
    int numeroNoites;
    int codigoCliente;
    int numeroQuarto;
} Estadia;

// Fun��o para calcular a diferen�a em dias entre duas datas
int calcularNumeroNoites(const char *dataCheckInStr, const char *dataCheckOutStr) {
    int diaCheckIn, mesCheckIn, anoCheckIn;
    int diaCheckOut, mesCheckOut, anoCheckOut;

    sscanf(dataCheckInStr, "%d/%d/%d", &diaCheckIn, &mesCheckIn, &anoCheckIn);
    sscanf(dataCheckOutStr, "%d/%d/%d", &diaCheckOut, &mesCheckOut, &anoCheckOut);

    // C�lculo da diferen�a em dias
    int diasCheckIn = anoCheckIn * 365 + mesCheckIn * 30 + diaCheckIn;
    int diasCheckOut = anoCheckOut * 365 + mesCheckOut * 30 + diaCheckOut;

    return diasCheckOut - diasCheckIn;
}

// Fun��o para formatar a data do formato DDMMYYYY para DD/MM/YYYY
void formatarData(char *data) {
    char novaData[11];
    snprintf(novaData, sizeof(novaData), "%.2s/%.2s/%.4s", data, data + 2, data + 4);
    strcpy(data, novaData);
}

// Fun��o para criar uma string de data no formato DD/MM/YYYY a partir do dia, m�s e ano
void criarData(char *data, int dia, int mes, int ano) {
    snprintf(data, 11, "%02d/%02d/%04d", dia, mes, ano);
}

void registrarCliente() {
    Cliente cliente;
    int encontrado = 0;

    printf("Digite o c�digo do cliente: ");
    scanf("%d", &cliente.codigo);
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]s", cliente.nome);
    printf("Digite o endere�o do cliente: ");
    scanf(" %[^\n]s", cliente.endereco);
    printf("Digite o telefone do cliente: ");
    scanf(" %[^\n]s", cliente.telefone);

    FILE *arquivoLeitura = fopen("clientes.txt", "r");
    if (arquivoLeitura != NULL) {
        Cliente temp;
        while (fscanf(arquivoLeitura, "%d %[^\n] %[^\n] %[^\n]", &temp.codigo, temp.nome, temp.endereco, temp.telefone) == 4) {
            if (temp.codigo == cliente.codigo) {
                encontrado = 1;
                break;
            }
        }
        fclose(arquivoLeitura);
    }

    if (!encontrado) {
        FILE *arquivoEscrita = fopen("clientes.txt", "a");
        fprintf(arquivoEscrita, "%d\n%s\n%s\n%s\n", cliente.codigo, cliente.nome, cliente.endereco, cliente.telefone);
        fclose(arquivoEscrita);
        printf("Cliente registrado com sucesso!\n");
    } else {
        printf("C�digo de cliente j� existe. Registro falhou.\n");
    }
}

void registrarFuncionario() {
    Funcionario funcionario;
    int encontrado = 0;

    printf("Digite o c�digo do funcion�rio: ");
    scanf("%d", &funcionario.codigo);
    printf("Digite o nome do funcion�rio: ");
    scanf(" %[^\n]s", funcionario.nome);
    printf("Digite o telefone do funcion�rio: ");
    scanf(" %[^\n]s", funcionario.telefone);
    printf("Digite a fun��o do funcion�rio: ");
    scanf(" %[^\n]s", funcionario.funcao);
    printf("Digite o sal�rio do funcion�rio: ");
    scanf("%lf", &funcionario.salario);

    FILE *arquivoLeitura = fopen("funcionarios.txt", "r");
    if (arquivoLeitura != NULL) {
        Funcionario temp;
        while (fscanf(arquivoLeitura, "%d %[^\n] %[^\n] %[^\n] %lf", &temp.codigo, temp.nome, temp.telefone, temp.funcao, &temp.salario) == 5) {
            if (temp.codigo == funcionario.codigo) {
                encontrado = 1;
                break;
            }
        }
        fclose(arquivoLeitura);
    }

    if (!encontrado) {
        FILE *arquivoEscrita = fopen("funcionarios.txt", "a");
        fprintf(arquivoEscrita, "%d\n%s\n%s\n%s\n%lf\n", funcionario.codigo, funcionario.nome, funcionario.telefone, funcionario.funcao, funcionario.salario);
        fclose(arquivoEscrita);
        printf("Funcion�rio registrado com sucesso!\n");
    } else {
        printf("C�digo de funcion�rio j� existe. Registro falhou.\n");
    }
}

void registrarQuarto() {
    Quarto quarto;
    int encontrado = 0;

    printf("Digite o n�mero do quarto: ");
    scanf("%d", &quarto.numeroQuarto);
    printf("Digite a capacidade de h�spedes: ");
    scanf("%d", &quarto.capacidadeHospedes);
    printf("Digite a taxa di�ria: ");
    scanf("%lf", &quarto.taxaDiaria);
    strcpy(quarto.status, "vago");

    FILE *arquivoLeitura = fopen("quartos.txt", "r");
    if (arquivoLeitura != NULL) {
        Quarto temp;
        while (fscanf(arquivoLeitura, "%d %d %lf %[^\n]", &temp.numeroQuarto, &temp.capacidadeHospedes, &temp.taxaDiaria, temp.status) == 4) {
            if (temp.numeroQuarto == quarto.numeroQuarto) {
                encontrado = 1;
                break;
            }
        }
        fclose(arquivoLeitura);
    }

    if (!encontrado) {
        FILE *arquivoEscrita = fopen("quartos.txt", "a");
        fprintf(arquivoEscrita, "%d\n%d\n%lf\n%s\n", quarto.numeroQuarto, quarto.capacidadeHospedes, quarto.taxaDiaria, quarto.status);
        fclose(arquivoEscrita);
        printf("Quarto registrado com sucesso!\n");
    } else {
        printf("N�mero do quarto j� existe. Registro falhou.\n");
    }
}

void registrarEstadia() {
    Estadia estadia;
    int clienteEncontrado = 0, quartoEncontrado = 0, estadiaValida = 1;
    int diaCheckIn, mesCheckIn, anoCheckIn, diaCheckOut, mesCheckOut, anoCheckOut;

    printf("Digite o c�digo da estadia: ");
    scanf("%d", &estadia.codigo);

    printf("Digite a data de check-in:\n");
    printf("Dia: ");
    scanf("%d", &diaCheckIn);
    printf("M�s: ");
    scanf("%d", &mesCheckIn);
    printf("Ano: ");
    scanf("%d", &anoCheckIn);
    criarData(estadia.dataCheckIn, diaCheckIn, mesCheckIn, anoCheckIn);

    printf("Digite a data de check-out:\n");
    printf("Dia: ");
    scanf("%d", &diaCheckOut);
    printf("M�s: ");
    scanf("%d", &mesCheckOut);
    printf("Ano: ");
    scanf("%d", &anoCheckOut);
    criarData(estadia.dataCheckOut, diaCheckOut, mesCheckOut, anoCheckOut);

    // Verificar se a data de check-out � posterior � data de check-in
    if (strcmp(estadia.dataCheckIn, estadia.dataCheckOut) >= 0) {
        printf("Datas inv�lidas. A data de check-out deve ser posterior � data de check-in. Registro de estadia falhou.\n");
        return;
    }

    estadia.numeroNoites = calcularNumeroNoites(estadia.dataCheckIn, estadia.dataCheckOut);
    if (estadia.numeroNoites <= 0) {
        printf("Datas inv�lidas. Registro de estadia falhou.\n");
        return;
    }

    printf("Digite o c�digo do cliente: ");
    scanf("%d", &estadia.codigoCliente);
    printf("Digite o n�mero do quarto: ");
    scanf("%d", &estadia.numeroQuarto);

    // Verificar se o cliente existe
    FILE *arquivoLeituraCliente = fopen("clientes.txt", "r");
    if (arquivoLeituraCliente != NULL) {
        Cliente tempCliente;
        while (fscanf(arquivoLeituraCliente, "%d %[^\n] %[^\n] %[^\n]", &tempCliente.codigo, tempCliente.nome, tempCliente.endereco, tempCliente.telefone) == 4) {
            if (tempCliente.codigo == estadia.codigoCliente) {
                clienteEncontrado = 1;
                break;
            }
        }
        fclose(arquivoLeituraCliente);
    }

    if (!clienteEncontrado) {
        printf("C�digo de cliente n�o encontrado. Registro de estadia falhou.\n");
        return;
    }

    // Verificar se o quarto existe e est� dispon�vel
    FILE *arquivoLeituraQuarto = fopen("quartos.txt", "r");
    FILE *arquivoEscritaQuartoTemp = fopen("quartos_temp.txt", "w");
    if (arquivoLeituraQuarto != NULL && arquivoEscritaQuartoTemp != NULL) {
        Quarto tempQuarto;
        while (fscanf(arquivoLeituraQuarto, "%d %d %lf %[^\n]", &tempQuarto.numeroQuarto, &tempQuarto.capacidadeHospedes, &tempQuarto.taxaDiaria, tempQuarto.status) == 4) {
            if (tempQuarto.numeroQuarto == estadia.numeroQuarto) {
                quartoEncontrado = 1;
                if (strcmp(tempQuarto.status, "ocupado") == 0) {
                    estadiaValida = 0;
                    printf("Quarto j� est� ocupado. Registro de estadia falhou.\n");
                } else {
                    strcpy(tempQuarto.status, "ocupado");
                }
            }
            fprintf(arquivoEscritaQuartoTemp, "%d\n%d\n%lf\n%s\n", tempQuarto.numeroQuarto, tempQuarto.capacidadeHospedes, tempQuarto.taxaDiaria, tempQuarto.status);
        }
        fclose(arquivoLeituraQuarto);
        fclose(arquivoEscritaQuartoTemp);
        remove("quartos.txt");
        rename("quartos_temp.txt", "quartos.txt");
    }

    if (!quartoEncontrado) {
        printf("N�mero de quarto n�o encontrado. Registro de estadia falhou.\n");
        return;
    }

    if (estadiaValida) {
        FILE *arquivoEscrita = fopen("estadias.txt", "a");
        fprintf(arquivoEscrita, "%d\n%s\n%s\n%d\n%d\n%d\n", estadia.codigo, estadia.dataCheckIn, estadia.dataCheckOut, estadia.numeroNoites, estadia.codigoCliente, estadia.numeroQuarto);
        fclose(arquivoEscrita);
        printf("Estadia registrada com sucesso!\n");
    }
}

void listarClientes() {
    FILE *arquivoLeitura = fopen("clientes.txt", "r");
    if (arquivoLeitura != NULL) {
        Cliente cliente;
        while (fscanf(arquivoLeitura, "%d %[^\n] %[^\n] %[^\n]", &cliente.codigo, cliente.nome, cliente.endereco, cliente.telefone) == 4) {
            printf("C�digo: %d\n", cliente.codigo);
            printf("Nome: %s\n", cliente.nome);
            printf("Endere�o: %s\n", cliente.endereco);
            printf("Telefone: %s\n", cliente.telefone);
            printf("--------------------\n");
        }
        fclose(arquivoLeitura);
    } else {
        printf("Erro ao abrir o arquivo de clientes.\n");
    }
}

void listarFuncionarios() {
    FILE *arquivoLeitura = fopen("funcionarios.txt", "r");
    if (arquivoLeitura != NULL) {
        Funcionario funcionario;
        while (fscanf(arquivoLeitura, "%d %[^\n] %[^\n] %[^\n] %lf", &funcionario.codigo, funcionario.nome, funcionario.telefone, funcionario.funcao, &funcionario.salario) == 5) {
            printf("C�digo: %d\n", funcionario.codigo);
            printf("Nome: %s\n", funcionario.nome);
            printf("Telefone: %s\n", funcionario.telefone);
            printf("Fun��o: %s\n", funcionario.funcao);
            printf("Sal�rio: %.2lf\n", funcionario.salario);
            printf("--------------------\n");
        }
        fclose(arquivoLeitura);
    } else {
        printf("Erro ao abrir o arquivo de funcion�rios.\n");
    }
}

void listarQuartos() {
    FILE *arquivoLeitura = fopen("quartos.txt", "r");
    if (arquivoLeitura != NULL) {
        Quarto quarto;
        while (fscanf(arquivoLeitura, "%d %d %lf %[^\n]", &quarto.numeroQuarto, &quarto.capacidadeHospedes, &quarto.taxaDiaria, quarto.status) == 4) {
            printf("N�mero do quarto: %d\n", quarto.numeroQuarto);
            printf("Capacidade de h�spedes: %d\n", quarto.capacidadeHospedes);
            printf("Taxa di�ria: %.2lf\n", quarto.taxaDiaria);
            printf("Status: %s\n", quarto.status);
            printf("--------------------\n");
        }
        fclose(arquivoLeitura);
    } else {
        printf("Erro ao abrir o arquivo de quartos.\n");
    }
}

void listarEstadias() {
    FILE *arquivoLeitura = fopen("estadias.txt", "r");
    if (arquivoLeitura != NULL) {
        Estadia estadia;
        while (fscanf(arquivoLeitura, "%d %[^\n] %[^\n] %d %d %d", &estadia.codigo, estadia.dataCheckIn, estadia.dataCheckOut, &estadia.numeroNoites, &estadia.codigoCliente, &estadia.numeroQuarto) == 6) {
            printf("C�digo: %d\n", estadia.codigo);
            printf("Data de check-in: %s\n", estadia.dataCheckIn);
            printf("Data de check-out: %s\n", estadia.dataCheckOut);
            printf("N�mero de noites: %d\n", estadia.numeroNoites);
            printf("C�digo do cliente: %d\n", estadia.codigoCliente);
            printf("N�mero do quarto: %d\n", estadia.numeroQuarto);
            printf("--------------------\n");
        }
        fclose(arquivoLeitura);
    } else {
        printf("Erro ao abrir o arquivo de estadias.\n");
    }
}

// Fun��o para ler os dados de estadia de um arquivo
int lerEstadiaPorCodigo(int codigo, Estadia *estadia) {
    FILE *arquivoLeitura = fopen("estadias.txt", "r");
    if (arquivoLeitura == NULL) {
        printf("Erro ao abrir o arquivo de estadias.\n");
        return 0;
    }

    while (fscanf(arquivoLeitura, "%d %[^\n] %[^\n] %d %d %d", &estadia->codigo, estadia->dataCheckIn, estadia->dataCheckOut, &estadia->numeroNoites, &estadia->codigoCliente, &estadia->numeroQuarto) == 6) {
        if (estadia->codigo == codigo) {
            fclose(arquivoLeitura);
            return 1; // Encontrou a estadia
        }
    }

    fclose(arquivoLeitura);
    return 0; // Estadia n�o encontrada
}

void cancelarEstadia() {
    int codigoEstadia;
    printf("Digite o c�digo da estadia que deseja cancelar: ");
    scanf("%d", &codigoEstadia);

    FILE *arquivoLeitura = fopen("estadias.txt", "r");
    FILE *arquivoEscritaTemp = fopen("estadias_temp.txt", "w");

    if (arquivoLeitura == NULL || arquivoEscritaTemp == NULL) {
        printf("Erro ao abrir os arquivos de estadias.\n");
        return;
    }

    Estadia estadia;
    int encontrada = 0;

    while (fscanf(arquivoLeitura, "%d %[^\n] %[^\n] %d %d %d", &estadia.codigo, estadia.dataCheckIn, estadia.dataCheckOut, &estadia.numeroNoites, &estadia.codigoCliente, &estadia.numeroQuarto) == 6) {
        if (estadia.codigo == codigoEstadia) {
            encontrada = 1;
            continue; // Pula a estadia a ser cancelada
        }
        fprintf(arquivoEscritaTemp, "%d\n%s\n%s\n%d\n%d\n%d\n", estadia.codigo, estadia.dataCheckIn, estadia.dataCheckOut, estadia.numeroNoites, estadia.codigoCliente, estadia.numeroQuarto);
    }

    fclose(arquivoLeitura);
    fclose(arquivoEscritaTemp);

    if (!encontrada) {
        printf("Estadia n�o encontrada. Cancelamento falhou.\n");
        remove("estadias_temp.txt"); // Remove o arquivo tempor�rio
    } else {
        remove("estadias.txt");
        rename("estadias_temp.txt", "estadias.txt");
        printf("Estadia cancelada com sucesso!\n");
    }
}

void menu() {
    int opcao;

    do {
        printf("========== MENU ==========\n");
        printf("1 - Registrar cliente\n");
        printf("2 - Registrar funcion�rio\n");
        printf("3 - Registrar quarto\n");
        printf("4 - Registrar estadia\n");
        printf("5 - Listar clientes\n");
        printf("6 - Listar funcion�rios\n");
        printf("7 - Listar quartos\n");
        printf("8 - Listar estadias\n");
        printf("9 - Cancelar estadias\n");
        printf("0 - Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

switch (opcao) {
    case 1:
        registrarCliente();
        break;
    case 2:
        registrarFuncionario();
        break;
    case 3:
        registrarQuarto();
        break;
    case 4:
        registrarEstadia();
        break;
    case 5:
        listarClientes();
        break;
    case 6:
        listarFuncionarios();
        break;
    case 7:
        listarQuartos();
        break;
    case 8:
        listarEstadias();
        break;
    case 9:
        cancelarEstadia();
        break;
    case 0:
        printf("Encerrando o programa...\n");
        break;
    default:
        printf("Op��o inv�lida. Tente novamente.\n");
}

    } while (opcao != 0);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    menu();

    return 0;
}
