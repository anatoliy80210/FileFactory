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
	std::string line;
	std::string word;

	File infile;

#if CONTAINER == ARRAY || CONTAINER == FORWARD_LIST
	int count = 0;
#endif

	// while input remains
	while (stream) {
		// read contents of stdin to variable, by line
		std::getline(stream, line);

		// if there is an error with the stream, break
		if (!stream) {
			break;
		}
		
		// else, process word by word
		std::istringstream iss(line);

		// add the word to the File object
		while (iss >> word) {
#if CONTAINER == ARRAY
			infile[count] = word;
			count++;
#elif CONTAINER == FORWARD_LIST
			infile.push_front(word);
#else
			infile.push_back(word);
#endif
		}
	}

	// return the file object
#if CONTAINER == FORWARD_LIST
	infile.reverse();
#endif

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
	for (itr = file.cbegin(); itr != file.cend(); ++itr) {
		// get string
		std::string word = *itr;
		// if odd, revers
		if (count % 2 == 1) {
			// call helper function
			word = reverseString(word);
		}
		// print to stream
		print(word, stream);

		// increment
		count++;
	}
}

// print words in alternating order, first to last, meeting in middle
void FileFactory::printAlternatingWords(const File& file, std::ostream& stream) {
#if CONTAINER == FORWARD_LIST
	File copy = file;
	copy.reverse();

	int i = 0;
	int j = FileFactory::size(file);
#endif

	File::const_iterator front = file.cbegin();
	File::const_iterator back =
#if CONTAINER == FORWARD_LIST
		copy.cbegin();
#else
		file.cend();
#endif

	std::string word;

	// use two iterators, while front not past back
#if CONTAINER == FORWARD_LIST
	while (i != j) {
#else
	while (front != back) {
#endif
		// decrement back first
#if CONTAINER != FORWARD_LIST
		--back;
#endif

		// alternate the characters
		word = alternateString(*front);
		// print the front
		print(word, stream);
		// if not same word, print back
#if CONTAINER == FORWARD_LIST
		if (i != j) {
#else
		if (front != back) {
#endif
			word = alternateString(*back);
			print(word, stream);
#if CONTAINER == FORWARD_LIST
			--j;
			++back;
#endif
		}
		else {
			break;
		}
		// increment front
		++front;
#if CONTAINER == FORWARD_LIST
		++i;
#endif
	}
}

// turn contents of file into a C-String array
char** FileFactory::toCStringArray(const File& file, size_t& size) {
	size_t fileSize =
		// arrays and forward lists do not provide a 'count' function, so we'll have to calculate it...
#if CONTAINER == ARRAY || CONTAINER == FORWARD_LIST
		FileFactory::size(file);
#else
		// another method to have done this would be to use the size function implemented below, 
		// and just have the macro determine if a manual count or a simple return of the implemented size() function should be returned.
		size = file.size();
#endif


	char** result = new char*[fileSize];  // allocate memory
	size = fileSize;

	// iterator
	File::const_iterator itr;
	// index counter
	int count = 0;
	// for begin to end
	for (itr = file.cbegin(); itr != file.cend(); ++itr) {
		// allocate an element, with space for the null terminator
		result[count] = new char[(*itr).length() + 1];
		// copy to array index
		strncpy(result[count], (*itr).c_str(), (*itr).length() + 1);
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
	for (itr = file.cbegin(); itr != file.cend(); ++itr) {
		print(*itr, stream);
	}
}

// print file contents forward, non const
void FileFactory::printForward(File& file, std::ostream& stream) {
	File::iterator itr;

	// use forward iterator
	for (itr = file.begin(); itr != file.end(); ++itr) {
		print(*itr, stream);
	}
}

// print file contents backward, const
void FileFactory::printBackwardConst(const File& file, std::ostream& stream) {
#if CONTAINER == FORWARD_LIST
	File copy = file;
	copy.reverse();
#endif

	File::const_iterator itr =
#if CONTAINER == FORWARD_LIST
		copy.cbegin();
#else
		file.cend();
#endif

	// use a const iterator, starting at the back
#if CONTAINER == FORWARD_LIST
	while (itr != copy.cend()) {
#else
	while (itr != file.cbegin()) {
#endif

#if CONTAINER != FORWARD_LIST
		--itr; // decrement first
#endif

		print(*itr, stream);

#if CONTAINER == FORWARD_LIST
		++itr;
#endif
	}
}

// print file contents backward, non const
void FileFactory::printBackward(File& file, std::ostream& stream) {
#if CONTAINER == FORWARD_LIST
	File copy = file;
	copy.reverse();
#endif

	File::iterator itr =
#if CONTAINER == FORWARD_LIST
		copy.begin();
#else
		file.end();
#endif

	// use forward iterator, starting at the back
#if CONTAINER == FORWARD_LIST
	while (itr != copy.end()) {
#else
	while (itr != file.begin()) {
#endif
#if CONTAINER != FORWARD_LIST
		--itr; // decrement first
#endif

		print(*itr, stream);

#if CONTAINER == FORWARD_LIST
		++itr;
#endif
	}
}

// print file contents backwards, reverse iterator, const
void FileFactory::printBackwardReverseConst(const File& file, std::ostream& stream) {
#if CONTAINER == FORWARD_LIST
	File::const_iterator itr;
#else
	File::const_reverse_iterator itr;
#endif
	// use const reverse iterator
#if CONTAINER == FORWARD_LIST
	for (itr = file.cbegin(); itr != file.cend(); ++itr) {
#else
	for (itr = file.crbegin(); itr != file.crend(); ++itr) {
#endif
		print(*itr, stream);
	}
}

// print file contents backwards, reverse iterator, non const
void FileFactory::printBackwardReverse(File& file, std::ostream& stream) {
#if CONTAINER == FORWARD_LIST
	File::iterator itr;
#else
	File::reverse_iterator itr;
#endif
	// use a reverse iterator
#if CONTAINER == FORWARD_LIST
	for (itr = file.begin(); itr != file.end(); ++itr) {
#else
	for (itr = file.rbegin(); itr != file.rend(); ++itr) {
#endif
		print(*itr, stream);
	}
}

// print C-string array contents forward, const
void FileFactory::printForwardCStringConst(char** fileArray, const size_t size, std::ostream& stream) {
	for (unsigned int i = 0; i < size; i++) {
		// use const pointers to print
		const char* word = fileArray[i];
		print(word, stream);
	}
}

// print C-string array contents forward, non-const
void FileFactory::printForwardCString(char** fileArray, const size_t size, std::ostream& stream) {
	for (unsigned int i = 0; i < size; i++) {
		// use non-const pointers
		char* word = fileArray[i];
		print(word, stream);
	}
}

// print C-string array contents backward, const
void FileFactory::printBackwardCStringConst(char** fileArray, const size_t size, std::ostream& stream) {
	// i is unsigned, cannot go less than 0 -- start at size and use index - 1
	for (unsigned int i = size; i > 0; --i) {
		// use const pointers
		const char* word = fileArray[i-1];
		print(word, stream);
	}
}

// print C-string array contents backward, non const
void FileFactory::printBackwardCString(char** fileArray, const size_t size, std::ostream& stream) {
	// i is unsigned, cannot go less than 0 -- start at size and use index - 1
	for (unsigned int i = size; i > 0; --i) {
		// use non-const pointers
		char* word = fileArray[i-1];
		print(word, stream);
	}
}

void FileFactory::print(const std::string& word, std::ostream& stream) {
	if (word != "") {
		stream << word << std::endl;
	}
}

void FileFactory::print(const char* word, std::ostream& stream) {
	if (strcmp(word, "") != 0) {
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

// helper function to alternate the characters in the source string, first, last, second, next-to-last, etc.
std::string FileFactory::alternateString(const std::string& src) {
	std::ostringstream oss;
	// iterators
	std::string::const_iterator back;
	std::string::const_iterator front;

	front = src.cbegin();
	back = src.cend();

	while (front != back) {
		--back;
		oss << *front;

		if (front != back) {
			oss << *back;
		}
		else {
			break;
		}

		++front;
	}

	return oss.str();
}

#if CONTAINER == ARRAY || CONTAINER == FORWARD_LIST
size_t FileFactory::size(const File& file) {
	size_t count = 0;
	for (auto word : file) {
		count++;
	}

	return count;
}
#endif

