#include <stdio.h>
 
int main(int argc, char** argv)
{
    FILE *entrada1, *entrada2;
    int c,d;
 
    int bytesLidos = 1;

    if(argc != 3)
    {
        fprintf(stderr,"Erro na chamada do comando.\n");
        fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM1] [ARQUIVO ORIGEM2].\n", argv[0]);
        return 1;
    }
 
    entrada1 = fopen(argv[1],"rb");
    if(!entrada1)
    {
        fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }
 
    entrada2= fopen(argv[2],"rb");
    if(!entrada2)
    {
        fclose(entrada2);
        fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[2]);
        return 1;
    }
 
    c = fgetc(entrada1);
    d = fgetc(entrada2);
    while(c != EOF)
    {
        

        if(c != d){

            fprintf(stderr,"os arquivos   nao sao iguais no byte %d \n", bytesLidos);
            //return 1;
        }


        c = fgetc(entrada1);
        d = fgetc(entrada2);

        bytesLidos++;

    }
 

      fprintf(stdout,"os arquivos sao EXATAMENTE iguais\n");

    fclose(entrada1);
    fclose(entrada2);
    return 0;
}