#include <iostream>
#include <cstdlib>
#include <time.h>
#include<string>
#include <windows.h>
using namespace std;

bool isNumeric(string const& str)
{
	auto it = str.begin();
	while (it != str.end() && isdigit(*it)) {
		it++;
	}
	return !str.empty() && it == str.end();
}

string check(string const& selected, string const& input) {
	int ball = 0;
	int strake = 0;
	int out = 0;
	for (int i = 0; i < input.length(); i++) {
		if (selected.find(input.at(i)) != string::npos) {
			if (selected.at(i) == input.at(i)) {
				strake++;
			}
			else {
				ball++;
			}
		} else {
			out++;
		}
	}
	if (strake == 4) {
		return "FIND SUCCESS";
	}
	else {
		return ("Ball : " + to_string(ball) + " Strake : " + to_string(strake) + " out : " + to_string(out));
	}

}
bool isDuplication(string const& str) {
	string tmp = "";
	for (int i = 0; i < str.length(); i++) {
		if (tmp.find(str.at(i)) != string::npos) {
			return true;
		}
		tmp += str.at(i);
	}
	return false;

}

int main() {
	cout << "==숫자 야구게임 (종료는 q 입력, 화면 클리어 clear 입력)==" << endl;
	

	srand(time(NULL));
	int a = rand()%10;
	string select = to_string(a);
	for (int i = 0; i < 3; i++) {
		a = rand() % 10;
		while (select.find(to_string(a)) != string::npos) {
			a = rand() % 10;
		}
		select += to_string(a);
	}

	cout << "정답 : " << select << endl;

	string result = "";

	

	while (result != "FIND SUCCESS") {
		cout << "중복없이 4숫자 입력> ";
		string input;
		cin >> input;
		if (input == "clear") {
			system("cls");
			cout << "==숫자 야구게임 (종료는 q 입력, 화면 클리어 clear 입력)==" << endl;
			continue;
		}
		while ((!isNumeric(input) || input.length() != 4 || isDuplication(input)) && _stricmp("q", input.c_str())) {
			cout << "잘못된 인풋" << endl;
			cout << "입력 > ";
			cin >> input;
		}

		if (!_stricmp("q", input.c_str())) {
			cout << "종료합니다.";
			return 0;
		}

		result = check(select, input);
		cout << result << endl;

	}
	
	return 0;
}