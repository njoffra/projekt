//---------------------------------------------------------------------------

#ifndef KlikH
#define KlikH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
//---------------------------------------------------------------------------
class TKlikForma : public TForm
{
__published:	// IDE-managed Components
	TButton *Igrac1Dugme;
	TButton *Igrac2Dugme;
	TButton *IzlazDugme;
	TText *Igrac1Tekst;
	TText *Igrac2Tekst;
	void __fastcall zatvori(TObject *Sender, TCloseAction &Action);
	void __fastcall IzlazDugmeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TKlikForma(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TKlikForma *KlikForma;
//---------------------------------------------------------------------------
#endif
