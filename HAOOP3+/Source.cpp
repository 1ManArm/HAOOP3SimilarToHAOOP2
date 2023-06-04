#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <windows.h>
#include "Reservoir.h"
#include <fstream>
#include <conio.h>

//Задание 1:
class People {
private:
	int countid;
	char* Fio;
public:
	People();
	People(int _countid, const char* _fio);

	People(const People& obj);

	~People();

	inline void ShowPeople(int countpeople, People* p);
};

class Flat {
private:
	int* flat_number;
	People* PeopleFlat;
public:
	Flat();
	Flat(int _f, int countflat, People* p);

	void initFlat(int countflat, People* p);

	void ShowFlat(int countflat, int countpeople, People* p);

	Flat(const Flat& obj);

	~Flat();
};

class House {
private:
	int house_number;
	Flat* HouseFlat;
public:
	House();
	House(int _h, Flat* _f);

	void init(int _h, int countflat, Flat* f);
	void ShowHouse(int countflat, int countpeople, People* p);

	House(const House& obj);

	~House();
};

People::People() {
	countid = 0;
	Fio = new char[7] { "NoName" };
}

People::People(int _countid, const char* _fio) {
	int count_fio;
	count_fio = strlen(_fio);

	Fio = new char[count_fio + 1];

	countid = _countid;
	strcpy(Fio, _fio);
}

People::People(const People& obj) {
	int count_fio, countid;
	count_fio = strlen(obj.Fio);

	countid = obj.countid;

	Fio = new char[count_fio + 1];
	strcpy(Fio, obj.Fio);
}

People::~People() {
	delete[]Fio;
}

inline void People::ShowPeople(int countpeople, People* p) {
	std::cout << "ФИО жильцов: \n";

	for (size_t i = 0; i < countpeople; i++) {
		std::cout << p[i].Fio << std::endl;
	}
}

Flat::Flat() {
	flat_number = 0;
	PeopleFlat = 0;
}

Flat::Flat(int _f, int countflat, People* p) {
	flat_number[countflat] = _f;
	PeopleFlat = p;
}

void Flat::initFlat(int countflat, People* p) {
	flat_number = new int[countflat] { 7, 8, 9 };
	PeopleFlat = p;
}

void Flat::ShowFlat(int countflat, int countpeople, People* p) {
	std::cout << "Номера жилых квартир: ";
	for (size_t i = 0; i < countflat; i++)
	{
		std::cout << Flat::flat_number[i];
		if (i != countflat - 1)
			std::cout << ", ";
		else
			std::cout << ".";
	}
	std::cout << std::endl;
	PeopleFlat->ShowPeople(countpeople, p);
}

Flat::Flat(const Flat& obj) {
	flat_number = obj.flat_number;
	PeopleFlat = obj.PeopleFlat;
}

Flat::~Flat() {
	delete[]flat_number;
	delete[]PeopleFlat;
}

House::House() {
	house_number = 0;
	HouseFlat = 0;
}

House::House(int _h, Flat* _f) {
	house_number = _h;
	HouseFlat = _f;
}

void House::init(int _h, int countflat, Flat* f) {
	this->house_number = _h;
	HouseFlat = f;
}

void House::ShowHouse(int countflat, int countpeople, People* p) {
	std::cout << "Номер дома: " << house_number << std::endl;
	HouseFlat->ShowFlat(countflat, countpeople, p);
}

House::House(const House& obj) {
	house_number = obj.house_number;
	HouseFlat = obj.HouseFlat;
}

House::~House() {
	delete[] HouseFlat;
}
//Задание 2
void ShowAllInfo(Reservoir*& reservoir, int size) {
	if (size == 0) return;
	std::cout << "\n================================КОЛИЧЕСТВО ВОДОЕМОВ [" << size << "]=========================================\n\n";
	for (int i = 0; i < size; i++) {
		std::cout << i + 1 << ". ";
		reservoir[i].ShowAllParams();
		std::cout << std::endl;
	}
	std::cout << "\n================================================================================================\n";
}

void FindResevoir(Reservoir*& reservoir, int size, int index) {
	if (size == 0) return;
	int count = 1;
	for (int i = 0; i < size; i++) {
		if (reservoir[i].GetTypeIndex() == index) {
			std::cout << count++ << ". ";
			reservoir[i].ShowAllParams();
			std::cout << std::endl;
		}
	}
}

