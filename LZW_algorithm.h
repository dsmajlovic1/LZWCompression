#ifndef lzw_algorithm_hpp
#define lzw_algorithm_hpp

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stack>

namespace lzw_compression
{

	static uint16_t MAX_CHILDREN_NUMBER = 256;
	static uint16_t MAX_ENTRY_NUMBER = uint16_t(std::numeric_limits<uint16_t>::max);

	//Dictionary node class
	class Entry
	{
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
		uint16_t entriesMax;
	public:
		Dictionary();
		~Dictionary();

		uint16_t Length();
		void logSubentries(Entry* parent, System::String^ indent);
		void logDictionary();
		bool substring(Entry* start, char* string, uint16_t length);
		Entry* findSubentry(Entry* entry, uint16_t index);
		bool addChild(Entry* parent, char value);
		bool addChild(uint16_t index, char value);
		bool containsString(char* string, uint16_t length);
		uint16_t findIndex(char* string, uint16_t length);
		Entry* findEntry(uint16_t index);
	};

	//LZW implemention
	uint32_t encodeLZW(char* originalData, uint32_t size, uint16_t*& encodedContainer);
	uint32_t decodeLZW(uint16_t* encodedData, uint32_t size, char*& decodedContainer);



	//Methods implementations

#pragma region Entry_implementation
	Entry::Entry(Entry* parent, uint16_t code, char value)
	{
		this->parent = parent;
		this->code = code;
		this->value = value;
		childrenLength = 0;
		childrenMax = (1 << 8);
		children = new Entry * [childrenMax];
		for (int i = 0; i < childrenMax; i++) children[i] = nullptr;
	}

	Entry::~Entry()
	{
		for (int i = 0; i < childrenLength; i++)
		{
			delete children[i];
		}
		delete[] children;
	}

