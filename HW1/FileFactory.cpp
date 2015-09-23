/**
* File:		FileFactory.cpp
* Author:	Ryan Johnson
* Email:	johnsonrw82@cs.fullerton.edu
* Purpose:	This file is the implementation for a FileFactory class, that produces File objects and provides
*			static methods that print the contents to the supplied stream, using a variety of iteration methods.
*			This class supports reading from an input stream to a File object or C-string array and printing:
*			Forward:
*				Const/Non-const
*			Backward:
*				Const/Non-const
*				Const/Non-const, reverse iteration
*			Odd words reversed
*			Alternating words, meeting in middle
*			C-Strings Forward/Backward, const/non const
*/

#include "FileFactory.hpp"
#include <stdexcept>

// empty
FileFactory::FileFactory() {

}

// empty
FileFactory::~FileFactory() {

}

// read contents of input stream to File object
File FileFactory::readFileFromStream(std::istream& stream) {
	std::string word;

	File infile;

	// while input remains
	while (stream) {
		// read contents of stdin to variable
		stream >> word;

		// add the word to the File object
		infile.push_back(word);

		// if the eof is reached, break loop
		if (stream.eof()) {
			break;
		}
	}

	// return the file object
	return infile;
}

// print contents of file, using const methods
// specify direction and interator type
// forward printing with reverse iterators is not allowed and generates an exception
void FileFactory::printFileConst(const File& file,
	std::ostream& stream,
	FileFactory::PrintDirection direction,
	FileFactory::IteratorType iteratorType) {
	
	// determine iterator type
	switch (iteratorType) {
		// if normal iterators, support fwd/backward printing
		case NORMAL:
			if (direction == FORWARD) {
				printForwardConst(file, stream);
			}
			else {
				printBackwardConst(file, stream);
			}
			break;
		// reverse iteration is only supported when printing backward
		case REVERSE:
			if (direction == FORWARD) {
				// throw exception
				throw std::invalid_argument("This is not a supported print operation");
			}
			
			// print backward
			printBackwardReverseConst(file, stream);

			break;
	}
}

// print contents of file, using non const methods
// specify direction and interator type
// forward printing with reverse iterators is not allowed and generates an exception
void FileFactory::printFile(File& file,
	std::ostream& stream,
	FileFactory::PrintDirection direction,
	FileFactory::IteratorType iteratorType) {

	// determine iterator type
	switch (iteratorType) {
		// if normal iterators, support fwd/backward printing
		case NORMAL:
			if (direction == FORWARD) {
				printForward(file, stream);
			}
			else {
				printBackward(file, stream);
			}
			break;
		// reverse iteration is only supported when printing backward
		case REVERSE:
			if (direction == FORWARD) {
				// throw exception
				throw std::invalid_argument("This is not a supported print operation");
			}

			// print backward
			printBackwardReverse(file, stream);

			break;
	}
}

// print odd indexed words in reverse order
void FileFactory::printOddWordsReverse(const File& file, std::ostream& stream) {
	File::const_iterator itr;
	// counter for word number
	int count = 1;
	// begin to end
	for (itr = file.begin(); itr != file.end(); ++itr) {
		// get string
		std::string word = *itr;
		// if odd, revers
		if (count % 2 == 1) {
			// call helper function
			word = reverseString(word);
		}
		// print to stream
		stream << word << std::endl;

		// increment
		count++;
	}
}

// print words in alternating order, first to last, meeting in middle
void FileFactory::printAlternatingWords(const File& file, std::ostream& stream) {
	File::const_iterator front = file.begin();
	File::const_iterator back = file.end();

	// use two iterators, while front not past back
	while (front < back) {
		// decrement back first
		--back;
		// print the front
		stream << *front << std::endl;
		// if not same word, print back
		if ( front != back )
			stream << *back << std::endl;
		// increment front
		++front;
	}
}

// turn contents of file into a C-String array
char** FileFactory::toCStringArray(const File& file) {
	char** result = new char*[file.size()];  // allocate memory

	// iterator
	File::const_iterator itr;
	// index counter
	int count = 0;
	// for begin to end
	for (itr = file.begin(); itr != file.end(); ++itr) {
		// allocate an element, with space for the null terminator
		result[count] = new char[(*itr).length() + 1];
		// copy to array index
		strcpy_s(result[count], (*itr).length()+1, (*itr).c_str());
		// increment count
		count++;
	}

	// return the result
	return result;
}

