#include <stdio.h>
#include <stdlib.h>
//10.05.2013//1.sinif 2.donem  2.proje..(sonunda bitti oh be....)
struct ogrenci//ogrenci bilgilerini tutan struct ....
{
    int ogr_no;
    char ad_soyad[30];
    int sinif;
    int kredi;
    float not_ort;
    struct ogrenci *sonraki;
};
struct notlar//ogrencinin notlarini tutan struct....
{
    int ogr_no;
    int notu;
    struct notlar *noya_gore_sonraki;
    struct notlar *nota_gore_sonraki;
    struct notlar *nota_gore_onceki;
};
struct ders// bir dersin bilgilerini tutan struct....
{
    int ders_kodu;
    char ders_adi[25];
    int kredi;
    int ogr_sayisi;
    float not_ort;
    struct notlar *not_bilgisi;
};
int menu_secim();
int ders_kodu_al();
int ogr_no_al();
int hashing(int no);
struct ogrenci *ara(struct ogrenci *, int );
void ogrenci_sirali_ekle(struct ogrenci **, struct ogrenci *);
int ders_kodu_belirle(struct ders *[],int );
void ogr_nota_gore_ekle(struct notlar *,struct notlar *);
void ogr_noya_gore_ekle(struct notlar *,struct notlar *);
struct ders *koda_gore_ara(struct ders *[], int ,int );
void tasi(struct notlar *,struct notlar *);
void ders_bilgileri_goruntule(struct ders *[]);
struct ogrenci * sinifa_gore_listele(struct ogrenci *[], int ,int );
struct notlar * notlar_listesinden_noya_gore_cikar(struct notlar *,int,struct ders * );
struct notlar * notlar_listesinden_nota_gore_cikar(struct notlar *,int,struct ders *);
struct notlar *ders_icinde_ogr_arama(struct notlar *,int);
struct notlar *ders_kodsuz_ogr_no_ara(struct notlar *, int );
struct ogrenci * ogrenci_listesinden_cikar(struct ogrenci *,int );
void not_guncelle(struct ogrenci *,struct ders *,int ,int );
int main()
{
    int i,secenek,a,kod,donem,ders_kodu,ogr_no,kod_2,yeni_not,not_baraji,sinif,ogr_say=0,altmis_say=0,sayac=0,sayac_sinir_alti=0;
    float not_ortalama,toplam=0,yuzde;
    struct ogrenci *ogrenciler[100], *bir_ogrenci,*gecici,*bir_ogr;
    struct ders *dersler[89], *bir_ders;
    struct notlar *bir_not,*liste_dugumu,*gecici_ogr,*bir_no,*not_bir;
    char devam;
    for(i=0; i<100; i++)// hash fonkisyonuna gore cakisan ogr nolar icin olusturulan ogrenci tablosu...
    {
        ogrenciler[i]=NULL;
    }
    for(i=0; i<89; i++)//derslerin bilgisinin tutuldugu isaretci dersler dizisi....
    {
        dersler[i]=NULL;
    }
    do
    {
        secenek=menu_secim();
        switch(secenek)
        {
        case 1:
            bir_ogrenci=malloc(sizeof(struct ogrenci));//yeni bir ogrenci olusturulacagi icin malloc la hafizada yer ayirtildi...
            if(bir_ogrenci)
            {
                a=ogr_no_al();
                kod=hashing(a);
                if(ara(ogrenciler[kod],a)==NULL)//girilen no da ogrenci olup olmadigi kontrol edildi....
                {
                    bir_ogrenci->ogr_no=a;
                    printf("ogrencinin adini ve soyadini giriniz:\n");
                    fflush(stdin);
                    gets(bir_ogrenci->ad_soyad);
                    printf("ogrencinin sinifi:\n");
                    scanf("%d",&bir_ogrenci->sinif);
                    bir_ogrenci->kredi=0;
                    bir_ogrenci->not_ort=0.00;
                    ogrenci_sirali_ekle(&ogrenciler[kod],bir_ogrenci);//ogrenci ogrenciler dizisinde olusturulan tek baðli listeye eklendi...
                }
                else
                    printf("bu ogrenci zaten var!\n");
            }
            else
                printf("hafizada yer yok!!!\n");
            break;
        case 2:
            bir_ders=malloc(sizeof(struct ders));//yeni bir ders eklenecegi icin malloc la hafizada yer ayirtildi...
            if(bir_ders)
            {
                do
                {
                    printf("dersin verildigi donem:\n ");
                    scanf("%d",&donem);
                }
                while(donem<1 ||donem>8);
                ders_kodu=ders_kodu_belirle(dersler,donem);
                bir_ders->ders_kodu=ders_kodu;
                if(bir_ders->ders_kodu!=0)
                {
                    printf("ders kodu:%d\n",bir_ders->ders_kodu);
                    printf("dersin adini giriniz:\n");
                    fflush(stdin);
                    gets(bir_ders->ders_adi);
                    printf("dersin kredisini giriniz:\n");
                    scanf("%d",&bir_ders->kredi);
                    bir_ders->ogr_sayisi=0;
                    bir_ders->not_ort=0.00;
//                    if(dersler[ders_kodu-1]!=NULL)//eger daha once o kodda ders eklenmemiþse...
//                        printf("%d\n",dersler[ders_kodu-1]->ders_kodu);
                    bir_ders->not_bilgisi=malloc(sizeof(struct notlar));
                    bir_ders->not_bilgisi->notu=-1;
                    bir_ders->not_bilgisi->ogr_no=-1;
                    bir_ders->not_bilgisi->noya_gore_sonraki=bir_ders->not_bilgisi;//ogrencinin not bilgisini ders dügümüne baglayan baglar ayarlanir...
                    bir_ders->not_bilgisi->nota_gore_onceki=bir_ders->not_bilgisi;
                    bir_ders->not_bilgisi->nota_gore_sonraki=bir_ders->not_bilgisi;
                    dersler[bir_ders->ders_kodu-1]=bir_ders;
                    printf("ekleme islemi basari ile tamamlandi...\n");
                }
                else
                    printf("bu donem verilmesi gereken dersler zaten var\n");
            }
            else
                printf("hafizada yeteri kadar yer yok!\n");
            break;
        case 3:
            ders_kodu=ders_kodu_al();
            kod=ders_kodu/10;
            if(koda_gore_ara(dersler,ders_kodu,kod)!=NULL)
            {
                bir_ders=koda_gore_ara(dersler,ders_kodu,kod);
                do
                {
                    ogr_no=ogr_no_al();
                    kod_2=hashing(ogr_no);
                    bir_ogrenci=ara(ogrenciler[kod_2],ogr_no);
                    if(bir_ogrenci!=NULL)//oyle bir ogrencinin olup olmadigi arastirilir...
                    {
                        liste_dugumu=dersler[ders_kodu-1]->not_bilgisi;
                        bir_no=NULL;
                        bir_no=ders_icinde_ogr_arama(liste_dugumu,ogr_no);//varsa daha once o dersi alip almadigi arastirilir...
                        if(bir_no==NULL)
                        {
                            bir_not=malloc(sizeof(struct notlar));
                            bir_not->ogr_no=ogr_no;
                            if(bir_not)
                            {
                                printf("ogrencinin notunu giriniz:\n");
                                scanf("%d",&bir_not->notu);
                                yeni_not=bir_not->notu;
                                not_guncelle(ogrenciler[kod_2],bir_ders,yeni_not,ogr_no);//ogrencinin notu guncellenir..
                                bir_ogrenci->kredi=bir_ogrenci->kredi+bir_ders->kredi;
                                ogr_noya_gore_ekle(bir_not,liste_dugumu);
                                ogr_nota_gore_ekle(bir_not,liste_dugumu);
                                dersler[ders_kodu-1]->ogr_sayisi++;//o dersi alan ogrenci sayisi artirilir...
                                printf("ekleme islemi basariyla tamamlandi...\n");
                            }
                        }
                        else
                            printf("bu ogrenci zaten bu dersi aliyor\n");
                    }
                    else
                        printf("boyle bir ogrenci yok\n");
                    printf("Baska bir ogrenci var mi?\n");
                    fflush(stdin);
                    devam=getchar();
                }
                while(devam =='E' || devam=='e');// o derse eklenecek baska ogrencinin olup olmadigini sorgular...
            }
            else
                printf("boyle bir ders yok ki\n");
            break;
        case 4:
            ders_kodu=ders_kodu_al();
            kod=ders_kodu/10;
            if(koda_gore_ara(dersler,ders_kodu,kod)!=NULL)
            {
                ogr_no=ogr_no_al();
                kod_2=hashing(ogr_no);
                liste_dugumu=dersler[ders_kodu-1]->not_bilgisi;
                bir_not=ders_icinde_ogr_arama(liste_dugumu,ogr_no);
                if(bir_not!=NULL)
                {
                    printf("ogrencinin notunu giriniz:\n");
                    scanf("%d",&bir_not->notu);
                    yeni_not=bir_not->notu;
                    not_guncelle(ogrenciler[kod_2],bir_ders,yeni_not,ogr_no);
                    tasi(bir_not,liste_dugumu);//ogrenci yeni notuna gore listelerde uygun yere tasinir...
                    printf("guncelleme islemi basari ile tamamlanmistir...\n");
                }
                else printf("%d kodlu dersi %d nolu ogrenci almiyor ki!\n",ders_kodu,ogr_no);
            }
            else
                printf("boyle bir ders yok!\n");
            break;
        case 5:
            ogr_no=ogr_no_al();
            kod=hashing(ogr_no);
            bir_ogrenci=ara(ogrenciler[kod],ogr_no);
            if(bir_ogrenci==NULL)
                printf("Bu ogrenci bulunmamaktadir\n");
            else
            {
                bir_ogrenci=ogrenci_listesinden_cikar(ogrenciler[kod],ogr_no);//silinecek olan ogrenciyi ogrenci listesinden cikarir...
               // if(bir_ogrenci!=NULL)
                //{free(bir_ogrenci);}
                for(i=9; i<89; i++)
                {
                    if(dersler[i]!=NULL)
                    {
                        bir_ders=dersler[i];
                        liste_dugumu=bir_ders->not_bilgisi;
                        bir_not=notlar_listesinden_noya_gore_cikar(liste_dugumu,ogr_no,bir_ders);//silinecek olan ogrenciyi notlar listesinden nosuna gore çýkarir...
                        not_bir=notlar_listesinden_nota_gore_cikar(liste_dugumu,ogr_no,bir_ders);//silinecek olan ogrenciyi notlar listesinden notuna gore cikarir...
                    if(not_bir!=NULL && bir_not!=NULL)
                    {free(not_bir);
                    free(bir_not);
                    }}
                }
                printf("Silme isleminiz basariyla gerceklesmistir...\n");
            }
            break;
        case 6:
            ders_kodu=ders_kodu_al();
            kod=ders_kodu/10;
            if(koda_gore_ara(dersler,ders_kodu,kod)!=NULL)
            {
                bir_ders=koda_gore_ara(dersler,ders_kodu,kod);
                printf("Ders Kodu    Ders Adi    Kredi   Ogrenci Say   Not Ort\n");
                printf("----------  ----------- -------  -----------  ---------\n");
                printf("%d%12s%14d%9d        %.2f\n",bir_ders->ders_kodu,bir_ders->ders_adi,bir_ders->kredi,bir_ders->ogr_sayisi,bir_ders->not_ort);
                printf("Dersi  Alan  Ogrenciler:\n");
                printf("Ogr No   Ad Soyad    Sinif   Notu\n");
                printf("-------  ---------   ------  -------\n");
                if(dersler[ders_kodu-1]!=NULL)
                {
                    liste_dugumu=dersler[ders_kodu-1]->not_bilgisi;
                    gecici_ogr=liste_dugumu->nota_gore_sonraki;
                    while(gecici_ogr!=liste_dugumu)//o dersi alan ogrencileri listeler....
                    {
                        ogr_no=gecici_ogr->ogr_no;
                        kod=hashing(ogr_no);
                        bir_ogrenci=ara(ogrenciler[kod],ogr_no);
                        if(bir_ogrenci!=NULL)
                        {
                            printf("%d%12s%11d%10d\n\n",bir_ogrenci->ogr_no,bir_ogrenci->ad_soyad,bir_ogrenci->sinif,gecici_ogr->notu);
                        }
                        gecici_ogr=gecici_ogr->nota_gore_sonraki;
                    }
                }
            }
            else
                printf("boyle bir ders yok ki\n");
            break;
        case 7:
            sayac_sinir_alti=0,yuzde=0.00;//kullanici her case 7 ye girdiginde dogru sonuclar alabilmesi icin sayaclar buradada sifirlandi...
            ders_kodu=ders_kodu_al();
            kod=ders_kodu/10;
            sayac_sinir_alti=0;
            if(koda_gore_ara(dersler,ders_kodu,kod)!=NULL)
            {
                bir_ders=koda_gore_ara(dersler,ders_kodu,kod);
                printf("Gormek istediginiz not barajini giriniz:\n");
                scanf("%d",&not_baraji);
                printf("Notu yuksek olan ogrenciler:\n");
                printf("Ogr No    Ad Soyad      Sinif    Notu\n");
                printf("-------  ------------  ------- --------\n ");
                 liste_dugumu=dersler[ders_kodu-1]->not_bilgisi;
                bir_not=liste_dugumu->nota_gore_onceki;
                while(bir_not!=liste_dugumu &&  bir_not->notu >not_baraji)//notu barajin ustunde kalan ogrencileri listeler...
                {
                    bir_ogrenci->ogr_no=bir_not->ogr_no;
                    kod=hashing(bir_ogrenci->ogr_no);
                    bir_ogr=ara(ogrenciler[kod],bir_ogrenci->ogr_no);
                    if(bir_ogr!=NULL)
                    {
                        printf("%d%12s%11d%12d\n",bir_ogr->ogr_no,bir_ogr->ad_soyad,bir_ogr->sinif,bir_not->notu);
                        sayac_sinir_alti++;
                    }
                    bir_not=bir_not->nota_gore_onceki;
                }
                yuzde=(float)(sayac_sinir_alti*100)/bir_ders->ogr_sayisi;
                printf("notu %d nin ustunde olan ogrenci sayisi ve yuzdesi:%d ,%.2f\n",not_baraji,sayac_sinir_alti,yuzde);
            }
            else
                printf("Bu donem ders bulunmamaktadir!\n");
            break;
        case 8:
            sayac=0,sayac_sinir_alti=0,yuzde=0.00;//kullanici her case 8ye girdiginde dogru sonuclar alabilmesi icin sayaclar buradada sifirlandi...
            ders_kodu=ders_kodu_al();
            kod=ders_kodu/10;
            bir_ders=koda_gore_ara(dersler,ders_kodu,kod);
            sayac_sinir_alti=0;
            if(bir_ders!=NULL)
            {
                printf("Gormek istediginiz not barajini giriniz:\n");
                scanf("%d",&not_baraji);
                liste_dugumu=dersler[ders_kodu-1]->not_bilgisi;
                bir_not=liste_dugumu->nota_gore_sonraki;
                printf("Notu dusuk olan ogrenciler:\n");
                printf("Ogr No    Ad Soyad      Sinif    Notu\n");
                printf("-------  ------------  ------- --------\n ");
                while(bir_not!=liste_dugumu &&  bir_not->notu <not_baraji)//notu barajin altinda olan ogrencileri listeler...
                {
                    bir_ogrenci->ogr_no=bir_not->ogr_no;
                    kod=hashing(bir_ogrenci->ogr_no);
                    bir_ogr=ara(ogrenciler[kod],bir_ogrenci->ogr_no);
                    if(bir_ogr!=NULL)
                    {
                        printf("%d%12s%11d%12d\n",bir_ogr->ogr_no,bir_ogr->ad_soyad,bir_ogr->sinif,bir_not->notu);
                        sayac_sinir_alti++;
                    }
                    bir_not=bir_not->nota_gore_sonraki;
                }
                yuzde=(float)(sayac_sinir_alti*100)/bir_ders->ogr_sayisi;
                printf("notu %d nin altinda olan ogrenci sayisi ve yuzdesi:%d ,%.2f\n",not_baraji,sayac_sinir_alti,yuzde);
            }
            else
                printf("Bu donem ders bulunmamaktadir!\n");
            break;
        case 9://kodu girilen dersin bilgilerini goruntuler....
            ders_bilgileri_goruntule(dersler);
            break;
        case 10:
            ogr_no=ogr_no_al();
            kod=hashing(ogr_no);
            bir_ogrenci=ara(ogrenciler[kod],ogr_no);
            if(bir_ogrenci)//nosu girilen ogrenci varsa bilgileri goruntulenir....
            {
                printf("ogr no   ad soyad     sinif    kredi say    not ort   \n");
                printf("  ------   --------    -----    ----------   -------\n");
                printf("%d%12s%11d%12d      %.2f\n",bir_ogrenci->ogr_no,bir_ogrenci->ad_soyad,bir_ogrenci->sinif,bir_ogrenci->kredi,bir_ogrenci->not_ort);
            }
            else
                printf("boyle bir ogrenci yok ki!\n");
            break;
        case 11://bir ogrencinin bilgilerini ve aldigi desleri gorüntüler...
            ogr_no=ogr_no_al();
            kod=hashing(ogr_no);
            bir_ogrenci=ara(ogrenciler[kod],ogr_no);
            if(bir_ogrenci==NULL)
                printf("Bu numarada ogrenci bulunmamaktadir!!!\n");
            else
            {
                printf("ogr no   ad soyad     sinif    kredi say    not ort   \n");
                printf("------- ----------   -------  ----------   ---------\n");
                printf("%-4d    %-15s   %-4d    %-4d   %.2f\n",bir_ogrenci->ogr_no,bir_ogrenci->ad_soyad,bir_ogrenci->sinif,bir_ogrenci->kredi,bir_ogrenci->not_ort);
                printf("Aldigi  Dersler:\n");
                printf("Ders Kodu    Ders Adi     Kredi   Notu\n");
                printf("----------  ----------  --------  ------\n");
                for(i=9; i<89; i++)
                {
                    if(dersler[i]!=NULL)
                    {
                        liste_dugumu=dersler[i]->not_bilgisi;

                        bir_not=ders_icinde_ogr_arama(liste_dugumu,ogr_no);
                        if(bir_not!=NULL)
                            printf("%d%12s%14d%10d\n",dersler[i]->ders_kodu,dersler[i]->ders_adi,dersler[i]->kredi,bir_not->notu);
                    }
                }
            }
            break;
        case 12://girilen siniftaki ogrencileri goruntuler....
            printf("Gormek istediginiz ogrencilerin sinifini giriniz\n");
            scanf("%d",&sinif);
            printf("ogr no   ad soyad     sinif    kredi say    not ort   \n");
            printf("  ------   --------    -----    ----------   -------\n");
            ogr_say=0,altmis_say=0,not_ortalama=0.00,toplam=0;
            for(i=0; i<100; i++)
            {
                gecici=ogrenciler[i];
                while (gecici!=NULL)
                {
                    if (gecici->sinif==sinif)
                    {
                        printf("%d        %s             %d      %d      %.2f\n",gecici->ogr_no,gecici->ad_soyad,gecici->sinif,gecici->kredi,gecici->not_ort);
                        ogr_say++;
                        toplam=gecici->not_ort+toplam;
                        if(gecici->not_ort<60)
                        {
                            altmis_say++;
                        }
                    }
                    gecici=gecici->sonraki;
}
            }
            not_ortalama=(float)(toplam/ogr_say);
            printf("Sinifin ogrenci sayisi:%d\n",ogr_say);
            printf("Sinifin genel not ortalamasi:%.2f\n",(float)not_ortalama);
            printf("Donemlik agirlik not ortalamasi 60'in altinda olan ogrenci sayisi :%d\n",altmis_say);
            printf("Donemlik agirlik not ortalamasi 60'in altinda olan ogrenci yuzdesi: %.2f\n",(float)(altmis_say*100)/ogr_say);
            break;
        }
    }
    while(secenek!=13);
    return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------
int menu_secim()
{
    int secim;
    printf("-------OGRENCI TAKIP SISTEMI-2---------------------\n");
    printf("1-yeni bir ogrencinin eklenmesi\n");
    printf("2-yeni bir dersin eklenmesi\n");
    printf("3-bir dersi alan ogrencinin notlarinin eklenmesi\n");
    printf("4-bir dersi alan ogrencinin notlarinin guncellenmesi\n");
    printf("5-bir ogrencinin silinmesi\n");
    printf("6-bir dersin bilgileri ve dersi alan ogrencilerin listelenmesi\n");
    printf("7-bir dersi alan ogrencilerden notu belirli bir notun ustunde olan ogrencilerin listelenmesi\n");
    printf("8-bir dersi alan ogrencilerden notu belirli bir notun altinda olan ogrencilerin listelenmesi\n");
    printf("9-bir donemin derslerinin listelenmesi\n");
    printf("10-bir ogrencinin bilgilerinin listelienmesi\n");
    printf("11-bir ogrencinin bilgilerinin ve aldigi derslerin listelenmesi\n");
    printf("12-bir sinifta okuyan ogrencilerin listelenmesi\n");
    printf("13-cikis\n");
    do
    {
        printf("seciminizi giriniz:\n");
        scanf("%d",&secim);
    }
    while(secim<1 || secim>13);
    return secim;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
int hashing(int no)//ogrenciler dizisine ogrenici no ile eriþebilmek için uygulanan hash yontemi
{
    int sayi;
    sayi=(no-1)/100;
    return sayi;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void ogrenci_sirali_ekle(struct ogrenci **ilk, struct ogrenci *yeni)//ogr_no ya gore artan sýra ile tek bagli listeye ekleyen fonksiyon
{
    struct ogrenci *onceki, *gecici;
    if(*ilk==NULL)//liste bossa....
    {
        yeni->sonraki=NULL;
        *ilk=yeni;
    }
    else if((*ilk)->ogr_no>yeni->ogr_no)//en basa ekleniyorsa...
    {
        yeni->sonraki=*ilk;
        *ilk=yeni;
    }
    else // siraya göre uygun yere ekleyecek...
    {
        onceki=*ilk;
        gecici=(*ilk)->sonraki;
        while(gecici!=NULL && gecici->ogr_no<yeni->ogr_no)
        {
            onceki=gecici;
            gecici=gecici->sonraki;
        }
        yeni->sonraki=gecici;
        onceki->sonraki=yeni;
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------
struct ogrenci *ara(struct ogrenci *ilk, int aranan)//hashing fonksiyonuna gore olusturulan ogrenciler dizisinde ogrenci arar....
{
    while(ilk!=NULL  &&  aranan>ilk->ogr_no)
    {
        ilk=ilk->sonraki;
    }
    if((ilk==NULL)  ||  (aranan<ilk->ogr_no))
        return NULL;
    else return ilk;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
int ders_kodu_belirle(struct ders *dersler[89],int donem)//eklenecek olan yeni dersin kodunu belirleyen fonksiyon.....
{
    int kod,i;
    for(i=(donem*10)-1; i<=(donem*10)+8; i++)
    {
        if(dersler[i]==NULL)
        {
            kod=i+1;
            break;
            return kod;
        }
        else kod=0;
    }
    return kod;
}
//---------------------------------------------------------------------------------------------------------------------------------------
struct ders *koda_gore_ara(struct ders *dersler[89], int aranan,int kod)//ders kodunu alir ve dersler dizisinde dersin olup olmadigina bakar
{
    int a=kod*10;
    while(dersler[a-1]!=NULL && dersler[a-1]->ders_kodu<=aranan)
    {
        if (dersler[a-1]->ders_kodu==aranan) return dersler[a-1];
        a++;
    }
    return NULL;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void ogr_noya_gore_ekle(struct notlar *bir_not,struct notlar *listebasi) //ogrencileri nolarina gore dairesel tek baðli liste ile dersler isaretci dizisine ekleyen fonksiyon
{
    struct notlar *onceki;
    struct notlar *gecici;
    onceki=listebasi;
    gecici=listebasi->noya_gore_sonraki;

        while(gecici!=listebasi && gecici->ogr_no<bir_not->ogr_no)
        {
            onceki=gecici;
            gecici=gecici->noya_gore_sonraki;
        }
        bir_not->noya_gore_sonraki=gecici;
        onceki->noya_gore_sonraki=bir_not;
    }

//-------------------------------------------------------------------------------------------------------------------------------------------
void ogr_nota_gore_ekle(struct notlar *bir_not,struct notlar *listebasi)//ogrencileri notlarina gore dairesel cift baðli liste ile dersler isaretci dizisine ekleyen fonksiyon
{
    struct notlar *gecici;
    gecici=listebasi->nota_gore_sonraki;
    while (gecici!=listebasi && gecici->notu<bir_not->notu)
    {
        gecici=gecici->nota_gore_sonraki;
    }
    bir_not->nota_gore_onceki=gecici->nota_gore_onceki;
    bir_not->nota_gore_sonraki=gecici;
    gecici->nota_gore_onceki->nota_gore_sonraki=bir_not;
    gecici->nota_gore_onceki=bir_not;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void tasi(struct notlar *bir_not,struct notlar *listebasi)//notu güncellenen ogrenciyi yeni notuna gore listenin uygun yerine tasir....
{
    if(bir_not->nota_gore_onceki!=listebasi && bir_not->nota_gore_onceki->notu>bir_not->notu)
    {
        struct notlar *gecici=bir_not->nota_gore_onceki;
        while(gecici!=listebasi &&gecici->notu>bir_not->notu)
        {
            gecici=gecici->nota_gore_onceki;
        }
        bir_not->nota_gore_onceki->nota_gore_sonraki=bir_not->nota_gore_sonraki;
        bir_not->nota_gore_sonraki->nota_gore_onceki=bir_not->nota_gore_onceki;
        bir_not->nota_gore_sonraki=gecici->nota_gore_sonraki;
        bir_not->nota_gore_onceki=gecici;
        gecici->nota_gore_sonraki->nota_gore_onceki=bir_not;
        gecici->nota_gore_sonraki=bir_not;
    }
    if(bir_not->nota_gore_sonraki!=listebasi && bir_not->notu>bir_not->nota_gore_sonraki->notu)
    {
        struct notlar *gecici=bir_not->nota_gore_sonraki;
        while(gecici!=listebasi&& gecici->notu<bir_not->notu)
        {
            gecici=gecici->nota_gore_sonraki;
        }
        bir_not->nota_gore_onceki->nota_gore_sonraki=bir_not->nota_gore_sonraki;
        bir_not->nota_gore_sonraki->nota_gore_onceki=bir_not->nota_gore_onceki;
        bir_not->nota_gore_onceki=gecici->nota_gore_onceki;
        bir_not->nota_gore_sonraki=gecici;
        gecici->nota_gore_onceki->nota_gore_sonraki=bir_not;
        gecici->nota_gore_onceki=bir_not;
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------
void ders_bilgileri_goruntule(struct ders *dersler[89])//dersler isaretci dizisinde istenilen donemde verilen derslerin bilgilerini goruntüler.....
{
    int donem,i,toplam_kredi=0;
    do
    {
        printf("derslerini gormek istediginiz donemi giriniz:\n");
        scanf("%d",&donem);
    }
    while(donem<1 || donem>8);
    printf("Ders Kodu   Ders adi    Kredi     Ogrenci sayisi   Not ort\n ");
    printf("---------   --------    -----     --------------   --------\n");
    for(i=(donem*10)-1; i<(donem*10)+8; i++)
    {
        if(dersler[i]!=NULL)
        {
            printf("%d      %10s  %9d     %7d         %.2f\n",dersler[i]->ders_kodu,dersler[i]->ders_adi,dersler[i]->kredi,dersler[i]->ogr_sayisi,dersler[i]->not_ort);
            toplam_kredi=dersler[i]->kredi+toplam_kredi;
        }
    }
    printf("toplam kredi:%d\n",toplam_kredi);
}
//-------------------------------------------------------------------------------------------------------------------------------------------
struct ogrenci *sinifa_gore_listele(struct ogrenci *ogrenciler[100], int aranan_sinif,int i)//girilen siniftaki ogrencileri ogrenciler dizisinde arar ve bilgilerini gorüntüler...
{
    struct ogrenci *gecici=ogrenciler[i];
    while (gecici!=NULL)
    {
        if (gecici->sinif==aranan_sinif)
        {
            printf("%d        %s             %d      %d      %.2f\n",gecici->ogr_no,gecici->ad_soyad,gecici->sinif,gecici->kredi,gecici->not_ort);
        }
        gecici=gecici->sonraki;
    }
    return gecici;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
struct notlar *ders_icinde_ogr_arama(struct notlar *listebasi,int aranan)//ogrencinin belirtilen bir dersi alip almadigini sorgular...
{
    struct  notlar *gecici;
    gecici=listebasi->nota_gore_sonraki;
    while(gecici!=listebasi && gecici->ogr_no<aranan)
    {
        gecici=gecici->nota_gore_sonraki;
    }
    if(gecici->ogr_no==aranan)
    {
        return gecici;
    }
    else return NULL;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
struct notlar* notlar_listesinden_nota_gore_cikar(struct notlar *liste_basi,int ogr_no,struct ders *bir_ders)//silinen bir ogrencinin ders dügümüne bagli olan notlar listesindeki notlarini da silen  fonksiyon....
{
    struct notlar *gecici,*donen=NULL;
    gecici=liste_basi->nota_gore_sonraki;
    while(gecici!=liste_basi && gecici->ogr_no<ogr_no)
    {
        gecici=gecici->nota_gore_sonraki;
        }
       bir_ders->ogr_sayisi--;
        bir_ders->not_ort=((bir_ders->not_ort*bir_ders->kredi)-gecici->notu)/bir_ders->ogr_sayisi;
       donen=gecici;
        gecici->nota_gore_onceki->nota_gore_sonraki=gecici->nota_gore_sonraki;
        gecici->nota_gore_sonraki->nota_gore_onceki=gecici->nota_gore_onceki;
     return donen;

    }
//--------------------------------------------------------------------------------------------------------------------------------------------
struct ogrenci *ogrenci_listesinden_cikar(struct ogrenci *ilk,int ogr_no)//silinen bir ogrenciyi ogrenciler dizisinden cikaran fonksiyon....
{
struct ogrenci *onceki,*gecici,*donen=NULL;

        gecici=ilk;
        while(gecici!=NULL && ogr_no>gecici->ogr_no)
        {
            onceki=gecici;
            gecici=gecici->sonraki;
        }
         donen=gecici;
        onceki->sonraki=gecici->sonraki;
return donen;
}
//---------------------------------------------------------------------------------------------------------------------------------------------
 struct notlar *notlar_listesinden_noya_gore_cikar(struct notlar *liste_basi,int ogr_no,struct ders *bir_ders)//silinen bir ogrencinin ders dugumune bagli olan notlar listesinden no suna gire çikaran fonksiyon....
{
    struct notlar *onceki;
    struct notlar *gecici;
    struct notlar *donen=NULL;
    onceki=liste_basi;
    gecici=liste_basi->noya_gore_sonraki;
    while(gecici!=liste_basi && gecici->ogr_no<ogr_no)
    {    onceki=gecici;
        gecici=gecici->noya_gore_sonraki;
    }
    if(gecici!=liste_basi && gecici->ogr_no==ogr_no)
       {bir_ders->ogr_sayisi--;
        bir_ders->not_ort=((bir_ders->not_ort*bir_ders->kredi)-gecici->notu)/bir_ders->ogr_sayisi;
      donen=gecici;
    onceki->noya_gore_sonraki=gecici->noya_gore_sonraki;}
    return donen;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void not_guncelle(struct ogrenci *liste_basi,struct ders *bir_ders,int yeni_not,int no)//bir dersi alan ogrencinin notunu guncelleyen fonksiyon...
{
    struct ogrenci *gecici=liste_basi;
    while(gecici!=NULL && gecici->ogr_no<no)
    {
        gecici=gecici->sonraki;
    }
    if(gecici->ogr_no==no)
    {
        gecici->not_ort=(((gecici->not_ort)*(gecici->kredi))+((yeni_not)*(bir_ders->kredi)))/((gecici->kredi)+(bir_ders->kredi));
    }
   bir_ders->not_ort=(((bir_ders->not_ort)*(bir_ders->ogr_sayisi))+yeni_not)/(bir_ders->ogr_sayisi+1);

}
//--------------------------------------------------------------------------------------------------------------------------------------------
int ders_kodu_al()//kullanicidan ders kodu alan fonksiyon....
{
    int ders_kodu;
    do
    {
        printf("ders kodunu giriniz:\n");
        scanf("%d",&ders_kodu);
    }
    while(ders_kodu<10 || ders_kodu>89);
    return ders_kodu;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
int ogr_no_al()//kullanicidan ogrenci no alir....
{
   int ogr_no;
    do
    {
        printf("ogrenci numarasi giriniz:\n");
        scanf("%d",&ogr_no);
    }
    while(ogr_no<1 || ogr_no>10000);
    return ogr_no;
}
