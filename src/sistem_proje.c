#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "jval.h"

#define BUFFER_LEN 1024

typedef struct {
    char *sipKey;
    char *sipAd;
    char *sipMalzeme;
    char *sipRenk;
} Siparis;

int main(int argc, char *argv[]) {
    char line[BUFFER_LEN];
    char *tKey, *tAd, *tMalzeme, *tRenk;
    char *params[4] = {tKey, tAd, tMalzeme, tRenk};
    Siparis *sip;
    JRB redBlackTree, rDugum, sortedRB_tree;
    int i;
    
    redBlackTree = make_jrb();
    
    while(1) {
        printf("> ");
        fflush(stdout);
        fgets(line, BUFFER_LEN, stdin); // Kullanıcıdan komutu al ve line bufferina at.

        int length = strlen(line); // alinan komutun uzunlugu length degiskenine atandı.
        if (line[length - 1] == '\n') { // komutun sonunda '\n' -yeni satır ifadesi- varsa
            line[length - 1] = '\0';  // bunu satır sonu ifadesi olarak değiştir.
        }                           // son satırın '\0' olarak değişmesi strcmp() i düzgün çalıştırır
       
        if(strcmp(line, "quit") == 0) {
            break;
        }
        
        i = 0; // kaç adet parametre girildiğini anlamak için
        char *parcala; 
        parcala = strtok(line,"|"); 

        if(!strcmp(parcala, "add")) {
            parcala = strtok(NULL, "|"); // add ten sonraki ilk parametreye geldik.
            
            while(parcala != NULL) {
                params[i] = parcala;
                parcala = strtok(NULL, "|");
                i++;
            }
            
            if(i == 4) { // Dogru miktarda parametre girilmis ise
                rDugum = jrb_find_str(redBlackTree, params[0]); // agac içerisinde eklemek istedigim key varmi

                if(rDugum == NULL) { // böyle bir key ağaçta yoksa yeni node oluşturulmalı
                     sip = (Siparis *) malloc(sizeof(Siparis)); // *** FREE MEMORY ***,
                     sip->sipKey     = params[0];
                     sip->sipAd      = params[1];
                     sip->sipMalzeme = params[2];
                     sip->sipRenk    = params[3];
                     printf("sipKey = %s | sipAd = %s | sipMalzeme = %s | sipRenk = %s\n", sip->sipKey, sip->sipAd, sip->sipMalzeme, sip->sipRenk); // Test
                     jrb_insert_str(redBlackTree, sip->sipKey, new_jval_v(sip));
                }
                else {
                    printf("ERROR: Bu key degeri zaten var!\n");
                }
            }
            else {
                printf("ERROR: add için 4 adet parametre giriniz.\n");
            }
        } // if(add) bitişi
        else if(!strcmp(parcala, "pro")) {
         
        }
        else if(!strcmp(parcala, "search")) {
        
        }
        else if(!strcmp(parcala, "write")) {
        
        }
        else if(!strcmp(parcala, "print")) {
            jrb_traverse(rDugum, redBlackTree) {
        		printf("Print sonucu: %s\n", jval_s(rDugum->key));
        		// printf("%s ", jval_s(rDugum->val));
        	}
        }
        else {
            printf("Gecersiz komut. (add, search, write, print ve quit kullanilabilir.)\n");
        }
    }//WHILE(1) BITISI
    
    jrb_free_tree(redBlackTree);
    //free(sip); // Core dumped hatasına sebep oluyor
    return 0;
}
