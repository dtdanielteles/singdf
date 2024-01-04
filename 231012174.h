#ifndef DANIEL_H
#define DANIEL_H

/******************************************************************************
Aluno(a): Daniel Teles Brito
Matrícula: 231012174
Declaro que eu sou o(a) autor(a) deste trabalho e que o código não foi copiado
de outra pessoa nem repassado para alguém. Estou ciente de que poderei sofrer
penalizações na avaliação em caso de detecção de plágio.
*******************************************************************************/

// Inclusões de bibliotecas para:
#include <stdio.h> // Operações básicas de entrada e saída
#include <stdlib.h> // Alocação dinâmica de memória, conversão de tipos, etc
#include <string.h> // Manipulação de string
#include <locale.h>  // Configurar local e linguagem padrão
#include <stdbool.h> // Trabalhar com booleanos
#include <ctype.h> // Manipulação de caracteres
#include <conio.h> // Utiliar a função getch() no Windows

// Definição de tamanhos máximos de dados
#define TAM_MAX_NOME 100
#define TAM_MAX_CNPJ 19 // Considera CNPJ com separadoes no formarto: XX.XXX.XXX/0001-XX
#define TAM_MAX_STATUS 50
#define TAM_MAX_ID_CONTRATO 4
#define TAM_MAX_ID_CONSUMIDOR 19 // Considera o CNPJ no formato acima como valor máximo para ID
#define TAM_MAX_CNPJ_NUMERICO 15 // Considea CNPJ somente números
#define TAM_MAX_CPF_NUMERICO 12 // Considera CPF apenas números
#define TAM_MAX_DATA 11 // Considera data no formato DD/MM/AAAA
#define QUANT_MAX_MINIUSINAS 50 // Máximo de miniusinas no vetor lista
#define QUANT_MAX_RAS 33 // Máximo de RAs no vetor de listas

// Definição de constantes para as opções do menu
#define CONSULTAR_MINIUSINA 1
#define CONSULTAR_CONSUMIDOR 2
#define LISTAR_MINIUSINAS 3
#define LISTAR_MINIUSINAS_DESCRESCENTE_CAPACIDADE 4
#define LISTAR_RAS_DESCRESCENTE_QUANTIDADE 5
#define LISTAR_RAS_CRESCENTE_CONTRATOS 6
#define LISTAR_RAS_DESCRESCENTE_CAPACIDADE 7
#define LISTAR_RAS_DESCRESCENTE_PERCENTUAL 8
#define SAIR 9

// Struct de uma miniusina
struct miniusina{
    char cnpj[TAM_MAX_CNPJ]; // CNPJ da miniusina
    char nome[TAM_MAX_NOME]; // Nome da miniusina
    float capacidade; // Capacidade de geração de energia em Kwh
    int id_ra; // Número da RA
    char status[TAM_MAX_STATUS]; // Status de operação
    float energia_contratada; // Energia contratada nesta miniuinada
};

// Struct de um contrato
struct contrato{
    char id_contrato[TAM_MAX_ID_CONTRATO]; // Número do contrato
    char id_consumidor[TAM_MAX_ID_CONSUMIDOR]; // CPF ou CNPJ do consumidor
    char cnpj[TAM_MAX_CNPJ]; // CNPJ da miniusina
    char data_inicio[TAM_MAX_DATA]; // Data de início do contrato
    float energia_contratada; // Quantidade de energia contratada em Kwh
};

// Struct de um consumidor
struct consumidor{
    char id_consumidor[TAM_MAX_ID_CONSUMIDOR]; // CPF ou CNPJ do consumidor
    char nome[TAM_MAX_NOME]; // Nome do consmidor
    int id_ra; // Número da RA
};

// Struct de uma RA
struct ra{
    int id_ra; // Número da RA
    char nome_ra[TAM_MAX_NOME]; // Nome da RA
    int quantidade_miniusinas; // Quantidade de miniusinas por RA
    float capacidade; // Capacidade total de geração de energia da RA
    float percentual; // Percentual de energia disponível em cada RA
    int total_contratos; // Total de contratos da RA
    float energia_contratada; // Energia contratada nesta RA
};

// Procedimento para exibição do menu
void menu(){
    printf("************************************\n");
    printf("         BEM-VINDO AO SINGDF        \n");
    printf("************************************\n\n");
    printf("=> Escolha uma das opções do menu abaixo:\n\n");
    printf("1) Consultar miniusina cadastrada\n");
    printf("2) Consultar consumidor cadastrado\n");
    printf("3) Listar as miniusinas cadastradas\n");
    printf("4) Listar as miniusinas em operação por ordem decrescente de capacidade de geração de energia\n");
    printf("5) Listar as RAs por ordem decrescente de quantidade de miniusinas\n");
    printf("6) Listar as RAs por ordem crescente de número de contratos\n");
    printf("7) Listar as RAs por ordem decrescente de capacidade de geração\n");
    printf("8) Listar as RAs por ordem decrescente de percentual de energia disponível\n");
    printf("9) Sair do programa\n\n");
}

