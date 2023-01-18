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
int brojac1=0;
int brojac2=0;
int sekunda1=0;
int sekunda2=0;
void __fastcall Timer1Timer();
void __fastcall Timer2Timer();

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
	   Timer1Timer();
	}
	void ispisi_klikove()override {
		KlikForma->Igrac1Tekst->Text=this->klikovi; //kad pises za igraca1
	}
};

class Igrac2:public Igrac{
public:
	void pokreniTimer2(){ // ovdje definis tajmer ili samo ispis tajmer za 2 igraca
		Timer2Timer();
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
    brojac1++;
	if(brojac1<=1){
		StartTime1= Now();
			   }
	VrijemeText1->Visible = true;
	Timer1->Enabled = true;
	VrijemeText1->Enabled = True;
	!prvi_igrac;
	prvi_igrac.ispisi_klikove();
	if(sekunda1==10){  // ovdje umjesto ovog uslova treba kad istekne timer
		Igrac1Dugme->Enabled=false;
		VrijemeText1->Visible= false,
        VrIsteklo1->Text="Vrijeme isteklo";
		Igrac2Dugme->Enabled=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TKlikForma::Igrac2DugmeClick(TObject *Sender)
{
    brojac2++;
	if(brojac2<=1){
		StartTime2= Now();
			   }
	VrijemeText2->Visible = true;
	Timer2->Enabled = true;
	VrijemeText2->Enabled = True;
	!drugi_igrac;
	drugi_igrac.ispisi_klikove();
	if(sekunda2==10) {  // ovdje umjesto ovog uslova treba kad istekne timer
	   Igrac2Dugme->Enabled=false;
	   VrijemeText2->Visible= false,
		VrIsteklo2->Text="Vrijeme isteklo";
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
		RezultatText->Text="Nerijeseno";
        drugi_igrac.setSkor();
		skor = drugi_igrac.getSkor();
	   }
	}
}
//---------------------------------------------------------------------------



void __fastcall TKlikForma::Timer1Timer(TObject *Sender)
{
	TDateTime Diff = Now() - StartTime1;
	Word Hour, Min, Sec, MSec;
	DecodeTime(Diff, Hour, Min, Sec, MSec);
	VrijemeText1->Text = String(Sec);
    sekunda1=Sec;
}
//---------------------------------------------------------------------------

void __fastcall TKlikForma::Timer2Timer(TObject *Sender)
{
	TDateTime Diff = Now() - StartTime2;
	Word Hour, Min, Sec, MSec;
	DecodeTime(Diff, Hour, Min, Sec, MSec);
	VrijemeText2->Text = String(Sec);
    sekunda2=Sec;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


