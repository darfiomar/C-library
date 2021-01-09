#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#define LONGUEUR_MAX_LINE 250

typedef struct book{
    char* nom_auteur;
    char* titre_livre;
    char* renter;
    char* cne;
    int dispo,annee_edition;
    float prix;
}book;


typedef struct library{
book *books;
unsigned int bookCount;
}library;

unsigned int lineCount(FILE *f){
    char c;
    unsigned int newline_count = 1;
    fseek(f, 0, SEEK_SET);

    while ( (c=fgetc(f)) != EOF ) {
        if ( c == '\n' )
            newline_count++;
    }

    clearerr(f);
    fseek(f, 0, SEEK_SET);

    return newline_count;
}



book readBook(FILE *f){
    char line[LONGUEUR_MAX_LINE], tmp[LONGUEUR_MAX_LINE];
    book b;
    int i=0, j;

    if(feof(f))
        printf("end of file reached.");
    if(ferror(f))
        printf("an unexpected error happened");

    fgets(line, LONGUEUR_MAX_LINE, f);


    for(j=0;line[i] != ';'; i++, j++){
        tmp[j] = line[i];
    }
    tmp[j] = '\0';
    b.nom_auteur = malloc(j+1);
    strcpy(b.nom_auteur, tmp);




    for(j=0, i++;line[i] != ';'; i++, j++){
        tmp[j] = line[i];
    }
    tmp[j] = '\0';
    b.titre_livre = malloc(j+1);
    strcpy(b.titre_livre, tmp);


    for(j=0, i++;line[i] != ';'; i++, j++){
        tmp[j] = line[i];
    }
    tmp[j] = '\0';
    b.annee_edition = atoi(tmp);



    for(j=0, i++;line[i] != ';'; i++, j++){
        tmp[j] = line[i];
    }
    tmp[j] = '\0';
    b.prix = atof(tmp);



    for(j=0, i++;line[i] != ';'; i++, j++){
        tmp[j] = line[i];
    }
    tmp[j] = '\0';
    b.dispo = atoi(tmp);



    for(j=0, i++;line[i] != ';'; i++, j++){
        tmp[j] = line[i];
    }
    tmp[j] = '\0';
    b.cne = malloc(100);
    strcpy(b.cne, tmp);


    for(j=0, i++;line[i]; i++, j++){
        tmp[j] = line[i];
    }
    tmp[j] = '\0';
    b.renter = malloc(100);
    strcpy(b.renter, tmp);


    return b;

}
void encrypt(char *str,int key)
{
    unsigned int i;
    for(i=0;i<strlen(str);++i)
    {
        str[i] = str[i] - key;
    }
}

void decrypt(char *str,int key)
{
    unsigned int i;
    for(i=0;i<strlen(str);++i)
    {
        str[i] = str[i] + key;
    }
}
void bibencrypt(char *bib){
    FILE *f = fopen(bib, "r+");
    unsigned int i,lines = lineCount(f);
    char *books[lines] ;
    for(i=0;i<lines;i++){
        fgets(books[i], LONGUEUR_MAX_LINE, f);
        encrypt(books[i],0xFACA);
    }
    fclose(f);
    FILE *fp = fopen(bib, "w+");
    for(i=0;i<lines;i++){
        fputs(books[i], fp);
    }
    fclose(fp);
}
void bibdecrypt(char *bib){
    FILE *f = fopen(bib, "r+");
    unsigned int i,lines = lineCount(f);
    char *books[lines] ;
    for(i=0;i<lines;i++){
        fgets(books[i], LONGUEUR_MAX_LINE, f);
        decrypt(books[i],0xFACA);
    }
    fclose(f);
    FILE *fp = fopen(bib, "w+");
    for(i=0;i<lines;i++){
        fputs(books[i], fp);
    }
    fclose(fp);
}
library readLibrary(FILE *f){
    library lb;
    unsigned int lines = lineCount(f);
    book* bks = malloc(sizeof(book) * lines);
    int i;


    fseek(f, 0, SEEK_SET);
    clearerr(f);
    for(i=0; i< lines; i++){
        bks[i] = readBook(f);
    }

    lb.books = bks;
    lb.bookCount = lines;
    return lb;
}


book saisieBook(){
    char tmp[100];
    book livre;

    printf("Veuillez saisir le nom de l\'auteur du livre.\n");
    gets(tmp);
    livre.nom_auteur = malloc(strlen(tmp));
    strcpy(livre.nom_auteur, tmp);

    printf("Veuillez saisir le titre du livre.\n");
    gets(tmp);
    livre.titre_livre = malloc(strlen(tmp));
    strcpy(livre.titre_livre, tmp);

    printf("Veuillez indiquer l\'annee d\'edition du livre.\n");
    gets(tmp);
    livre.annee_edition = atoi(tmp);

    printf("Veuillez indiquer le prix du livre.\n");
    gets(tmp);
    livre.prix = atof(tmp);

    livre.renter = malloc(100);
    strcpy(livre.renter, "-");

    livre.cne = malloc(100);
    strcpy(livre.cne, "-");

    return livre;
}