// Procedimento para limpeza do buffer do teclado e posibilitar a leitura do nome
void limpar_buffer(){
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Procedimento que suspende a execução e aguarda o usuário apertar alguma tecla para retornar ao menu
void pausa(){
    printf("Pressione qualquer tecla para continuar...");
    #if defined(linux) || defined(unix) || defined(APPLE)
        getc(stdin);
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        getch();
    #endif
}

// Procedimento para limpar a tela ao retornar ao menu principal
void limpar_tela(){
    #if defined(linux) || defined(unix) || defined(APPLE)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

// Função para validação de CNPJ: Retorna booleano true(1) caso seja válido e false(0) caso inválido
bool valida_cnpj(char* cnpj_consulta) {
    // Declaração de variáveis
    int i, j; // Variáveis para controle
    int digito1 = 0, digito2 = 0; // Variáveis dos dígitos verificadores, inicializa com 0
    char cnpj_numerico[TAM_MAX_CNPJ_NUMERICO]; // Variavel CNPJ somente com numeros
    int comp = 0; // Comprimento

    // Percorre os caracteres do CNPJ atual e remove caracteres não numéricos para facilitar cálculos
    for (i = 0; cnpj_consulta[i] != '\0'; i++) {

        // Verifica se o caractere atual é um digito
        if (isdigit(cnpj_consulta[i])) {
            cnpj_numerico[comp++] = cnpj_consulta[i]; // Caso positivo adiciona ao cnpj numerico e incrementa comprimento
        }
    }
    cnpj_numerico[comp] = '\0'; // Adiciona o caractere nulo ao final da string

    // Verifica se todos os dígitos são iguais
    for (i = 1; i < 14; i++) {
        if (cnpj_numerico[i] != cnpj_numerico[0]) { // Compara cada dígito com o primeiro digito
            break; // Caso positivo, sai do loop
        }
    }

    // Se todos os digitos forem iguais, retorna falso
    if (i == 14) {
        return false;
    }

    // Verifica se o CNPJ está no formato XX.XXX.XXX/0001-XX
    if (strlen(cnpj_consulta) != 18 || cnpj_consulta[2] != '.' || cnpj_consulta[6] != '.' ||
        cnpj_consulta[10] != '/' || cnpj_consulta[15] != '-') {
        return false; // Caso não esteja, retorna falso
    }

    // Verifica o cálculo do primeiro dígito verificador
    for (i = 0, j = 5; i < 12; i++) { // Percorre os 12 primeiros dígitos do cnpj numérico
        digito1 += (cnpj_numerico[i] - '0') * j; // coverte o carctere em numero, multiplica pelo peso (j) e adiciona ao digito 1

        // Verifica o peso j: caso 2, vai para 9; se contrário, decrementa j em 1.
        if (j == 2) {
            j = 9;
        } else {
            j = j - 1;
        }
    }

    digito1 %= 11; // Calcula o resto da divisão de digito1 por 11

    // Verifica se o resto é menor que 2.
    if (digito1 < 2){
        digito1 = 0; // Se for, atribui zero a digito1;
    } else {
        digito1 = 11 - digito1; // caso contrário, atribui 11 menos o resto.
    }

    // Verifica o segundo dígito verificador
    for (i = 0, j = 6; i < 13; i++) {
        digito2 += (cnpj_numerico[i] - '0') * j;

        // Verifica o peso j: caso 2, vai para 9; se contrário, decrementa j em 1.
        if (j == 2){
            j = 9;
        } else {
            j = j - 1;
        }
    }

    digito2 %= 11; // Calcula o resto da divisão de digito2 por 11

    // Verifica se o resto é menor que 2.
    if (digito2 < 2){
        digito2 = 0; // Se for, atribui zero a digito2
    } else {
        digito2 = 11 - digito2; // caso contrário, atribui 11 menos o resto.
    }

    // Verificar se os dígitos verificadores estão corretos e correspondem ao digito do CNPJ original
    if ((digito1 == cnpj_numerico[12] - '0') && (digito2 == cnpj_numerico[13] - '0')) {
        return true; // Se os digitos estiverem corretos, retorna true
    }

    return false; // Caso contrário, falso
}

// Função para validação de CPF: Retorna booleano true(1) caso seja válido e false(0) caso inválido
bool valida_cpf(char *cpf_consulta) {
    // Declaração de variáveis
    int i, j = 0; // Variáveis de controle
    int digito1 = 0, digito2 = 0; // Variáveis que armazenam os dígitos verificadores
    int peso1 = 10, peso2 = 11; // Variáveis que representam os pesos utilizados no cálculo
    char cpf_numerico[TAM_MAX_CPF_NUMERICO]; // String que recebe o CPF somente com números

    // Verifica se o CPF possui 14 caracteres (incluindo pontos e hífen)
    if (strlen(cpf_consulta) != 14) {
        return false; // Caso o tamanho for diferente de 14, retorna falso
    }

    // Verifica se os caracteres estão nos locais corretos e remove os caracteres não numéricos
    for (i = 0; i < 14; i++) {
        if (i == 3 || i == 7) {
            if (cpf_consulta[i] != '.') { // Verifica se 1 e 3 são pontos
                return false;
            }
        } else if (i == 11) {
            if (cpf_consulta[i] != '-') { // Verifica se 11 é hifen
                return false;
            }
        } else if (isdigit(cpf_consulta[i])) {
            cpf_numerico[j++] = cpf_consulta[i]; // Adiciona os carcteres que são dígitos ao CPF numérico e incrementa j
        } else {
            return false;
        }
    }
    cpf_numerico[j] = '\0'; // Adiciona o carctere nulo ao CPF numerico

    // Verifica se o CPF possui 11 dígitos numéricos
    if (strlen(cpf_numerico) != 11) {
        return false;
    }

    // Verifica se todos os dígitos não são iguais
    for (i = 1; i < 11; i++) {

        // Compara cada digito com o primeiro
        if (cpf_numerico[i] != cpf_numerico[0]) {
            break; // Se for diferente sai do loop
        }
    }

    // Se todos forem iguais retorna falso
    if (i == 11) {
        return false;
    }

    // Calculo do primeiro dígito verificador
    for (i = 0; i < 9; i++) {
        digito1 += (cpf_numerico[i] - '0') * peso1; // Multiplica cada digito pelo peso correspondente e aoma ao digito 1
        peso1--; // Vai decrementando peso 1 a cada loop
    }

    digito1 = (digito1 * 10) % 11; // Digito 1 passa a valer o resto do digito 1 multiplicado por 10 dividido por 11

    // Calcula o segundo dígito verificador
    for (i = 0; i < 10; i++) {
        digito2 += (cpf_numerico[i] - '0') * peso2; // Multiplica cada digito pelo peso correspondente e soma ao digito 2
        peso2--; // Vai decrementando peso 2 a cada loop
    }

    digito2 = (digito2 * 10) % 11; // Digito 2 passa a valer o resto do digito 2 multiplicado por 10 dividido por 11

    // Verifica se os dígitos verificadores são válidos e correspondem aos dígitos originais
    if ((digito1 == (cpf_numerico[9] - '0') || (digito1 == 10 && cpf_numerico[9] == '0')) &&
        (digito2 == (cpf_numerico[10] - '0') || (digito2 == 10 && cpf_numerico[10] == '0'))) {
        return true; // Se bater, retorna true
    } else {
        return false; // Se não, retorna false
    }
}

// Função que recebe um número de uma RA e retorna o nomes desta RA
char* consulta_ra(int id_ra){
    // Declaração de variáveis
    FILE *arquivo_ra; // Variável para o arquivo de RAs
    struct ra ra_cadastrada; // Struct de uma RA

    arquivo_ra = fopen("ra.csv", "r"); // Abre o arquivo de RAs com permissão de leitura

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo_ra != NULL){

        // Descarta a primeira linha
        char primeira_linha[1000];
        fscanf(arquivo_ra, "%[^\n]\n", primeira_linha);

        // Enquanto não estiver no fim do arquivo, faz consultas linha por linha em busca da RA
        while (!feof(arquivo_ra)){
            fscanf(arquivo_ra, "%d;%[^\n]\n",
                &ra_cadastrada.id_ra,
                ra_cadastrada.nome_ra);

            // Caso encontre uma RA con o mesmo número executa as instruções:
            if (ra_cadastrada.id_ra == id_ra){
                fclose(arquivo_ra); // Fecha o arquivo de RAs
                char* nome_ra = (char*)malloc((strlen(ra_cadastrada.nome_ra) + 1) * sizeof(char)); // Declara a variável nome_ra e faz sua inicialização utilizando alocação dinâmica de memória (malloc)
                strcpy(nome_ra, ra_cadastrada.nome_ra); // Atribui o nome desta RA a variável de retorno
                return nome_ra; // Retorna o nome da RA
                free(nome_ra); // Libera memória alocada
            }
        }
        fclose(arquivo_ra); // Fecha o arquivo de RAs
    }
    return NULL; // Retorna nulo caso não encontre a RA
}

// Procedimento que busca miniusina cadastrada no arquivo, com base em CNPJ recebido do usuário
void consultar_miniusina(){
    // Declaração de variáveis
    FILE *arquivo_miniusinas; // Variável para o arquivo de miniusinas
    FILE *arquivo_contratos; // Variável para o arquivo de contratos
    struct miniusina miniusina_cadastrada; // Struct do tipo miniusina
    struct contrato contrato_cadastrado; // Struct do tipo contrato
    char cnpj_consulta[TAM_MAX_CNPJ]; // Variável que armazena o CNPJ informado pelo usuário
    int miniusina_encontrada = 0; // Variável (Flag) que indica se a miniusina foi ecnotrada (1), ou se não foi encontrada (0)
    int contador_contratos = 0; // Variável de contador do número de contratos de cada miniusina

    printf("\nDigite o CNPJ (com separadores) da miniusina a ser consultada: "); // Solicita a digitaçao do CNPJ
    scanf(" %[^\n]", cnpj_consulta); // Lê e armazena na respectiva variável

    // Chama a função de validação e se o cnpj for válido executa a consulta
    if (valida_cnpj(cnpj_consulta)){

        arquivo_miniusinas = fopen("miniusinas.csv", "r"); // Abre o arquivo csv de miniusinas com permissão de leitura

        // verifica se o arquivo de miniusinas foi aberto corretamente
        if (arquivo_miniusinas != NULL){

            char primeira_linha[1000]; // Variável para descarte da primeira linha
            fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha); // Descarta a primeira linha

            // Enquanto não chegar no fim do arquivo efetua consultas linha por linha, armazenando cada coluna na sua respectiva variável
            while (!feof(arquivo_miniusinas)){
                fscanf(arquivo_miniusinas, "%[^;];%[^;];%f;%d;%[^\n]\n",
                       miniusina_cadastrada.cnpj,
                       miniusina_cadastrada.nome,
                       &miniusina_cadastrada.capacidade,
                       &miniusina_cadastrada.id_ra,
                       miniusina_cadastrada.status);

                char nome_ra[TAM_MAX_NOME]; // Cria variável para armazenar o nome da RA
                char* resultado_consulta = consulta_ra(miniusina_cadastrada.id_ra); // Envia o número da RA e chama a função que retorna o nome da RA

                // Verifica se a função retornou o nome da RA
                if (resultado_consulta != NULL) {
                    strcpy(nome_ra, resultado_consulta); // Caso positivo atribui o resultado da consulta ao nome da RA
                } else {
                    strcpy(nome_ra, "Não encontrado"); // Em casso de erro exibe mensagem
                }

                // Melhora exibição do status Operação
                if (strcmp(miniusina_cadastrada.status, "operacao")==0){
                    strcpy(miniusina_cadastrada.status, "Operação");
                }

                // Caso encontre miniusina com mesmo CNPJ informado, exibe na tela
                if (strcmp(cnpj_consulta, miniusina_cadastrada.cnpj) == 0){ // Comparação de strings
                    printf("\n\n*** DADOS DA MINIUSINA ***\n\n");
                    printf("CNPJ: %s\n", miniusina_cadastrada.cnpj);
                    printf("Nome: %s\n", miniusina_cadastrada.nome);
                    printf("Capacidade total de geração de energia: %.1f kWh\n", miniusina_cadastrada.capacidade);
                    printf("Região Administrativa: %s\n", nome_ra);
                    printf("Status: %s\n\n", miniusina_cadastrada.status);
                    miniusina_encontrada = 1; // Atribui valor 1 que indica que foi encontrada miniusina
                }
            }

            // Verificação dos contratos
            arquivo_contratos = fopen("contratos.csv", "r"); // Abre o arquivo de contratos com permissão de leitura

            // Verifica se o arquivo foi aberto corretamente
            if (arquivo_contratos != NULL){

                // Descarta primeira linha
                char primeira_linha[1000];
                fscanf(arquivo_contratos, "%[^\n]\n", primeira_linha);

                // Executa consultas linha por linha, até o fim do aqauivo, em busca de contratos
                while (!feof(arquivo_contratos)){
                    fscanf(arquivo_contratos, "%[^;];%[^;];%[^;];%[^;];%f\n",
                    contrato_cadastrado.id_contrato,
                    contrato_cadastrado.id_consumidor,
                    contrato_cadastrado.cnpj,
                    contrato_cadastrado.data_inicio,
                    &contrato_cadastrado.energia_contratada);

                    // Caso localize contrato com o mesmo CNPJ da mimiusina, exibe na tela os dados
                    if (strcmp(cnpj_consulta, contrato_cadastrado.cnpj) == 0){
                        printf("\n*** CONTRATO LOCALIZADO ***\n\n");
                        printf("Número do contrato: %s\n", contrato_cadastrado.id_contrato);
                        printf("CPF/CNPJ do consumidor: %s\n", contrato_cadastrado.id_consumidor);
                        printf("CNPJ da miniusina: %s\n", contrato_cadastrado.cnpj);
                        printf("Data de início do contrato: %s\n", contrato_cadastrado.data_inicio);
                        printf("Quantidade de energia contratada: %.1f kWh\n\n", contrato_cadastrado.energia_contratada);
                        contador_contratos++; // Incrementa contador
                    }
                }
            } else{
                printf("\n\nNão foi possível acessar o arquivo de contratos.\n\n");// Em caso de erro na abertura do aqruivo de contratos, exibe a mensagem
            }
        } else {
            printf("\n\nErro ao abrir o arquivo de miniusinas.\n\n");// Em caso de erro na abertura do aqruivo de miniusinas, exibe a mensagem
        }

        // Informa caso não exista miniusina cadastrada com o CNPJ informado
        if (miniusina_encontrada == 0) {
            printf("\nNão foi encontrada miniusina com o CNPJ informado!\n\n\n");
        }

        // Exibe total de contratos ou se não possui contratos
        if (contador_contratos > 0){
            printf("Total de contratos: %d\n\n\n", contador_contratos);
        } else if (miniusina_encontrada != 0){
            printf("Esta miniusina não possui contratos ativos.\n\n\n");
        }

        fclose(arquivo_miniusinas); // Fecha o arquivo de miniusinas
        fclose(arquivo_contratos); // Fecha arquivo de contratos

    // Comunica em caso de CNPJ inválido ou fora do formato
    } else {
        printf("\nO CNPJ informado é inválido.\n\n\n");
    }
}

