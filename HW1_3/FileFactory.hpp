/**
* File:		FileFactory.hpp
* Author:	Ryan Johnson
* Email:	johnsonrw82@cs.fullerton.edu
* Purpose:	This file is the header definition for a FileFactory class, that produces File objects and provides
*			static methods that print the contents to the supplied stream, using a variety of iteration methods.
*/

#ifndef FILE_FACTORY_HPP
#define FILE_FACTORY_HPP

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define VECTOR			1
#define DEQUE			2
#define LIST			3
#define FORWARD_LIST	4
#define ARRAY			5

#ifndef CONTAINER
#define CONTAINER VECTOR
#endif

// includes
#include <iostream>
#include <type_traits>
#include <iterator>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <array>
#include <string>
#include <cstring>
#include <sstream>

// type alias
using File =
#if CONTAINER == VECTOR
	std::vector<std::string>;
#elif CONTAINER == DEQUE
	std::deque<std::string>;
#elif CONTAINER == LIST
	std::list<std::string>;
#elif CONTAINER == FORWARD_LIST
	std::forward_list<std::string>;
#elif CONTAINER == ARRAY
	std::array<std::string,10000>;
#else
#error "Invalid container choice"
#endif

// class definition
class FileFactory {
public:
	// print direction enum
	enum PrintDirection {
		FORWARD, BACKWARD
	};

	// iterator type enum
	enum IteratorType {
		NORMAL, REVERSE
	};

	// constructor/destructor
	FileFactory();
	virtual ~FileFactory();

	// read file from stream, return a File object containing words read from stream
	static File readFileFromStream(std::istream& stream);

	// print the contents of the file using const methods, in the direction and iteration method provided
	static void printFileConst(const File& file, 
		std::ostream& stream,
		FileFactory::PrintDirection direction = FileFactory::PrintDirection::FORWARD, 
		FileFactory::IteratorType iteratorType = FileFactory::IteratorType::NORMAL);

	// print the contents of the file using non-const methods, in the direction and iteration method provided
	static void printFile(File& file,
		std::ostream& stream,
		FileFactory::PrintDirection direction = FileFactory::PrintDirection::FORWARD,
		FileFactory::IteratorType iteratorType = FileFactory::IteratorType::NORMAL);

	// print the contents of the file where odd words are in reverse
	static void printOddWordsReverse(const File& file, std::ostream& stream);
	// print the contents of the file using alternating words, meeting in the middle
	static void printAlternatingWords(const File& file, std::ostream& stream);

	// produce an array of C-strings from supplied file
	static char** toCStringArray(const File& file, size_t& size);

	// print the contents of a C-string array of given size, in direction provided, using const methods
	static void printArrayConst(char** fileArray,
		const size_t size,
		std::ostream& stream,
		FileFactory::PrintDirection direction = FileFactory::PrintDirection::FORWARD);

	// print the contents of a C-string array of given size, in direction provided, using non-const methods
	static void printArray(char** fileArray,
		const size_t size,
		std::ostream& stream,
		FileFactory::PrintDirection direction = FileFactory::PrintDirection::FORWARD);

// private methods
private:
	// print file forward, const
	static void printForwardConst(const File& file, std::ostream& stream);
	// print file forward, non const
	static void printForward(File& file, std::ostream& stream);
	// print file backward, const
	static void printBackwardConst(const File& file, std::ostream& stream);
	// print file backward, non const
	static void printBackward(File& file, std::ostream& stream);
	// print file backward, reverse iteration, const
	static void printBackwardReverseConst(const File& file, std::ostream& stream);
	// print file backward, reverse iteration, non const
	static void printBackwardReverse(File& file, std::ostream& stream);

	// helper function to reverse a std::string (assumes no use of built-in reverse functions)
	static std::string reverseString(const std::string& src);
	// helper function to alternate the characters in the source string, first, last, second, next-to-last, etc.
	static std::string alternateString(const std::string& src);
	// print c string array forward, const
	static void printForwardCStringConst(char** fileArray, const size_t size, std::ostream& stream);
	// print c string array forward, non const
	static void printForwardCString(char** fileArray, const size_t size, std::ostream& stream);
	// print c string array backward, const
	static void printBackwardCStringConst(char** fileArray, const size_t size, std::ostream& stream);
	// print c string array backward, non const
	static void printBackwardCString(char** fileArray, const size_t size, std::ostream& stream);

	// print helper functions
	static void print(const std::string& word, std::ostream& stream);
	static void print(const char* word, std::ostream& stream);

#if CONTAINER == ARRAY || CONTAINER == FORWARD_LIST
	static size_t size(const File& file);
#endif
}; // end class FileFactory

#endif
