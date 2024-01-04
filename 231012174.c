/********************************************************************************
Aluno(a): Daniel Teles Brito
Matrícula: 231012174

Declaro que eu sou o(a) autor(a) deste trabalho e que o código não foi copiado
de outra pessoa nem repassado para alguém. Estou ciente de que poderei sofrer
penalizações na avaliação em caso de detecção de plágio.

*********************************************************************************/

/********************************************************************************

Unb - FGA
Trabalho final de APC 2023.1
Sistema de Informações sobre Geração e Distribuição Fotovoltaica (SINGDF) v2.0
Última atualização: 07/07/2023

Este software tem por objetivo gerir e acompanhar a produção, e o consumo
de energia fotovoltaica no Distrito Federal.

*********************************************************************************/

// Inclusão de biblioteca pessoal de funções, defines, includes, structs e procedimentos
#include "231012174.h"

// Função principal do programa
int main() {
    setlocale(LC_CTYPE, "Portuguese"); // Configura exibição em língua portuguesa

    int opcao; // Variávael que armazena opção
    int resultado;

    // Executa enquanto o usuário não solicitar saída
    do {
        menu(); // Exibe o menu
        resultado = scanf("%d", &opcao); // Lê e armazena a opção do usuário, atribui 0 a resultado se for digitada uma letra

        // Se for digitado uma letra, atribui opção como zero e limpa o buffer
        if (resultado == 0){
            opcao = 0;
            limpar_buffer();
        }

        // De a cordo com a opção escolhida, executa os procedimentos adequados
        switch (opcao) {

            // Consulta miniusina cadastrada através do CNPJ
            case CONSULTAR_MINIUSINA:
            consultar_miniusina(); // Procedimento para executar a ação prevista na opção
            limpar_buffer(); // Limpa buffer
            pausa(); // Aguarda ação
            limpar_tela(); // Limpa tela
            break; // Sai do loop e retorna para o menu

            // Consulta consumidor cadastrado através do CPF/CNPJ
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

            // Lista as miniusinas em operação por ordem decrescente de capacidade de geração de energia
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

            // Lista as RAs por ordem crescente de número de contratos
            case LISTAR_RAS_CRESCENTE_CONTRATOS:
            listar_ras_crescente_contratos();
            limpar_buffer();
            pausa();
            limpar_tela();
            break;

            // Lista as RAs por ordem decrescente de capacidade de geração
            case LISTAR_RAS_DESCRESCENTE_CAPACIDADE:
            listar_ras_decrescente_capacidade();
            limpar_buffer();
            pausa();
            limpar_tela();
            break;

            // Lista as RAs por ordem decrescente de percentual de energia disponível
            case LISTAR_RAS_DESCRESCENTE_PERCENTUAL:
            listar_ras_decrescente_percentual();
            limpar_buffer();
            pausa();
            limpar_tela();
            break;

            // Encerra execução do sistema
            case SAIR:
            printf("\nEncerrando execução do programa...\n\n\n"); // Exibe mensagem informando que o sistema será encerrado
            limpar_buffer();
            limpar_tela();
            break;

            // Em caso de opção inválida, exibe a mensagem
            default:
            printf("\nOpção inválida! Confira o número digitado.\n\n\n");
            pausa();
            limpar_tela();
            break;
        }
    } while(opcao != SAIR);

    return 0;
}