// Procedimento que lista todas as miniusinas cadastradas no arquivo
void listar_miniusinas(){
    // Declaração de variáveis
    FILE *arquivo_miniusinas; // Cria variável para o arquivo
    struct miniusina miniusina_cadastrada; // Cria struct do tipo miniusina

    arquivo_miniusinas = fopen("miniusinas.csv", "r"); // Abre o arquivo csv com permissão de leitura

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo_miniusinas != NULL){

        char primeira_linha[1000]; // Variável para descarte da primeira linha
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha); // Descarta a primeira linha do arquivo

        // Exibe o cabeçalho
        printf("\n*************************************************\n");
        printf("         MINIUSINAS CADASTRADAS NO SINGDF\n");
        printf("*************************************************\n\n");

        // Enquanto não chegar ao fim do arquivo executa os passos abaixo:
        while (!feof(arquivo_miniusinas)){
            //faz a leitura linha por linha e armazena os valores nas respectivas variáveis da struct
            fscanf(arquivo_miniusinas, "%[^;];%[^;];%f;%d;%[^\n]\n",
                   miniusina_cadastrada.cnpj,
                   miniusina_cadastrada.nome,
                   &miniusina_cadastrada.capacidade,
                   &miniusina_cadastrada.id_ra,
                   miniusina_cadastrada.status);


                char nome_ra[TAM_MAX_NOME]; // Cria variável para armazenar o nome da RA
                char* resultado_consulta = consulta_ra(miniusina_cadastrada.id_ra); // Envia o número da RA e chama a função que retorna o nome da RA

                // Verifica se a função retornou o nome da RA
                if (resultado_consulta != NULL) {
                    strcpy(nome_ra, resultado_consulta); // Caso positivo atribui o resultado da consulta ao nome da RA
                } else {
                    strcpy(nome_ra, "Não encontrado"); // Em casso de erro exibe mensagem
                }

                // Melhora exibição do status Operação
                if (strcmp(miniusina_cadastrada.status, "operacao")==0){
                        strcpy(miniusina_cadastrada.status, "Operação");
                }

                // Exibe a miniusina ao usuário
                printf("CNPJ: %s\n", miniusina_cadastrada.cnpj);
                printf("Nome: %s\n", miniusina_cadastrada.nome);
                printf("Capacidade total de geração de energia: %.1f kWh\n", miniusina_cadastrada.capacidade);
                printf("Região Administrativa: %s\n", nome_ra);
                printf("Status: %s\n\n", miniusina_cadastrada.status);

        }
    } else {
        printf("\nErro! Não foi possível abrir o arquivo de miniusinas.\n\n"); // Em caso de erro na abertura do arquivo, exibe mensagem
        }

    fclose(arquivo_miniusinas); // Fecha o arquivo após fim das consultas
}

