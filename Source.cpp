#include <iostream>
#include "LZW.h"
#include "DecompressionLZW.h"
#include <algorithm>
#include <fstream>

using namespace std;

int main(){
	int s;
	cin >> s;
	if(s == 1){
		LZW *l = new LZW("pdf.pdf","przyklad2");
		sort(l->Storage->Repeat,l->Storage->Repeat + l->Storage->LengthOfDict);
		ofstream *ofs;
		ofs = new ofstream("statystyka.txt",ofstream::trunc);
		for(int i = 0; i < l->Storage->LengthOfDict;i++)
			*ofs << (int)(l->Storage->Repeat[i]) << " ";
	} else if(s == 0)
	{
		DLZW *l = new DLZW("przyklad2","FPI1.pdf");
	}
	else if(s == 2){
		ofstream *ofs = new ofstream("np",ofstream::trunc | ofstream::binary);
		int t = 5;
		ofs->write((char *)(&t),4);
		t = 10;
		ofs->close();
		ifstream *ifs = new ifstream("np",ifstream::binary);
		ifs->read((char *)(&t),4);
		cout << t;
		system("pause");
	}
	else if(s == 3)
	{
		unsigned short *R = new unsigned short[10];
		for (int i = 0; i < 10; i++)
		{
			R[i] = 500 - i;
		}
	sort(R,R + 10);
	for (int i = 0; i < 10; i++)
	{
		cout << R[i] << " ";
	}
	}
	return 0;
}