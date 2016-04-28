#include <iostream>
#define M 10
using namespace std;

typedef unsigned int hashType;

struct Data {
	char * firstName;
	char * lastName;
	int age;
	hashType hash;
};
Data * EMPTY = new Data{" ", " ", -1, 0};

hashType getHash(Data * data) {
	int waga = 65599, sum = 0;
	for (int i = 0; data->firstName[i] != 0; i++)
		sum = sum * waga + data->firstName[i];
	for (int i = 0; data->lastName[i] != 0; i++)
		sum = sum * waga + data->lastName[i];
	return sum*waga + data->age;
}

bool insert(Data * arr[], Data * data) {
	hashType h = getHash(data);
	hashType start = h % M;

	if (arr[start] == NULL || arr[start] == EMPTY) {
		data->hash = h;
		arr[start] = data;
		return true;
	}

	int i = start + 1;
	while (i != M) {
		if (arr[i] == NULL || arr[start] == EMPTY) {
			data->hash = h;
			arr[i] = data;
			return true;
		}
		i = (i + 1) % M;
	}
	return false; // przepe³nienie
}

int cmp(Data * data1, Data * data2) {
	int i = 0;
	while (data1->firstName[i] != 0 || data2->firstName[i] != 0) {
		if (data1->firstName[i] != data2->firstName[i]) return 0;
		i++;
	}
	i = 0;
	while (data1->lastName[i] != 0 || data2->lastName[i] != 0) {
		if (data1->lastName[i] != data2->lastName[i]) return 0;
		i++;
	}
	return (int) (data1->age == data2->age);
}

int search(Data * arr[], Data * el) {
	hashType h = getHash(el);

	for (int i = 0; i < M; i++) {
		int ind = (h + i) % M;
		if (arr[ind] == NULL) break;
		if (arr[ind]->hash != h) continue;
		if (cmp(arr[ind], el)) return ind;
	}
	return -1;
}

void remove(Data * arr[], Data * el) {
	int ind = search(arr, el);
	if (ind == -1) return;
	Data * tmp = arr[ind];
	delete tmp;
	arr[ind] = EMPTY;
}

void show(Data * arr[]) {
	for (int i = 0; i < M; i++) {
		if (arr[i] != NULL && arr[i] != EMPTY) {
			cout << arr[i]->firstName << " " << arr[i]->lastName << endl;
			cout << "age: " << arr[i]->age << endl;
			cout << "hash: "<< arr[i]->hash << endl;
		}
	}
}

int main() {
	Data * arr[M];
	memset(arr, NULL, sizeof(int*) * (M));

	Data * a = new Data{ "Damian" , "Robins", 21 };
	Data * b = new Data{ "Lola" , "Dekl", 22 };
	Data * c = new Data{ "Marek" , "Holas", 33 };
	insert(arr, a);
	insert(arr, b);
	insert(arr, c);

	Data * d = new Data{ "Rob" , "Holas", 43 };
	cout << search(arr, b) << endl;
	cout << search(arr, d) << endl;

	Data * e = new Data{ "Damia" , "Robins", 21 };
	cout << cmp(a, e) << endl;

	cout << endl;
	show(arr);
	cout << endl;

	remove(arr, b);
	insert(arr, e);
	cout << search(arr, e) << endl;
	b = new Data{ "Lola" , "Dekl", 22 };
	cout << search(arr, b) << endl;

	cout << endl;
	show(arr);
	cout << endl;

	insert(arr, b);

	cout << endl;
	show(arr);
	

	system("pause");
	return 0;
}