// Procedimento que executa busca de consumidores com o CPF ou CNPJ informado pelo usuário, e busca constratos vinculados a este consumidor
void consultar_consumidor(){
    // Declaração de variáveis
    FILE *arquivo_consumidores; // Variável para o arquivo de consumidores
    FILE *arquivo_contratos; // Variável para o arquivo de coontratos
    struct consumidor consumidor_cadastrado; // Struct do tipo consumidor
    struct contrato contrato_cadastrado; // Struct do tipo contrato
    char id_consumidor[TAM_MAX_ID_CONSUMIDOR];// Variável que recebe o CPF ou CNPJ do consumidor
    int consumidor_encontrado = 0; // Variável (Flag) que indica se o consumidor foi encontrado
    int contador_contratos = 0; // Variável contador do múmero de contratos do consumidor

    printf("\nDigite o CPF OU CNPJ (com separadores) do consumidor a ser consultado: "); // Solicita a identificação do consumidor
    scanf("%s", id_consumidor); // Lê e armazena na variavel adequada

    // Verifica se o CPF ou CNPJ informado é válido
    if (valida_cpf(id_consumidor) || valida_cnpj(id_consumidor)){

        arquivo_consumidores = fopen("consumidores.csv", "r"); // Abre o arquivo de consumidores com permissaão de leitura

        // Verifica se o arquivo foi aberto corretamente
        if (arquivo_consumidores != NULL){

            // Descarta a primeira linha
            char primeira_linha[1000];
            fscanf(arquivo_consumidores, "%[^\n]\n", primeira_linha);

            // Enquanto não estiver no fim do aqruivo, executa consultas linha por linhas
            while (!feof(arquivo_consumidores)){
                fscanf(arquivo_consumidores, "%[^;];%[^;];%d\n",
                       consumidor_cadastrado.id_consumidor,
                       consumidor_cadastrado.nome,
                       &consumidor_cadastrado.id_ra);

                char nome_ra[TAM_MAX_NOME]; // Cria variável para armazenar o nome da RA
                char* resultado_consulta = consulta_ra(consumidor_cadastrado.id_ra); // Envia o número da RA e chama a função que retorna o nome da RA

                // Verifica se a função retornou o nome da RA
                if (resultado_consulta != NULL) {
                    strcpy(nome_ra, resultado_consulta); // Caso positivo atribui o resultado da consulta ao nome da RA
                } else {
                    strcpy(nome_ra, "Não encontrado"); // Em casso de erro exibe mensagem
                }

                // Caso enconre o consumidor com mesmo CPF ou CNPJ, exibir na tela
                if (strcmp(id_consumidor, consumidor_cadastrado.id_consumidor) == 0){ // Comparação de strings
                    printf("\n\n*** DADOS DO CONSUMIDOR ***\n\n");

                    // Verifica se é CPF ou CNPJ
                    if (valida_cnpj(id_consumidor)){
                        printf("CNPJ do consumidor: %s\n", consumidor_cadastrado.id_consumidor);
                    } else {
                        printf("CPF do consumidor: %s\n", consumidor_cadastrado.id_consumidor);
                    }

                    //printf("CPF/CNPJ: %s\n", consumidor_cadastrado.id_consumidor);
                    printf("Nome: %s\n", consumidor_cadastrado.nome);
                    printf("Região Administrativa: %s\n", nome_ra);
                    consumidor_encontrado = 1; // Atribiu valor 1 a variável flag que indica que o consumidor foi encontrado
                }
            }

            arquivo_contratos = fopen("contratos.csv", "r"); // Abre o arquivo de contratos com permissão de leitura

            // Verifica se o arquivo foi aberto corretamente
            if (arquivo_contratos != NULL){

                // Descarta a primeira linha
                char primeira_linha[1000];
                fscanf(arquivo_contratos, "%[^\n]\n", primeira_linha);

                // Enquanto não estiver no fim do arquivo, exevuta consulta linha por linha
                while (!feof(arquivo_contratos)){
                    fscanf(arquivo_contratos, "%[^;];%[^;];%[^;];%[^;];%f\n",
                    contrato_cadastrado.id_contrato,
                    contrato_cadastrado.id_consumidor,
                    contrato_cadastrado.cnpj,
                    contrato_cadastrado.data_inicio,
                    &contrato_cadastrado.energia_contratada);

                    // Caso localize contrato com mesmo ID do consumidor, exibe na tela os dados
                    if (strcmp(id_consumidor, contrato_cadastrado.id_consumidor) == 0){ // Comparação de strings
                        printf("\n*** CONTRATO LOCALIZADO ***\n\n");
                        printf("Número do contrato: %s\n", contrato_cadastrado.id_contrato);

                        // Verifica se é CPF ou CNPJ
                        if (valida_cnpj(id_consumidor)){
                            printf("CNPJ do consumidor: %s\n", contrato_cadastrado.id_consumidor);
                        } else {
                            printf("CPF do consumidor: %s\n", contrato_cadastrado.id_consumidor);
                        }

                        printf("CNPJ da miniusina: %s\n", contrato_cadastrado.cnpj);
                        printf("Data de início do contrato: %s\n", contrato_cadastrado.data_inicio);
                        printf("Quantidade de energia contratada: %.1f kWh\n\n", contrato_cadastrado.energia_contratada);
                        contador_contratos++; // Incrementa contador de contratos
                    }
                }
            } else {
                printf("\n\nErro ao abrir o arquivo de contratos.\n\n\n"); // Informa em caso de erro na abertura do arquivo de contratos
            }

            // Informa caso não seja encontrado consumidor com o ID informado pelo usuário
            if (consumidor_encontrado == 0) {
                //Verifica se foi digitado CPF ou CNPJ pelo usuário
                if (valida_cnpj(id_consumidor)){
                    printf("\n\nNão foi encontrado consumidor com o CNPJ informado!\n\n\n");
                } else {
                    printf("\n\nNão foi encontrado consumidor com o CPF informado!\n\n\n");
                }
            }

            // Exibe total de contratos ou se o cliente não possui contratos
            if (contador_contratos > 0){
                printf("=> Total de contratos: %d\n\n\n", contador_contratos);
            } else if (consumidor_encontrado != 0){
                printf("\nEste consumidor não possui contratos ativos.\n\n\n");
            }

        } else {
            printf("\n\nErro ao abrir o arquivo de consumidores.\n\n\n"); // Informa em caso de erro na abertura do arquivo de consumidores
        }

        fclose(arquivo_consumidores); // Fecha o arquivo de consumidores
        fclose(arquivo_contratos); // Fecha o arquivo de contratos

    } else {
        printf("\nO CPF/CNPJ digitado é inválido.\n\n\n"); // Infora caso o CPF ou CNPJ digitado seja inválido
    }
}

