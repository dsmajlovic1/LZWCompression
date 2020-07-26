#ifndef lzw_algorithm_hpp
#define lzw_algorithm_hpp

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stack>

namespace lzw_compression
{

	static uint16_t MAX_CHILDREN_NUMBER = 256;
	static uint16_t MAX_ENTRY_NUMBER = uint16_t( std::numeric_limits<uint16_t>::max );

	//Dictionary node class
	class Entry
	{
	private:

	public:
		uint16_t code;
		char value;
		Entry* parent;
		Entry** children;
		uint16_t childrenLength;
		uint16_t childrenMax;
		Entry(Entry* parent, uint16_t code, char value);
		~Entry();
		bool addChild(Entry* newEntry);
	};

	//Coding dictionary class
	class Dictionary
	{
	private:
		Entry** initialEntries;
		uint16_t entriesNumber;
	public:
		Dictionary();
		~Dictionary();

		bool substring(Entry* start, char* string, uint16_t length);
		Entry* findSubentry(Entry* entry, uint16_t index);
		bool addChild(Entry* parent, char value);
		bool addChild(uint16_t index, char value);
		bool containsString(char* string, uint16_t length);
		uint16_t findIndex(char* string, uint16_t length);
		Entry* findEntry(uint16_t index);
	};

	//LZW implemention
	uint16_t* encodeLZW(char* originalData);
	char* decodeLZW(uint16_t* encodedData);


	//Methods implementations

#pragma region Entry_implementation
	Entry::Entry(Entry* parent, uint16_t code, char value)
	{
		this->parent = parent;
		this->code = code;
		this->value = value;
		childrenLength = 0;
		childrenMax = (1 << 6);
		children = new Entry * [childrenMax];
		for (uint16_t i = 0; i < childrenMax; i++) children[i] = nullptr;
	}

	Entry::~Entry()
	{
		for (uint16_t i = 0; i < childrenLength; i++)
		{
			delete children[i];
		}
		delete[] children;
	}

	bool Entry::addChild(Entry* newEntry)
	{
		try
		{
			//if all alocated memory is used, allocate more memory
			if (this->childrenLength >= this->childrenMax)
			{
				if (childrenMax >= MAX_CHILDREN_NUMBER) return false;
				childrenMax = (childrenMax << 1);
				Entry** newArray = new Entry * [childrenMax];

				for (uint16_t i = 0; i < childrenLength; i++)
				{
					newArray[i] = children[i];
				}
				delete[] children;
				children = newArray;
			}

			children[childrenLength] = newEntry;
			this->childrenLength++;
			return true;
		}
		catch (...)
		{
			//std::cout << "addChild exception" << std::endl;
			return false;
		}
	}
#pragma endregion Entry_implementation

#pragma region Dictionary_implementation
	Dictionary::Dictionary()
	{
		initialEntries = new Entry * [MAX_CHILDREN_NUMBER];
		entriesNumber = MAX_CHILDREN_NUMBER;

		//Entry** entryList = new Entry * [256];
		for (uint16_t i = 0; i < MAX_CHILDREN_NUMBER; i++)
		{
			int size = 0;
			Entry* newEntry = new Entry(nullptr, i, (char(i)));
			initialEntries[i] = newEntry;
			size = sizeof(initialEntries[i]);
		}

		//initialEntries = entryList;
	}
	Dictionary::~Dictionary()
	{
		for (uint16_t i = 0; i < MAX_CHILDREN_NUMBER; i++)
		{
			delete initialEntries[i];
		}
		delete[] initialEntries;
	}
	bool Dictionary::addChild(Entry* parent, char value)
	{
		if (this->entriesNumber >= MAX_ENTRY_NUMBER) return false;
		//if (parent->childrenLength == parent->childrenMax) return false;

		//parent->children[parent->childrenLength] = new Entry(parent, parent->childrenLength, value);
		//parent->childrenLength++;
		try
		{
			parent->addChild(new Entry(parent, this->entriesNumber, value));
			this->entriesNumber++;
			return true;
		}
		catch (...)
		{
			//std::cout << "addChild exception" << std::endl;
			return false;
		}
	}

	bool Dictionary::addChild(uint16_t index, char value)
	{
		if (index >= this->entriesNumber) return false;
		if (index < MAX_CHILDREN_NUMBER) return this->addChild(initialEntries[index], value);

		Entry* parentPtr = nullptr;
		for (uint16_t i = 0; i < MAX_CHILDREN_NUMBER; i++)
		{
			parentPtr = findSubentry(initialEntries[i], index);
			if (parentPtr != nullptr) break;
		}

		return this->addChild(parentPtr, value);
	}

	Entry* Dictionary::findSubentry(Entry* entry, uint16_t index)
	{
		for (uint16_t i = 0; i < entry->childrenLength; i++)
		{
			if (entry->children[i]->code == index) return entry->children[i];
			else
			{
				Entry* ptr = findSubentry(entry->children[i], index);
				if (ptr != nullptr) return ptr;
			}
		}
		return nullptr;
	}
	Entry* Dictionary::findEntry(uint16_t index)
	{
		if (index < MAX_CHILDREN_NUMBER) return initialEntries[index];

		Entry* ptr = nullptr;
		for (uint16_t i = 0; i < MAX_CHILDREN_NUMBER; i++)
		{
			ptr = findSubentry(initialEntries[i], index);
			if (ptr != nullptr) return ptr;
		}
		return ptr;
	}

