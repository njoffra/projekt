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
	void povecaj_klikove(){
		this->klikovi++;
	}
	virtual void ispisi_klikove(){
		KlikForma->Igrac1Tekst->Text=0; //na pocetku za oba
		KlikForma->Igrac2Tekst->Text=0;
	}
};
class Igrac1: public Igrac{
private:

public:
	void pokreniTimer1(){

	}
	void ispisi_klikove()override {
		KlikForma->Igrac1Tekst->Text=this->klikovi; //kad pises za igraca1
	}
};
class Igrac2:public Igrac{

public:
	void pokreniTimer2(){

	}
	void ispisi_klikove() override{
		KlikForma->Igrac2Tekst->Text=this->klikovi;
	}
};
//---------------------------------------------------------------------------
__fastcall TKlikForma::TKlikForma(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TKlikForma::zatvori(TObject *Sender, TCloseAction &Action)
{
NavigacijaForma->KlikButton->Enabled = false;
		//NavigacijaForma->ukupni_bodovi += skor; // ukupni_bodovi je deklarisana Navigacija.h
		//NavigacijaForma->UkupniBodovi->Text = NavigacijaForma->ukupni_bodovi;
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
