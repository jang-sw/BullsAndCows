#ifndef GAME_H
#define GAME_H


bool isNumeric(std::string const& str);
std::string check(std::string const& selected, std::string const& input);
bool isDuplication(std::string  const& str);
std::string getPcNum(std::vector<int> pcPredict);
std::vector<std::string> split(std::string input, char delimiter);
#endif