	bool Dictionary::containsString(char* string, uint16_t length)
	{
		if (length == 0) return false;
		bool contains = false;
		for (uint16_t i = 0; i < MAX_CHILDREN_NUMBER; i++)
		{
			if (initialEntries[i]->value == string[0])
			{
				contains = substring(initialEntries[i], string, length);
			}
		}
		return contains;
	}


	bool Dictionary::substring(Entry* start, char* string, uint16_t length)
	{
		if (length == 0) return true;
		if (start->value == string[0])
		{
			bool contains = false;
			if (length == 1) return true;
			for (uint16_t i = 0; i < start->childrenLength; i++)
			{
				if (substring(start->children[i], (string + 1), length - 1)) contains = true;
			}
			return contains;
		}
		else return false;
	}

	uint16_t Dictionary::findIndex(char* string, uint16_t length)
	{
		//throw exception, define exception
		if (length == 0) return 0;
		bool continueLoop = true;
		int stringValue = (uint16_t)string[0];
		Entry* node = this->initialEntries[string[0]];

		//line not needed
		if (length == 1) return node->code;

		for (uint16_t i = 0; i < length; i++)
		{
			if (i == length - 1) return node->code;

			for (uint16_t j = 0; j < node->childrenLength; j++)
			{
				if (node->children[j]->value == string[i + 1]) {
					node = node->children[j];
					break;
				}
			}
		}
		//remove?
		return node->code;
	}
#pragma endregion Dictionary_implementation

#pragma region LZW_implementation

	uint16_t* encodeLZW(char* originalData)
	{
		try
		{
			Dictionary* encodingDictionary = new Dictionary();

			uint16_t* encodedStream = new uint16_t[4096];
			uint16_t streamMax = 4096;
			encodedStream[0] = 0;
			uint16_t streamLength = 0;

			char* dataStream = originalData;
			char* currentCharacter = dataStream;
			uint16_t substringLength = 0;

			while (*dataStream >= 0)
			{
				//if string is in the dictionary, continue search with longer string
				if (encodingDictionary->containsString(dataStream, substringLength + 1))
				{
					/*
					for (int i = 0; i < substringLength + 1; i++)
					{
						std::cout << dataStream[i];
					}
					std::cout << std::endl; */
					substringLength++;
				}
				//if the string is not in the dictionary, encoded the last entry in dictionary, add new entry to the dictionary
				else
				{
					encodedStream[streamLength + 1] = encodingDictionary->findIndex(dataStream, substringLength);
					encodedStream[0] = streamLength;
					streamLength++;

					encodingDictionary->addChild(encodedStream[streamLength], dataStream[substringLength]);

					dataStream = dataStream + substringLength;
					substringLength = 0;

					//if all alocated memory is used, allocate more memory
					if (streamLength >= streamMax) {
						streamMax = (streamMax << 1);
						uint16_t* newStream = new uint16_t[streamMax];
						for (uint16_t i = 0; i < streamLength; i++) newStream[i] = encodedStream[i];

						delete[] encodedStream;
						encodedStream = newStream;
					}
				}
			}

			encodedStream[streamLength + 1] = static_cast<char>EOF;
			streamLength++;
			encodedStream[0] = streamLength;

			return encodedStream;
		}
		catch (...)
		{
			//throw custom exception
			//std::cout << "encodeLZw exception" << std::endl;
			return nullptr;
		}
	}

	char* decodeLZW(uint16_t* encodedData)
	{
		Dictionary* decodingDictionary = new Dictionary();

		uint16_t streamLength = encodedData[0];
		uint16_t decodedLength = 0;
		encodedData = encodedData + 1;
		char* decodedStream = new char[streamLength+1];
		uint16_t streamMax = streamLength;

		//decodedStream[0] = 0;

		for (uint16_t i = 0; i < streamLength-1; i++)
		{
			if (encodedData[i] == static_cast<uint8_t>(EOF)) break;
			Entry* entry = decodingDictionary->findEntry(encodedData[i]);
			std::stack<char> string;

			while (entry != nullptr)
			{
				string.push(entry->value);
				entry = entry->parent;
			}

			if (decodedLength + string.size() + 1 >= streamMax)
			{
				streamMax = (streamMax << 1);
				char* newArray = new char[streamMax];

				for (uint16_t i = 0; i < decodedLength; i++)
				{
					newArray[i] = decodedStream[i];
				}
				delete[] decodedStream;
				decodedStream = newArray;
			}

			if (i != 0 && !string.empty() ) decodingDictionary->addChild(encodedData[i - 1], string.top());

			while (!string.empty())
			{
				decodedStream[decodedLength] = string.top();

				string.pop();
				decodedLength++;
			}
		}
		//decodedStream[0] = decodedLength;
		decodedStream[decodedLength + 1] = static_cast<uint8_t>(-1);
		return decodedStream;
	}

#pragma endregion LZW_implementation
}

#endif // !lzw_algorithm_hpp

