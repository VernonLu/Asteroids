#include "Score.h"

Score::Score() :value(0) {
	setString(std::to_wstring(value));
}

Score::~Score() {}

int Score::operator=(const int& v) {
	value = v;
	setString(std::to_wstring(value));
	return value;
}

int Score::operator+=(const int& v) {
	value += v;
	setString(std::to_wstring(value));
	return value;
}

bool Score::operator>=(const int& v) {
	return value >= v;
}
bool Score::operator==(const int& v){
	return false;
}
