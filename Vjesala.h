//---------------------------------------------------------------------------

#ifndef VjesalaH
#define VjesalaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
//---------------------------------------------------------------------------
class TVjesalaForma : public TForm
{
__published:	// IDE-managed Components
	void __fastcall zatvori(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TVjesalaForma(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TVjesalaForma *VjesalaForma;
//---------------------------------------------------------------------------
#endif
