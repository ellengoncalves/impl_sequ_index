#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000000 // tamanho do vetor arquivo
#define TAM 10000 // tamanho/quantidade de posicoes e chaves a estrutura tabela possui

// definicao da estrutura da tabela de indices
struct indice{
    int chave;
    int posicao;
};

void carrega_arquivo_classificado(int array[], int size);
void imprime_arquivo(int array[], int size);
void preenche_tabela(struct indice arquivo[], int vetor[], int tam_vetor);
void busca_sequencial_indexada(int vetor[], int tam_vetor, struct indice arquivo[], int tam_struct, int x);

int main(){
    
    struct indice tabela[TAM];
    int arquivo[SIZE];
    int valor_busca;

    // preenche o vetor arquivo com os valores aleatorios
    carrega_arquivo_classificado(arquivo, SIZE);
    // imprime o vetor arquivo com os valores
    imprime_arquivo(arquivo, SIZE);

    // preenche e mostra a tabela de indices
    printf("*-----Vetor Tabela:-----*\n\n");
    preenche_tabela(tabela, arquivo, SIZE);

    // valor a ser buscado no vetor arquivo
    printf("Qual valor voce deseja buscar? ");
    scanf("%d", &valor_busca);

    // realiza a busca do valor digitado no vetor arquivo, aqui esse valor primeiro vai passar pela estrutura da tabela para que assim receba dois parametro para busca (o valor a ser buscado esta entre esses dois parametros, numero x e y), a fim de evitar que o valor seja procurado de 1 em 1 posicao no vetor arquivo
    busca_sequencial_indexada(arquivo, SIZE, tabela, TAM, valor_busca);

    return 0;
}

// preenche o vetor arquivo com valores aleatorios e ja classificados
void carrega_arquivo_classificado(int array[], int size){
    srand((unsigned)time(NULL));

    array[0] = rand() % 1000;
    for (int i = 1; i != size; i++){
        array[i] = array[i - 1] + (rand() % 100);
    }
}

// imprime o vetor aleatorio classificado
void imprime_arquivo(int array[], int size){
    for (int i = 0; i != size; i += 1){
        printf("[%d]: %d\n", i, array[i]);
    }
    printf("\n\n");
}

// preenche a estrutura da tabela de indices
void preenche_tabela(struct indice arquivo[], int vetor[], int tam_vetor){

    arquivo[0].chave = vetor[0];
    arquivo[0].posicao = 0;

    printf("[%d]: %d\n", arquivo[0].posicao, arquivo[0].chave);

    for (int i = 9999; i < tam_vetor; i += 10000){
        arquivo[i].chave = vetor[i];
        arquivo[i].posicao = i;
        printf("[%d]: %d\n", arquivo[i].posicao, arquivo[i].chave);
    }
}

// realiza a busca squencial indexada
void busca_sequencial_indexada(int vetor[], int tam_vetor, struct indice arquivo[], int tam_struct, int valor){
    int i;

   // um loop for é usado para percorrer a tabela de índices (arquivo[]) procurando o intervalo adequado para o valor de busca. O loop percorre até que o valor da chave na tabela de índices seja maior do que o valor de busca ou até o final da tabela de índices (tam_struct)
    for (i = 0; i < tam_struct && arquivo[i].chave <= valor; i++){
        i = arquivo[i].posicao; // atualiza o valor de 'i' para a posição da proxima chave na tabela de indices, garantindo que a busca seja realizada no intervalo necessario

        // aqui verifica-se se o índice i está dentro dos limites válidos do vetor (tam_vetor). Se estiver dentro dos limites, significa que há um intervalo de busca definido pela tabela de índices.
        if (i < tam_vetor){

            // o while é usado para percorrer o vetor dentro do intervalo definido pela tabela de índices. Ele continua até encontrar um valor maior ou igual ao valor de busca.
            while (i < tam_vetor && vetor[i] < valor){
                i++;
            }

            // verifica se o valor foi encontrado no vetor dentro do intervalo
            if (i < tam_vetor && vetor[i] == valor){
                //caso sim
                printf("O valor %d foi encontrado! E está na posição %d\n do vetor arquivo", valor, i);
                // caso nao
            }else{
                printf("O valor %d não se encontra no código\n", valor);
            }
        // aqui também caso nao, porém, funciona caso o índice i estiver fora dos limites do vetor, isso significa que o valor de busca está além do maior valor presente no vetor. Nesse caso, uma mensagem é impressa indicando que o valor não está presente no código.
        }else{
            printf("O valor %d não se encontra no código\n", valor);
        }
    }
}
