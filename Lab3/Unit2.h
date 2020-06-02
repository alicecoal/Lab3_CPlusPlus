//---------------------------------------------------------------------------
#include <vcl.h>
#include <string>
#include <vector>
#include <Unit1.h>
#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------

struct Info {
	AnsiString name;
	int department;
	int months;
	AnsiString job;
};

class Worker {
	public:
		Worker* prev;
		AnsiString name;
		int department;
		int months;
		AnsiString job;
	public:
		Worker(Info);
		Worker(AnsiString);
		AnsiString WInfo();
		static void ShowList(TForm1*, Worker*);
		static Worker* Add(Worker*, Info);
		static Worker* Delete(Worker* list, Worker* item);
		static Worker* Find(Worker*, AnsiString);
};

#endif
