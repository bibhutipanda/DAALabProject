#include <stdio.h>
#include <string.h>
struct location
        {
        char name[50];
//        int cost;
//        struct location *connected;
        };
int main() {
    char ch='n';
    char c[1000];
    int n=5;
    FILE *fp;
    fp=fopen("master.txt","at+");
    struct location city;
    struct location p;

    n++;
    while(n--)
    {
//        fscanf(fp,"%[^\n]", c);
//        printf("%s",c);
        while (fgets(c, sizeof(c), fp)) {
            /* note that fgets don't strip the terminating \n, checking its
               presence would allow to handle lines longer that sizeof(line) */
            printf("%s", fp);
        }
    }

//        do
//    {
//        printf("\nEnter Name : ");
//        scanf("%s",city.name);
//        strcat(city.name,"\n");
//        fprintf(fp,"%s",city.name);
////
////        printf("\nDo you want to add another data (y/n) : ");
////
////        scanf("%c",&ch);
//
//    }while(n--);

    fclose(fp);
//    printf("Data Written succesfully\n");

    return 0;
}