#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "pnm.h"
#include "codeBarre.h"

int main(){

    int a = 89864495;
    char tab[] = {8,9,8,6,4,4,9,5};
    if(!isdigit(tab[0]))
        printf("pas un nombre\n");
    else
        printf("un nombre\n");
    /*char bin[7][7];
    int cpt = 0;
    for(unsigned i = 0; i < 7; i++){
        for(unsigned j = 0; j < 7; j++){
            if(cpt % 2 == 0)
                bin[i][j] = 1;
            else
           j     bin[i][j] = 0;
            cpt++;
        }
    }*/
    int **dec = decimal_to_binary(a);
    for(unsigned i = 0; i < 7; i++){
        printf("[ ");
        for(unsigned j = 0; j < 7; j++){
            printf("%d ", dec[i][j]);
        }
        printf("]\n");
    }
    FILE* fp = fopen("lesmat.txt", "r");
    if(fp == NULL)
        return-1;
    else{
        PNM* image = set_value_matrix(dec, 70, 70);
        image = set_lines_columns(70);
        image = set_magicnumber(P1);
        char test[] = {'t','e','s','t','.','p','b','m'};
        write_pnm(get_pnm(image), test);
        printf("ok\n");
    }
    /*if(dec != NULL){
        int tab1[70][70];
        int begin1 = 0;
        int begin2 = 0;
        int end1 = 10;;
        int end2 = 10;
        unsigned int l;
        for(unsigned i = 0; i < 7; i++){
            for(unsigned j = 0; j < 7; j++){//Change the names of the variables !!!
                for(unsigned k = begin1; k < end1; k++){//replace it with a constant (hardcodage)
                    for(l = begin2; l < end2; l++){
                        tab1[k][l] = dec[i][j];
                    }
                }
                begin2 += 10;
                end2 += 10;
            }
        }
        for(unsigned i = 0; i < 70; i++){
            printf("[ ");
            for(unsigned j = 0; j < 70; j++){
                printf("%d ", tab1[i][j]);
            }
            printf("]\n");
        }
    }*/
    return 0;
}