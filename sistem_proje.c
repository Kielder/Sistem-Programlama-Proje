#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

int karsilastir(Jval d1, Jval d2);

int main(int argc, char *argv[]) {
    IS      is, wr;
    JRB     redBlackTree, rDugum, sortedTree;
    FILE    *fp;
    char    params[100];
    char    temp[100];

    redBlackTree = make_jrb();

    is = new_inputstruct(NULL); // use NULL for std input
    wr = new_inputstruct(argv[1]);

    if(wr == NULL) {
        printf("ERROR: Verilen dosya ismi hatali.\n");
    }
    else if(argc == 2) { // ./program fileName şeklinde başlatıldığında .txt içindeki verileri ağaca ekler.
        while(get_line(wr) != EOF) {
            if(!strcmp(wr->text2,"add") && wr->NF == 4) {
                strcpy(temp, wr->fields[1]);
                strcat(temp, ",");
                strcat(temp, wr->fields[2]);
                strcat(temp, ",");
                strcat(temp, wr->fields[3]);
                jrb_insert_str(redBlackTree, strdup(wr->fields[0]), new_jval_s(strdup(temp)));
            }
            else {
                printf("ERROR: Bicim olarak uygun olmayan kayita rastlandi. Agaca eklenmedi.\n");
            }
        }
    }

    while(strcmp(is->text2, "quit\n")) {
        printf("> ");
        fflush(stdout);

        while(get_line(is) >= 0) {
            if(!strcmp(is->text2, "add")) { 
                if(is->NF < 4 || is->NF > 4) {
                    printf("ERROR: 4 adet parametre girmelisiniz.\n");
                }
                else {
                    if(jrb_find_str(redBlackTree, is->fields[0]) == NULL) { // Eklemek istenilen key önceden yoksa
                        strcpy(params, "");
                        strcat(params, is->fields[1]);
                        strcat(params, ",");
                        strcat(params, is->fields[2]);
                        strcat(params, ",");
                        strcat(params, is->fields[3]);
                        jrb_insert_str(redBlackTree, strdup(is->fields[0]), new_jval_s(strdup(params)));
                    }
                    else
                        printf("ERROR: Eklemek istediginiz key degeri agac icerisinde mevcut.\n");
                }
            }
            else if(!strcmp(is->text2, "search")) {
                if(is->NF < 1 || is->NF > 1) {
                    printf("ERROR: 1 adet parametre girmelisiniz.\n");
                }
                else {
                    memset(temp,0,sizeof(temp));
                    jrb_traverse(rDugum, redBlackTree) {
                        strcpy(temp, rDugum->key.s); // Örn: "search|a" diye 'a' anahtarını arattığımızda
                        strcat(temp, "\n"); // fields[0] = "a\n" olarak atandığından rDugum sonuna strcat ile "\n" ekle
                        if(!strcmp(temp, is->fields[0])) {
                            printf("%s,%s", rDugum->key.s, rDugum->val.s);
                            break;
                        }
                        else if(jrb_next(rDugum) == jrb_nil(redBlackTree)) { // En son nodeta olup temp != is->fields[0]
                            printf("Aranan kayit bulunamadi.\n");            // ise ekrana bulamadığını yazdıracak.
                            break;
                        }
                    }
                }
            }
            else if(!strcmp(is->text2, "write")) {
                if(is->NF < 1 || is->NF > 1) {
                    printf("ERROR: 1 adet parametre girmelisiniz.\n");
                }
                else {
                    int length = strlen(is->fields[0]) - 1;
                    memset(temp,0,sizeof(temp));
                    strncpy(temp, is->fields[0], length);
                    fp = fopen(temp, "w+");

                    if(fp == NULL) 
                        printf("ERROR: Dosya okuma/yazma hatası!\n");
                    else {
                        sortedTree = make_jrb();            
                        jrb_traverse(rDugum, redBlackTree) {
                            jrb_insert_gen(sortedTree, rDugum->key, rDugum->val, karsilastir);
                        }
                        jrb_traverse(rDugum, sortedTree) {
                            strcpy(temp, rDugum->key.s);
                            strcat(temp, ",");
                            strcat(temp, rDugum->val.s); // temp içinde örneğin: "07,iPhone,Metal,White" var artık
                            fprintf(fp, "%s", temp);   // açtığımız dosya içerisine 'temp' değerini yaz. 
                        }
                        fclose(fp);
                    }
                }
            }
            else if (!strncmp(is->text2, "print", 5)) {   
                sortedTree = make_jrb();            
                jrb_traverse(rDugum, redBlackTree) {
                   jrb_insert_gen(sortedTree, rDugum->key, rDugum->val, karsilastir);
                }

                jrb_traverse(rDugum, sortedTree) {
                    printf("%s,%s", rDugum->key.s, rDugum->val.s);
                }
            }
            else if(strncmp(is->text2, "quit", 4)){
                    printf("ERROR: Gecersiz komut.\n");
            }

            break;
        }
    }//WHILE() BITISI

    // Temizleme
    jrb_traverse(rDugum, redBlackTree) {
        if(rDugum->flink != NULL)
            free(jval_s(rDugum->key));
    }
    if(sortedTree != NULL) {
        jrb_traverse(rDugum, sortedTree) {
            if(rDugum->flink != NULL)
                free(jval_s(rDugum->key));
        }
    }
    jrb_free_tree(redBlackTree);
    if(sortedTree != NULL) {
        jrb_free_tree(sortedTree);
    }
    jettison_inputstruct(is);
    jettison_inputstruct(wr);

    return 0;
}

int karsilastir(Jval d1, Jval d2) {
    if(atoi(d1.s) > atoi(d2.s)) {
        return 1;
    }
    if(atoi(d1.s) < atoi(d2.s))
        return -1;
    else 
        return 0;
}