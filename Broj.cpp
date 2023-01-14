//---------------------------------------------------------------------------

#include <fmx.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <sstream>
#include <string>
#include <stack>
#include <cmath>
#include <stdexcept>
#include <stdlib.h>
#include <memory>

#pragma hdrstop

#include "Broj.h"
#include "Navigacija.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TBrojForma *BrojForma;
//---------------------------------------------------------------------------
int skor;
//std::unique_ptr<int> topscore = nullptr;
std::unique_ptr<int> topscore = std::make_unique<int>(0);
std::shared_ptr<int> ptrsuma = std::make_shared<int>(0);
std::unique_ptr<int> result = std::make_unique<int>(0);
std::string uString (int a){
  std::ostringstream ss;
  ss<<a;
  return ss.str();
}

__fastcall TBrojForma::TBrojForma(TComponent* Owner)
	: TForm(Owner)
{
		//StartTime = Now();
		//Vrijeme->Enabled = true;
}
//---------------------------------------------------------------------------



void __fastcall TBrojForma::Label1Click(TObject *Sender)
{

	//Label2->Text="Nele";
}
//---------------------------------------------------------------------------
const int MIN_NUM = 1;
const int MAX_NUM = 9;

void __fastcall TBrojForma::Button1Click(TObject *Sender)
{   srand(time(0));
	StartTime = Now();
    Vrijeme->Enabled = true;
	  while (true) {
	  int brojevi[5];
			for(int i=0; i<5; i++){
            brojevi[i] = MIN_NUM +(rand()%(MAX_NUM-MIN_NUM+1));
            *ptrsuma += brojevi[i];
			}
	  ButtonNum1->Text=uString(brojevi[0]).c_str();

	  ButtonNum2->Text=uString(brojevi[1]).c_str();

	  ButtonNum3->Text=uString(brojevi[2]).c_str();

	  ButtonNum4->Text=uString(brojevi[3]).c_str();

	  ButtonNum5->Text=uString(brojevi[4]).c_str();
		// izabere random operator
		char operators[] = {'+', '/', '*', '-'};
		char op = operators[rand() % 4];

		// kalkulacije
		//int result;
		switch (op) {
		  case '+':
			*result = brojevi[1] + *ptrsuma;
			break;
		  case '/':
			*result = brojevi[2] / *ptrsuma;
			break;
		  case '*':
			*result = brojevi[3] * *ptrsuma;
			break;
		  case '-':
			*result = brojevi[4] - *ptrsuma;
			break;
		}

		// Ako je rezultat u rangu i ako je veci od sume onda ce ga printati i izaci iz loopa
		if (*result > 100 && *result <= 1000 && *result > *ptrsuma) {
		  Label6->Text = uString(*result).c_str();
		  break;
		}
	  }
	  Button1->Enabled = False;

}

//---------------------------------------------------------------------------


void __fastcall TBrojForma::NumberClick2(TObject *Sender)
{
		TButton* b = ((TButton*)Sender);

		if (EditDisplay->Text== "0")
		{
			EditDisplay->Text = b->Text;
		}else
		{
			EditDisplay->Text = EditDisplay->Text + b->Text;
		}
}
//---------------------------------------------------------------------------
void __fastcall TBrojForma::OperatorClick(TObject *Sender)

  {
			TButton* b = ((TButton*)Sender);

			if (EditDisplay->Text== "0")
			{
				EditDisplay->Text = b->Text;
			}else
			{
				EditDisplay->Text = EditDisplay->Text + b->Text;
			}
	}


//---------------------------------------------------------------------------

double performOp(char op, double num1, double num2)
	{
	if (op == '+')
		return num1 + num2;
	else if (op == '-')
		return num1 - num2;
	else if (op == '*')
		return num1 * num2;
	else if (op == '/')
		return num1 / num2;
	else
		return 0;
	}
	// provjerava je li char operator
	bool jeOperator(char c)
	{
	return (c == '+' || c == '-' || c == '*' || c == '/');
		}

	// provjerava prednost operatora
	int prednost(char op)
	{
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/')
		return 2;
	else
		return 0;
		}

