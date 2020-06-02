//---------------------------------------------------------------------------

#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
Worker::Worker(AnsiString str)
{
	std::vector<AnsiString> info;
	int pos = 0, count = 0;
	for (int i = 1, len = str.Length(); i <= len;)
	{
		if (str[i] != '|')
		{
			count++;
			i++;
		}
		else
		{
			count--;
			AnsiString st = str.SubString(pos, count);
			info.push_back(st);
			i += 2;
			pos = i;
			count = 0;
		}
	}
	name = info[0];
	department = StrToInt(info[1]);
	AnsiString q = info[2];
	int year, month, yearN, monthN;
	month = StrToInt(q.SubString(0,2));
	year = StrToInt(q.SubString(4,4));
	if (month>12 || month==0 || year>2020 || year<1940) {
		throw "Wrong data format!";
	}
	monthN = 5;
	yearN = 2020;
	int z = (yearN*12 + monthN) - (year*12 + month);
	months = z;
	job = info[3];
	prev = NULL;
}

Worker::Worker(Info x)
{
	name = x.name;
	department = x.department;
	months = x.months;
	job = x.job;
	prev = NULL;
}

AnsiString Worker::WInfo()
{
	AnsiString str = "";
	str = name + " | " + IntToStr(department) + " | "  + job + " | " + IntToStr(months) + " | ";
	return str;
}

void Worker::ShowList(TForm1* F, Worker* list)
{
	if (!list)
	{
		return;
	}
	Worker* x = list;
	while(x) {
		F->Info->Lines->Add(x->WInfo());
		x = x->prev;
	}
}

Worker* Worker::Add(Worker* list, Info value)
{
	Worker* x;
	x = new Worker(value);
	x->prev = list;
	list = x;
	return list;
}

Worker* Worker::Delete(Worker* list, Worker* x)
{
	Worker* cur = list;
	if (!x)
	{
		return list;
	}
	if (x == list)
	{
		Worker* tmp = list->prev;
		delete list;
		return tmp;
	}
	while (cur)
	{
		if (cur->prev == x)
		{
			cur->prev = x->prev;
            break;
		}
		cur = cur->prev;
    }
	delete x;
    return list;
}

Worker* Worker::Find(Worker* list, AnsiString a)
{
	Worker* x = list;
	Worker* ans = NULL;
	while (x)
	{
			Worker y = *x;
			if (.name == a)
			{
				ans = x;
				break;
			}
			x = x->prev;
	}
	return ans;
}


