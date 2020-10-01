#include<iostream>          //std::cout         
#include<fstream>           //std::file               
#include<algorithm>         //std::sort                
#include<utility>           //std::pair
#include<vector>            //std::vector
#include<locale.h>          //std::setlocale
using namespace std;

vector<int>koku;                                                          
int  kokuBul(int );                                           //Kav�a��n k�k�n� bul
void merge(int ,int);                                         //farkli k�ke sahip olan kav�aklar� bile�tir  
vector<int>kokuOlustur(int);                                  //Yeni vector olu�tur
void kruskalYazdir(vector<pair<int,pair<int,int>>>,int,int);  //kruskal ��z�m� ve maliyet bilgileri yazdir

	


int main(){
	setlocale(LC_ALL, "Turkish");          //T�rk�e harfi hatalar� �nlemek i�in
	
	//de�i�ken ve veriyap�lar� tan�mland�
	vector<int> veri;
	vector<pair<int , pair<int,int>> >kruskal;  
	int kSayisi,cSayisi;
	int temp;
	int i=0;
	int cs=0,ks=0;
	int tasarrufsuzMaliyet = 0, toplamMaliyet = 0, toplamKazanc = 0 ;
	
	//Giris dosyas� tan�mland�
	ifstream girisDosyasi;
	girisDosyasi.open("sehirplani.txt",ios::in);
	
	//Dosyan�n bulunup bulunmad��� kontrol edilir
	if(!girisDosyasi){
		cout<<"Giris dosyas� bulunamad�..."<<endl;
		exit(-1);
	}
		
	//dosyadi veriler "veri" vector �ne atand�	
	while(!girisDosyasi.eof()){
		girisDosyasi>>temp;
		veri.push_back(temp);
	}
	
	//ilk iki de�er s�ras�yla kav�ak say�s� ve cadde sayisi
	kSayisi = veri[0]; veri.erase(veri.begin());
	cSayisi = veri[0]; veri.erase(veri.begin());
	pair<int , pair<int,int> >cadde[cSayisi];
	
	//veri vector �ndeki veriler cadde(ayr�tlar) ad�nda pair dizisine atand�
	for(int i=0;i<3*cSayisi;++i){
		cadde[i].second.first=veri[3*i];  
		cadde[i].second.second=veri[3*i+1];    
		cadde[i].first=veri[3*i+2];           		 
	}
	
	
	//caddeleri yazd�r
	cout<<"Caddeler(S�ralanmadan �nce) :"<<endl<<endl;
	for(int i=0;i<cSayisi;i++){
		cout<<cadde[i].second.first<<"------"<<cadde[i].second.second<<"--------"<<cadde[i].first<<endl;
	}
	
	sort(cadde,cadde+cSayisi); // sort fonksiyonu ile caddeler maliyetlerine g�re s�raland�
	
	
	//caddeleri yazd�r
	cout<<endl<<endl<<"Caddeler(Maliyetlerine g�re s�raland�ktan sonra) :"<<endl<<endl;
	for(int i=0;i<cSayisi;i++){
		cout<<cadde[i].second.first<<"------"<<cadde[i].second.second<<"--------"<<cadde[i].first<<endl;
	}
		
	
	koku = kokuOlustur(kSayisi);    // koku(global) ad�ndaki vector �n boyut ve ilk de�erleri atand�
		
	//kruskal algoritmas�yla lambalar� a��k olmas� gereken yollar bulunur ve maliyetleri hesaplan�r  
	
	for(cs=0,ks=0;cs<(kSayisi-1)||ks<cSayisi;++ks){
		 tasarrufsuzMaliyet+= cadde[ks].first;     //tasarrufsuz Maliyet
    	if(kokuBul(cadde[ks].second.first) != kokuBul(cadde[ks].second.second)){ //kav�ak k�kleri kontrol ayn� olup olmad��� kontorl et
    		merge( cadde[ks].second.first , cadde[ks].second.second );          //farkl� ise birle�tir
    		kruskal.push_back(cadde[ks]);                                      //al�nan cadde kruskal pair vect�r�ne atan
    		toplamMaliyet += cadde[ks].first;      //toplamMaliyet
    		++cs;
		}
	}
	
	cout<<endl<<endl<<"Kruskal algoritmas�yla problemin ��z�m�:  "<<endl<<endl;

	kruskalYazdir(kruskal,toplamMaliyet,tasarrufsuzMaliyet); // kruskal ��z�m� ve maliyet bilgileri yazd�r�l�r
	
	
	return 0;
}


//Kav�a��n k�k�n� bulan fonksiyon
int  kokuBul(int a){
	if(koku[a]==a) return a;
	return kokuBul(koku[a]);
}

//farkli k�ke sahip olan kav�aklar� bile�tiren fonksiyon
void merge(int a,int b){
    	koku[kokuBul(a)] = kokuBul(b);
}

//yeni vector olu�turur
vector<int>kokuOlustur(int x){
	vector<int>kok(x);
	for(int i=0;i<x;++i){
		kok[i]=i;
	}
	return kok;
}

//kruskal ��z�m� ve maliyet bilgileri yazdiran fonksiyonu
void kruskalYazdir(vector<pair<int,pair<int,int> > >vect,int a,int b){
	for(int a=0; a<vect.size(); ++a){
		cout<<vect[a].second.first<<"		"<<vect[a].second.second<<endl;
	}
	cout<<endl<<endl;
	cout<<"Toplam maliyet  : "<<a<<" AOA Liras�"<<endl;
	cout<<"Toplam kazanc   : "<<b-a<<" AOA Liras�"<<endl;
}


