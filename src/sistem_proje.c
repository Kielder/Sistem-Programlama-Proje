// #include <stdlib.h>
// #include <stdio.h>
// #include "jrb.h"
// #include "fields.h"

// typedef struct {
// 	char *key;
// 	char *isim;
// 	char *soyad;
// } Kisi;

// int main() {
//     IS is;

// 	JRB agac, ptr;
// 	Kisi *ks;
// 	agac = make_jrb();
// 	ks = (Kisi *) malloc(sizeof(Kisi));
// 	ks->key = "aloha"; ks->isim = "muratcan"; ks->soyad = "yurga";

//     is = new_inputstruct(NULL); // use NULL for stdin
//     while(get_line(is) >= 0) {
//         for (int i = 0; i < is->NF; i++) {
//             //printf("is->fields[i] = %s\n", is->fields[i]);
//             printf("%d: %s\n", is->line, is->fields[i]);
//         }
//     }

// 	//jrb_insert_str(t, strdup(myis->fields[i]), new_jval_v(NULL));
// 	// jrb_insert_str(agac, strdup(ks->key), new_jval_v(ks));
	
// 	// jrb_traverse(ptr, agac) {
// 	// 	ks = (Kisi *) ptr->val.v;
// 	//     printf("key: %s,  isim: %s, soyad: %s\n", jval_s(ptr->key), ks->isim, ks->soyad);
// 	// }
	
// 	free(ks);
// 	return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "jval.h"
#include "fields.h"

#define BUFFER_LEN 1024

typedef struct {
    char *sipKey;
    char *sipAd;
    char *sipMalzeme;
    char *sipRenk;
} Siparis;

int main(int argc, char *argv[]) {
    IS is;
    char line[BUFFER_LEN];
    char params[50];
    Siparis *sip;
    JRB redBlackTree, rDugum, sortedRB_tree;
    
    redBlackTree = make_jrb();
    is = new_inputstruct(NULL); // use NULL for std input
    
    while(strcmp(is->text2, "quit\n")) {
        printf("> ");
        fflush(stdout);
        while(get_line(is) >= 0) {
            if(!strcmp(is->text2, "add")) { 
                if(is->NF < 4 || is->NF > 4) {
                    printf("4 adet parametre girmelisiniz\n");
                }
                else {
                    strcpy(params, "");
                    strcat(params, is->fields[0]);
                    strcat(params, ",");
                    strcat(params, is->fields[1]);
                    strcat(params, ",");
                    strcat(params, is->fields[2]); // jrb_insert_str(redBlackTree, strdup(sip->sipKey), new_jval_v(sip));
                    strcat(params, ",");
                    strcat(params, is->fields[3]);
                    printf("PARAMS: %s\n", params);
                    jrb_insert_str(redBlackTree, strdup(is->text2), new_jval_s(params));
                    // Ağaca eklemede bir sıkıntı yok. Örnek eklenen: add|mc|a|b|c
                    // Çıktı: sipKey: add ve Valuelar: mc,a,b,c
                }
            }
            else if(!strcmp(is->text2, "search")) {
                if(jrb_find_str(redBlackTree, is->fields[0]) != NULL) {
                    printf("Aranan deger bulundu!\n");
                    jrb_traverse(rDugum, redBlackTree) { // İçeriği yazdırabiliyorum fakat birden fazla içerik eklendiği zaman
                        //sip = (Siparis *) rDugum->val.v; // sıkıntılar çıkıyor. sonradan kayboluyor bazı içerikler
                        printf("%s, %s" , rDugum->key.s, rDugum->val.s);
                    }       
                }
            }

            break;
        }
        // jrb_traverse(rDugum, redBlackTree) { // İçeriği yazdırabiliyorum fakat birden fazla içerik eklendiği zaman
        //         //sip = (Siparis *) rDugum->val.v; // sıkıntılar çıkıyor. sonradan kayboluyor bazı içerikler
        //         printf("sipKey: %s ve Value: %s\n" , rDugum->key.s, rDugum->val.s);
        // }
    }//WHILE() BITISI
    
    jrb_free_tree(redBlackTree);
    //free(sip); // Core dumped hatasına sebep oluyor
    return 0;
}