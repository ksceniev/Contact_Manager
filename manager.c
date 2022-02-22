#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30

typedef struct Contato{
    char nome[N], ph[N], email[N];
    int addr; 
} contato;

FILE *fp, *tfp;

int main(){
    contato ct;
    char ch, qr[N], str[N];
    int op, i, c, n, ok;

    main:

    printf("\n\nSISTEMA DE GESTAO DE CONTATOS\n\n");
    do{
        printf("[1] ADICIONAR CONTATO\n[2] LISTAR CONTATOS\n[3] PROCURAR CONTATO\n[4] EDITAR CONTATO\n[5] DELETAR CONTATO\n[0] SAIR\n");
        printf("DIGITE UMA OPÇÃO VALIDA: ");
        scanf("%d", &op);
    }while(op != 0 && op != 1 && op != 2 && op !=3 && op !=4 && op != 5);

    switch(op){
        case 0:

            printf("Bye! \n");
            break;
        
        case 1:
            fp = fopen("contatos.data", "a");

            for(i = 0;; i++){
                getchar();

                printf("Nome: ");
                fgets(ct.nome, N, stdin);
                fflush(stdin);

                printf("Email: ");
                fgets(ct.email, N, stdin);
                fflush(stdin);

                printf("Telefone: ");
                fgets(ct.ph, N, stdin);
                fflush(stdin);

                printf("Endereço -6 digitos-: ");
                scanf("%i", &ct.addr);
                fflush(stdin);
                printf("\n");

                fwrite(&ct, sizeof(ct), 1, fp);

                printf("NOVO CONTATO? (y/n): ");
                scanf(" %c", &ch);
                
                if((ch == 'n') || (i == N)){
                    fclose(fp);
                    goto main;
                }
            }

        case 2:
            
            fp = fopen("contatos.data", "r");
            fflush(stdin);

            for(;fread(&ct, sizeof(ct), 1, fp) != 0;){
                printf("\nNome: %sEmail: %sTelefone: %sEndereço: %i\n", ct.nome, ct.email, ct.ph, ct.addr);
            }
            
            fclose(fp);
            goto main;

        case 3:
            
            do{
                fp = fopen("contatos.data", "r");
                
                getchar();
                printf("Procurar: ");
                fgets(qr, N, stdin);

                sprintf(str, "%i", ct.addr);
                printf("\n");

                for(c = 0; fread(&ct, sizeof(ct), 1, fp) != 0;){ /* reescrever esse for */

                    if(strcmp(ct.nome, qr) == 0 || strcmp(ct.email, qr) == 0 || strcmp(ct.ph, qr) == 0 || strcmp(str, qr) == 0){
                        printf("Nome: %sEmail: %sTelefone: %sEndereço: %i\n", ct.nome, ct.email, ct.ph, ct.addr);
                        c++;
                    }
                }

                if(c == 0)
                    printf("NADA ENCONTRADO!\n");
                

                fclose(fp);
                printf("\n");
                printf("OUTRA BUSCA? (y/n): ");
                scanf(" %c", &ch);

            }while(ch == 'y');

            goto main;

        case 4:

            do{    
                fp = fopen("contatos.data", "r");
                tfp = fopen("temp.data", "w");

                getchar();
                printf("CONTATO A EDITAR: ");
                fgets(str, N, stdin);
                printf("\n");

                for(c = 0; fread(&ct, sizeof(ct), 1, fp) != 0;){
                    if(strcmp(str, ct.nome) == 0){
                        printf("Nome: %sEmail: %sTelefone: %sEndereço: %i\n\n", ct.nome, ct.email, ct.ph, ct.addr);
                        c++;
                    }
                    else
                        fwrite(&ct, sizeof(ct), 1, tfp);
                }

                if(c == 0)
                    printf("CONTATO NAO EXISTE\n");

                printf("+EDITOR+\n");
                printf("Nome: ");
                fgets(ct.nome, N, stdin);
                fflush(stdin);

                printf("Email: ");
                fgets(ct.email, N, stdin);
                fflush(stdin);

                printf("Telefone: ");
                fgets(ct.ph, N, stdin);
                fflush(stdin);

                printf("Endereço -6 digitos-: ");
                scanf("%i", &ct.addr);
                fflush(stdin);
                printf("\n");

                printf("EDITAR OUTRO CONTATO? (y/n): ");
                scanf(" %c", &ch);

                fwrite(&ct, sizeof(ct), 1, tfp);
                fclose(fp), fclose(tfp);

                remove("contatos.data");
                rename("temp.data", "contatos.data");
            }while(ch == 'y');

            goto main;
        
        case 5:

            do{ 
                getchar();
                printf("CONTATO A DELETAR: ");
                fgets(str, N, stdin);

                fp = fopen("contatos.data", "r");
                tfp = fopen("temp.data", "w");

                for(c = 0; fread(&ct, sizeof(ct), 1, fp) != 0;){
                    if(strcmp(ct.nome, str) != 0)
                        fwrite(&ct, sizeof(ct), 1, tfp);
                    else 
                        c++;
                }

                fclose(fp), fclose(tfp);
                remove("contatos.data");
                rename("temp.data", "contatos.data");

                printf("\nDELETAR OUTRO CONTATO? (y/n): ");
                scanf(" %c", &ch);

            }while(ch == 'y');

            goto main;      
    }

    return 0;

}