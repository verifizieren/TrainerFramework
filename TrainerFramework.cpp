#include "pch.h"
#include "menu.h"


void MyMenu() {
	Menu test;

	bool bool1 = true;
	bool bool2 = false;
	float float1 = 5.2;
	int int1 = 6;

	test.Header("Test", "x32", "1.0.0");
	test.BoolFeat("Test bool 1", bool1);
	test.BoolFeat("Test bool 2", bool2);
	test.IntFeat("Test int", int1);
	test.FloatFeat("Test float", float1);
}


int main() {
	while (true) {
		MyMenu();
		Sleep(900);
		system("cls");
	}
}