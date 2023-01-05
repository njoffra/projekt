//---------------------------------------------------------------------------

#include <fmx.h>

#pragma hdrstop
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <algorithm>
#include <windows.h>
#include <fstream>


#include "Zaokruzi.h"
#include "Navigacija.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
using namespace std;
TZaokruziForma *ZaokruziForma;
int skor;
int broj_pokusaja=0;
int izabran_odgovor;
int tacan_odg_rb;
int seed;

vector <String> pitanja = {"A", "b"};
vector <String> odg1 = {"A", "b"};
vector <String> odg2 = {"A", "b"};
vector <String> tacan_odg = {"A", "b"};

//---------------------------------------------------------------------------

void ocisti(){
	ZaokruziForma->Odgovor1->IsChecked = false;
	ZaokruziForma->Odgovor2->IsChecked = false;
	ZaokruziForma->Odgovor3->IsChecked = false;
	ZaokruziForma->Odgovor4->IsChecked = false;
}


void izmjesaj_pitanja(){

	srand(time(NULL));
	seed = rand()%20+1;

	std::srand (seed);
	random_shuffle(pitanja.begin(), pitanja.end());

	std::srand (seed);
	random_shuffle(odg1.begin(), odg1.end());

	std::srand (seed);
	random_shuffle(odg2.begin(), odg2.end());

	std::srand (seed);
	random_shuffle(tacan_odg.begin(), tacan_odg.end());
}

__fastcall TZaokruziForma::TZaokruziForma(TComponent* Owner)
	: TForm(Owner)
{

	izmjesaj_pitanja();
	srand(time(NULL));
	rand();
	tacan_odg_rb = rand()% 3 + 1;
	TekstPitanja->Text = pitanja[broj_pokusaja];

	if(tacan_odg_rb == 1){
		Odgovor1->Text = tacan_odg[broj_pokusaja];
		Odgovor2->Text = odg1[broj_pokusaja];
		Odgovor3->Text = odg2[broj_pokusaja];
	}
	else if(tacan_odg_rb == 2){
		Odgovor1->Text = odg1[broj_pokusaja];
		Odgovor2->Text = tacan_odg[broj_pokusaja];
		Odgovor3->Text = odg2[broj_pokusaja];
	}
	else{
        Odgovor1->Text = odg1[broj_pokusaja];
		Odgovor2->Text = odg2[broj_pokusaja];
		Odgovor3->Text = tacan_odg[broj_pokusaja];
    }
	Odgovor4->Text = "Ne znam";
	TrenutniBodovi->Text = skor;

}
//---------------------------------------------------------------------------

void __fastcall TZaokruziForma::Odgovor1Change(TObject *Sender)
{
	izabran_odgovor = 1;
}
//---------------------------------------------------------------------------

void __fastcall TZaokruziForma::Odgovor2Change(TObject *Sender)
{
	izabran_odgovor = 2;

}
//---------------------------------------------------------------------------

void __fastcall TZaokruziForma::Odgovor3Change(TObject *Sender)
{
	izabran_odgovor = 3;
}
//---------------------------------------------------------------------------

void __fastcall TZaokruziForma::Odgovor4Change(TObject *Sender)
{
	izabran_odgovor = 4;
}

void __fastcall TZaokruziForma::PotvrdiDugmeClick(TObject *Sender)
{
    int a;
	srand(time(NULL));
	rand();
	if(tacan_odg_rb == 1){

					if(izabran_odgovor == 1) skor = skor + 3;
					else if(izabran_odgovor == 4) skor = skor;
					else  skor = skor - 1;
					ocisti();
					}

			else if(tacan_odg_rb == 2){
					if(izabran_odgovor == 2) skor = skor + 3;
					else if(izabran_odgovor == 4) skor = skor;
					else skor = skor - 1;
					ocisti();
					}

			else if(tacan_odg_rb == 3){
					if(izabran_odgovor == 3) skor = skor + 3;
					else if(izabran_odgovor == 4) skor = skor;
					else  skor = skor - 1;
                    ocisti();

				}
                broj_pokusaja++;

	if(broj_pokusaja < pitanja.size()){
    tacan_odg_rb = rand()% 3 + 1;
			TekstPitanja->Text = pitanja[broj_pokusaja];
			if(tacan_odg_rb==1){
				Odgovor1->Text = tacan_odg[broj_pokusaja];
				a = rand()%2+1;
				if(a==1){
					Odgovor2->Text = odg1[broj_pokusaja];
					Odgovor3->Text = odg2[broj_pokusaja];
				}
				else{
					Odgovor2->Text = odg2[broj_pokusaja];
					Odgovor3->Text = odg1[broj_pokusaja];
				}
			}
			else if(tacan_odg_rb==2){
				Odgovor2->Text = tacan_odg[broj_pokusaja];
				a = rand()%2+1;
				if(a==1){
					Odgovor1->Text = odg1[broj_pokusaja];
					Odgovor3->Text = odg2[broj_pokusaja];
				}
				else{
					Odgovor1->Text = odg2[broj_pokusaja];
					Odgovor3->Text = odg1[broj_pokusaja];
				}
			}
			else if(tacan_odg_rb==3){
				Odgovor3->Text = tacan_odg[broj_pokusaja];
				a = rand()%2+1;
				if(a==1){
					Odgovor1->Text = odg1[broj_pokusaja];
					Odgovor2->Text = odg2[broj_pokusaja];
				}
				else{
					Odgovor1->Text = odg2[broj_pokusaja];
					Odgovor2->Text = odg1[broj_pokusaja];
				}
			}
			Odgovor4->Text = "Ne znam";

	}
	else{
		NavigacijaForma->ZaokruziButton->Enabled = false;
		NavigacijaForma->ukupni_bodovi += skor;
		NavigacijaForma->UkupniBodovi->Text = NavigacijaForma->ukupni_bodovi;
		this->Close();
		NavigacijaForma->Show();
	}

	TrenutniBodovi->Text = skor;
}

//---------------------------------------------------------------------------





//---------------------------------------------------------------------------

