#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
struct ucusno//ucus noları dizisi icin ve kalkis yeri icin yapi
{
    int ucusnumarasi;
    char kalkisyeri[20];
    char varisyeri[20];
    char kalkiszamani[4];
    int koltukkapasitesi;
    int boskoltuksayisi;
    float baslangic_biletifyati;
    struct ucusno *kakisyeri_sonraki;
    struct biletler *biletler_sonraki;
};
struct biletler//biletler icin yapı
{
    int ucusun;
    char yolcuTC[12];
    float bilet_fiyati;
    struct biletler *biletsonraki;
};
void harf_ayari1(char *kalkis);//harf uyumu
void bilet_silme(struct biletler **bas);//biletler silinir
void kalkis_limitine_gore_listele(struct ucusno *ilk_ptr);//% 50 altindakiler noya gore siralanir
void kalkis_varis_sirali_listele(struct ucusno **ilk,char *yer,char *yer2);//kalkis varis yeri gilen ucus arama
void bilet_listele(struct biletler **bas);//biletler listelenir
int ucus_numarasi_alma();//ucus numarasi alir
int secenek_alma();//secenek yazip alir
void bilet_listesine_ekle(struct biletler **bas,struct biletler *yeni);//bilet listesine ekleme yapar
void kalkis_yerine_gore_ekle(struct ucusno **ilk,struct ucusno *eklenecek);//kalkis yerine gore ekleme yapilir
struct ucusno *kalkis_yerine_gore_cikar(struct ucusno **ilk,struct ucusno *aranan);//kalkis listesinden cikarma yapilir
void kalkis_yerine_gore_listele(struct ucusno **ilk_ptr,char *yer);//kalkis yerine gore listeleme yapilir
void bilet_listesinde_cikar(struct biletler **bas,char *tc);//bilet listesinden bir bilet silme
int bilet_listele_TC_yegore(struct biletler **bas,char *tc );//tc ye gore gore sıralı ucusun bilelerini listeleme ve kazanc durumu gosterir
void baslik();//baslik atar
int main()
{
    struct ucusno *dizi[9000]= {NULL};                                      //gerekli tanimlamalar
    struct ucusno  *hashkalkisyerinegore[26];                                // ""
    struct ucusno *bir_ucus,*bir_kalkis;                                      //""
    struct biletler *biletlistesi=NULL,*bir_dugum;                            //""
    int carpan, secenek,ucus_girilen,hash,i,bilet_sayisi ,bulundu=0;          //""
    char yenikarakter,TC_girilen[12],cevap,kalkis_yeri[20],varis_yeri[20];    //""
    float bilet_fiyatlari,toplam_bilet_fiyati=0,bos_kolutuk_orani;            //""
    for(i=0; i<26; i++)                          //kalkis dugumleri kendini gosterir
    {
        hashkalkisyerinegore[i]=malloc(sizeof(struct ucusno));//dugum olusur
        hashkalkisyerinegore[i]->kakisyeri_sonraki=hashkalkisyerinegore[i];//kendine atatılır
    }
    printf("\t******HAVAYOLU BILET SATIS SISTEMINE HOSGELDINIZ******\n\n");
    do
    {
        secenek = secenek_alma();
        switch(secenek)
        {
        case 1:/*bir ucusun eklenmesi*/
            ucus_girilen=ucus_numarasi_alma();
            if(dizi[ucus_girilen-1000]==NULL)// ilgili noda ucus yok ise
            {
                bir_ucus=malloc(sizeof(struct ucusno));// malloc fonksiyonu ile adres olusturduk
                if(bir_ucus!=NULL)
                {
                    bir_ucus->ucusnumarasi=ucus_girilen;// bilgilerin olusturulmasi
                    printf("\tKalkis yerini giriniz:");
                    fflush(stdin);
                    scanf("%s",bir_ucus->kalkisyeri);
                    harf_ayari1(bir_ucus->kalkisyeri);
                    printf("\tVaris Yerini Giriniz:");
                    fflush(stdin);
                    scanf("%s",bir_ucus->varisyeri);
                    harf_ayari1(bir_ucus->varisyeri);
                    printf("\tkalkis saatini giriniz:");
                    fflush(stdin);
                    scanf("%c%c%c%c%c",&bir_ucus->kalkiszamani[0],&bir_ucus->kalkiszamani[1],&yenikarakter,&bir_ucus->kalkiszamani[2],&bir_ucus->kalkiszamani[3]);
                    printf("\tKoltuk Kapasitesini Giriniz:");
                    scanf("%d",&bir_ucus->koltukkapasitesi);
                    bir_ucus->boskoltuksayisi=bir_ucus->koltukkapasitesi;
                    printf("\tBaslangic bilet fiyatini giriniz:");
                    scanf("%f",&bir_ucus->baslangic_biletifyati);
                    hash=toupper(bir_ucus->kalkisyeri[0])-'A';//indis bulunuyor hashe eklemek icin
                    dizi[ucus_girilen-1000]=bir_ucus;// ucus dizisine ekleniyor adres
                    kalkis_yerine_gore_ekle(&hashkalkisyerinegore[hash],bir_ucus);//kalkis dizisine ekleniyor
                    printf("\tEkleme islemi gerceklesmistir\n");
                    dizi[ucus_girilen-1000]->biletler_sonraki=NULL;// bilet dizinde bilet basini sifir yapiyoruz
                    printf("\t\t Ekleme islemi basari ile gerceklesmistir:)\n\n");
                }
                else
                    printf("Malloc fonksiyonu NULL olusturdu!!\a\n");//malloc null dondururse
            }
            else
                printf("\tZaten bu numaraya ait bir kayit vardir!!!\a\n\n");//ucus zaten var ise uyari

            break;
        case 2:// ucus zaman guncelleme
            ucus_girilen=ucus_numarasi_alma();
            if(dizi[ucus_girilen-1000]!=NULL)//ucus numarasina ait ucus varsa
            {
                bir_ucus=dizi[ucus_girilen-1000];
                hash=toupper(bir_ucus->kalkisyeri[0])-'A';
                bir_kalkis=kalkis_yerine_gore_cikar(&hashkalkisyerinegore[hash],bir_ucus);//listeden ucus cıkarılıyor
                printf("Yeni saati ve zamani ss:dd seklinde giriniz:");//yeni saat alimi
                fflush(stdin);
                scanf("%c%c%c%c%c",&bir_ucus->kalkiszamani[0],&bir_ucus->kalkiszamani[1],&yenikarakter,&bir_ucus->kalkiszamani[2],&bir_ucus->kalkiszamani[3]);
                kalkis_yerine_gore_ekle(&hashkalkisyerinegore[hash],bir_ucus);
                printf("\nGuncelleme islemi basari ile gerceklesmistir:)\n\n");//guncellendi
            }
            else
                printf("\t\tBu numaraya ait bir ucus bulunmamaktadir!!!\a\n\n");//ucus yok mesaji
            break;
        case 3:// bilet satma
            ucus_girilen=ucus_numarasi_alma();
            if(dizi[ucus_girilen-1000]!=NULL)//ucus numarasi var ise
            {
                bilet_sayisi=0;// bilet sayisi sifirladım
                bir_ucus=dizi[ucus_girilen-1000];
                printf("Almak istediginiz bilet sayisini giriniz:");
                scanf("%d",&bilet_sayisi);//bilet adeti alindi
                if(bilet_sayisi>10 ||bir_ucus->boskoltuksayisi<bilet_sayisi)// uygun sayida bilet yok ya da 10 dan fazla bilet almak istemisse
                    printf("Uygun sayida bilet yok veya 10 dan fazla bilet almak istediniz\a\n\n");
                else
                {
                    toplam_bilet_fiyati=bilet_fiyatlari=0;
                    bos_kolutuk_orani=(bir_ucus->boskoltuksayisi)*100/bir_ucus->koltukkapasitesi;//bos koltuk orani bulur
                    carpan=(100-bos_kolutuk_orani)/10;// orana göre carpan hesaplar carpan:int old. tam bolme yapar
                    bilet_fiyatlari=bir_ucus->baslangic_biletifyati*((float)carpan/10+1);//bilet fiyati hesaplama
                    toplam_bilet_fiyati+=bilet_fiyatlari*bilet_sayisi;//toplam fiyat hesaplair
                    printf("1 bilet fiyati: %.2f\n",bilet_fiyatlari);
                    printf("Toplam bilet fiyati: %.2f\n",toplam_bilet_fiyati);
                    printf("Biletleri almak istiyor musunuz?:");
                    fflush(stdin);
                    scanf("%c",&cevap);//cevap alinir
                    if(cevap=='e' || cevap=='E')//cevap evet ise
                    {
                        for(i=0 ; i<bilet_sayisi; i++)// biletler eklenir
                        {
                            bir_dugum=malloc(sizeof(struct biletler));//bilet icin dügüm olusturulur
                            printf("%d. yolcunun TC kimlik Numarasini Giriniz:",i+1);
                            fflush(stdin);
                            scanf("%s",bir_dugum->yolcuTC);// yolcu tc si alinir
                            bir_dugum->bilet_fiyati=bilet_fiyatlari;// bir dügümün bilet fiyatine bilet fiyati eklenir
                            bilet_listesine_ekle(&dizi[ucus_girilen-1000]->biletler_sonraki,bir_dugum);// bilet ekle
                        }
                        bir_ucus->boskoltuksayisi-=bilet_sayisi;//bos koltuk sayisi azaltilir
                        printf("Bilet alma islemi basari ile gerceklesmistir\n\n");// bilet alimi gerceklesti
                    }
                    else
                        printf("Bilet almadiniz\n\n");// bilet almadi
                }
            }
            else
                printf("\t\tBu numaraya ait ucus bulunmamaktadir\a\n\n");//ucus numarasina ait ucus yok
            break;
        case 4:/*bir ucusun iptal edilmesi*/
            ucus_girilen=ucus_numarasi_alma();
            if(dizi[ucus_girilen-1000]!=NULL)//ucus var ise
            {
                bir_ucus=dizi[ucus_girilen-1000];
                hash=toupper(bir_ucus->kalkisyeri[0])-'A';//hash indisi belirleme
                bir_kalkis=kalkis_yerine_gore_cikar(&hashkalkisyerinegore[hash],bir_ucus);//kalkis listesinden cikarma
                if(bir_ucus->boskoltuksayisi!=bir_ucus->koltukkapasitesi)
                {
                    biletlistesi=bir_ucus->biletler_sonraki;
                    bilet_silme(&biletlistesi);//bilet listesinden bütün dügümler silinir
                    printf("Tum Biletler silindi\n");//bütün biletler silinir
                }
                else
                    printf("Bu numaraya ait bilet alinmamistir.\a\n");// bilet alinmamistir
                free(bir_kalkis);//kalkis silinir
                dizi[ucus_girilen-1000]=NULL;//ucus listesinin tutuldugu pointer dizisinde null atanır
            }
            else
                printf("\t\tBu numaraya ait ucus bulunmamaktadir\a\n\n");//ucus yok ise
            break;
        case 5:/*bir ucus icin satilan biletlerin iptal edilmesi*/
            ucus_girilen=ucus_numarasi_alma();
            if(dizi[ucus_girilen-1000]!=NULL)//ucus var ise
            {
                printf("\tYolcunun TC kimlik numarasini giriniz:");
                fflush(stdin);
                scanf("%s",TC_girilen);// TC alinir kullanicidan
                if(dizi[ucus_girilen-1000]->biletler_sonraki!=NULL)// ucus var ise
                {
                    bilet_listesinde_cikar(&dizi[ucus_girilen-1000]->biletler_sonraki,TC_girilen);// bilet listesinden cikartilir
                    dizi[ucus_girilen-1000]->boskoltuksayisi+=1;//bos koltuk sayisi guncellenir
                }
                else
                    printf("\tBu ucus numarasina ait bilet alimi yapilmamistir.\a\n\n");
            }
            else
                printf("\t Bu numaraya ait kayit bulunmamaktadir!!\a\n\n");
            break;
        case 6:/*bir yerden kalkan ucuslarin bilgilerinin listelenmesi*/
            printf("\tUcusun Kalktigi Yeri Giriniz:");
            fflush(stdin);
            scanf("%s",kalkis_yeri);
            harf_ayari1(kalkis_yeri);
            hash=toupper(kalkis_yeri[0])-'A';
            kalkis_yerine_gore_listele(&hashkalkisyerinegore[hash],kalkis_yeri);
            break;
        case 7://bir yerden bir yere olan ucuslarin bilgilerinin listelenmesi
            printf("Ucusun Kalktigi Yeri Giriniz:");
            fflush(stdin);
            scanf("%s",kalkis_yeri);// kalkis aldik
            harf_ayari1(kalkis_yeri);
            printf("Ucusun varis yerini giriniz:");
            fflush(stdin);
            scanf("%s",varis_yeri);// varis aldik
            harf_ayari1(varis_yeri);
            hash=toupper(kalkis_yeri[0])-'A';
            kalkis_varis_sirali_listele(&hashkalkisyerinegore[hash],kalkis_yeri,varis_yeri);// kalkis varis a gore listelendi
            break;
        case 8://bir ucusun bilgilerinin ve o ucusa iliskin biletlerin listelenmesi
            ucus_girilen=ucus_numarasi_alma();
            if(dizi[ucus_girilen-1000]!=NULL)//ucus var ise
            {
                bir_ucus=dizi[ucus_girilen-1000];
                bos_kolutuk_orani=(100-(float)bir_ucus->boskoltuksayisi/bir_ucus->koltukkapasitesi*100);
                baslik();
                printf("%5d %10s  %10s  %6c%c:%c%c  %9d  %9d  %10.2f\n ",bir_ucus->ucusnumarasi,bir_ucus->kalkisyeri,bir_ucus->varisyeri,bir_ucus->kalkiszamani[0],bir_ucus->kalkiszamani[1],bir_ucus->kalkiszamani[2],bir_ucus->kalkiszamani[3],bir_ucus->koltukkapasitesi,bir_ucus->boskoltuksayisi,bos_kolutuk_orani);
                printf("*****************************************************************************\n");
                if(bir_ucus->boskoltuksayisi!=bir_ucus->koltukkapasitesi)//bilet bilgi listesi
                {
                    biletlistesi=dizi[ucus_girilen-1000]->biletler_sonraki;
                    bilet_listele(&biletlistesi);//bilet listeleme fonk cagirma
                }
                else
                    printf("\t Bu ucusa ait bilet bulunmamaktadir\a\n\n");
            }
            else
                printf("\t Bu numarada ucus kaydi bulunmamaktadir!!!\a\n\n");
            break;
        case 9://koltuk doluluk%%50 alti ucus listesi
            baslik();
            for(i=0; i<26; i++)//hash tablosunun tamamı dolasilir
            {
                if(hashkalkisyerinegore[i]->kakisyeri_sonraki!=hashkalkisyerinegore[i])//bu dügümde kayit var ise bir yerşn adresşnş tutuyor ise
                    kalkis_limitine_gore_listele(hashkalkisyerinegore[i]);//limitin altinda olanlar listelenir
            }
            break;
        case 10://Bir yolcunun biletlerinin listesi
            printf("\t\tBiletlerini Gormek Istediginiz\n \t\tTC kimlik Numarasini Giriniz:");
            fflush(stdin);
            scanf("%s",TC_girilen);// TC Kimlik noya gore listeleme
            printf("\t UCUS NO   KALKIS YERI VARIS YERI  ZAMANI  FIYATI \n");
            for(i=0; i<9000; i++)
            {
                if(dizi[i]!=NULL)
                {
                    bir_dugum=dizi[i]->biletler_sonraki;
                    bulundu=bilet_listele_TC_yegore(&bir_dugum,TC_girilen);// butun ucuslarda tc aranır ve listeleme yağilir
                    if(bulundu!=0)//bilet listesi yapilir TC ye gore
                    {
                        printf("\t %6d %10s%13s  %4c%c:%c%c  %4.2fTL\n",dizi[i]->ucusnumarasi,dizi[i]->kalkisyeri,dizi[i]->varisyeri,dizi[i]->kalkiszamani[0],dizi[i]->kalkiszamani[1],dizi[i]->kalkiszamani[2],dizi[i]->kalkiszamani[3],dizi[i]->baslangic_biletifyati);

                    }
                    bulundu=0;
                }
            }
            break;
        }

    }
    while(secenek!=11);
    return 0;
}
int secenek_alma()//secenekler i ekrana yazddirma ve secenek alma fonksiyonu
{
    int secim;
    printf("\t\t******MENU*************\n");
    printf("\t\t1.Yeni Ucusun Eklenmesi\n");
    printf("\t\t2.Bir Ucusun Kalkis Zamaninin Degistirilmesi\n");
    printf("\t\t3.Bir Ucusa Iliskin Bilet Satilmasi\n");
    printf("\t\t4.Bir Ucusun Iptal Edilmesi\n");
    printf("\t\t5.Bir Ucus Icin Satilan Biletlerin Iptal Edilmesi\n");
    printf("\t\t6.Bir Yerden Kalkan Ucuslarin Bilgilerinin Listelenmesi\n");
    printf("\t\t7.Bir Yerden Bir Yere Olan Ucuslarin Bilgilerinin Listelenmesi\n");
    printf("\t\t8.Bir ucusun bilgilerinin ve ucusa iliskin satilan \n\t\tbiletlerin listelennmesi\n");
    printf("\t\t9.Koltuk doluluk orani %%50 nin altinda olan ucuslarin\n\t\t listelenmesi\n");
    printf("\t\t10.Bir yolcunun Biletlerinin listelenmesi\n");
    printf("\t\t11.Cikis \n");
    do
    {
        printf("\t\tSeciminizi giriniz:");//secim alma
        scanf("%d",&secim);
        if(secim>11 || secim <1)// yanlis ise uyari verme
            printf("\t\tYanlis bir secimde bullundunuz 1-11 arasinda olmali!!!\a\n");
    }
    while(secim>11 || secim <1);//yanlis ise hep doner dogru girinceye kadar
    printf("********************************************************************************\n\n");
    return secim;
}
int ucus_numarasi_alma()//ucus numarasi  alma ve dondurme ana fonksiyona
{
    int ucus_numarasi;
    do
    {
        printf("\t\tUcus numarasini giriniz:");
        scanf("%d",&ucus_numarasi);//ucus no alir
        if(ucus_numarasi>9999 || ucus_numarasi<1000)//yanlis ise uyari mesaji verir
            printf("\t\tYanlis giris yaptiniz!!!\a\n");
    }
    while(ucus_numarasi>9999 || ucus_numarasi<1000);//yanlis ise hep doner
    printf("\t\t*****************************************\n\n");
    return ucus_numarasi;//ucus no doner
}
void kalkis_yerine_gore_ekle(struct ucusno **ilk,struct ucusno *eklenecek)//kalkis yerine gore sirali ekler
{
    struct ucusno *onceki,*simdiki,*gecici;
    onceki=(*ilk);//bas in adresi oncekine atanir
    simdiki=(*ilk)->kakisyeri_sonraki;//simdiki ise bas ın sonrakisi dir
    while(simdiki!=*ilk && (strcmp(simdiki->kalkisyeri,eklenecek->kalkisyeri))<0 )//eklenecek icin uygun yer aranir ada gore
    {
        onceki=simdiki;//simdikionceki olur
        simdiki=simdiki->kakisyeri_sonraki;//simdikinin sonrakisi simdiki olur
    }
    if(strcmp(simdiki->kalkisyeri,eklenecek->kalkisyeri)==0)//ayni isimli kalkislerde
    {
        if(strcmp(simdiki->kalkiszamani , eklenecek->kalkiszamani)>0)//zamani kucuk olan one gecer
        {
            onceki->kakisyeri_sonraki = eklenecek;//eklenecek one
            eklenecek->kakisyeri_sonraki = simdiki;//simdiki ise sonraya alınır
        }
        else//zıttı durumda
        {
            gecici=simdiki->kakisyeri_sonraki;
            simdiki->kakisyeri_sonraki=eklenecek;
            eklenecek->kakisyeri_sonraki=gecici;
        }
    }
    if(strcmp(simdiki->kalkisyeri,eklenecek->kalkisyeri)>0)//simdikinin kalkis yeri daha buyuk ise
    {
        onceki->kakisyeri_sonraki=eklenecek;
        eklenecek->kakisyeri_sonraki=simdiki;
    }
    if(simdiki==*ilk)//herhangi bir yere ekleme
    {
        onceki->kakisyeri_sonraki=eklenecek;
        eklenecek->kakisyeri_sonraki=simdiki;
    }
}
struct ucusno *kalkis_yerine_gore_cikar(struct ucusno **ilk,struct ucusno *aranan)//sirali olarak kalkis yerine gore cikarma islemi yapilir
{
    struct ucusno *onceki,*simdiki;//degisken tanimi
    onceki=(*ilk);//
    simdiki=(*ilk)->kakisyeri_sonraki;
    while(simdiki!=*ilk && strcmp(simdiki->kalkiszamani,aranan->kalkiszamani)<0)//ucus arama
    {
        onceki=simdiki;
        simdiki=onceki->kakisyeri_sonraki;
    }
    if(simdiki!=*ilk)//liste bitmeden cikmis ise
    {
        onceki->kakisyeri_sonraki=simdiki->kakisyeri_sonraki;//dugumler yer degistirir
    }
    return simdiki;//ciralir dugun doner fonksiyona
}
void kalkis_yerine_gore_listele(struct ucusno **ilk_ptr,char *yer)//kalkis yerine gore listeme yapilir
{
    struct ucusno *simdiki;
    float doluluk;
    simdiki=(*ilk_ptr)->kakisyeri_sonraki;
    baslik();
    while(simdiki!=*ilk_ptr)//liste sonuna kadar
    {
        if(strcmp(simdiki->kalkisyeri,yer)==0)
        {doluluk=(100-(float)simdiki->boskoltuksayisi/simdiki->koltukkapasitesi*100);
        fflush(stdin);//listeleme yapilir
        printf("%5d %10s  %10s  %6c%c:%c%c  %9d  %9d  %10.2f\n",simdiki->ucusnumarasi,simdiki->kalkisyeri,simdiki->varisyeri,simdiki->kalkiszamani[0],simdiki->kalkiszamani[1],simdiki->kalkiszamani[2],simdiki->kalkiszamani[3],simdiki->koltukkapasitesi,simdiki->boskoltuksayisi,doluluk);
        simdiki=simdiki->kakisyeri_sonraki;
        }
    }
}
void bilet_listesine_ekle(struct biletler **bas,struct biletler *yeni)
{
    struct biletler *simdiki, *onceki;

    if((*bas)==NULL)//en basa eklenecek ise
    {
        yeni->biletsonraki=NULL;
        *bas=yeni;
    }
    else if(atoll(yeni->yolcuTC)<(atoll((*bas)->yolcuTC)))// bir tane dugum var ise
    {
        yeni->biletsonraki=*bas;
        *bas=yeni;
    }
    else//araya eklenecek ise
    {
        onceki=*bas;
        simdiki=(*bas)->biletsonraki;
        while(simdiki!=NULL &&atoll(simdiki->yolcuTC)<atoll(yeni->yolcuTC))//tc ye gore listede uygun yer aranir
        {
            onceki=simdiki;
            simdiki=simdiki->biletsonraki;
        }
        yeni->biletsonraki=simdiki;//dugum adresleri yer degistirir
        onceki->biletsonraki=yeni;// "      "           "  "
    }

}
void bilet_listesinde_cikar(struct biletler **bas,char *tc)// bilet cikarma islemi icin kullanilir
{
    struct biletler *onceki,*simdiki;
    if(*bas==NULL)//bos bilet listesi ise
        printf("\t\tBu Kisi Bilet alinmamistir....\a\n");
    else if(atoll((*bas)->yolcuTC)==atoll(tc))// en basta ise bilet
    {
        simdiki=*bas;
        *bas=(*bas)->biletsonraki;
        free(simdiki);//dugum bosaltılır serbest bırakılır
    }
    else
    {
        onceki=*bas;
        simdiki=(*bas)->biletsonraki;
        while(simdiki!=NULL && atoll(simdiki->yolcuTC)<atoll(tc))//bilet aranir
        {
            onceki=simdiki;
            simdiki=simdiki->biletsonraki;
        }
        if(simdiki!=NULL && atoll(simdiki->yolcuTC)==atoll(tc))//bilet bulup cikti ise
        {
            onceki->biletsonraki=simdiki->biletsonraki;
            free(simdiki);// bu gugum serbest birakilir
        }
        else
            printf("\t\tBu kisiye ait bilet bulunmamaktadir.\n");//bilet yok ise
    }
}
void kalkis_varis_sirali_listele(struct ucusno **ilk,char *yer,char *yer2)// kalkis ve varis yerine gore listeleme yapar
{
    struct ucusno *simdiki;
    float doluluk;
    simdiki=(*ilk)->kakisyeri_sonraki;
    baslik();
    while(simdiki!=*ilk)// bir dairesel bagli liste dolasilir
    {
        if(strcmp(simdiki->kalkisyeri,yer)==0 && strcmp(simdiki->varisyeri,yer2)==0)//uygun kalkis varis bulundu ise yazdirilir
        {
            doluluk=(100-(float)simdiki->boskoltuksayisi/simdiki->koltukkapasitesi*100);
            printf("%5d %10s  %10s  %6c%c:%c%c  %9d  %9d  %10.2f\n",simdiki->ucusnumarasi,simdiki->kalkisyeri,simdiki->varisyeri,simdiki->kalkiszamani[0],simdiki->kalkiszamani[1],simdiki->kalkiszamani[2],simdiki->kalkiszamani[3],simdiki->koltukkapasitesi,simdiki->boskoltuksayisi,doluluk);
        }
        simdiki=simdiki->kakisyeri_sonraki;//ilerleme yapilir
    }
}
void bilet_listele(struct biletler **bas)//bilet listeleme
{
    struct biletler *simdiki;
    float toplam_bilet_fiyati=0,ortalama=0;
    int bilet_say=0;
    simdiki=(*bas);
    printf("  TC KIMLIK     FIYATI\n");
    while(simdiki!=NULL)//bilet listesi dolasilir
    {
        printf(" %10s%10.2f TL\n",simdiki->yolcuTC,simdiki->bilet_fiyati);//bilet listesi yazilir
        bilet_say+=1;
        toplam_bilet_fiyati+=simdiki->bilet_fiyati;
        simdiki=simdiki->biletsonraki;
    }
    ortalama=toplam_bilet_fiyati/bilet_say;
    printf("\t\tToplam bilet fiyati: %.2f\n",toplam_bilet_fiyati);//toplam fiyat
    printf("\t\tToplam bilet sayisi: %d\n",bilet_say);//bilet sayisi
    printf("\t\tOrtalama bilet fiyati: %.2f\n",ortalama);//ortalama
}
int bilet_listele_TC_yegore(struct biletler **bas,char *tc)//bilet listele TC ye gore
{
    struct biletler *simdiki;
    int bulunan=0;
    simdiki=*bas;
    while(simdiki!=NULL)
    {
        if(atoll(simdiki->yolcuTC)==atoll(tc))
        {
            bulunan=1;//bulunca 1 degerini dondurur
            break;
        }
        simdiki=simdiki->biletsonraki;
    }
    return bulunan;//bulmazsa 0 doner bulursa 1 bulunca yazar
}

