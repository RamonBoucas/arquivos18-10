#include <stdio.h>
#include <string.h>
//#define TAMANHO 4096

typedef struct _Endereco Endereco;
 
struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};
 

int compare_function(const void *a,const void *b) {

Endereco *e1 = (Endereco *) a;
Endereco *e2 = (Endereco *) b;

 
//return e1->cep - e2->cep;
 
return(strcmp(e1->cep,e2->cep));

}



int main(int argc, char** argv)
{
    FILE *entrada, *saida;
    Endereco e;
    int qtd;

    int contArquivos = 0;

    int tamanhoMaximoRegistros = 2000;
 
    Endereco  vetor[tamanhoMaximoRegistros];


    if(argc != 2)
    {
        fprintf(stderr,"Erro na chamada do comando.\n");
        fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] .\n", argv[0]);
        return 1;
    }
 
    entrada = fopen(argv[1],"rb");
    if(!entrada)
    {
        fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }
 
    
    qtd = fread(&e,1,sizeof(Endereco),entrada);

    while(qtd > 0){
 
        char nomeArquivo[50];

        snprintf(nomeArquivo,50,"sai%d%s",contArquivos,".dat");
        


        printf("%s",nomeArquivo);


        saida = fopen(nomeArquivo,"wb");
        contArquivos++;

        int contRegArquivo = 0;
        int contRegVetor = 0;


        while((contRegArquivo < tamanhoMaximoRegistros) && (qtd > 0)){

            vetor[contRegArquivo] = e;
            //fwrite(&e,1,sizeof(Endereco),saida);
            qtd = fread(&e,1,sizeof(Endereco),entrada);
            contRegArquivo++;
        }

        qsort(vetor,contRegArquivo,sizeof(Endereco),compare_function);
         

        while(contRegVetor < contRegArquivo)  {

            e = vetor[contRegVetor];
            fwrite(&e,1,sizeof(Endereco),saida);
            contRegVetor++;
        }

        fclose(saida);
    }

fclose(entrada);

// aqui termina o picotador de arquivos

int quantidadeArquivosOriginais = contArquivos;
int contadorEscrita = quantidadeArquivosOriginais;
int contadorLeitura1 = 0;
int contadorLeitura2 = 1;


while(5 == 5){

 

char nomeArquivoEscrita[50];
snprintf(nomeArquivoEscrita,50,"sai%d%s",contadorEscrita,".dat");

char nomeArquivoLeitura1[50];
snprintf(nomeArquivoLeitura1,50,"sai%d%s",contadorLeitura1,".dat");

char nomeArquivoLeitura2[50];
snprintf(nomeArquivoLeitura2,50,"sai%d%s",contadorLeitura2,".dat");

FILE *leitura1,*leitura2,*escrita1;
 
leitura1 = fopen(nomeArquivoLeitura1,"rb");

if(leitura1 == NULL){
	printf("algo estranho aconteceu,");
	break;
	 
}

leitura2 = fopen(nomeArquivoLeitura2,"rb");

if(leitura2 == NULL){
	printf("acabou , o ultimo arquivo é o resultado final e deve ser igual ao cep ordenado");
	break;
}

escrita1 = fopen(nomeArquivoEscrita,"wb");

  printf("%s",nomeArquivoLeitura1);
  printf("%s",nomeArquivoLeitura2);
  printf("%s",nomeArquivoEscrita);

intercala(leitura1,leitura2,escrita1);



contadorLeitura1 += 2;
contadorLeitura2 += 2;
contadorEscrita++;


}








    return 0;
}

int intercala(FILE *entrada1,FILE *entrada2, FILE*saida)
{
    //FILE *entrada1,*entrada2 ,*saida;
   // char buffer[TAMANHO];
    int qtd1,qtd2;
    Endereco e1,e2;
 
    /*
    if(argc != 4)
    {
        fprintf(stderr,"Erro na chamada do comando.\n");
        fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM]  [ARQUIVO ORIGEM2]  [ARQUIVO DESTINO].\n", argv[0]);
        return 1;
    }
 
    entrada1 = fopen(argv[1],"rb");
    if(!entrada1)
    {
        fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }
 

    entrada2 = fopen(argv[2],"rb");
    if(!entrada2)
    {
        fclose(entrada1);
        fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[2]);
        return 1;
    }

    */
    //entrada1 = fopen(argv[1],"rb");
    //entrada2 = fopen(argv[2],"rb");
    //saida = fopen(argv[3],"wb");
    /*
    if(!saida)
    {
        fclose(entrada1);
        fclose(entrada2);
        fprintf(stderr,"Arquivo %s não pode ser aberto para escrita\n", argv[3]);
        return 1;
    }
 */
    qtd1 = fread(&(e1),1,sizeof(Endereco),entrada1);
    qtd2 = fread(&(e2),1,sizeof(Endereco),entrada2);

    int x =0;

    while((qtd1>0) && (qtd2>0)){

        if(strncmp(e1.cep,e2.cep,8) < 0){

            fwrite(&(e1),1,sizeof(e1),saida);
            qtd1 = fread(&(e1),1,sizeof(Endereco),entrada1);

        }else{

            fwrite(&(e2),1,sizeof(e2),saida);
            qtd2 = fread(&(e2),1,sizeof(Endereco),entrada2);

        }

        x++;
    }

    if(qtd1 <= 0){
        // significa que o cabeçote leu todo o arquivo 1
        while(qtd2 >0) {
            fwrite(&(e2),1,sizeof(e2),saida);
            qtd2 = fread(&(e2),1,sizeof(Endereco),entrada2);
        }

    }else if(qtd2 <= 0){
        // significa que o cabeçote leu todo o arquivo 2
        while(qtd1 > 0) {
            fwrite(&(e1),1,sizeof(e1),saida);
            qtd1 = fread(&(e1),1,sizeof(Endereco),entrada1);
        }

    }

    fclose(entrada1);
    fclose(entrada2);
    fclose(saida);
    return 0;
}