	bool Entry::addChild(Entry* newEntry)
	{
		if (childrenLength >= MAX_CHILDREN_NUMBER) return false;
		try
		{			
			children[childrenLength] = newEntry;

			//if all alocated memory is used, allocate more memory
			if (this->childrenLength >= this->childrenMax)
			{
				if (childrenMax >= MAX_CHILDREN_NUMBER) return false;
				if (this->childrenLength * 2 < MAX_CHILDREN_NUMBER) childrenMax = childrenLength * 2;
				else childrenMax = MAX_CHILDREN_NUMBER;

				Entry** newArray = new Entry * [this->childrenMax];

				for (int i = 0; i < childrenLength; i++)
				{
					newArray[i] = children[i];
				}

				delete[] children;
				children = newArray;
			}
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
		initialEntries = new Entry * [MAX_CHILDREN_NUMBER*2];
		entriesMax = MAX_CHILDREN_NUMBER * 2;
		entriesNumber = MAX_CHILDREN_NUMBER;

		for (int i = 0; i < MAX_CHILDREN_NUMBER; i++)
		{
			Entry* newEntry = new Entry(nullptr, i, (char(i)));
			initialEntries[i] = newEntry;
		}

		//initialEntries = entryList;
	}
	Dictionary::~Dictionary()
	{
		for (int i = 0; i < MAX_CHILDREN_NUMBER; i++)
		{
			delete initialEntries[i];
		}
		delete[] initialEntries;
	}
	uint16_t Dictionary::Length()
	{
		return this->entriesNumber;
	}
	bool Dictionary::addChild(Entry* parent, char value)
	{
		if (this->entriesNumber >= MAX_ENTRY_NUMBER) return false;
		if (parent->childrenLength >= MAX_CHILDREN_NUMBER) throw "Dictionary capacity reached";

		//parent->children[parent->childrenLength] = new Entry(parent, parent->childrenLength, value);
		//parent->childrenLength++;
		try
		{
			Entry* newEntry = new Entry(parent, this->entriesNumber, value);
			if (parent->addChild(newEntry)) {
				initialEntries[newEntry->code] = newEntry;
				this->entriesNumber++;

				if (entriesNumber >= entriesMax) {
					if (entriesNumber * 2 < MAX_ENTRY_NUMBER) entriesMax = entriesNumber * 2;
					else entriesMax = MAX_ENTRY_NUMBER;
					Entry** newArray = new Entry * [entriesMax];

					for (int i = 0; i < entriesNumber; i++)
					{
						newArray[i] = initialEntries[i];
					}
					delete[] initialEntries;
					initialEntries = newArray;
				}

				return true;
			}
			else {
				delete newEntry;
				return false;
			}
		}
		catch (...)
		{
			//std::cout << "addChild exception" << std::endl;
			return false;
		}
	}

	void Dictionary::logSubentries(Entry* parent, System::String^ indent)
	{
		System::IO::StreamWriter^ stream = System::IO::File::AppendText("C:\\Users\\Delila\\Desktop\\logTree.txt");
		array<char>^ writeArray = gcnew array<char>(6);
		writeArray[0] = static_cast<char>((parent->code >> 8));
		writeArray[1] = static_cast<char>(parent->code);
		writeArray[2] = '-';
		writeArray[3] = parent->value;
		writeArray[4] = ':';
		writeArray[5] = '\n';
		//char* charOne = new char[1];
		//charOne[0] = static_cast<char>(writeArray[3]);
		char charOne = static_cast<char>(writeArray[3]);
		//if(stream->Length == 0)stream->Write(writeArray, stream->Length, 6);
		//else stream->Write(writeArray, stream->Length-1, 6);
		System::String^ string = gcnew System::String(indent + parent->code.ToString() + "-" + gcnew System::String(&charOne)+ " sub "+ parent->childrenLength.ToString()+  ":\n");
		stream->WriteLine(string);
		//delete[] charOne;

		stream->Close();
		for (int i = 0; i < parent->childrenLength; i++)
		{
			logSubentries(parent->children[i], indent+"		");
		}
			

		
	}

	void Dictionary::logDictionary()
	{
		if (System::IO::File::Exists("C:\\Users\\Delila\\Desktop\\logTree.txt"))
		{
			System::IO::File::Delete("C:\\Users\\Delila\\Desktop\\logTree.txt");
		}
		System::IO::File::Create("C:\\Users\\Delila\\Desktop\\logTree.txt")->Close();
		for (int i = 0; i < MAX_CHILDREN_NUMBER; i++)
		{
			logSubentries(this->initialEntries[i], "");
		}
			


	}

	bool Dictionary::addChild(uint16_t index, char value)
	{
		if (this->entriesNumber >= MAX_ENTRY_NUMBER) return false;
		if (index >= this->entriesNumber) return false;
		if (index < MAX_CHILDREN_NUMBER) return this->addChild(initialEntries[index], value);

		Entry* parentPtr = nullptr;
		for (int i = 0; i < MAX_CHILDREN_NUMBER; i++)
		{
			parentPtr = findSubentry(initialEntries[i], index);
			if (parentPtr != nullptr) break;
		}

		return this->addChild(parentPtr, value);
	}

	Entry* Dictionary::findSubentry(Entry* entry, uint16_t index)
	{
		Entry* ptr = nullptr;
		for (int i = 0; i < entry->childrenLength; i++)
		{
			if (entry->children[i]->code == index) return entry->children[i];
			else
			{
				ptr = findSubentry(entry->children[i], index);
				if (ptr != nullptr) return ptr;
			}
		}
		return ptr;
	}
	Entry* Dictionary::findEntry(uint16_t index)
	{
		/*if (index < MAX_CHILDREN_NUMBER) return initialEntries[index];

		Entry* ptr = nullptr;
		for (int i = 0; i < MAX_CHILDREN_NUMBER; i++)
		{
			ptr = findSubentry(initialEntries[i], index);
			if (ptr != nullptr) return ptr;
		}
		return ptr;*/
		if (index < entriesNumber) return initialEntries[index];
		else return nullptr;
	}

	bool Dictionary::containsString(char* string, uint16_t length)
	{
		if (length == 0) return false;
		if (length == 1 && string[0] >= 0 && string[0] < 256) return true;

		bool contains = false;
		for (int i = 0; i < MAX_CHILDREN_NUMBER; i++)
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
			for (int i = 0; i < start->childrenLength; i++)
			{
				if (substring(start->children[i], (string + 1), length - 1)) contains = true;
			}
			return contains;
		}
		else return false;
	}

	uint16_t Dictionary::findIndex(char* string, uint16_t length)
	{
		if (length == 0) return 0;
		if (string[0] > 256 || string[0] < 0) return 0;
		bool continueLoop = true;
		int stringValue = (uint16_t)string[0];
		Entry* node = this->initialEntries[string[0]];

		if (length == 1) return node->code;

		for (int i = 0; i < length; i++)
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

		return node->code;
	}
#pragma endregion Dictionary_implementation

#pragma region LZW_implementation

