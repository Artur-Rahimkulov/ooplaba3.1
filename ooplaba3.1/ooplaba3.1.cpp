#include <iostream>
#include <ctime>
using namespace std;

class Item {// базовый класс
public:
	virtual void showName() {
		printf("Item\n");
	}
	virtual~Item() {
	}
};

class Point : public Item {//класс наследник от класса Thing
private:
	int x;
	int y;
public:
	Point() {
		x = 0;
		y = 0;
	}

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	Point(const Point& t) {
		x = t.x;
		y = t.y;
	}

	void showName() {//метод, показывающий название класса
		printf("Point\n");
	}
	~Point() {
	}
};

class ColoredPoint : public Item {//другой класс наследник от класса Thing
private:
	int x;
	int y;
	int color;
public:
	ColoredPoint() {
		x = 0;
		y = 0;
		color = 0;
	}

	ColoredPoint(int x, int y, int color) {
		this->x = x;
		this->y = y;
		this->color = color;
	}

	ColoredPoint(const ColoredPoint& c) {
		x = c.x;
		y = c.y;
		color = c.color;
	}
	~ColoredPoint() {

	}

	void showName() {//метод, показывающий название класса
		printf("ColoredPoint\n");
	}
};

class MyStorage {//класс хранилище
private:
	int size;//размер массива
	Item** storage;//массив указателей
public:

	MyStorage() {
		size = 0;
	}

	MyStorage(int i) {
		size = i;
		storage = new Item * [size];
	}

	void setObject(int i, Item* newObject) {
		storage[i] = newObject;
	}

	void addObject(Item* newObject) {//добавляет объект в массив
		Item** storage2 = new Item * [size + 1];
		if (size != 0) {
			for (int j = 0; j < size; j++) {
				storage2[j] = storage[j];
			}
			delete[] storage;
		}
		storage = storage2;
		storage[size] = newObject;
		size = size + 1;
	}


	Item& getObject(int i) {
		return *storage[i];
	}

	int getCount() {//возвращает размер массива
		return size;
	}


	void deleteObject(int i) {
		storage[i] = nullptr;
	}

	void removeObject(int i) {//удаляет объект из массива
		if (size != 0 && i < size && size != 1) {
			Item** storage2 = new Item * [size - 1];
			for (int j = 0; j < i; j++) {
				storage2[j] = storage[j];
			}
			for (int j = i; j < size - 1; j++) {
				storage2[j] = storage[j + 1];
			}
			delete storage[i];
			delete[] storage;
			size = size - 1;
			storage = storage2;
		}
		else if (size == 1) {
			storage[0] = nullptr;
			size = 0;
		}



	}

	void showNameObject(int i) {//вызывает showName у определенного объекта
		if (size != 0 && size > i)
			storage[i]->showName();
	}

	void showNameStorage() {//вызывает showName у всех объектов
		if (size != 0) {
			for (int i = 0; i < size; i++) {
				storage[i]->showName();
			}
		}
	}

	~MyStorage() {
		for (int i = 0; i < size; i++) {
			delete storage[i];
		}
		delete[] storage;
	}
};

void cycle(MyStorage& storage, int max) {//цикл, который позволяет повторить несколько действии 100, 1000, 10000 раз
	unsigned int s = clock();
	printf("\n\n");
	for (int i = 0; i < max; i++) {
		int a = rand() % 3;
		int b;
		if (storage.getCount() != 0) {
			b = rand() % storage.getCount();
		}
		else {
			b = 0;
		}

		int k = rand() % 2;
		switch (a) {
		case 0:
			if (k == 0)
				storage.addObject(new Point);
			else
				storage.addObject(new ColoredPoint);

			printf("addObject\n");
			break;
		case 1:
			storage.removeObject(b);
			printf("removeObject\n");
			break;
		case 2:
			storage.showNameObject(b);
			break;
		}
	}
	unsigned int e = clock();
	unsigned int time = e - s;
	printf("\nВремя: %d миллисекунд\n", time);
	printf("Количество объектов: %d\n", storage.getCount());
}

int main()
{

	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	MyStorage storage(100);
	for (int i = 0; i < storage.getCount(); i++) {
		int a = rand() % 2;
		if (a == 0) {
			storage.setObject(i, new ColoredPoint());
		}
		else {
			storage.setObject(i, new Point());
		}
	}

	cycle(storage, 100);
	printf("\n\n");
	system("pause");
	cycle(storage, 1000);
	printf("\n\n");
	system("pause");
	cycle(storage, 10000);
	printf("\n\n");
	system("pause");


}