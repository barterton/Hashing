#include "hash.h"

int main() {

	std::cout << "---------------" << std::endl;
	std::cout << "HASHING PROGRAM " << std::endl;
	std::cout << "---------------\n" << std::endl;

	hash h = hash("dictionary.txt");
	h.loadFile();
	h.fillVector();
	h.runHash();
	h.printHashMap();
	std::cout << "Number of collisions: " << h.getCollisions() << std::endl;

	h.findValue();

	system("pause");
	return 0;
}