/**
* File:		main.cpp
* Author:	Ryan Johnson
* Email:	johnsonrw82@cs.fullerton.edu
* Purpose:	This file contains the main entry point for the FileFactory program for HW1. All printing operations
*			are initiated from here.
*/


// includes
#include "FileFactory.hpp"

// main entry point
int main() {
	// create a file using std::cin
	File f = FileFactory::readFileFromStream(std::cin);

	// print forward - const
	std::cout << "Const - Forward - Normal Iterator" << std::endl;
	FileFactory::printFileConst(f, std::cout, FileFactory::PrintDirection::FORWARD, FileFactory::IteratorType::NORMAL);

	// print backward - const
	std::cout << "\nConst - Backward - Normal Iterator" << std::endl;
	FileFactory::printFileConst(f, std::cout, FileFactory::PrintDirection::BACKWARD, FileFactory::IteratorType::NORMAL);
	
	// print forward - non const
	std::cout << "\nForward - Normal Iterator" << std::endl;
	FileFactory::printFile(f, std::cout, FileFactory::PrintDirection::FORWARD, FileFactory::IteratorType::NORMAL);

	// print backward - non const
	std::cout << "\nBackward - Normal Iterator" << std::endl;
	FileFactory::printFile(f, std::cout, FileFactory::PrintDirection::BACKWARD, FileFactory::IteratorType::NORMAL);

	// print backward - reverse iteration - const
	std::cout << "\nConst - Backward - Reverse Iterator" << std::endl;
	FileFactory::printFileConst(f, std::cout, FileFactory::PrintDirection::BACKWARD, FileFactory::IteratorType::REVERSE);

	// print backward - reverse iteration - non const
	std::cout << "\nBackward - Reverse Iterator" << std::endl;
	FileFactory::printFile(f, std::cout, FileFactory::PrintDirection::BACKWARD, FileFactory::IteratorType::REVERSE);

	// print odd words in reverse
	std::cout << "\nOdd words in reverse" << std::endl;
	FileFactory::printOddWordsReverse(f, std::cout);

	// print alternating words
	std::cout << "\nAlternating words" << std::endl;
	FileFactory::printAlternatingWords(f, std::cout);

	// construct a c-string array from File
	size_t size;
	char** myFile = FileFactory::toCStringArray(f,size);
	
	// print c-string array foward - const
	std::cout << "\nConst C-Strings - Forward" << std::endl;
	FileFactory::printArrayConst(myFile, size, std::cout, FileFactory::PrintDirection::FORWARD);

	// print c-string array backward - const
	std::cout << "\nConst C-Strings - Backward" << std::endl;
	FileFactory::printArrayConst(myFile, size, std::cout, FileFactory::PrintDirection::BACKWARD);

	// print c-string array foward - non const
	std::cout << "\nC-Strings - Forward" << std::endl;
	FileFactory::printArray(myFile, size, std::cout, FileFactory::PrintDirection::FORWARD);

	// print c-string array backward - non const
	std::cout << "\nC-Strings - Backward" << std::endl;
	FileFactory::printArray(myFile, size, std::cout, FileFactory::PrintDirection::BACKWARD);

	// clean up
	delete[] myFile;

	return 0;
}