#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include "header.h"


 void lineprinter();
 void exitman();
 unsigned int lineCount(FILE *f);
 book readBook(FILE *f);
 library readLibrary(FILE *f);
 book saisieBook();
 void writeBook(FILE *f, book livre);
 void newbook(FILE *f);
 void setlib();
 void printallbooks(FILE *f);
 void webpageinit();


int main()
{
    int j=0;
    char password[30],database[30]="admin";
    printf("\t\t_______________________________________________\n");
    printf("\t\t|                                             |\n");
    printf("\t\t|      Gestionnaire de ENSA-bibliotheque      |\n");
    printf("\t\t|_____________________________________________|\n");
    printf("\n\n");
    printf("\t\t             -----> Sign in <-----          \n");
    printf("\t\t            USERNAME : ENSA-LIBRARY          \n");
    do{
        printf("\t\t            PASSWORD : ");
        gets(password);
        if(strcmp(database,password)==0)  // test password
        {
            printf("\n\t\t            -----> CONNECTED <-----          \n");
            Sleep(1000);
            system("cls");
            int i;
            printf("\t\t_______________________________________________\n");
            printf("\t\t|                                             |\n");
            printf("\t\t|      Gestionnaire de ENSA-bibliotheque      |\n");
            printf("\t\t|_____________________________________________|\n");
            printf("\n\n\n");
            printf("\t(01)  - Nos livres.\n ");
            printf("\t(02)  - Gestion.\n ");
            printf("\t(03)  - Nouveau livre.\n ");
            printf("\t(XX)  - Quitter l\'application.\n ");
            printf("\n   Veuillez tapper le numero de l\'operation que vous souhaitez executer : ");
            scanf("%d",&i);getchar();
            printf("\n");
            lineprinter();
            //bibdecrypt("bibliotheque.txt");
            switch(i){
                case 1 :{
                    FILE *f = fopen("bibliotheque.txt", "r");
                    printallbooks(f);
                    fclose(f);
                    exitman();
                    Sleep(1000);
                    webpageinit();
                    break;}
                case 2 :{
                    setlib();
                    break;}
                case 3 :{
                    FILE *f = fopen("bibliotheque.txt", "a+");
                    newbook(f);
                    fclose(f);
                    exitman();
                    break;
                }
                default :  exitman();
            }
            //bibencrypt("bibliotheque.txt");
            break ;
        }
        else
        {
            j++;
            printf("\t\t\tINVALID password. Please try again !\n");
        }
    }while(j<3);
    if(j>=3) printf("\n\t\t  You have entered a wrong password too many times.\n\n");

    system("pause>null");
    return 0;
}
