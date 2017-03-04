#ifndef DRZEWOLEKSYKOGRAFICZNE
#define DRZEWOLEKSYKOGRAFICZNE

using namespace std;

struct Wezel{
		unsigned short Indeks;
		unsigned char Glebokosc;
		Wezel *Rodzic;
		Wezel * Wsk[256];
		Wezel(Wezel * K, unsigned short I){
			if(K != nullptr)
			Glebokosc = K->Glebokosc + 1;
			Rodzic = K;
			Indeks = I;
			for (int i = 0; i < 256; i++)
			{
				Wsk[i] = nullptr;
			}
		}
	};

class DrzewoL{
public:
	
	Wezel *Korzen;

	void DodajElement(Wezel * K, unsigned short I, unsigned char Indeks){
		K->Wsk[(int)Indeks] = new Wezel(K,I);
	};

	void WstawNoweSlowo(char * b, int length,unsigned short I){
		Wezel *K = Korzen;
		for (int i = 0; i < length - 1; i++)
			K = K->Wsk[(unsigned char)b[i]];
		K->Wsk[(unsigned char)b[length - 1]] = new Wezel(K,I);
	}

	DrzewoL(){
		Korzen = new Wezel(nullptr,0);
		Korzen->Glebokosc = 0;
		for (int i = 0; i < 256; i++)
		{
			Korzen->Wsk[i] = new Wezel(Korzen,i);
		}
	}

};
#endif