void __fastcall TBrojForma::ButtonJednakoClick(TObject *Sender)
{
	bool jest = false;
	{
	std::string rezultat = AnsiString(EditDisplay->Text).c_str();
	std::stringstream ss(rezultat);
	std::stack<double> numbers;
	std::stack<char> ops;
	char c;
	double num;

	// izvlaci operatore i brojeve do kraja
	while (ss >> c)
	{
		if (c == '(')
		{
			// pusha otvorenu zagradu na stack
			ops.push(c);
		}
		else if (isdigit(c))
		{
			// izvlaci brojeve
			ss.putback(c);
			ss >> num;
			numbers.push(num);
		}
		else if (jeOperator(c))
		{
			// radi potrebne kalkulacije prije nego pusha na stack
			while (!ops.empty() && prednost(ops.top()) >= prednost(c))
			{

				double num2 = numbers.top();
				numbers.pop();
				double num1 = numbers.top();
                numbers.pop();
				char op = ops.top();
                ops.pop();
                numbers.push(performOp(op, num1, num2));
            }
            ops.push(c);
        }
        else if (c == ')')
        {
            // kalkulacije do sljedece otvorene zagrade
            while (ops.top() != '(')
            {
                double num2 = numbers.top();
                numbers.pop();
                double num1 = numbers.top();
                numbers.pop();
                char op = ops.top();
                ops.pop();
                numbers.push(performOp(op, num1, num2));
            }
            ops.pop();
        }
    }

    // naredne kalkulacije
    while (!ops.empty())
		{
        double num2 = numbers.top();
        numbers.pop();
		double num1 = numbers.top();
        numbers.pop();
        char op = ops.top();
        ops.pop();
		numbers.push(performOp(op, num1, num2));
		}
		*topscore=numbers.top();
        if (topscore) {
			ButtonRezultat->Text = *topscore;
		} else {
			ButtonRezultat->Text = "null";
			}
	}

//---------------------------------------------------------------------------
 }

//---------------------------------------------------------------------------

void __fastcall TBrojForma::BrisiClick(TObject *Sender)
{
    EditDisplay->Text = " ";
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void __fastcall TBrojForma::IzlazClick(TObject *Sender)
{
if(*result==*topscore){
		Bodovi->Text="Cestitke, osvojili se maksimalne bodove.";
		skor = 20;
		}else if(abs(*result - *topscore <= 5)){
				Bodovi->Text="Osvojili ste 15 bodova.";
				skor = 15;
			}else if(abs(*result - *topscore <= 10)){
					Bodovi->Text="Osvojili ste 10 bodova.";
					skor = 10;
				}else if(abs(*result - *topscore <= 15)){
						Bodovi->Text="Osvojili ste 5 bodova.";
						skor = 5;
					}else if(abs(*result - *topscore >= 20)){
							Bodovi->Text="Osvojili ste 0 bodova.";
							skor = 0;
						}

	NavigacijaForma->BrojButton->Enabled = false;
	NavigacijaForma->ukupni_bodovi += skor; // ukupni_bodovi je deklarisana Navigacija.h
	NavigacijaForma->UkupniBodovi->Text = NavigacijaForma->ukupni_bodovi;
	ButtonNum1->Enabled = false;
	ButtonNum2->Enabled = false;
	ButtonNum3->Enabled = false;
	ButtonNum4->Enabled = false;
	ButtonNum5->Enabled = false;
	ButtonPlus->Enabled = false;
	ButtonMinus->Enabled = false;
	ButtonPuta->Enabled = false;
	ButtonDijeli->Enabled = false;
	ButtonBrisi->Enabled = false;
	ButtonLZagrada->Enabled = false;
	ButtonDZagrada->Enabled = false;
	ButtonJednako->Enabled = false;
	EditDisplay->Enabled = false;
	VrijemeText->Text = "Vrijeme isteklo";
	Vrijeme->Enabled = False;
}
//---------------------------------------------------------------------------


void __fastcall TBrojForma::VrijemeTimer(TObject *Sender) //This event occurs every second.
{
		TDateTime Diff = Now() - StartTime;
		Word Hour, Min, Sec, MSec;
		DecodeTime(Diff, Hour, Min, Sec, MSec);
		VrijemeText->Text = String(Sec); //+" :"+String(MSec);

		if(Sec==999){
		   ButtonNum1->Enabled = false;
		   ButtonNum2->Enabled = false;
		   ButtonNum3->Enabled = false;
		   ButtonNum4->Enabled = false;
		   ButtonNum5->Enabled = false;
		   ButtonPlus->Enabled = false;
		   ButtonMinus->Enabled = false;
		   ButtonPuta->Enabled = false;
		   ButtonDijeli->Enabled = false;
		   ButtonBrisi->Enabled = false;
		   ButtonLZagrada->Enabled = false;
		   ButtonDZagrada->Enabled = false;
		   ButtonJednako->Enabled = false;
		   EditDisplay->Enabled = false;
		   VrijemeText->Text = "Vrijeme isteklo";
           Bodovi->Text="Osvojili ste 0 bodova.";
		   Vrijeme->Enabled = False;
		}

}
//---------------------------------------------------------------------------


void __fastcall TBrojForma::IzlazPraviClick(TObject *Sender)
{
    this->Close();
	NavigacijaForma->Show();
    //resetovanje pointera zbog memory leaks
	topscore.reset();
	ptrsuma.reset();
	result.reset();
}
//---------------------------------------------------------------------------

