#ifndef dlzw
#define dlzw
#include <string>
#include "LZWStorage.h"
#include "InOut.h"

class DLZW{
public:
	InOut *IO;
	LZWStorage *Storage;

	void MainLoop(){
		unsigned short t1,t2;
		IO->read(&t1);
		IO->Write(Storage->dict[t1],Storage->Length[t1]);
		Storage->LengthOfDict++;
		while(IO->read(&t2)){
			if(Storage->LengthOfDict < 65536){
				Storage->dict[Storage->LengthOfDict] = new char[Storage->Length[t1] + 1];
				for (int i = 0; i < Storage->Length[t1]; i++)
					Storage->dict[Storage->LengthOfDict][i] = Storage->dict[t1][i];
				Storage->dict[Storage->LengthOfDict][Storage->Length[t1]] = Storage->dict[t2][0];
				Storage->Length[Storage->LengthOfDict] = Storage->Length[t1] + 1;
				Storage->LengthOfDict++;
			}
			IO->Write(Storage->dict[t2],Storage->Length[t2]);

			t1 = t2;
		}
	}

public:
	DLZW(string a, string b){
		IO = new InOut(a,b);
		Storage = new LZWStorage();
		MainLoop();
	}
};

#endif