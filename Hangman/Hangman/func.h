#pragma once
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <time.h>
#include <sys\locking.h>
#include <string.h>
#include <ctype.h>
#define max_length 21

//функция загрузки слова из файла words.txt
bool loadWord(FILE * file, char* word) {
	int i = 0;
	char s[max_length]{ 0 };
	static int count = -1;
// подсчет количества слов в файле
	if (count == -1) {
		while (!feof(file)) {
			fgets(s, max_length, file);
			count++;
		}
		if (count == 0)
			return false;
		fseek(file, 0, 0);
	}
// выбираем случайное слово для игры
	int r = rand() % count;
	while (i <= r) {
		fgets(s, max_length, file);
		i++;
	}
// определяем длину слова и копируем его
	int wordlen = strlen(s);
	if (s[wordlen - 1] == 10)
		s[wordlen - 2] = 0;
	strcpy(word, s);
// блокировка файла
	int hFile = _fileno(file);
	int size = _filelength(hFile);
	fseek(file, 0, 0);
	_locking(hFile, _LK_NBLCK, size);

	return true;

}
