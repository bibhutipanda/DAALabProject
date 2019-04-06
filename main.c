#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct city {
    char cityname[20];
    int n;
};

//struct city* reconstruction(){}

void main () {
    int n,t;
    struct city input;
    struct city *node;
    FILE *outfile,*infile;

    // open Accounts file for writing
//    outfile = fopen("city.bin", "wb");
//    if (outfile == NULL) {
//        fprintf(stderr, "\nError opening accounts.dat\n\n");
//        exit(1);
//    }
//
//    // instructions to user
//    printf("Enter \"stop\" for First Name to end program.");
//
//    // endlessly read from keyboard and write to file
//    // prompt user
//    printf("\nCity name: ");
//    scanf("%s", input.cityname);
//    // exit if no name provided
//    if (strcmp(input.cityname, "stop") == 0)
//        exit(1);
//    // continue reading from keyboard
//    printf("Number of connected cities : ");
//    scanf("%d", &n);
//    input.n=n;
//    fwrite(&input, sizeof(struct city *), 1, outfile);
//    while (n--) {
//        node = (struct city *) malloc(sizeof(struct city));
//        printf("Enter connected city name: ");
//        scanf("%s", node->cityname);
//        printf("Enter cost from source city: ");
//        scanf("%d", &(node->n));
//        fwrite(node, sizeof(struct city *), 1, outfile);
//        printf ("City name = %s\nCost = %d\n",node->cityname,node->n);
//    }
//    fclose(outfile);
    infile = fopen ("city.bin","rb");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening accounts.dat\n\n");
        exit (1);
    }


    while (fread (&input, sizeof(struct city), 1, infile))
    {
        printf("City name = %s\n",input.cityname);
        printf("Cost = %d\n",input.n);
    }
        fclose(infile);
}