// Procedimento para ordenação (Selection Sort) das miniusinas em operação por ordem decrescente de capacidadede de produção de energia
void ordenar_miniusinas_decrescente_capacidade(struct miniusina lista[], int tamanho){
    // Declaração de variáveis
    int i, j, posicao_maior; // Variáveis para os laços de repetição, posicao maior é a miniusina de maior capacidade
    struct miniusina temp; // Struct que armazena temporariamente uma miniusina durante a troca de posilão

    // Percorre todo o vetor
    for (i = 0; i < tamanho - 1; i++){
        posicao_maior = i;

        // Busca a miniusina com maior capacidade de produção
        for (j = i + 1; j < tamanho; j++){
            if (lista[j].capacidade > lista[posicao_maior].capacidade){
                posicao_maior = j;
            }
        }

        // Instruções para troca de posição i e da miniusina de maior capacidade
        temp = lista[i];
        lista[i] = lista[posicao_maior];
        lista[posicao_maior] = temp;
    }
}

// Procedimento que exibe as miniusinas em operação em ordem decrescente de capacidade de produção de energia
void listar_miniusinas_descrescente_capacidade(){
    // Declaração de variáveis
    FILE *arquivo_miniusinas; // Variável para o arquivo de miniusinas
    struct miniusina miniusina_cadastrada; // Struct de uma miniusina
    struct miniusina lista_miniusinas[QUANT_MAX_MINIUSINAS]; // Vetor de struct, lista de struct de miniusinas
    int contador_miniusinas; // Variável contador de miniusinas

    arquivo_miniusinas = fopen("miniusinas.csv", "r"); // Abre o arquivo de miniusinas com permissão de leitura

    // Verifica se o arquivo de miniusinas foi aberto corretamente
    if (arquivo_miniusinas != NULL){

        // Descarta a primeira linha
        char primeira_linha[1000];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha);

        // Exibe cabeçalho
        printf("\n*************************************************\n");
        printf("  MINIUSINAS EM OPERAÇÃO POR ORDEM DECRESCENTE\n");
        printf("     DE CAPACIDADE DE GERAÇÃO DE ENERGIA\n");
        printf("*************************************************\n\n");

        // Enquanto não estiver no fim do arquivo executa a consulta linha por linha
        while (!feof(arquivo_miniusinas)){
                fscanf(arquivo_miniusinas, "%[^;];%[^;];%f;%d;%[^\n]\n",
                    miniusina_cadastrada.cnpj,
                    miniusina_cadastrada.nome,
                    &miniusina_cadastrada.capacidade,
                    &miniusina_cadastrada.id_ra,
                    miniusina_cadastrada.status);

            // Verifica se a usina está em operação comparando as strings
            if (strcmp(miniusina_cadastrada.status, "operacao") == 0){
                lista_miniusinas[contador_miniusinas] = miniusina_cadastrada; // Caso verdadeiro adiciona a miniusina na lista
                contador_miniusinas++; // Incrementa o contador de miniusinas em operação
            }
        }

        // Chama o procedimento que ordena as miniusinas da lista
        ordenar_miniusinas_decrescente_capacidade(lista_miniusinas, contador_miniusinas);

        // Estrutura de repetição para exibir as miniusinas ordenadas
        for (int i = 0; i < contador_miniusinas; i++){
            printf("CNPJ: %s\n", lista_miniusinas[i].cnpj);

            char nome_ra[TAM_MAX_NOME]; // Cria variável para armazenar o nome da RA
            char* resultado_consulta = consulta_ra(lista_miniusinas[i].id_ra); // Envia o número da RA e chama a função que retorna o nome da RA

            // Verifica se a função retornou o nome da RA
            if (resultado_consulta != NULL) {
                strcpy(nome_ra, resultado_consulta); // Caso positivo atribui o resultado da consulta ao nome da RA
            } else {
                strcpy(nome_ra, "Não encontrado"); // Em caso de erro exibe mensagem
            }

            // Imprime os dados
            printf("Região Administrativa: %s\n", nome_ra);
            printf("Capacidade total de geração de energia: %.1f kWh\n\n", lista_miniusinas[i].capacidade);
        }
    } else {
        printf("\nErro! Não foi possível abrir o arquivo de miniusinas.\n\n"); // Informa em caso de erro na abertura do arquivo de miniusinas
    }

    fclose(arquivo_miniusinas); // Fecha o arquivo de miniusinas
}

// Procedimento que ordena (Selection sort) as RA's em ordem decrescente de quantidade de miniusinas
void ordenar_ras_decrescente_quantidade(struct ra lista[], int quantidade_ras){
    // Declaração de variáveis
    int i, j, posicao_maior; // Variáveis para os laços de repetição, posicao maior é a ra com mais miniusinas
    struct ra temp; // Struct que armazena temporariamente uma RA durante a troca de posição

    // Percorre todo o vetor
    for (i = 0; i < quantidade_ras - 1; i++){
        posicao_maior = i;

        // Busca a RA com mais miniusinas
        for (j = i + 1; j < quantidade_ras; j++){
            if (lista[j].quantidade_miniusinas > lista[posicao_maior].quantidade_miniusinas){
                posicao_maior = j;
            }
        }

        // Instruções para troca de posição i e da RA com mais miniusinas
        temp = lista[i];
        lista[i] = lista[posicao_maior];
        lista[posicao_maior] = temp;
    }
}