void writeBook(FILE *f, book livre){
    clearerr(f);
    fprintf(f,"\n");
    fputs(livre.nom_auteur,f);fprintf(f,";");
    fputs(livre.titre_livre,f);fprintf(f,";");
    fprintf(f,"%d",livre.annee_edition);fprintf(f,";");
    fprintf(f,"%.2f",livre.prix);fprintf(f,";");
    fprintf(f,"1");fprintf(f,";");
    fprintf(f,"-");fprintf(f,";");
    fprintf(f,"-");
}

void newbook(FILE *f){ // fonction qui permet d'ajouter de nouveaux livres a la bibliothèque !
    int i, book_number;
    book b;

    printf("Donnez le nombre de livres que vous voulez enregistrer : ");
    scanf("%d",&book_number);getchar();// buffer

    for(i=0;i<book_number;i++){
        printf("Veuillez saisir les informations du livre numero %d .\n\n",i+1);
        b = saisieBook();
        writeBook(f, b);
        lineprinter();
    }

}
void printallbooks(FILE *f){
    library lb = readLibrary(f);
    FILE *fp = fopen("index.html","w");
    fprintf(fp,"<!DOCTYPE html><html > <head> <meta charset=\"UTF-8\"> <title>ENSA-Bibliothèque</title> <link rel=\"stylesheet\" href=\"css/reset.css\"><link rel=\"stylesheet\" href=\"css/style.css\"> </head> <body> <section> <h1> Nos Livres </h1> <div class=\"tbl-header\"><table cellpadding=\"0\" cellspacing=\"0\" border=\"0\"> <thead> <tr> <th>Titre du livre</th> <th>Nom de l'auteur</th> <th>Année de d'édition</th> <th>Prix (MAD)</th> <th>Disponible</th> <th>Nom de l'emprunteur</th> <th>CNE de l'emprunteur</th> </tr></thead></table></div><div class=\"tbl-content\"><table cellpadding=\"0\" cellspacing=\"0\" border=\"0\"> <tbody>");
    int i;
    for(i=0;i<lb.bookCount;i++){
        fprintf(fp,"<tr>");
        fprintf(fp,"<td>%s</td>",lb.books[i].titre_livre);
        fprintf(fp,"<td>%s</td>",lb.books[i].nom_auteur);
        fprintf(fp,"<td>%d</td>",lb.books[i].annee_edition);
        fprintf(fp,"<td>%.2f</td>",lb.books[i].prix);
        if(lb.books[i].dispo == -1){
            fprintf(fp,"<td>VENDU</td>");
            fprintf(fp,"<td>-----</td>");
            fprintf(fp,"<td>-----</td>");
        }
        else{
            if(lb.books[i].dispo == 1){
                fprintf(fp,"<td>OUI</td>");
                fprintf(fp,"<td>-----</td>");
                fprintf(fp,"<td>-----</td>");
            }
            else{
                fprintf(fp,"<td>NON</td>");
                fprintf(fp,"<td>%s</td>",lb.books[i].renter);
                fprintf(fp,"<td>%s</td>",lb.books[i].cne);
            }
        fprintf(fp,"</tr>");
        }
    }
    fprintf(fp,"</tbody></table></div></section><div class=\"made-with-love\"> <strong>Copyright © &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp 2016 WorldDev Team, LLC.&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp All Rights Reserved.</strong><\/div><script src=\"js/min.js\"></script><script src=\"js/index.js\"></script> </body></html>");
    fclose(fp);
    printf("- L\'affichage des livres de la bibliotheque s\'effectuera sur une page web dans  quelques secondes :) \n\n");
    Sleep(2000);
    system("index.html");

}
void webpageinit(){
    FILE *fp = fopen("index.html","w");
    fprintf(fp,"<!DOCTYPE html><html ><head> <meta charset=\"UTF-8\"> <title>ENSA-Bibliothèque</title> <script type=\"text/JavaScript\">setTimeout(alert(\"- Seul le programme de gestion de la bibliothèque peut ouvrir cette page web.\\n- Si vous êtes la, c\\'est parceque vous avez ouvert cette page volontairement.\\n- Par conséquent, aucune information ne sera fournie.\\n- Cette page sert à afficher tous les livres de la bibliothèque.\\n- Pour plus de renseignements, veuillez consulter l\'application !\"),0000);</script> <link rel=\"stylesheet\" href=\"css/reset.css\"><link rel=\"stylesheet\" href=\"css/style.css\"> </head> <body> <section> <h1>accès interdit au public !</h1> <br><br></div><center><img src=\"css/bg_404.png\"></center><br><br></section><div class=\"made-with-love\"> <strong>Copyright © &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp 2016 WorldDev Team, LLC. &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp All Rights Reserved.</strong><\/div><script src=\"js/min.js\"></script><script src=\"js/index.js\"></script> </body></html>");
    fclose(fp);
}
void setlib(){
    FILE *f;
    char clientbook[100];
    char clientname[100];
    char clientcne[100];
    int c,i,fixer=-1;
    char rep;
    f = fopen("bibliotheque.txt", "r");
    library lb = readLibrary(f);
    fclose(f);
    printf("Donnez le titre du livre que vous cherchez : ");
    gets(clientbook);
    for(i=0; i<lb.bookCount; i++){
        if(strcmp(clientbook,lb.books[i].titre_livre)==0) fixer = i ;
    }
    if(fixer!=-1){
        if(lb.books[fixer].dispo == -1){
            printf("  Titre du livre : %s\n",lb.books[fixer].titre_livre);
            printf("  Nom de l\'auteur : %s\n",lb.books[fixer].nom_auteur);
            printf("  Annee d\'edition du livre : %d\n",lb.books[fixer].annee_edition);
            printf("\n  Livre vendu .\n ");

            exitman();
        }
        else{
            printf("Nous disposons du livre que vous chercher ! \n\n");
            printf("  Titre du livre : %s\n",lb.books[fixer].titre_livre);
            printf("  Nom de l\'auteur : %s\n",lb.books[fixer].nom_auteur);
            printf("  Annee d\'edition du livre : %d\n",lb.books[fixer].annee_edition);
            printf("  Prix du livre : %.2f\n",lb.books[fixer].prix);
            printf("\n");
            if(lb.books[fixer].dispo == 1){
                printf("\t(01)  - Pret d\'un livre.\n ");
                printf("\t(02)  - Achat d\'un livre.\n ");
                printf("\t(XX)  - Quitter l\'application.\n ");
                printf("\n   Veuillez tapper le numero de l\'operation que vous souhaitez executer : ");
                scanf("%d",&c);getchar();
                printf("\n");
                lineprinter();
                switch(c){
                    case 1 :{
                        printf("\t- Pret d\'un livre.\n");
                        printf(" Donnez votre CNE : ") ;
                        gets(clientcne);
                        printf(" Donnez votre nom complet : ") ;
                        gets(clientname);
                        strcpy(lb.books[fixer].cne,clientcne);
                        strcpy(lb.books[fixer].renter,clientname);
                        strcat(lb.books[fixer].renter,"\n");
                        lb.books[fixer].dispo = 0;
                        printf("\n Valide. Veuillez rendre le livre avant la fin de l\'annee !\n");
                        exitman();
                        break;}
                    case 2 :{
                        printf("\t- Achat d\'un livre.\n");
                        printf("  Prix du livre : %.2f\n",lb.books[fixer].prix);
                        printf("Valider l\'achat ('o' pour valider / autre pour annuler ) : ");
                        scanf("%c",&rep);getchar();
                        if(rep == 'o'){
                            lb.books[fixer].dispo = -1;
                            printf("   Achat valide.\n ");
                        }
                        else printf("   Achat annule.\n ");
                        exitman();
                        break;}
                    default :  exitman();
                }
            }
            else{
                printf("Le livre que voulez n\'est pas disponible :/ \n");
                printf(" Nom de l\'emprunteur du livre : %s",lb.books[fixer].renter);
                printf(" CNE de l\'emprunteur du livre : %s\n",lb.books[fixer].cne);
                printf("Voulez vous rendre le livre ('o' pour valider / autre pour annuler ) : ");
                scanf("%c",&rep);getchar();
                if(rep == 'o'){
                    strcpy(lb.books[fixer].cne,"-");
                    strcpy(lb.books[fixer].renter,"-\n");
                    lb.books[fixer].dispo = 1;
                    printf("   Livre remis a la bibliotheque.\n ");
                }
                exitman();
            }
        }
    }
    else {printf("Le livre que vous cherchez n\'existe pas :(\n");exitman();}
    f = fopen("bibliotheque.txt", "w");
    for(i=0; i<lb.bookCount; i++){
        fprintf(f,"%s;%s;%d;%.2f;%d;%s;%s",lb.books[i].nom_auteur, lb.books[i].titre_livre, lb.books[i].annee_edition, lb.books[i].prix, lb.books[i].dispo, lb.books[i].cne, lb.books[i].renter );
    }
    fclose(f);
}
void exitman(){
    printf("\n");
    lineprinter();
    printf("\tMerci d\'avoir utilise notre programme, a bientot !\n");
    lineprinter();
}
void lineprinter(){
    printf("-------------------------------------------------------------------------------\n");
}

#endif // HEADER_H_INCLUDED
