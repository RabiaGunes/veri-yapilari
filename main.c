#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct komsular
{

    int komsu_plaka;
    struct komsular *k_next;


};
typedef struct sehirler
{

    char sehir_adi[20];
    char bolge_adi[5];
    int plaka_kodu;
    int komsu_sayisi;
    struct sehirler *d_next;
    struct sehirler *d_prev;
    struct komsular *komsu;


} BLISTE;



BLISTE  *ilk1=NULL, *son1=NULL;


BLISTE *sehir_ara(char *komsu_adi)
{

    BLISTE *ara=ilk1;

    while(strcmp(ara->sehir_adi,komsu_adi)!=0)
    {

        ara=ara->d_next;
        if(ara==NULL)
            return NULL;


    }

    return ara;



}

void kullanici_komsu_ekle(char *komsu_adi)
{

    BLISTE *ara=sehir_ara(komsu_adi);

    if(ara==NULL)
    {

        int secim;
        printf("komsu olarak eklemek istediginiz sehir yok eklemek ister misiniz?(e:1 h:0)");
        scanf("%d",&secim);

        if(secim==1)
        {
            kullanici_sehir_ekle();
        }

    }
    else if(ara!=NULL)
    {
        printf("---%s---%d--",ara->sehir_adi,ara->plaka_kodu);

        printf("hangi sehire komsuluk eklemek istersiniz");
        char *y_sehir_adi=malloc(sizeof(char)*20);
        scanf("%s",y_sehir_adi);

        BLISTE *liste2=sehir_ara(y_sehir_adi);

        if(liste2!=NULL)
        {

            printf("burdayim");

            struct komsular *yeni=(struct  komsular*) malloc(sizeof(struct  komsular));
            yeni->komsu_plaka=ara->plaka_kodu;

            if(liste2->komsu==NULL)  // liste bos ise
            {

                liste2->komsu=yeni;
                yeni->k_next=NULL;


            }


            else
            {
                printf("burdama2");
                struct  komsular *sira=liste2->komsu;
                struct komsular *sira_once;
                if(yeni->komsu_plaka <= liste2->komsu->komsu_plaka)
                {
                    yeni->k_next=liste2->komsu;
                    liste2->komsu=yeni;

                }
                else
                {
                    int sayi=0;
                    while(sira->komsu_plaka < yeni->komsu_plaka)
                    {
                        sira_once=sira;
                        if(sira->k_next==NULL)
                        {
                            sayi=1;
                            break;
                        }

                        sira=sira->k_next;
                    }
                    if(sayi==1)
                    {
                        sira->k_next=yeni;
                        yeni->k_next=NULL;

                    }
                    else
                    {
                        yeni->k_next=sira;
                        sira_once->k_next=yeni;
                    }
                }



            }
        }
        else
        {
            int secim;
            printf("komsuyu ekleyeceginiz sehir yok eklemek ister misiniz?(e:1 h:0)");
            scanf("%d",&secim);
            if(secim==1)
            {
                kullanici_sehir_ekle();
            }

        }



    }






}



void ekle_sehir(int plaka_kodu, char *sehir_adi, char *bolge_adi, int komsu_sayisi )
{

    BLISTE *sehir = (struct sehirler*) malloc(sizeof(struct sehirler));

    sehir->plaka_kodu=plaka_kodu;
    strcpy(sehir->sehir_adi,sehir_adi);
    strcpy(sehir->bolge_adi,bolge_adi);
    sehir->komsu_sayisi=komsu_sayisi;
    sehir->komsu=NULL;

    if (ilk1 == NULL)
    {
        ilk1 = sehir;
        son1 = sehir;
        ilk1->d_prev = NULL;
        son1->d_next=NULL;


    }
    else
    {
        if(sehir->plaka_kodu < ilk1->plaka_kodu)  // basa ekleme
        {

            sehir->d_next=ilk1;
            ilk1->d_prev=sehir;
            ilk1=sehir;
            ilk1->d_prev=NULL;
        }
        else if(sehir->plaka_kodu > son1->plaka_kodu)  // sona ekleme
        {
            son1->d_next=sehir;
            sehir->d_prev=son1;
            son1=sehir;
            son1->d_next=NULL;

        }
        else  // araya ekleme
        {
            struct sehirler *ara;
            ara=ilk1;

            while(ara->plaka_kodu < sehir->plaka_kodu )
                ara=ara->d_next;


            sehir->d_next=ara;
            sehir->d_prev=ara->d_prev;
            ara->d_prev->d_next=sehir;
            ara->d_prev = sehir;
            /*ara->d_next=sehir;
            sehir->d_prev=ara;
            ara->d_next->d_prev=sehir;*/


        }

    }





}


void Listele()
{
    struct sehirler *liste=ilk1;

    while(liste!=NULL)
    {
        printf("%d,",liste->plaka_kodu);
        printf("%s,",liste->sehir_adi);
        printf("%s,",liste->bolge_adi);
        printf("%d",liste->komsu_sayisi);

        struct komsular *iter = liste->komsu;



        while(iter!=NULL)
        {
            printf(",%d",iter->komsu_plaka);
            if(iter->k_next==NULL)
                break;
            iter=iter->k_next;
        }




        liste=liste->d_next;
        printf("\n");
    }


}

