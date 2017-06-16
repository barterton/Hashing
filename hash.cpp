#include "hash.h"

hash::hash(std::string fileName) {
	m_FileName = fileName;
	std::vector<std::string> words;
	std::vector<word> hashed;
	
}
int hash::getCollisions() {
	return m_Collisions;
}

void hash::fillVector() {

	std::cout << "Reserving Hash Size: " << words.size() * 1.6 << std::endl;

	std::cout << "Initialising...";
	
	for (int x = 0; x < words.size()*1.6; x++) {
		word temp("--------");
		hashed.push_back(temp);
	}
	
	std::cout << "\aDone "  << std::endl;
}

//runHash
//calls the addHashMap method for all the words stored in the dictionary vector

void hash::runHash() {

	std::cout << "Hashing...";
	for (int i = 0; i < words.size(); i++) {
		addHashMap(Hash(words[i]), words[i]);
	}
	std::cout << "\aDone" << std::endl;
}


//probe
//Collision resolving method where a different hash function is called and a new hash value is returned and used as an offset
//Used in the findWord method and checkPosition method

int hash::probe(int hashedVal, std::string word) { //double hashing
	int seed = 181;
	unsigned long hash = 0;
	for (int i = 0; i < word.length(); i++) {
		hash = (hash * seed) + (word[i]);
	}
	hash = (hash + hashedVal) % hashed.size();
	return hash;
}

//addHashMap method
//adds a word to hashedVal index in the hash table if checkPosition returns true

void hash::addHashMap(int hashedVal, std::string word) {
		hashed[checkPosition(hashedVal, word)].setWord(word);

}

//checkPosition method
//Checks if a position in the hash table is free and returns the hash index if free
//If not free then it changes the hash index by an offset probe

int hash::checkPosition(int hashedVal, std::string word) { 
	bool check = false;
	int offset = probe(hashedVal, word);
	int hashVal = hashedVal;
	int numClash = 0;
	

	while (!check) {
		if (hashed[hashVal].getWord() == "--------") {
			check = true;
			numClash++;
			hashed[hashVal].setNumClash(numClash);
			return hashVal;
		}
		else {
			
			m_Collisions++;
			numClash++;
			hashVal = (hashVal + offset) % hashed.size();
			check = false;
		}
	}
}

// findWord method
// to see if the word is in the table, 
//returns true if in the table, false if == to the init value "--------" preventing infinite looping

bool hash::findWord(int hashedVal, std::string word) { 
	bool check = false;
	int offset = probe(hashedVal, word);
	int hashVal = hashedVal;
	int count = 1;

	while (!check) {
		if (hashed[hashVal].getWord() == word) {
			successfulSearch++;
			check = true;
			std::cout << count << " probes used" << std::endl;
			return check;
		}
		else {	
			hashVal = (hashVal + offset) % hashed.size();
			count++;
			if (hashed[hashVal].getWord() == "--------") {
				unsuccessfulSearch++;
				check = false;
				std::cout << count << " probes used" << std::endl;
				return check;
			}
		}
	}
}
//findValue method
//void method to check if a value is in the hash table
//uses the findWord method 

void hash::findValue() { 
	std::string word;
	int index = 0;
	bool running = true;
	int hashCount = 0;

	for (int i = 0; i < hashed.size(); i++) {
		if (hashed[i].getWord() == "--------") {
			hashCount++;
		}
	} 
	std::cout << "Num of hashed values: " << hashed.size() - hashCount << std::endl;

	std::cout << "\nEnter words below to search for in dictionary..." << std::endl;
	while (running) {

		std::cout << "Search: ";
		std::cin >> word;
		index = Hash(word);

		if (findWord(index, word) == false) {
			std::cout << "Word is not in the dictionary" << std::endl;
			
		}
	}
}

//printHashMap
//prints the hash table to a file logs.txt

void hash::printHashMap() {

	std::cout << "Logging Results...";
	std::ofstream log;
	log.open("logs.txt");

	for (int x = 0; x < hashed.size(); x++) {
		
		log << x << ":" << hashed[x].getWord()  << " numClash: "<< "(" << hashed[x].getNumClash() << ")" << std::endl;
	}
	log.close();
	std::cout << "\aDone" << std::endl;
}

//Hash
//hash function takes parameter key returns an index for the word sent to the parameter

int hash::Hash(std::string key) {

	int seed = 131;//131
	unsigned long hash = 0;

	for (int i = 0; i < key.length(); i++) {
		hash = (hash * seed) + key[i];
	}
	return hash % hashed.size();
}

void hash::loadFile() {
	std::ifstream file(m_FileName);
	std::string line;

	std::cout << "Reading file to vector...";

	if (file.is_open()){
		while (std::getline(file, line)){
			words.push_back(line);
		}
		file.close();
		std::cout << "Done\a\n";
	}

	else std::cout << "Unable to open file";
}




