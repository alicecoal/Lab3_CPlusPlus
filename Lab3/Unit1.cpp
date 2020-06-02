//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TStringList* tmp = new TStringList;
TFileStream *fl = NULL;
Worker* list = NULL;
Worker* chosen = NULL;
int filter = 1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ShowClick(TObject *Sender)
{
	AnsiString data = Data->Text;
	Info->Lines->Clear();
	chosen = NULL;
	try {
			Worker::ShowList(Form1, list);
		}
		catch (...)
		{
			Data->Text = "Wrong data";
		}
}

void __fastcall TForm1::ShowDepClick(TObject *Sender)
{
   AnsiString data = Data->Text;
   Info->Lines->Clear();
   chosen = NULL;
   try
   {
	   int x = StrToInt(data);
	   Worker* cur = list;
	   while (cur)
	   {
			Worker y = *cur;
			if (y.department == x)
			{
				Form1->Info->Lines->Add(cur->WInfo());
			}
			cur = cur->prev;
	   }
   }
   catch (...)
   {
		Data->Text = "Wrong data";
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ShowMonClick(TObject *Sender)
{
   AnsiString data = Data->Text;
   Info->Lines->Clear();
   chosen = NULL;
   try
   {
	   int x = StrToInt(data);
	   Worker* cur = list;
	   while (cur)
	   {
			Worker y = *cur;
			if (y.months >= x)
			{
				Form1->Info->Lines->Add(cur->WInfo());
			}
			cur = cur->prev;
	   }
   }
   catch (...)
   {
		Data->Text = "Wrong data";
   }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::AddClick(TObject *Sender)
{
	struct Info x;
	try {
		x.name = Name->Text;
		x.department = StrToInt(Department->Text);
		int year, month, yearN, monthN;
		AnsiString q = Experience->Text;
		month = StrToInt(q.SubString(0,2));
		year = StrToInt(q.SubString(4,4));
		if (month>12 || month==0 || year>2020 || year<1940) {
			throw "Wrong data format!";
		}
		monthN = 5;
		yearN = 2020;
		int z = (yearN*12 + monthN) - (year*12 + month);
		x.months = z;
		x.job = Job->Text;
		if (list==NULL)
		{
			list = new Worker(x);
		}
		else
		{
			list = Worker::Add(list, x);
		}
		Name->Text = "";
		Department->Text = "";
		Experience->Text = "";
		Job->Text = "";
	} catch (...) {
		Name->Text = "ERROR";
		Department->Text = "ERROR";
		Experience->Text = "ERROR";
		Job->Text = "ERROR";
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SrchClick(TObject *Sender)
{
	AnsiString person = Search->Text;
	Worker* x;
	if (!list)
	{
		ShowMessage("EMPTY");
        return;
	}
	Info->Lines->Clear();
	x = Worker::Find(list, person);
	if (x)
	{
		Info->Lines->Add(x->WInfo());
		chosen = x;
	}
	else
	{
		Info->Lines->Add("ERROR");
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::DelClick(TObject *Sender)
{
	AnsiString person = Search->Text;
	chosen = Worker::Find(list, person);
	if (!list)
	{
		ShowMessage("EMPTY");
		return;
	}
	if (!chosen)
	{
		ShowMessage("Nobody is selected!");
		return;
	}
	Info->Lines->Clear();
	list = Worker::Delete(list, chosen);
	chosen = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DataClick(TObject *Sender)
{
	Data->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SearchClick(TObject *Sender)
{
    Search->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OpenClick(TObject *Sender)
{
	if (!OpenDialog1->Execute()){
		ShowMessage("You didn't choose anything.");
		return;
	}
	try
	{
		tmp->LoadFromFile(OpenDialog1->FileName);
	}
	catch (...)
	{
		ShowMessage("There is no such file. Created new one.");
		fl = new TFileStream(OpenDialog1->FileName, fmCreate);
		fl->Free();
	}
	Info->Lines->Clear();
	list = NULL;
	for (int i = 0; i < tmp->Count; i++)
	{
		if (list==NULL)
		{
			list = new Worker(tmp->Strings[i]);
		}
		else
		{
			Worker* x;
			x = new Worker(tmp->Strings[i]);
			x->prev = list;
			list = x;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveClick(TObject *Sender)
{
	if (!SaveDialog1->Execute())
	{
		ShowMessage("ERROR");
		return;
	}
	Info->Lines->Clear();
	list->ShowList(Form1, list);
	Info->Lines->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------


