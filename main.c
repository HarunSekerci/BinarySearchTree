
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct Tree {
    int eleman;
    struct Tree* left, * right;
} Tree;

Tree* root = NULL;

Tree* addData() {
    Tree* buffer;
    buffer = (Tree*) malloc(sizeof (Tree)); //bellek yer tahsisi
    if (buffer == NULL) {
        printf("Bellek dolu..");
        return NULL;
    }
    printf("Elemani giriniz\n");
    scanf("%d", &(buffer->eleman)); //eklenen elemanın gecici degiskene atanması
    //buffer->eleman = value;
    buffer->right = NULL;
    buffer->left = NULL;
    return buffer;
}

void addTree(Tree* buffer) {//gecici degiskenden gelen verinin agaca eklenmesi
    Tree* temp, * parent;
    if (root == NULL) root = buffer; //kok kısmının olup olmadıgının kontrolü
    else {
        temp = root;
        while (temp != NULL) {
            parent = temp;
            if ((buffer->eleman) < (temp->eleman)) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        if ((buffer->eleman) < (parent->eleman)) {
            parent->left = buffer;
        } else {
            parent->right = buffer;
        }
    }
}
int findNum=0; //Aranan sayı
int stepsNum = 1; //Aranan sayının adım sayısını tutan değişken

Tree *dataSeek(Tree *temp) {
    if (findNum == temp->eleman) {
        printf("\nAranan eleman %d.adimda bulundu aranan eleman:%d\n", stepsNum, findNum);
    } else {
        if (findNum < temp->eleman) {//Aranılan sayının agacın solunda olup olmadıgının kontrolü
            stepsNum++;
            if (temp->left != NULL) {
                dataSeek(temp->left); //Aranılan sayı agacın solunda ise fonksiyonun recusive olarak çalışması
            } else {
                printf("Aradiginiz eleman bulunamadi.\n");
            }
        } else {//Aranılan sayının agacın sağında olup olmadığının kontrolü 
            stepsNum++;
            if (temp->right != NULL) {
                dataSeek(temp->right); //Aranılan sayı agacın sagında ise fonksiyonun recusive olarak çalışması
            } else {
                printf("Aradiginiz eleman bulunamadi.\n");
            }
        }
    }
}
int leafTotal = 0; //Yaprakların toplamını tutan değişken
int leafCounter = 0; //Yaprakların sayısını tutan değişken

int getLeafAverage(Tree *buffer) {
    if (buffer == NULL) return 0;
    if (buffer->left == NULL && buffer->right == NULL) {//Solu ve sağı null ise bu bir yapraktır.
        leafTotal += buffer->eleman; //Yaprakların toplanması
        leafCounter++; //Yaprak sayısı
        return 1;
    } else {
        return getLeafAverage(buffer->left) + getLeafAverage(buffer->right); //Sol ve sag kısmın recursıve olarak bulunması

    }
}
int MaksControl = 0; //Büyük değerin varsa yazılıp yazılmadığının kontrolü

void MaksValue(Tree *temp3, int value) {
    if (temp3 != NULL) {
        MaksValue(temp3->left, value); //agacın recusive olarak en kücük elemanın bulunması
        if (value < temp3->eleman) {//sırayla elemanların recusıve olarak kontrol edılmesı
            printf("%d ", temp3->eleman);
            MaksControl = 1;
        }
        MaksValue(temp3->right, value);
    }
}
int rankCounter = 0; //Derece bulma fonksiyonumun kaç adım gittigini tutan sayaç
int rank = 0; //Bulunmak istenilen ağaç seviyesi

void findRank(Tree *ranked) {
    if (ranked != NULL) {
        if (rankCounter != rank) {//adım sayısının girilen dereceye esit olmadıgı zaman calısan kısım, kısaca tum agacı dolastıgım kısım burası
            rankCounter++;
            findRank(ranked->left);
            findRank(ranked->right);
            rankCounter--;
        } else {// adım sayısının girilen dereceye esıt olan tum elemanların yazılması
            printf("%d ", ranked->eleman);
        }
    }
}

int main(int argc, char** argv) {
    int choosing = 0, num;
    // Example data sets
    /*int data[13];
    memset(data, 0, sizeof (data));
    data[0] = 105;
    data[1] = 87;
    data[2] = 126;
    data[3] = 74;
    data[4] = 95;
    data[5] = 117;
    data[6] = 132;
    data[7] = 45;
    data[8] = 80;
    data[9] = 90;
    data[10] = 100;
    for (int i = 0; i < 11; i++) {
        addTree(addData(data[i]));
    }*/
    while (1) {
        printf("**************************************\n");
        printf("* Veri Ekleme             ---> [1]   *\n");
        printf("* Dereceli eleman bulma   ---> [2]   *\n");
        printf("* Girilen degeri arama    ---> [3]   *\n");
        printf("* Yapraklarin ortalamasi  ---> [4]   *\n");
        printf("* Daha buyuk eleman bulma ---> [5]   *\n");
        printf("* Cikis                   ---> [6]   *\n");
        printf("**************************************\n");
        scanf("%d", &choosing);
        system("CLS");
        switch (choosing) {
            case 1:
                addTree(addData());
                printf("Ekleme islemi basarili\n");
                break;
            case 2:
                printf("Yazdirmak istediginiz agac seviyesini giriniz:");
                scanf("%d", &rank);
                findRank(root);
                printf("\n");
                break;
            case 3:
                printf("Aramak istediginiz sayiyi giriniz\n");
                scanf("%d", &findNum);
                dataSeek(root);
                printf("\n");
                break;
            case 4:
                getLeafAverage(root);
                printf("Yaprak dugum ortalamasi:%d\n", (leafTotal / leafCounter));
                break;
            case 5:
                printf("Hangi sayidan buyuk degerleri gormek istiyorsunuz\n");
                scanf("%d", &num);
                printf("%d sayisindan buyuk degerler --> ", num);
                MaksValue(root, num);
                if (MaksControl == 0) printf("Daha buyuk deger bulunamadi...\n");
                printf("\n");
                break;
            case 6:
                exit(1);
                break;
        }
    }
}
