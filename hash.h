#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>




#include "word.h"

class hash {

public:
	hash(std::string fileName);
	void runHash();
	void fillVector();

	int probe(int hashedVal, std::string word);

	int getCollisions();
	int Hash(std::string key);

	void loadFile(); 
	void addHashMap(int hashedVal, std::string word);
	void printHashMap();
	int checkPosition(int hashedVal, std::string word);
	bool findWord(int hashedVal, std::string word);

	void findValue();

private:
	int successfulSearch = 0;
	int unsuccessfulSearch = 0;

	int m_TableSize;
	std::string m_FileName;
	int m_Collisions;
	std::vector<std::string> words;
	std::vector<word> hashed;

};
