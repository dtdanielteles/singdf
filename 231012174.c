/********************************************************************************
Aluno(a): Daniel Teles Brito
Matr�cula: 231012174

Declaro que eu sou o(a) autor(a) deste trabalho e que o c�digo n�o foi copiado
de outra pessoa nem repassado para algu�m. Estou ciente de que poderei sofrer
penaliza��es na avalia��o em caso de detec��o de pl�gio.

*********************************************************************************/

/********************************************************************************

Unb - FGA
Trabalho final de APC 2023.1
Sistema de Informa��es sobre Gera��o e Distribui��o Fotovoltaica (SINGDF) v2.0
�ltima atualiza��o: 07/07/2023

Este software tem por objetivo gerir e acompanhar a produ��o, e o consumo
de energia fotovoltaica no Distrito Federal.

*********************************************************************************/

// Inclus�o de biblioteca pessoal de fun��es, defines, includes, structs e procedimentos
#include "231012174.h"

// Fun��o principal do programa
int main() {
    setlocale(LC_CTYPE, "Portuguese"); // Configura exibi��o em l�ngua portuguesa

    int opcao; // Vari�vael que armazena op��o
    int resultado;

    // Executa enquanto o usu�rio n�o solicitar sa�da
    do {
        menu(); // Exibe o menu
        resultado = scanf("%d", &opcao); // L� e armazena a op��o do usu�rio, atribui 0 a resultado se for digitada uma letra

        // Se for digitado uma letra, atribui op��o como zero e limpa o buffer
        if (resultado == 0){
            opcao = 0;
            limpar_buffer();
        }

        // De a cordo com a op��o escolhida, executa os procedimentos adequados
        switch (opcao) {

            // Consulta miniusina cadastrada atrav�s do CNPJ
            case CONSULTAR_MINIUSINA:
            consultar_miniusina(); // Procedimento para executar a a��o prevista na op��o
            limpar_buffer(); // Limpa buffer
            pausa(); // Aguarda a��o
            limpar_tela(); // Limpa tela
            break; // Sai do loop e retorna para o menu

            // Consulta consumidor cadastrado atrav�s do CPF/CNPJ
            case CONSULTAR_CONSUMIDOR:
            consultar_consumidor();
            limpar_buffer();
            pausa();
            limpar_tela();
            break;

            // Lista todas as miniusinas cadastradas
            case LISTAR_MINIUSINAS:
            listar_miniusinas();
            limpar_buffer();
            pausa();
            limpar_tela();
            break;

            // Lista as miniusinas em opera��o por ordem decrescente de capacidade de gera��o de energia
            case LISTAR_MINIUSINAS_DESCRESCENTE_CAPACIDADE:
            listar_miniusinas_descrescente_capacidade();
            limpar_buffer();
            pausa();
            limpar_tela();
            break;

            // Lista as RAs por ordem decrescente de quantidade de miniusinas
            case LISTAR_RAS_DESCRESCENTE_QUANTIDADE:
            listar_ras_decrescente_quantidade();
            limpar_buffer();
            pausa();
            limpar_tela();
            break;

            // Lista as RAs por ordem crescente de n�mero de contratos
            case LISTAR_RAS_CRESCENTE_CONTRATOS:
            listar_ras_crescente_contratos();
            limpar_buffer();
            pausa();
            limpar_tela();
            break;

            // Lista as RAs por ordem decrescente de capacidade de gera��o
            case LISTAR_RAS_DESCRESCENTE_CAPACIDADE:
            listar_ras_decrescente_capacidade();
            limpar_buffer();
            pausa();
            limpar_tela();
            break;

            // Lista as RAs por ordem decrescente de percentual de energia dispon�vel
            case LISTAR_RAS_DESCRESCENTE_PERCENTUAL:
            listar_ras_decrescente_percentual();
            limpar_buffer();
            pausa();
            limpar_tela();
            break;

            // Encerra execu��o do sistema
            case SAIR:
            printf("\nEncerrando execu��o do programa...\n\n\n"); // Exibe mensagem informando que o sistema ser� encerrado
            limpar_buffer();
            limpar_tela();
            break;

            // Em caso de op��o inv�lida, exibe a mensagem
            default:
            printf("\nOp��o inv�lida! Confira o n�mero digitado.\n\n\n");
            pausa();
            limpar_tela();
            break;
        }
    } while(opcao != SAIR);

    return 0;
}
