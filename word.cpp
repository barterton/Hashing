#include "word.h"

word::word(std::string n) {
	name = n;
	numClash = 0;
}
std::string word::getWord(){
	return name;
}

void word::setWord(std::string n) {
	name = n;
}

int word::getNumClash() {
	return numClash;
}
void word::setNumClash(int c) {
	numClash = c;
}