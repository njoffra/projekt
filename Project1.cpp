//---------------------------------------------------------------------------

#include <fmx.h>
#ifdef _WIN32
#include <tchar.h>
#endif
#pragma hdrstop
#include <System.StartUpCopy.hpp>
//---------------------------------------------------------------------------
USEFORM("Spajanje.cpp", SpajanjeForma);
USEFORM("Zaokruzivanje.cpp", ZaokruzivanjeForma);
USEFORM("Broj.cpp", BrojForma);
USEFORM("Klik.cpp", KlikForma);
USEFORM("Navigacija.cpp", NavigacijaForma);
//---------------------------------------------------------------------------
extern "C" int FMXmain()
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TNavigacijaForma), &NavigacijaForma);
		Application->CreateForm(__classid(TBrojForma), &BrojForma);
		Application->CreateForm(__classid(TSpajanjeForma), &SpajanjeForma);
		Application->CreateForm(__classid(TKlikForma), &KlikForma);
		Application->CreateForm(__classid(TZaokruzivanjeForma), &ZaokruzivanjeForma);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