// print the contents of a C-string array of specified size in direction specified, using const methods
void FileFactory::printArrayConst(char** fileArray,
	const size_t size,
	std::ostream& stream,
	FileFactory::PrintDirection direction) {

	// if fwd/backward
	switch (direction) {
		case FORWARD:
			// print forward
			printForwardCStringConst(fileArray, size, stream);
			break;
		case BACKWARD:
			// print backward
			printBackwardCStringConst(fileArray, size, stream);
			break;
	}
}

// print the contents of a C-string array of specified size in direction specified, using non const methods
void FileFactory::printArray(char** fileArray,
	const size_t size,
	std::ostream& stream,
	FileFactory::PrintDirection direction) {

	// if fwd/backward
	switch (direction) {
	case FORWARD:
		// print forward
		printForwardCString(fileArray, size, stream);
		break;
	case BACKWARD:
		// print backward
		printBackwardCString(fileArray, size, stream);
		break;
	}
}

/// PRIVATE FUNCTIONS AREA ///

// print file contents forward, const
void FileFactory::printForwardConst(const File& file, std::ostream& stream) {
	File::const_iterator itr;

	// use a forward iterator
	for (itr = file.begin(); itr != file.end(); ++itr) {
		stream << *itr << std::endl;
	}
}

// print file contents forward, non const
void FileFactory::printForward(File& file, std::ostream& stream) {
	File::iterator itr;

	// use forward iterator
	for (itr = file.begin(); itr != file.end(); ++itr) {
		stream << *itr << std::endl;
	}
}

// print file contents backward, const
void FileFactory::printBackwardConst(const File& file, std::ostream& stream) {
	File::const_iterator itr = file.end();

	// use a const iterator, starting at the back
	while (itr != file.begin()) {
		--itr; // decrement first
		stream << *itr << std::endl;
	}
}

// print file contents backward, non const
void FileFactory::printBackward(File& file, std::ostream& stream) {
	File::iterator itr = file.end();

	// use forward iterator, starting at the back
	while (itr != file.begin()) {
		--itr;  // decrement first
		stream << *itr << std::endl;
	}
}

// print file contents backwards, reverse iterator, const
void FileFactory::printBackwardReverseConst(const File& file, std::ostream& stream) {
	File::const_reverse_iterator itr;
	// use const reverse iterator
	for (itr = file.rbegin(); itr != file.rend(); ++itr) {
		stream << *itr << std::endl;
	}
}

// print file contents backwards, reverse iterator, non const
void FileFactory::printBackwardReverse(File& file, std::ostream& stream) {
	File::reverse_iterator itr;
	// use a reverse iterator
	for (itr = file.rbegin(); itr != file.rend(); ++itr) {
		stream << *itr << std::endl;
	}
}

// print C-string array contents forward, const
void FileFactory::printForwardCStringConst(char** fileArray, const size_t size, std::ostream& stream) {
	for (unsigned int i = 0; i < size; i++) {
		// use const pointers to print
		const char* word = fileArray[i];
		stream << word << std::endl;
	}
}

// print C-string array contents forward, non-const
void FileFactory::printForwardCString(char** fileArray, const size_t size, std::ostream& stream) {
	for (unsigned int i = 0; i < size; i++) {
		// use non-const pointers
		char* word = fileArray[i];
		stream << word << std::endl;
	}
}

// print C-string array contents backward, const
void FileFactory::printBackwardCStringConst(char** fileArray, const size_t size, std::ostream& stream) {
	// i is unsigned, cannot go less than 0 -- start at size and use index - 1
	for (unsigned int i = size; i > 0; --i) {
		// use const pointers
		const char* word = fileArray[i-1];
		stream << word << std::endl;
	}
}

// print C-string array contents backward, non const
void FileFactory::printBackwardCString(char** fileArray, const size_t size, std::ostream& stream) {
	// i is unsigned, cannot go less than 0 -- start at size and use index - 1
	for (unsigned int i = size; i > 0; --i) {
		// use non-const pointers
		char* word = fileArray[i-1];
		stream << word << std::endl;
	}
}

// helper function to reverse a std::string, assumes no use of any built-in reversing functions
std::string FileFactory::reverseString(const std::string& src) {
	// ostringstream for gathering characters
	std::ostringstream oss;
	// reverse iterator
	std::string::const_reverse_iterator itr;

	// iterate over the string from the back, add to the string stream
	for (itr = src.rbegin(); itr != src.rend(); ++itr) {
		oss << *itr;
	}

	// return std::string from the stream
	return oss.str();
}