	uint32_t encodeLZW(char* originalData, int size, uint16_t* &encodedContainer)
	{
		try
		{
			Dictionary* encodingDictionary = new Dictionary();

			uint16_t* encodedStream = new uint16_t[size];
			int streamMax = size;
			int streamLength = 0;
			int current = 0;

			char* dataStream = originalData;
			int substringLength = 1;

			while (current < size)
			{
				//if string is in the dictionary, continue search with longer string
				if (encodingDictionary->containsString(dataStream, substringLength) && (dataStream + substringLength < originalData + size))
				{
					substringLength++;
					current++;
				}
				else if (encodingDictionary->containsString(dataStream, substringLength) && (dataStream + substringLength == originalData + size))
				{
					current++;
					//if all alocated memory is used, allocate more memory
					if (streamLength >= streamMax) {
						streamMax = (streamMax << 1);
						uint16_t* newStream = new uint16_t[streamMax];
						for (int i = 0; i < streamLength; i++) newStream[i] = encodedStream[i];

						delete[] encodedStream;
						encodedStream = newStream;
					}

					encodedStream[streamLength] = encodingDictionary->findIndex(dataStream, substringLength);
					streamLength++;
				}
				//if the string is not in the dictionary, encode the last found entry in dictionary, add new entry to the dictionary
				else
				{
					//if all alocated memory is used, allocate more memory
					if (streamLength >= streamMax) {
						streamMax = (streamMax << 1);
						uint16_t* newStream = new uint16_t[streamMax];
						for (int i = 0; i < streamLength; i++) newStream[i] = encodedStream[i];

						delete[] encodedStream;
						encodedStream = newStream;
					}

					encodedStream[streamLength] = encodingDictionary->findIndex(dataStream, substringLength - 1);
					encodingDictionary->addChild(encodedStream[streamLength], dataStream[substringLength - 1]);
					
					streamLength++;

					dataStream = dataStream + substringLength -1;
					substringLength = 1;
				}
			}
			

			//encodingDictionary->logDictionary();

			delete encodingDictionary;

			encodedContainer = encodedStream;

			return streamLength;
		}
		catch (...)
		{
			throw "Encoding error";
		}
	}

	uint32_t decodeLZW(uint16_t* encodedData, uint32_t size, char* &decodedContainer)
	{
		try
		{
			Dictionary* decodingDictionary = new Dictionary();

			//uint32_t streamLength = size;
			uint32_t decodedLength = 0;
			char* decodedStream = new char[size];
			uint32_t streamMax = size;

			for (int i = 0; i < size; i++)
			{
				if (i >= 200000)
				{
					i = i;
				}

				Entry* entry;
				Entry* entryPtr;
				if (encodedData[i] == decodingDictionary->Length())
				{
					entry = decodingDictionary->findEntry(encodedData[i - 1]);
				}
				else {
					entry = decodingDictionary->findEntry(encodedData[i]);
				}
				std::stack<char> string;
				entryPtr = entry;

				while (entry != nullptr)
				{
					string.push(entry->value);
					entry = entry->parent;
				}

				if (decodedLength + string.size() >= streamMax)
				{
					streamMax = (streamMax << 2);
					char* newArray = new char[streamMax];

					for (int i = 0; i < decodedLength; i++)
					{
						newArray[i] = decodedStream[i];
					}
					delete[] decodedStream;
					decodedStream = newArray;
				}

				if (i != 0 && !string.empty() && encodedData[i] != decodingDictionary->Length()) decodingDictionary->addChild(encodedData[i - 1], string.top());
				else if (i != 0 && !string.empty() && encodedData[i] == decodingDictionary->Length())
				{
					decodingDictionary->addChild(entryPtr, string.top());

					entry = decodingDictionary->findSubentry(entryPtr, encodedData[i]);
					while (!string.empty())
					{
						string.pop();
					}
					while (entry != nullptr)
					{
						string.push(entry->value);
						entry = entry->parent;
					}

				}

				while (!string.empty())
				{
					decodedStream[decodedLength] = string.top();

					string.pop();
					decodedLength++;
				}
			}
			delete decodingDictionary;

			char* shortenedArray = new char[decodedLength];
			for (int i = 0; i < decodedLength; i++)
				shortenedArray[i] = decodedStream[i];

			delete[] decodedStream;

			decodedContainer = shortenedArray;
			return decodedLength;
		}
		catch (...)
		{
			throw "Decoding error";
		}
	}

#pragma endregion LZW_implementation
}

#endif // !lzw_algorithm_hpp

