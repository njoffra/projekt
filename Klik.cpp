//---------------------------------------------------------------------------

#include <fmx.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <ctime>
#pragma hdrstop

#include "Klik.h"
#include "Navigacija.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
using namespace std;
TKlikForma *KlikForma;
int skor;

class Igrac{
protected:
	int skor;
	int klikovi;
public:
	Igrac(){
		this->klikovi=0;
		this->skor=0;
	}
	virtual void setSkor(){
		this->skor=(int)(this->klikovi/3);
	}
	int getSkor(){
		return this->skor;
	}
	int getKlikovi(){
		return this->klikovi;
	}
	void operator!(){
		this->klikovi++;
	}
	virtual void ispisi_klikove(){
		KlikForma->Igrac1Tekst->Text=0; //na pocetku za oba
		KlikForma->Igrac2Tekst->Text=0;
	}
};

class Igrac1: public Igrac{
public:
	void pokreniTimer1(){ // ovdje definis tajmer ili samo ispis tajmer za 1 igraca

	}
	void ispisi_klikove()override {
		KlikForma->Igrac1Tekst->Text=this->klikovi; //kad pises za igraca1
	}
};

class Igrac2:public Igrac{
public:
	void pokreniTimer2(){ // ovdje definis tajmer ili samo ispis tajmer za 2 igraca

	}
	void ispisi_klikove() override{
		KlikForma->Igrac2Tekst->Text=this->klikovi;
	}
};
Igrac1 prvi_igrac;
Igrac2 drugi_igrac;

//---------------------------------------------------------------------------
__fastcall TKlikForma::TKlikForma(TComponent* Owner)
	: TForm(Owner)
{
	Igrac igrac;
	igrac.ispisi_klikove();
}
//---------------------------------------------------------------------------
void __fastcall TKlikForma::zatvori(TObject *Sender, TCloseAction &Action)
{
		NavigacijaForma->KlikButton->Enabled = false;
		this->Close();
		NavigacijaForma->Show();
}
//---------------------------------------------------------------------------


void __fastcall TKlikForma::IzlazDugmeClick(TObject *Sender)
{
		NavigacijaForma->ukupni_bodovi += skor;
		NavigacijaForma->UkupniBodovi->Text = NavigacijaForma->ukupni_bodovi;
		this->Close();
		NavigacijaForma->Show();
}
//---------------------------------------------------------------------------

void __fastcall TKlikForma::Igrac1DugmeClick(TObject *Sender)
{
	// ne znam gdje ces pokrenut tajmer mozda ovdje ali onda moras osigurat da se samo jednom pokrene
	!prvi_igrac;
	prvi_igrac.ispisi_klikove();
	if(prvi_igrac.getKlikovi()>=30){  // ovdje umjesto ovog uslova treba kad istekne timer
		Igrac1Dugme->Enabled=false;
		Igrac2Dugme->Enabled=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TKlikForma::Igrac2DugmeClick(TObject *Sender)
{
	!drugi_igrac;
	drugi_igrac.ispisi_klikove();
	if(drugi_igrac.getKlikovi()>=30) {  // ovdje umjesto ovog uslova treba kad istekne timer
	   Igrac2Dugme->Enabled=false;
	   if(prvi_igrac.getKlikovi() > drugi_igrac.getKlikovi()){ // ovo poslije svega provjerava koji je igrac pobjedio pa cemo vidjet sta cemo kako cemo dalje
		RezultatText->Text="Igrac 1 je pobjedio";
		prvi_igrac.setSkor();
		skor = prvi_igrac.getSkor();
		}
	   else if(prvi_igrac.getKlikovi() < drugi_igrac.getKlikovi()){
		RezultatText->Text="Igrac 1 je pobjedio";
		drugi_igrac.setSkor();
		skor = drugi_igrac.getSkor();
		}
	   else{
		RezultatText->Text="Nerjeseno";
        drugi_igrac.setSkor();
		skor = drugi_igrac.getSkor();
	   }
	}
}
//---------------------------------------------------------------------------

