//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Vjesala.h"
#include "Navigacija.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TVjesalaForma *VjesalaForma;
int skor;
//---------------------------------------------------------------------------
__fastcall TVjesalaForma::TVjesalaForma(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TVjesalaForma::zatvori(TObject *Sender, TCloseAction &Action)
{
NavigacijaForma->VjesalaButton->Enabled = false;
		NavigacijaForma->ukupni_bodovi += skor; // ukupni_bodovi je deklarisana Navigacija.h
		NavigacijaForma->UkupniBodovi->Text = NavigacijaForma->ukupni_bodovi;
		this->Close();
		NavigacijaForma->Show();
}
//---------------------------------------------------------------------------