// Procedimento que exibe as RA'S em ordem decrescente de quantidade de miniusinas
void listar_ras_decrescente_quantidade(){
    // Declaração de variáveis
    FILE *arquivo_miniusinas; // Arquivo de miniusinas
    struct ra lista_ra[QUANT_MAX_RAS]; // Cria vetor/lista de RA's
    struct miniusina miniusina_cadastrada; // Struct de uma miniusina
    int contador_ra = 0; // Contador de RAs
    int i; // Controle

    arquivo_miniusinas = fopen("miniusinas.csv", "r"); // Abre o arquivo de miniusinas

    // Verifica se foi aberto corretamente
    if (arquivo_miniusinas != NULL){

        // Descarta a primeira linha
        char primeira_linha[1000];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha);

        // Exibe cabeçalho
        printf("\n*************************************************\n");
        printf("            RAs POR ORDEM DECRESCENTE \n");
        printf("           DE QUANTIDADE DE MINIUSINAS\n");
        printf("*************************************************\n\n");

        // Enquanto não estiver no fim do arquivo, executa consulta linha por linha e armazena nas variáveis
        while (!feof(arquivo_miniusinas)){
                fscanf(arquivo_miniusinas, "%[^;];%[^;];%f;%d;%[^\n]\n",
                    miniusina_cadastrada.cnpj,
                    miniusina_cadastrada.nome,
                    &miniusina_cadastrada.capacidade,
                    &miniusina_cadastrada.id_ra,
                    miniusina_cadastrada.status);

            // Verifica se a miniusina seguinte pertence a alguma RA já cadastrada
            for (i = 0; i < contador_ra; i++){
                // Se encontrar mais uma miniusina na mesma RA, incrementa quantidade de miniusinas
                if (lista_ra[i].id_ra == miniusina_cadastrada.id_ra){
                    lista_ra[i].quantidade_miniusinas++;
                    break;
                }
            }

            // Cadastra a primeira miniusina da RA's no vetor de lista
            if (i == contador_ra){
                lista_ra[contador_ra].id_ra = miniusina_cadastrada.id_ra;
                lista_ra[contador_ra].quantidade_miniusinas = 1;
                contador_ra++; // Incrementa contador
            }
        }

        // Chama o procedimento de ordenação, envia a lista e a quantidade de RA's, retorna a lista ordenada
        ordenar_ras_decrescente_quantidade(lista_ra, contador_ra);

        // Repetição que percorre toda a lista de RA's e printa os dados
        for (int i = 0; i < contador_ra; i++){
            printf("Número da RA: %d\n", lista_ra[i].id_ra);

            char nome_ra[TAM_MAX_NOME]; // Cria variável para armazenar o nome da RA
            char* resultado_consulta = consulta_ra(lista_ra[i].id_ra); // Envia o número da RA e chama a função que retorna o nome da RA

            // Verifica se a função retornou o nome da RA
            if (resultado_consulta != NULL) {
                strcpy(nome_ra, resultado_consulta); // Caso positivo atribui o resultado da consulta ao nome da RA
            } else {
                strcpy(nome_ra, "Não encontrado"); // Em caso de erro exibe mensagem
            }

            // Imprime os dados
            printf("Nome da RA: %s\n", nome_ra);
            printf("Quantidade de miniusinas: %d\n\n", lista_ra[i].quantidade_miniusinas);
        }

    } else {
        printf("\nErro! Não foi possível abrir o arquivo de miniusinas.\n\n"); // Informa em caso de erro
    }

    fclose(arquivo_miniusinas); // Fecha o arquivo de miniusinas
}

// Procedimento que ordena (Selection sort) as RA's em ordem decrescente de capacidade de geração de energia
void ordenar_ras_decrescente_capacidade(struct ra lista[], int quantidade_ras){
    // Declaração de variáveis
    int i, j, posicao_maior; // Variáveis para os laços de repetição, posicao maior é a ra com mais capacidade
    struct ra temp; // Struct que armazena temporariamente uma RA durante a troca de posição

    // Percorre todo o vetor
    for (i = 0; i < quantidade_ras - 1; i++){
        posicao_maior = i;

        // Busca a RA com maior capacidade
        for (j = i + 1; j < quantidade_ras; j++){
            if (lista[j].capacidade > lista[posicao_maior].capacidade){
                posicao_maior = j;
            }
        }

        // Instruções para troca de posição i e da RA com maior capacidade
        temp = lista[i];
        lista[i] = lista[posicao_maior];
        lista[posicao_maior] = temp;
    }
}

// Procedimento que exibe as RA'S em ordem decrescente de capacidade de geração de energia
void listar_ras_decrescente_capacidade(){
    // Declaração de variáveis
    FILE *arquivo_miniusinas; // Arquivo de miniusinas
    struct ra lista_ra[QUANT_MAX_RAS]; // Cria vetor/lista de RA's
    struct miniusina miniusina_cadastrada; // Struct de uma miniusina
    int contador_ra = 0; // Contador de RAs
    int i; // Controle

    arquivo_miniusinas = fopen("miniusinas.csv", "r"); // Abre o arquivo de miniusinas

    // Verifica se foi aberto corretamente
    if (arquivo_miniusinas != NULL){

        // Descarta a primeira linha
        char primeira_linha[1000];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha);

        // Exibe cabeçalho
        printf("\n*************************************************\n");
        printf("           RAs POR ORDEM DECRESCENTE DE\n");
        printf("         CAPACIDADE DE GERAÇÃO DE ENERGIA\n");
        printf("*************************************************\n\n");

        // Enquanto não estiver no fim do arquivo, executa consulta linha por linha e armazena nas variáveis
        while (!feof(arquivo_miniusinas)){
                fscanf(arquivo_miniusinas, "%[^;];%[^;];%f;%d;%[^\n]\n",
                    miniusina_cadastrada.cnpj,
                    miniusina_cadastrada.nome,
                    &miniusina_cadastrada.capacidade,
                    &miniusina_cadastrada.id_ra,
                    miniusina_cadastrada.status);

            // Verifica se a miniusina seguinte pertence a alguma RA já cadastrada
            for (i = 0; i < contador_ra; i++){
                // Se encontrar mais uma miniusina na mesma RA, incrementa capacidade de geração
                if (lista_ra[i].id_ra == miniusina_cadastrada.id_ra){
                    lista_ra[i].capacidade += miniusina_cadastrada.capacidade;
                    break;
                }
            }

            // Cadastra a primeira miniusina da RA's no vetor de lista e atribui a primeira capacidade
            if (i == contador_ra){
                lista_ra[contador_ra].id_ra = miniusina_cadastrada.id_ra;
                lista_ra[contador_ra].capacidade = miniusina_cadastrada.capacidade;
                contador_ra++; // Incrementa contador
            }
        }

        // Chama o procedimento de ordenação, envia a lista e a quantidade de RA's, retorna a lista ordenada
        ordenar_ras_decrescente_capacidade(lista_ra, contador_ra);

        // Repetição que percorre toda a lista de RA's e printa os dados
        for (int i = 0; i < contador_ra; i++){
            printf("Número da RA: %d\n", lista_ra[i].id_ra);

            char nome_ra[TAM_MAX_NOME]; // Cria variável para armazenar o nome da RA
            char* resultado_consulta = consulta_ra(lista_ra[i].id_ra); // Envia o número da RA e chama a função que retorna o nome da RA

            // Verifica se a função retornou o nome da RA
            if (resultado_consulta != NULL) {
                strcpy(nome_ra, resultado_consulta); // Caso positivo atribui o resultado da consulta ao nome da RA
            } else {
                strcpy(nome_ra, "Não encontrado"); // Em caso de erro exibe mensagem
            }

            // Imprime os dados
            printf("Nome da RA: %s\n", nome_ra);
            printf("Capacidade total de geração de energia: %.1f kWh\n\n", lista_ra[i].capacidade);
        }

    } else {
        printf("\nErro! Não foi possível abrir o arquivo de miniusinas.\n\n"); // Informa em caso de erro
    }

    fclose(arquivo_miniusinas); // Fecha o arquivo de miniusinas
}

