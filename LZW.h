#ifndef lzw
#define lzw
#include <string>
#include "LZWStorage.h"
#include "InOut.h"
#include "DrzewoLeksykograficzne.h"

using namespace std;



class LZW{
public:
	DrzewoL *DL;
	InOut *IO;
	LZWStorage *Storage;
	char *buf;
	unsigned long IlePetliMainLoop;
	unsigned short help1;	//numer indeksu do zapisu do pliku
	int help2;	//ilosc elementow w nowym elemencie do slownika
	//metoda porownujaca strumien wejsciowy ze slownikiem 
	// i wychwytujaca najdluzsze slowo
	//korzystam z tego, ze dlusze slowa sa coraz dalej zapisane
	bool Compare(char *a, char *b, int length){
		int i = 0;
		while(a[i] == b[i] && i < length)
			i++;
		if(i == length)
			return true;
		else
			return false;
	}

	bool CmpDoDict(Wezel * K,char *newElInDict){
		char temp = buf[0];
		bool TF = true,TF2;
		if(TF2 = (K->Glebokosc == 0 ? true: IO->read(&temp))){
			newElInDict[K->Glebokosc] = temp;
			help1 = K->Indeks;
			help2 = K->Glebokosc;
			if(K->Wsk[(unsigned char)temp] != nullptr)
				return CmpDoDict(K->Wsk[(unsigned char)temp],newElInDict);
			else 
				return true;
		}
		else
			return false;
	}

	bool CompareToDict(int i,char *newElInDict,int numberOfElement){
		char temp = buf[0];
		bool TF = true,TF2;
		if(TF2 = (numberOfElement == 0 ? true: IO->read(&temp))){
			newElInDict[numberOfElement] = temp;
			help1 = i;
			help2 = numberOfElement;
			while(i != Storage->LengthOfDict && TF){
				if(Storage->Length[i] >= numberOfElement + 1)
					if(Compare(buf,Storage->dict[i],numberOfElement + 1))
					{
						TF = false;
						return CompareToDict(i,newElInDict,numberOfElement + 1);
					}
					i++;
			}
			return true;
		}
		else
			return false;
	}

	void MainLoop2(){
		IO->read(&(buf[0]));
		while (CmpDoDict(DL->Korzen,buf))
		{
			if(Storage->LengthOfDict < 65535){
				Storage->LengthOfDict++;
				Storage->Length[Storage->LengthOfDict] = help2 + 1;
				Storage->Repeat[Storage->LengthOfDict] = 0;
				DL->WstawNoweSlowo(buf,help2 + 1,Storage->LengthOfDict);
			}
			IlePetliMainLoop++;
			//if(IlePetliMainLoop == 65535)
				//system("pause");
			IO->Write(&help1);
			Storage->Repeat[help1]++;
			buf[0] = buf[help2];
		}

	}

	void MainLoop(){
		IO->read(&(buf[0]));
		while (CompareToDict(0,buf,0))
		{
			if(Storage->LengthOfDict < 65535){
				Storage->LengthOfDict++;
				Storage->dict[Storage->LengthOfDict] = new char[help2 + 1];
				Storage->Length[Storage->LengthOfDict] = help2 + 1;
				Storage->Repeat[Storage->LengthOfDict] = 0;
				for (int i = 0; i < help2 + 1; i++)
					Storage->dict[Storage->LengthOfDict][i] = buf[i];
				//Storage.LengthOfDict++;	
			}
			IO->Write(&help1);
			Storage->Repeat[help1]++;
			buf[0] = buf[help2];
		}

	}
public:
	LZW(string a, string b){
		IO = new InOut(a,b);
		Storage = new LZWStorage();
		buf = new char[3000];
		DL = new DrzewoL();
		help1 = 0;
		help2 = 0;
		IlePetliMainLoop = 0;
		MainLoop2();

	}

};

#endif