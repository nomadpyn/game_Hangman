#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<windows.h>
#include<time.h>
#include<string.h>
#include"func.h"

using namespace std;

void main() {
// открытие файла для чтения	
	FILE* f = fopen("words_eng.txt", "rb");
	
	if (f == 0)	{
		perror("Open");
		return;
	}

	srand(time(0));
	char Word[20];

	if (!loadWord(f, Word))	{
		cout << "Error !!!" << endl;
		fclose(f);
		return;
	}
	char answer;
	do
	{
		Game(Word);
		if (Tries == 0)
		{
			cout << "Count of words: " << CountWords << endl;
			cout << "Bye-bye" << endl;
			break;
		}
		cout << "Continue ??? (Y/N)\t";
		cin >> answer;
		if (answer == 'Y' || answer == 'y')
			if (!loadWord(f, Word))
			{
				cout << "Error !!!" << endl;
				fclose(f);
				return;
			}
	} while (answer == 'Y' || answer == 'y');

	int hFile = _fileno(f);

	int size = _filelength(hFile);

	fseek(f, 0, 0);

	_locking(hFile, _LK_UNLCK, size);

	fclose(f);	
}