// Procedimento que ordena (Selection sort) as RA's em ordem decrescente de percentual de energia disponível
void ordenar_ras_decrescente_percentual(struct ra lista[], int quantidade_ras){
    // Declaração de variáveis
    int i, j, posicao_maior; // Variáveis para os laços de repetição, posicao maior é a ra com maior percentual
    struct ra temp; // Struct que armazena temporariamente uma RA durante a troca de posição

    // Percorre todo o vetor
    for (i = 0; i < quantidade_ras - 1; i++){
        posicao_maior = i;

        // Busca a RA com maior percentual
        for (j = i + 1; j < quantidade_ras; j++){
            if (lista[j].percentual > lista[posicao_maior].percentual){
                posicao_maior = j;
            }
        }

        // Instruções para troca de posição i e da RA com maior percentual
        temp = lista[i];
        lista[i] = lista[posicao_maior];
        lista[posicao_maior] = temp;
    }
}

// Procedimento que exibe as RA'S em ordem decrescente de percentual de energia disponível
void listar_ras_decrescente_percentual(){
    // Declaração de variáveis
    FILE *arquivo_miniusinas; // Arquivo de miniusinas
    FILE *arquivo_contratos; // Arquivo de contratos
    struct ra lista_ra[QUANT_MAX_RAS]; // Cria vetor/lista de RA's
    struct miniusina miniusina_cadastrada; // Struct de uma miniusina
    struct contrato contrato_cadastrado; // Struct de um contrato
    int contador_ra = 0; // Contador de RAs
    int i; // Controle
    float total_geral = 0; // Total de energia em todas as RAS


    arquivo_miniusinas = fopen("miniusinas.csv", "r"); // Abre o arquivo de miniusinas

    // Verifica se foi aberto corretamente
    if (arquivo_miniusinas != NULL){

        miniusina_cadastrada.energia_contratada = 0; // inicializa

        // Descarta a primeira linha
        char primeira_linha[1000];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha);

        // Exibe cabeçalho
        printf("\n*************************************************\n");
        printf("           RAs POR ORDEM DECRESCENTE DE \n");
        printf("         PERCENTUAL DE ENERGIA DISPONÍVEL\n");
        printf("*************************************************\n\n");

        // Enquanto não estiver no fim do arquivo, executa consulta linha por linha e armazena nas variáveis
        while (!feof(arquivo_miniusinas)){
                fscanf(arquivo_miniusinas, "%[^;];%[^;];%f;%d;%[^\n]\n",
                    miniusina_cadastrada.cnpj,
                    miniusina_cadastrada.nome,
                    &miniusina_cadastrada.capacidade,
                    &miniusina_cadastrada.id_ra,
                    miniusina_cadastrada.status);

            arquivo_contratos = fopen("contratos.csv", "r"); // Abre arquivo de contratos

            // Verifica abertura
            if (arquivo_contratos != NULL){

                int encontrado = 0; // flag

                // consulta linha por linha
                while (!feof(arquivo_contratos)){
                    fscanf(arquivo_contratos, "%[^;];%[^;];%[^;];%[^;];%f\n",
                            contrato_cadastrado.id_contrato,
                            contrato_cadastrado.id_consumidor,
                            contrato_cadastrado.cnpj,
                            contrato_cadastrado.data_inicio,
                            &contrato_cadastrado.energia_contratada);

                    // Caso localize contrato com o mesmo CNPJ da mimiusina, atribui a energia contraatda da miniudina
                    if (strcmp(miniusina_cadastrada.cnpj, contrato_cadastrado.cnpj) == 0){
                        miniusina_cadastrada.energia_contratada += contrato_cadastrado.energia_contratada;
                        encontrado = 1;
                    }
                }

                // atribui zero as miniusinas sem contratos
                if (encontrado != 1){
                    miniusina_cadastrada.energia_contratada = 0;
                }

            } else {
                printf("\nErro! Não foi possível abrir o arquivo de miniusinas.\n\n");
            }

            fclose(arquivo_contratos);

            // Verifica se a miniusina seguinte pertence a alguma RA já cadastrada
            for (i = 0; i < contador_ra; i++){
                // Se encontrar mais uma miniusina na mesma RA, incrementa capacidade de geração
                if (lista_ra[i].id_ra == miniusina_cadastrada.id_ra){
                    total_geral += miniusina_cadastrada.capacidade; // Incrementa o total
                    lista_ra[i].capacidade += miniusina_cadastrada.capacidade;
                    lista_ra[i].energia_contratada += miniusina_cadastrada.energia_contratada;
                    break;
                }
            }

            // Cadastra a primeira miniusina da RA's no vetor de lista e atribui a primeira capacidade
            if (i == contador_ra){
                lista_ra[contador_ra].id_ra = miniusina_cadastrada.id_ra;
                lista_ra[contador_ra].energia_contratada = 0;
                lista_ra[contador_ra].capacidade = miniusina_cadastrada.capacidade;
                lista_ra[contador_ra].energia_contratada = miniusina_cadastrada.energia_contratada;
                total_geral += lista_ra[contador_ra].capacidade; // Incrementa a capacidade ao total geral
                contador_ra++; // Incrementa contador
            }
        }

        // Calcula e incrementa o percentual de cada RA
        for (i = 0; i < contador_ra; i++){
            lista_ra[i].percentual = ((lista_ra[i].capacidade - lista_ra[i].energia_contratada) / lista_ra[i].capacidade) * 100;
        }

        // Chama o procedimento de ordenação, envia a lista e a quantidade de RA's, retorna a lista ordenada
        ordenar_ras_decrescente_percentual(lista_ra, contador_ra);

        // Repetição que percorre toda a lista de RA's e printa os dados
        for (int i = 0; i < contador_ra; i++){
            printf("Número da RA: %d\n", lista_ra[i].id_ra);

            char nome_ra[TAM_MAX_NOME]; // Cria variável para armazenar o nome da RA
            char* resultado_consulta = consulta_ra(lista_ra[i].id_ra); // Envia o número da RA e chama a função que retorna o nome da RA

            // Verifica se a função retornou o nome da RA
            if (resultado_consulta != NULL) {
                strcpy(nome_ra, resultado_consulta); // Caso positivo atribui o resultado da consulta ao nome da RA
            } else {
                strcpy(nome_ra, "Não encontrado"); // Em caso de erro exibe mensagem
            }

            // Imprime os dados
            printf("Nome da RA: %s\n", nome_ra);
            printf("Percentual de energia disponível: %.2f %%\n\n", lista_ra[i].percentual);
        }

    } else {
        printf("\nErro! Não foi possível abrir o arquivo de miniusinas.\n\n"); // Informa em caso de erro
    }

    fclose(arquivo_miniusinas); // Fecha o arquivo de miniusinas
}