void listeyi_oku()
{

    FILE *fp1;
    char birkelime[100];
    char *c;
    int plaka;
    int komsu_sayisi;
    char *sehir_adi;
    char *bolge_adi;

    fp1 = fopen("sehirler3.txt","r");

    do
    {
        c = fgets(birkelime,100,fp1); /* bir satir okuyalim */

        const char *ayrac = ",";// bosluk, nokta ve virgul, noktali virgul...

        char *kelime = strtok(c, ayrac);
        int sayac=0;


        while (kelime != NULL && sayac<4)
        {
            while(sayac<4 )
            {
                printf("%s\n", kelime);
              printf("sayac:%d\n",sayac);
               if(sayac==0)
                    plaka=atoi(kelime);
               else if(sayac==1)
                    sehir_adi=kelime;
               else if(sayac==2)
                     bolge_adi=kelime;
               else if(sayac==3)
                     komsu_sayisi=atoi(kelime);


                kelime = strtok(NULL, ayrac);
                sayac++;


            }


        }

ekle_sehir(plaka,sehir_adi,bolge_adi,komsu_sayisi);
    } while (c != NULL);



    }


BLISTE *plaka_ara(int aranan)
{

    struct sehirler *ara;
    ara=ilk1;

    while(ara)
    {
        if(aranan==ara->plaka_kodu)
            return ara;
        ara=ara->d_next;
    }
    return NULL;
}

BLISTE *sil_sehir()
{

    int plaka;
    printf("\silmek istediginiz sehrin plakasini giriniz:");
    scanf("%d",&plaka);

    BLISTE *p;

    p=plaka_ara(plaka);

    if(p==NULL)
    {
        printf("\nboyle bir sehir mevcut degil..\n");
        return NULL;
    }


    if(p==ilk1)  //ilk dugum mu
    {
        if(ilk1->d_next!=NULL)  //İLK DUGUM SİLME
        {
            ilk1=p->d_next;
            ilk1->d_prev=NULL;
        }
        else  // sadece bir sehir varsa
        {
            ilk1=NULL;
            son1=NULL;
        }

    }
    else  // ilk dugum degilse
    {

        if(p==son1) // sonda ise
        {
            printf("-----%d\n",p->plaka_kodu);
            son1->d_prev->d_next=NULL;
            printf("****%d",son1->plaka_kodu);
            son1=p->d_prev;
            printf("****%d",son1->plaka_kodu);

        }

        else
        {
            p->d_prev->d_next=p->d_next;
            p->d_next->d_prev=p->d_prev;  //arada ise


        }

    }

    free(p);
    return p;

}

void kullanici_sehir_ekle()
{


    int plaka ;
    printf("eklemek istediginiz sehrin bilgilerini giriniz:\n");
    printf("sehrin plakasi:");
    scanf("%d",&plaka);


    if(plaka_ara(plaka)==NULL)
    {

        int komsu_sayisi;
        char *sehir_adi=malloc(sizeof(char)*20);
        char *bolge_adi=NULL;




        printf("sehrin adi:");
        scanf("%s",sehir_adi);

        bolge_adi =malloc(sizeof(char)*10);

        if(bolge_adi !=NULL)
        {
            printf("sehrin bolgesi:");

            scanf("%s",bolge_adi);
        }

        printf("sehrin komsu sayisi:");
        scanf("%d",&komsu_sayisi);

        ekle_sehir(plaka,sehir_adi,bolge_adi,komsu_sayisi);
    }
    else
    {
        printf("eklemek istediginiz sehir zaten var..\n");
    }
}
int main()
{

    //listeyi_oku();
    int secim;
    do
    {
        printf(" 1:sehir ekleme\n 2:komsuluk ekleme\n 3:sehir silme\n 4:komsu silme\n 5:sehir arama\n 6:bolgeye gore listeleme\n 7:listele\n");
        printf(" 8:kullanici sehir ekle\n 9:kullanici komsu ekle\n  10:dosyadan oku\n");
        printf("lutfen secim yapiniz:(cikis:0)\n");
        scanf("%d",&secim);

        switch(secim)
        {
        case 1 :
            ekle_sehir(8,"adana","ak",5);
            ekle_sehir(5,"van","ma",10);
            ekle_sehir(3,"mersin","sa",7);
            ekle_sehir(2,"kars","ga",15);
            ekle_sehir(7,"izmir","ia",6);
            break;
        case 3 :
            sil_sehir();
            break;
        case 7 :
            Listele();
            break;
        case 8 :
            kullanici_sehir_ekle();
            break;

        case 9 :
            kullanici_komsu_ekle("agri");
            break;

        case 10 :
            listeyi_oku();
            break;

        default:
            printf("yanlis secim yaptiniz..");
            break;
        }

    }
    while(secim!=0);




    return 0;
}
