// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include "jrb.h"
// #include "fields.h"

// int main(int argc, char *argv[]) {
//     IS wr;
//     //wr = new_inputstruct("test.txt");

//     FILE *fp;
//     fp = fopen("test.txt", "w+");

//     char buf[50];
//     strcpy(buf, "icerik");

//     if(fp != NULL)
//         fprintf(fp, "Agac dosyaya yazildi!\n");
//     else
//         printf("NULL!\n");

//     fclose(fp);
//     return 0;
// }

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
                        // Ağaca eklemede bir sıkıntı yok. Örnek eklenen: add|mc|a|b|c
                        // Çıktı ----> sipKey: add ve Valuelar: mc,a,b,c
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
                    strncpy(temp, is->fields[0], length); // dosya ismini düzgün şekilde almak için (çalışıyor)
                    fp = fopen(temp, "w+"); // parametre olarak verilen dosyayı yazmak için aç (yoksa oluşturur)

                    printf("Dosya ismi (temp): %s\n", temp);
                    if(fp == NULL) 
                        printf("ERROR: Dosya okuma/yazma hatası!\n");
                    else {
                        jrb_traverse(rDugum, redBlackTree) {
                            strcpy(temp, rDugum->key.s);
                            strcat(temp, ",");
                            strcat(temp, rDugum->val.s); // temp içinde örneğin: "07,iPhone,Metal,White" var artık
                            fprintf(fp, "%s", temp);   // açtığımız dosya içerisine 'temp' değerini yaz.
                            // printf(" temp son hali: %s", temp);
                            //printf("%s,%s" , rDugum->key.s, rDugum->val.s);
                        }
                    }
                }
            }
            else if (!strncmp(is->text2, "print", 5)) { // EKSIK. Key numarasının büyüklüğüne göre sıralanmalı
                sortedTree = make_jrb();
                jrb_traverse(rDugum, redBlackTree) {
                    jrb_insert_gen(sortedTree, rDugum->val, JNULL, karsilastir);
                }

                jrb_rtraverse(rDugum, sortedTree) {
                    //g = (Golfer *) rnode->key.v;
                    printf("key.s: %s ve val.s %s\n", rDugum->key.s, rDugum->val.s);
                    // dll_traverse(rDugum, g->scores) {
                    //     s = (Score *) dnode->val.v;
                    //     printf("  %3d : %s\n", s->score, s->tname);
                    // }
                }
            }
            else if(strncmp(is->text2, "quit", 4)){
                    printf("ERROR: Gecersiz komut.\n");
            }

            break;
        }
        // jrb_traverse(rDugum, redBlackTree) {
        //         printf("%s,%s" , rDugum->key.s, rDugum->val.s);
        // }
    }//WHILE() BITISI

    jrb_free_tree(redBlackTree);
    jettison_inputstruct(is);
    return 0;
}

int karsilastir(Jval d1, Jval d2) {
    if(d1.s < d2.s) 
        return 1;
    if(d1.s > d2.s)
        return -1;
    else 
        return 0;
}