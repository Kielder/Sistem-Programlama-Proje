#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 1024

typedef struct {
    int  sipKey;
    char sipAd[100];
    char sipMalzeme[100];
    char sipRenk[100];
} Siparis;

int main(int argc, char *argv[]) {
    char line[BUFFER_LEN];
    
    while(1) {
        printf("> ");
        fflush(stdout);
        fgets(line, BUFFER_LEN, stdin); // Kullanıcıdan komutu al ve line bufferina at.

        int length = strlen(line); // alinan komutun uzunlugu length degiskenine atandı.
        if (line[length - 1] == '\n') { // komutun sonunda '\n' -yeni satır ifadesi- varsa
            line[length - 1] = '\0';  // bunu satır sonu ifadesi olarak değiştir.
        }

        if(strcmp(line, "quit") == 0) { // son satırın '\0' olarak değişmesi strcmp() i düzgün çalıştırır
            // BURADA TEMIZLEME ISLERI YAPILMALI.
            break;
        }

        char *parcala; 
        parcala = strtok(line," |"); // komutu "|" ya da boşluğa göre ayrı stringlere bölmek için
        
        int i = 0;
        while(parcala != NULL) {
            if(!strcmp(parcala,"add") && i == 0) { // sadece ilk parametreye bakmak için i değişkeni
                printf("add tespit edildi!\n");
            }

            parcala = strtok(NULL, " |");
            i++;
        }
    }

    return 0;
}
