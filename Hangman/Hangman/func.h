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
#include<chrono>
#define max_length 21

using namespace std;
// переменные для количества попыток и количества угаданных слов
int Tries{ 10 };
int CountWords{ 0 };

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
// функция начала игры
void Game(char* word) {
// переводим слово в верхний регистры
	_strupr(word);
	int l = strlen(word);
// строка копия для отображения
	char* copy = new char[l + 1];
	memset(copy, '*', l);
	copy[l] = 0;
//	алфавит для отображения в консоли
	char letters[52]{};
	int i{}, j{};
	for (i = 0; i < 26; i++) {
		letters[j++] = i + 'A';
		letters[j++] = ' ';
	}
	letters[51] = 0;

	int fails{ 0 };
	char letter;
	char* pos;
	bool replace = false;
	auto start = chrono::steady_clock::now();
	do {
		
		system("cls");
		cout << copy << endl << endl;
		cout << letters << endl << endl;
		cout << "Count of tries: " << Tries << endl
			<< endl;
		cout << "Input any letter:\t";
		cin >> letter;
// проверка нажата ли буква
		if (!isalpha(letter)) {
			cout << "It's not a letter" << endl;
			Sleep(1000);
			continue;
		}
		letter = toupper(letter);
// поиск буквы в алфавите		
		pos = strchr(letters, letter);

		if (pos == 0)
		{
			cout << "This letter have been already pressed" << endl;
			Sleep(1000);
			continue;
		}
		else
		{
			pos[0] = ' ';
		}
// поиск буквы в загаданном слове
		for (i = 0; i < l; i++)
		{
			if (word[i] == letter)
			{
				copy[i] = letter;
				replace = true;
			}
		}
		if (replace == false) {
			Tries--;
			fails++;
		}
		else
			replace = false;

		auto end = chrono::steady_clock::now();
// вывод при победе на экран
		if (strcmp(word, copy) == 0)
		{
			system("cls");
			cout << copy << endl << endl;
			cout << "Count of fails: " << fails << " from 10\n";
			cout << "Time in game " << chrono::duration_cast<chrono::seconds>(end - start).count() << " sec\n";
			cout << "Congratulation !!!" << endl;
			CountWords++;
			break;
		}
		
		
	}
	while(Tries != 0);
	delete[] copy;
}