void AddReservoir(Reservoir*& reservoir, int& size) {
	Reservoir r;
	std::string name;
	int h;
	r.SetType();
	std::cin.clear();
	std::cin.ignore();

	do {
		std::cout << "\nИмя водоема: ";
		std::cin >> name;
	} while (!r.SetName(name));

	do {
		std::cout << "\nДлина водоема:";
		std::cin >> h;
		std::cin.clear();
		std::cin.ignore();
	} while (!r.SetHeight(h));

	do {
		std::cout << "\nШирина водоема:";
		std::cin >> h;
		std::cin.clear();
		std::cin.ignore();
	} while (!r.SetWidth(h));

	do {
		std::cout << "\nГлубина водоема:";
		std::cin >> h;
		std::cin.clear();
		std::cin.ignore();
	} while (!r.SetMaxDepth(h));
	Reservoir* tmp = new Reservoir[size + 1];

	for (int i = 0; i < size; i++) {
		tmp[i] = reservoir[i];
	}
	tmp[size] = r;
	delete[] reservoir;
	size++;
	reservoir = tmp;
	system("cls");
}

void RemoveReservoir(Reservoir*& reservoir, int& size) {
	bool check = false;
	if (size == 0 or reservoir == nullptr) return;
	std::string name;
	std::cout << "\nИмя водоема для удаления: ";
	std::cin >> name;
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (reservoir[i].GetName() == name) {
			check = true;
		}
	}
	if (check) {
		Reservoir* tmp = new Reservoir[size - 1];
		for (int i = 0; i < size; i++) {
			if (reservoir[i].GetName() == name) continue;
			tmp[count++] = reservoir[i];
		}
		delete[] reservoir;
		size--;
		reservoir = tmp;
	}
	system("cls");
}

void Save(Reservoir*& reservoir, int& size) {
	Reservoir r;
	std::string name = r.GetFileName();
	std::ofstream save(name, std::ios::binary);
	save.write((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		reservoir[i].Save(save);
	}
	save.close();
}

void Load(Reservoir*& reservoir, int& size) {
	Reservoir r;
	int a;
	std::string name = r.GetFileName();
	std::ifstream load(name, std::ios::binary);
	load.read((char*)&a, sizeof(int));
	if (size > 0) delete[] reservoir;
	reservoir = new Reservoir[a];
	for (int i = 0; i < a; i++) {
		reservoir[i].Load(load);
	}
	size = a;
	load.close();
}

void CheckTypes(const Reservoir* reservoir, const int size) {
	if (size == 0) return;
	std::string name, name2;
	std::string tmp = "1", tmp2 = "11";
	int count = 0;
	std::cout << "\nВведите имя 1 водоема для проверки их типов: ";
	std::cin >> name;
	std::cout << "\nВведите имя 2 водоема для проверки их типов: ";
	std::cin >> name2;
	for (int i = 0; i < size; i++) {
		if (reservoir[i].GetName() == name) {
			tmp = reservoir[i].GetType();
		}
		if (reservoir[i].GetName() == name2) {
			tmp2 = reservoir[i].GetType();
		}
	}
	if (tmp == tmp2) {
		std::cout << "\nУ водоемов одинаковый тип!\n";
	}
	else std::cout << "\nВодоемы разных типов!";
}



int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//Задание 1:

	int countid = 1;

	int countpeople = 3;

	int counhouse = 1;

	int countflat = 3;

	People* p = new People[countpeople]{
		{countid++, "Никулин Анатолий Владимирович"},
		{countid++, "Александров Евгений Втальевич"},
		{countid++, "Горобец Владимир Степанович"}
	};

	std::cout << std::endl;
	std::cout << "-------------------";
	std::cout << std::endl;

	Flat f;

	f.initFlat(countflat, p);

	House ha;
	ha.init(20, countflat, &f);

	ha.ShowHouse(countflat, countpeople, p);

	std::cout << std::endl;

	system("pause");

	//Задание 2:

	setlocale(LC_ALL, "");
	int size = 0;
	std::string n, name;
	int h;
	Reservoir* reservoir = new Reservoir[size];
	char choice;
	while (true) {
		do {
			std::cout << "\n1. Показать все водоемы";
			std::cout << "\n2. Показать все водоемы одного типа";
			std::cout << "\n3. Добавить водоем";
			std::cout << "\n4. Удалить водоем";
			std::cout << "\n5. Проверить совместимость типов водоемов";
			std::cout << "\n6. Сохранить в файл";
			std::cout << "\n7. Загрузить из файла";
			choice = _getch();
		} while (choice < 0 and choice > 7);

		switch (choice) {
		case '1': system("cls");  ShowAllInfo(reservoir, size); break;
		case '2': system("cls");
			do {
				std::cout << "\n1. Океан \n2. Море \n3. Озеро \n4. Пруд";
				choice = _getch();
			} while (choice < 0 and choice > 4);
			h = choice - 48;
			system("cls");
			FindResevoir(reservoir, size, h);
			break;
		case '3':
			system("cls");
			AddReservoir(reservoir, size);
			break;
		case '4':
			system("cls");
			RemoveReservoir(reservoir, size);
			break;
		case '5':
			system("cls");
			CheckTypes(reservoir, size);
			break;
		case '6':
			system("cls");
			Save(reservoir, size);
			break;
		case '7':
			system("cls");
			Load(reservoir, size);
			break;
		}
	}
	return 0;
}