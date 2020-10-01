#include<iostream>          //std::cout         
#include<fstream>           //std::file               
#include<algorithm>         //std::sort                
#include<utility>           //std::pair
#include<vector>            //std::vector
#include<locale.h>          //std::setlocale
using namespace std;

vector<int>koku;                                                          
int  kokuBul(int );                                           //Kavþaðýn kökünü bul
void merge(int ,int);                                         //farkli köke sahip olan kavþaklarý bileþtir  
vector<int>kokuOlustur(int);                                  //Yeni vector oluþtur
void kruskalYazdir(vector<pair<int,pair<int,int>>>,int,int);  //kruskal çözümü ve maliyet bilgileri yazdir

	


int main(){
	setlocale(LC_ALL, "Turkish");          //Türkçe harfi hatalarý önlemek için
	
	//deðiþken ve veriyapýlarý tanýmlandý
	vector<int> veri;
	vector<pair<int , pair<int,int>> >kruskal;  
	int kSayisi,cSayisi;
	int temp;
	int i=0;
	int cs=0,ks=0;
	int tasarrufsuzMaliyet = 0, toplamMaliyet = 0, toplamKazanc = 0 ;
	
	//Giris dosyasý tanýmlandý
	ifstream girisDosyasi;
	girisDosyasi.open("sehirplani.txt",ios::in);
	
	//Dosyanýn bulunup bulunmadýðý kontrol edilir
	if(!girisDosyasi){
		cout<<"Giris dosyasý bulunamadý..."<<endl;
		exit(-1);
	}
		
	//dosyadi veriler "veri" vector üne atandý	
	while(!girisDosyasi.eof()){
		girisDosyasi>>temp;
		veri.push_back(temp);
	}
	
	//ilk iki deðer sýrasýyla kavþak sayýsý ve cadde sayisi
	kSayisi = veri[0]; veri.erase(veri.begin());
	cSayisi = veri[0]; veri.erase(veri.begin());
	pair<int , pair<int,int> >cadde[cSayisi];
	
	//veri vector ündeki veriler cadde(ayrýtlar) adýnda pair dizisine atandý
	for(int i=0;i<3*cSayisi;++i){
		cadde[i].second.first=veri[3*i];  
		cadde[i].second.second=veri[3*i+1];    
		cadde[i].first=veri[3*i+2];           		 
	}
	
	
	//caddeleri yazdýr
	cout<<"Caddeler(Sýralanmadan önce) :"<<endl<<endl;
	for(int i=0;i<cSayisi;i++){
		cout<<cadde[i].second.first<<"------"<<cadde[i].second.second<<"--------"<<cadde[i].first<<endl;
	}
	
	sort(cadde,cadde+cSayisi); // sort fonksiyonu ile caddeler maliyetlerine göre sýralandý
	
	
	//caddeleri yazdýr
	cout<<endl<<endl<<"Caddeler(Maliyetlerine göre sýralandýktan sonra) :"<<endl<<endl;
	for(int i=0;i<cSayisi;i++){
		cout<<cadde[i].second.first<<"------"<<cadde[i].second.second<<"--------"<<cadde[i].first<<endl;
	}
		
	
	koku = kokuOlustur(kSayisi);    // koku(global) adýndaki vector ün boyut ve ilk deðerleri atandý
		
	//kruskal algoritmasýyla lambalarý açýk olmasý gereken yollar bulunur ve maliyetleri hesaplanýr  
	
	for(cs=0,ks=0;cs<(kSayisi-1)||ks<cSayisi;++ks){
		 tasarrufsuzMaliyet+= cadde[ks].first;     //tasarrufsuz Maliyet
    	if(kokuBul(cadde[ks].second.first) != kokuBul(cadde[ks].second.second)){ //kavþak kökleri kontrol ayný olup olmadýðý kontorl et
    		merge( cadde[ks].second.first , cadde[ks].second.second );          //farklý ise birleþtir
    		kruskal.push_back(cadde[ks]);                                      //alýnan cadde kruskal pair vectörüne atan
    		toplamMaliyet += cadde[ks].first;      //toplamMaliyet
    		++cs;
		}
	}
	
	cout<<endl<<endl<<"Kruskal algoritmasýyla problemin çözümü:  "<<endl<<endl;

	kruskalYazdir(kruskal,toplamMaliyet,tasarrufsuzMaliyet); // kruskal çözümü ve maliyet bilgileri yazdýrýlýr
	
	
	return 0;
}


//Kavþaðýn kökünü bulan fonksiyon
int  kokuBul(int a){
	if(koku[a]==a) return a;
	return kokuBul(koku[a]);
}

//farkli köke sahip olan kavþaklarý bileþtiren fonksiyon
void merge(int a,int b){
    	koku[kokuBul(a)] = kokuBul(b);
}

//yeni vector oluþturur
vector<int>kokuOlustur(int x){
	vector<int>kok(x);
	for(int i=0;i<x;++i){
		kok[i]=i;
	}
	return kok;
}

//kruskal çözümü ve maliyet bilgileri yazdiran fonksiyonu
void kruskalYazdir(vector<pair<int,pair<int,int> > >vect,int a,int b){
	for(int a=0; a<vect.size(); ++a){
		cout<<vect[a].second.first<<"		"<<vect[a].second.second<<endl;
	}
	cout<<endl<<endl;
	cout<<"Toplam maliyet  : "<<a<<" AOA Lirasý"<<endl;
	cout<<"Toplam kazanc   : "<<b-a<<" AOA Lirasý"<<endl;
}


