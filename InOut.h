#ifndef INOUT
#define INOUT
#include <fstream>
#include <string>

using namespace std;
class InOut{
	friend class LZW;
private:
	ifstream *ifs;
	ofstream *ofs;

public:
	InOut(){};
	InOut(string a, string b){

		ifs = new ifstream(a,ifstream::binary);		//otwiera plik do odczytu
		ofs = new ofstream(b,ofstream::trunc | ofstream::binary);	//tworzy plik, jesli taki istnieje, to go czysci
	};

	//metoda wczytuj¹ca znak i zwracajaca false, jesli koniec pliku


	//metoda zapisujaca znak
	void Write(unsigned short *t){
		/*char t1[4];
		t1[0] = *t & 0x000000ff;
		t1[1] = *t & 0x0000ff00;
		t1[2] = *t & 0x00ff0000;
		t1[3] = *t & 0xff000000;*/

		ofs->write((char *)t,2);
	}

	void Write(char *t, int length){
		ofs->write(t,sizeof(char)*length);
	}

	bool read(char *t){	

		if(!ifs->fail()){
			ifs->get(*t);
			return true;
		}else
			return false;
	}

	bool read(unsigned short *t){	
		ifs->read((char *)t,2);
		if(!ifs->fail()){
			return true;
		}else
			return false;
	};

};

#endif