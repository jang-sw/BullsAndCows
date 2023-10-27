#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <windows.h>
#include <vector>
#include <sstream>
#include "game.h"


using namespace std;

int main() {
	cout << "==숫자 야구게임 (종료는 q 입력, 화면 클리어 clear 입력)==" << endl;
	cout << "중복없는 당신의 4자리 숫자를 입력하세요 >";
	string playerInput;

	cin >> playerInput;
	while ((playerInput == "clear" || !isNumeric(playerInput) || playerInput.length() != 4 || isDuplication(playerInput)) && _stricmp("q", playerInput.c_str())) {
		
		if (playerInput == "clear") {
			system("cls");
			cout << "==숫자 야구게임 (종료는 q 입력, 화면 클리어 clear 입력)==" << endl;
			cout << "중복없는 당신의 4자리 숫자를 입력하세요 > ";
			cin >> playerInput;
		}
		else {
			cout << "잘못된 인풋" << endl;
			cout << "입력 > ";
			cin >> playerInput;
		}
	}
	if (!_stricmp("q", playerInput.c_str())) {
		cout << "종료합니다.";
		return 0;
	}

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

	vector<int> pcPredict = {0,1,2,3,4,5,6,7,8,9};
	string removed = "";

	string result = "";
	 
	

	while (result != "FIND SUCCESS") {
		cout << "당신의 차례 :: 중복없이 4숫자 입력 > ";
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
			cout << "정답 : " << select << endl;
			return 0;
		}

		result = check(select, input);
		if (result != "FIND SUCCESS") {
			cout << "PLAYER : " << split(result, ',')[0] << " ball,  " << split(result, ',')[1] << " Strake,  " << split(result, ',')[2] << " out" << endl;

			string pcNum = getPcNum(pcPredict);
			cout << "PC의 차례 :: " << pcNum << endl;

			string pcResult = check(pcNum, playerInput);
			if (pcResult == "FIND SUCCESS") {
				cout << "당신의 패배" << endl;
				cout << "정답 : " << select << endl;
				return 0;
			}
			else {
				cout <<  "PC : " << split(pcResult, ',')[0] << " ball,  " << split(pcResult, ',')[1] << " Strake,  " << split(pcResult, ',')[2] << " out" << endl;
				if (split(pcResult, ',')[2] == "4") {
					int n0 = pcNum.at(0) - '0'; // 
					int n1 = pcNum.at(1) - '0'; // 
					int n2 = pcNum.at(2) - '0'; // 
					int n3 = pcNum.at(3) - '0'; // 
					remove(pcPredict.begin(), pcPredict.end(), n0);
					remove(pcPredict.begin(), pcPredict.end(), n1);
					remove(pcPredict.begin(), pcPredict.end(), n2);
					remove(pcPredict.begin(), pcPredict.end(), n3);

					if (removed.find(pcNum.at(0)) == string::npos) {
						removed += pcNum.at(0);
					}
					if (removed.find(pcNum.at(1)) == string::npos) {
						removed += pcNum.at(1);
					}
					if (removed.find(pcNum.at(2)) == string::npos) {
						removed += pcNum.at(2);
					}
					if (removed.find(pcNum.at(3)) == string::npos) {
						removed += pcNum.at(3);
					}

				}
				else if (split(pcResult, ',')[0] == "4") {
					int n0 = pcNum.at(0) - '0';
					int n1 = pcNum.at(1) - '0';
					int n2 = pcNum.at(2) - '0';
					int n3 = pcNum.at(3) - '0';
					
					if (removed.find(pcNum.at(0)) == string::npos) {
						pcPredict.push_back(n0);
						pcPredict.push_back(n0);

					}
					if (removed.find(pcNum.at(1)) == string::npos) {
						pcPredict.push_back(n1);
						pcPredict.push_back(n1);

					}
					if (removed.find(pcNum.at(2)) == string::npos) {
						pcPredict.push_back(n2);
						pcPredict.push_back(n2);

					}
					if (removed.find(pcNum.at(3)) == string::npos) {
						pcPredict.push_back(n3);
						pcPredict.push_back(n3);
					}
				}
				else if (split(pcResult, ',')[2] == "1") {
					int n0 = pcNum.at(0) - '0';
					int n1 = pcNum.at(1) - '0';
					int n2 = pcNum.at(2) - '0';
					int n3 = pcNum.at(3) - '0';
					if (removed.find(pcNum.at(0)) == string::npos) {
						pcPredict.push_back(n0);
					}
					if (removed.find(pcNum.at(1)) == string::npos) {
						pcPredict.push_back(n1);
					}
					if (removed.find(pcNum.at(2)) == string::npos) {
						pcPredict.push_back(n2);
					}
					if (removed.find(pcNum.at(3)) == string::npos) {
						pcPredict.push_back(n3);
					}
				}

			}
		}
		else {
			cout << result << endl;
			return 0;
		}

	}
	
	return 0;
}


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
		}
		else {
			out++;
		}
	}
	if (strake == 4) {
		return "FIND SUCCESS";
	}
	else {
		return (to_string(ball) + "," + to_string(strake) + "," + to_string(out));
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
string getPcNum(vector<int> pcPredict) {
	srand(time(NULL));
	int size = pcPredict.size();
	int a = rand() % size;
	int c = pcPredict[a];
	string select = to_string(c);

	for (int i = 0; i < 3; i++) {
		a = rand() % size;
		int c2 = pcPredict[a];
		while (select.find(to_string(c2)) != string::npos) {
			a = rand() % size;
			c2 = pcPredict[a];
		}
		select += to_string(c2);
	}
	return select;
}

vector<string> split(string input, char delimiter) {
	vector<string> answer;
	stringstream ss(input);
	string temp;

	while (getline(ss, temp, delimiter)) {
		answer.push_back(temp);
	}

	return answer;
}