void kalkis_limitine_gore_listele(struct ucusno *ilk_ptr)//kalkis limitine  gore listeleme yapilir ucus no sirali bir şekilde
{
    struct ucusno *simdiki;
    float doluluk;
    simdiki=ilk_ptr->kakisyeri_sonraki;
    while(simdiki!=ilk_ptr)
    {
        doluluk=100-((float)simdiki->boskoltuksayisi/simdiki->koltukkapasitesi*100);
        if(doluluk<50)//%50 alti siralanir ve yazdirilir
        {
            printf("%5d %10s  %10s  %6c%c:%c%c  %9d  %9d  %10.2f\n",simdiki->ucusnumarasi,simdiki->kalkisyeri,simdiki->varisyeri,simdiki->kalkiszamani[0],simdiki->kalkiszamani[1],simdiki->kalkiszamani[2],simdiki->kalkiszamani[3],simdiki->koltukkapasitesi,simdiki->boskoltuksayisi,doluluk);
        }
        simdiki=simdiki->kakisyeri_sonraki;
    }
}
void bilet_silme(struct biletler **bas)//bütün bilet dugumllerinin iptal edilmesi ucus iptal edildigi taktirde
{
    struct biletler *simdiki,*gecici;
    simdiki=(*bas)->biletsonraki;
    while(simdiki!=NULL)//bilet listesi null oluncaya kadar yapilir
    {
        gecici=simdiki;
        free(gecici);
        simdiki=simdiki->biletsonraki;
    }
}

void harf_ayari1(char *kalkis)//buyuk kucuk haf uyumu
{
    int i;
    char a;
    for(i=0; i<20; i++)
    {
        a=kalkis[i];

        if(&kalkis[i]!=NULL)
        {
            kalkis[i]=toupper(a);//null degilse buyutur
        }
        else
            break;
    }
}
void baslik()//baslik yazma fonksiyonu
{
    printf("UCUS NO  KALKIS YERI   VARIS YERI  ZAMANI   KAPASITE  BOS KOLTUK  DOLULUK\n");
    printf("------  -----------   ---------    ------   --------  ----------  ------- \n");
}
