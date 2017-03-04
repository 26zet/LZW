#ifndef lzwstorage
#define lzwstorage
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class LZWStorage{

	friend class LZW;
public:
	char * dict[65536];
	unsigned char Length[65536];
	unsigned short Repeat[65536];
	unsigned int LengthOfDict;

public:
	LZWStorage(){

		for (int i = 0; i < 256; i++){
			dict[i] = new char[1];
			dict[i][0] = (char)i;
			Length[i] = 1;
			Repeat[i] = 0;
		}
		for(int i = 256; i < 65536; i++)
			Repeat[i] = 0;
		LengthOfDict = 255;
	}

	void AddToDict(char * t, unsigned char i){
		dict[LengthOfDict] = t;
		Length[LengthOfDict] = i;
		LengthOfDict++;
	}

	short ReturnLengthOfDict(){return LengthOfDict;};

};

#endif