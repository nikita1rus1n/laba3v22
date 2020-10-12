#include <iostream>
#include <time.h>
#include <cstring>
#include <string>
#include <locale.h>
#include <Windows.h>
using namespace std;

class MyClass {
	char* str;
	int length = 0;
public:
	MyClass() { // конструктор по умол.
		string dstr = "default";

		length = dstr.length();

		str = new char[length];
		for (int i = 0; i < length; i++) {
			*(str + i) = dstr[i];
		}
	}
	MyClass(string str1) { // конструктор иницил.
		length = str1.length();
		str = new char[length];
		for (int i = 0; i < length; i++) {
			*(str + i) = str1[i];
		}

	}
	MyClass(const MyClass& st) { // конструктор копиров.
		length = st.length;
		str = new char[length];
		for (int i = 0; i < st.length; i++) {
			*(str + i) = st.str[i];
		}

	}


	MyClass operator+=(const MyClass& st) { // сложение строк  
		char* strtemp;
		strtemp = new char[length];
		for (int i = 0; i < length; i++) {
			*(strtemp + i) = *(str + i);
		}
		delete[]str;
		str = new char[st.length + length];
		for (int i = 0; i < length; i++) {
			*(str + i) = *(strtemp + i);
		}
		for (int i = 0; i < st.length; i++) {
			*(str + i + length) = *(st.str + i);
		}

		length = st.length + length;
		delete[]strtemp;
		return (*this);
	}



	void set() { // изменение строки
		string setstr;
		cin >> setstr;
		delete[]str;

		length = setstr.length();

		str = new char[length];
		for (int i = 0; i < length; i++) {
			*(str + i) = setstr[i];
		}

	}
	void pr() { // вывод строки на экран

		for (int i = 0; i < length; i++) {
			cout << *(str + i);
		}
		cout << endl;
	}

	void prpodstr(int podlength) { // вывод строки на экран
		if (podlength <= length) {
			for (int i = 0; i < podlength; i++) {
				cout << *(str + i);
			}
		}
		else { cout << "Длина подстроки больше длины строки!"; }


		cout << endl;
	}

	void sort() { // сортировка пузырьком по возрастанию
		char temp;
		for (int i = 0; i < length - 1; i++) {
			for (int j = 0; j < length - 1 - i; j++) {
				if (int(*(str + j)) > int(*(str + j + 1))) {
					temp = *(str + j + 1);
					*(str + j + 1) = *(str + j);
					*(str + j) = temp;
				}
			}
		}
	}

	~MyClass() {
		delete[]str;

	}
	friend MyClass operator+ (MyClass& st, MyClass& st2); // дружественные функции-операторы (бинарные арифметические (+ и - ))
	friend MyClass operator+ (MyClass& st, string st1);
	friend int operator- (MyClass& st, MyClass& st2);
	friend int operator- (MyClass& st, string st1);
};

MyClass operator+(MyClass& st, MyClass& st2) { // бинарный арифметический + (операнд объект объект)
	MyClass strtemp;
	delete[]strtemp.str;
	strtemp.length = st.length + st2.length;
	strtemp.str = new char[strtemp.length];

	for (int i = 0; i < st.length; i++) {
		*(strtemp.str + i) = *(st.str + i);
	}
	for (int i = 0; i < st2.length; i++) {
		*(strtemp.str + i + st.length) = *(st2.str + i);
	}


	return strtemp;
};

MyClass operator+(MyClass& st, string st1) { // бинарный арифметический +  (операнды объект строка)
	MyClass strtemp;
	delete[]strtemp.str;
	strtemp.length = st.length + st1.length();
	strtemp.str = new char[strtemp.length];

	for (int i = 0; i < st.length; i++) {
		*(strtemp.str + i) = *(st.str + i);
	}
	for (int i = 0; i < st1.length(); i++) {
		*(strtemp.str + i + st.length) = st1[i];
	}


	return strtemp;
}

int operator-(MyClass& st, MyClass& st2) { // бинарный арифметический - (разность длин строк)
	int length;
	if (st.length < st2.length) {
		length = st2.length - st.length;
	}
	else length = st.length - st2.length;
	return length;
}

int operator-(MyClass& st, string st1) { // бинарный арифметический - (разность длин строк)
	int length;
	if (st.length < st1.length()) {
		length = st1.length() - st.length;
	}
	else length = st.length - st1.length();
	return length;
}
int main() {
	system("chcp 1251");
	system("CLS");
	setlocale(LC_ALL, "Russian");
	int length, podlength;

	MyClass str1("test ");
	cout << "str1:" << endl;
	str1.pr();
	MyClass str2("iq");
	cout << "str2:" << endl;
	str2.pr();

	cout << "Введите длинну подстроки: ";
	cin >> podlength;

	str1 += str2;
	cout << "str1+=str2:" << endl;
	str1.pr();
	cout << "Подстрока:" << endl;
	str1.prpodstr(podlength); // вывод подстроки

	MyClass str3(str2); // конструктор копиров.
	cout << "str3(str3=str2):" << endl;
	str3.pr();


	cout << "str3=";
	str3.set(); // изменение строки

	cout << "sort str3:" << endl;
	str3.sort(); // сортировка
	str3.pr();

	MyClass str4 = str1 + str2; //  перегрузка дружественной функции    (разные типы операндов объект) 
	cout << "str4=str1+str2:" << endl;
	str4.pr();

	MyClass str5("str5");
	MyClass str6 = str1 + str5;
	cout << "str1 + str5:" << endl;
	str6.pr();
	MyClass str7 = str5 + "STR"; // разные типы операндов (строка)
	cout << "str5 + \"STR\":" << endl;
	str7.pr();


	length = str1 - str2;										// разные типы операндов (объект)
	cout << "str1.length-str2.length:" << length << endl;
	length = str1 - "bbbb";										// разные типы операндов (строка)
	cout << "str1.length-\"bbbb\".length():" << length << endl;


	MyClass* strm;
	strm = new MyClass[3];
	for (int i = 0; i < 3; i++) {
		cout << "Введите strm [" << i << "]" << endl;
		strm[i].set();
	}

	for (int i = 0; i < 3; i++) {
		cout << "strm [" << i << "]:" << endl;
		strm[i].pr();
	}

	delete[]strm;
	return 0;
}