#pragma once

#include <string>;

class word {

public:

	word(std::string n);

	std::string getWord();
	void setWord(std::string n);
	
	int getNumClash();
	void setNumClash(int c);
	

private:

	std::string name;
	int numClash;
};