// Procedimento que ordena (Selection sort) as RA's em ordem crescente de número de contratos
void ordenar_ras_crescente_contratos(struct ra lista[], int quantidade_ras){
    // Declaração de variáveis
    int i, j, posicao_menor; // Variáveis para os laços de repetição, posicao menor é a ra com menos contratos
    struct ra temp; // Struct que armazena temporariamente uma RA durante a troca de posição

    // Percorre todo o vetor
    for (i = 0; i < quantidade_ras - 1; i++){
        posicao_menor = i;

        // Busca a RA com menos contratos
        for (j = i + 1; j < quantidade_ras; j++){
            if (lista[j].total_contratos < lista[posicao_menor].total_contratos){
                posicao_menor = j;
            }
        }

        // Instruções para troca de posição i e da RA com mmenos contratos
        temp = lista[i];
        lista[i] = lista[posicao_menor];
        lista[posicao_menor] = temp;
    }
}

// Procedimento que exibe as RA's em ordem crescente de número de contratos
void listar_ras_crescente_contratos(){
    // Declaração de variáveis
    FILE *arquivo_miniusinas; // Arquivo de miniusinas
    FILE *arquivo_contratos; // Arquivo de contratos
    struct ra lista_ra[QUANT_MAX_RAS]; // Cria vetor/lista de RA's
    struct miniusina miniusina_cadastrada; // Struct de uma miniusinas
    struct contrato contrato_cadastrado; // Struct de um contrato
    int contador_ra = 0; // Contador de RAs
    int i; // Controle

    arquivo_miniusinas = fopen("miniusinas.csv", "r"); // Abre o arquivo de miniusinas

    // Verifica se foi aberto corretamente
    if (arquivo_miniusinas != NULL){

        // Descarta a primeira linha
        char primeira_linha[1000];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha);

        // Exibe cabeçalho
        printf("\n*************************************************\n");
        printf("            RAs POR ORDEM CRESCENTE \n");
        printf("            DE NÚMERO DE CONTRATOS\n");
        printf("*************************************************\n\n");

        // Enquanto não estiver no fim do arquivo, executa consulta linha por linha e armazena nas variáveis
        while (!feof(arquivo_miniusinas)){
                fscanf(arquivo_miniusinas, "%[^;];%[^;];%f;%d;%[^\n]\n",
                    miniusina_cadastrada.cnpj,
                    miniusina_cadastrada.nome,
                    &miniusina_cadastrada.capacidade,
                    &miniusina_cadastrada.id_ra,
                    miniusina_cadastrada.status);

            // Verifica se a miniusina seguinte pertence a alguma RA já cadastrada
            for (i = 0; i < contador_ra; i++){
                // Se encontrar mais uma miniusina na mesma RA, procura contratos
                if (lista_ra[i].id_ra == miniusina_cadastrada.id_ra){

                    arquivo_contratos = fopen("contratos.csv", "r"); // Abre o arquivo de contratos

                    // Verifica se foi aberto corretamente
                    if (arquivo_contratos != NULL){

                        // Descarta primeira linha
                        char primeira_linha[1000];
                        fscanf(arquivo_contratos, "%[^\n]\n", primeira_linha);

                        // Executa consultas linha por linha, até o fim do arquivo, em busca de contratos
                        while (!feof(arquivo_contratos)){
                                fscanf(arquivo_contratos, "%[^;];%[^;];%[^;];%[^;];%f\n",
                                contrato_cadastrado.id_contrato,
                                contrato_cadastrado.id_consumidor,
                                contrato_cadastrado.cnpj,
                                contrato_cadastrado.data_inicio,
                                &contrato_cadastrado.energia_contratada);

                            // Caso localize contrato com o mesmo CNPJ da mimiusina, incrementa ao total da RA
                            if (strcmp(miniusina_cadastrada.cnpj, contrato_cadastrado.cnpj) == 0){
                                lista_ra[i].total_contratos++;
                            }
                        }

                    } else {
                        printf("\nErro! Não foi possível abrir o arquivo de contratos.\n\n"); // Comunica em caso de erro
                    }

                    fclose(arquivo_contratos); // Fecha o arquivo de contratos
                    break;
                }
            }

            // Cadastra a primeira miniusina da RA's no vetor de lista
            if (i == contador_ra){
                lista_ra[contador_ra].id_ra = miniusina_cadastrada.id_ra;
                lista_ra[contador_ra].total_contratos = 0; // Inicializa o total com 0

                arquivo_contratos = fopen("contratos.csv", "r"); // Abre o arquivo de contratos

                // Verifica se foi aberto corretamente
                if (arquivo_contratos != NULL){

                    // Descarta primeira linha
                    char primeira_linha[1000];
                    fscanf(arquivo_contratos, "%[^\n]\n", primeira_linha);

                    // Executa consultas linha por linha, até o fim do arquivo, em busca de contratos
                    while (!feof(arquivo_contratos)){
                            fscanf(arquivo_contratos, "%[^;];%[^;];%[^;];%[^;];%f\n",
                            contrato_cadastrado.id_contrato,
                            contrato_cadastrado.id_consumidor,
                            contrato_cadastrado.cnpj,
                            contrato_cadastrado.data_inicio,
                            &contrato_cadastrado.energia_contratada);

                        // Caso localize contrato com o mesmo CNPJ da mimiusina, inicializa a contagem
                        if (strcmp(miniusina_cadastrada.cnpj, contrato_cadastrado.cnpj) == 0){
                            lista_ra[i].total_contratos = 1;
                        }
                    }

                } else {
                    printf("\nErro! Não foi possível abrir o arquivo de contratos.\n\n"); // Avisa em caso de erro
                }
                contador_ra++; // Incrementa contador
                fclose(arquivo_contratos); // Fecha arquivo de contratos
            }
        }

        // Chama o procedimento de ordenação, envia a lista e a quantidade de RA's, retorna a lista ordenada
        ordenar_ras_crescente_contratos(lista_ra, contador_ra);

        // Repetição que percorre toda a lista de RA's e printa os dados
        for (int i = 0; i < contador_ra; i++){
            printf("Número da RA: %d\n", lista_ra[i].id_ra);

            char nome_ra[TAM_MAX_NOME]; // Cria variável para armazenar o nome da RA
            char* resultado_consulta = consulta_ra(lista_ra[i].id_ra); // Envia o número da RA e chama a função que retorna o nome da RA

            // Verifica se a função retornou o nome da RA
            if (resultado_consulta != NULL) {
                strcpy(nome_ra, resultado_consulta); // Caso positivo atribui o resultado da consulta ao nome da RA
            } else {
                strcpy(nome_ra, "Não encontrado"); // Em caso de erro exibe mensagem
            }

            // Imprime os dados
            printf("Nome da RA: %s\n", nome_ra);
            printf("Número de contratos: %d\n\n", lista_ra[i].total_contratos);
        }

    } else {
        printf("\nErro! Não foi possível abrir o arquivo de miniusinas.\n\n"); // Informa em caso de erro
    }

    fclose(arquivo_miniusinas); // Fecha o arquivo de miniusinas
}

#endif
