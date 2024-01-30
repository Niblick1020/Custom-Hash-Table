
// myHash.h

using namespace std;

template <class Type1, class Type2 >
class myHash
{
public:
// Constructor to initialize the hash table with default capacity
	myHash() {
		
		// Initialize table with 10 items, each having a chain of 5 entries
		table = new tableItem[10];

		for (int i = 0; i < 10; i++)
		{
			entry * temp;
			temp = new entry[5];
			table[i].list = temp;
			table[i].amount = 0;
			table[i].capacity = 5;
		}
		capacity = 10;
	}
	// Copy constructor (currently does the same as the default constructor)
	myHash(const myHash <Type1, Type2 >&) {
		table = new tableItem[10];

		for (int i = 0; i < 10; i++)
		{
			entry * temp;
			temp = new entry[5];
			table[i].list = temp;
			table[i].amount = 0;
			table[i].capacity = 5;
		}
		capacity = 10;
	}

	// Function to print all items in the hash table
	void printHashTable()
	{
		for (int i = 0; i < capacity; i++)
		{
			cout << "Table " << i << endl;
			for (int j = 0; j < table[i].amount; j++)
			{
				cout << "[ " << table[i].list[j].key << ", ";
				cout << table[i].list[j].item << " ]; ";
			}
			cout << "\n" << endl;
		}
	}

	const myHash <Type1, Type2 >& operator =(const myHash <Type1, Type2 >&);

	// Destructor to clean up dynamically allocated memory
	~myHash() {

		for (int i = 0; i < 10; i++)
			delete[] table[i].list;

		delete[] table;
	}

	// Overloading the '[]' operator to access hash table items
	Type2 & operator [](Type1 index) {

		size_t key = hashFunction(index);

		if (table[key].amount == table[key].capacity)
			increaseChain(key);

		int left = 0;
		int right = table[key].amount;
		int m = 0;

		while (left <= right)
		{
			m = (left + (right)) / 2;

			if (table[key].list[m].key == index)
				return table[key].list[m].item;
			else if (table[key].list[m].key < index)
				left = m + 1;
			else
				right = m - 1;
		}

		entry temp;
		temp.key = index;
		temp.item = Type2(0);
		entry temp2 = table[key].list[m];
		table[key].list[m] = temp;


		for (int i = m + 1; i < table[key].amount + 1; i++)
		{
			temp = temp2;
			temp2 = table[key].list[i];
			table[key].list[i] = temp;
		}

		table[key].amount++;

		return table[key].list[m].item;
	}
private:
	// Hash function to determine the index for a given key
	size_t hashFunction(int index) {

		size_t temp = 0;

		while (index > 0)
		{
			temp += index % 10;
			index = index / 10;
		}
		return(temp % capacity);
	}
	// Function to increase the chain length at a given index
	void increaseChain(int key) {
		entry * biggerList;
		biggerList = new entry[2 * table[key].capacity];

		for (int i = 0; i < table[key].capacity; i++)
		{
			biggerList[i] = table[key].list[i];
		}
		entry * temp = table[key].list;

		table[key].list = biggerList;

		delete[] temp;

		table[key].capacity = 2 * table[key].capacity;
	}

	// Inner struct representing a key-value pair
	struct entry
	{
		Type1 key;
		Type2 item;
	};
	// Inner struct representing a hash table item with its chain
	struct tableItem
	{
		size_t amount;
		size_t capacity;
		entry * list;
	};
	tableItem * table;
	size_t capacity;
};