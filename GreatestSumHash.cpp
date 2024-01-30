
//GreatestSumHash.cpp

#include <fstream>
#include <iostream>
#include "myHash.h"

using namespace std;

int main()
{
	std::ifstream in_data;

	// Open the file containing the data
	in_data.open("s.txt");
	// in_data.open("d.txt");

    if (!in_data) {
        cerr << "Error opening input file." << endl;
        return 1; // Exit the program with an error code
    }

	// Creating an instance of the myHash class
	myHash<int, bool> obj_hash;


	while (true) {

		int n;
		int data;
		int greatest_value = 0;

		// Reading number of elements
		in_data >> n;

		// Exit the loop if a zero is read, indicating no more sets
		if (n == 0) break;

		// Dynamically allocate memory for keys
		int *keys = new int[n];

		// Reading data and populating the hash table
		for (int i = 0; i < n; i++)
		{
			in_data >> data;
			keys[i] = data;

			if (data > greatest_value)
				greatest_value = data;

			obj_hash[data] = true;
		}

		int greatest_sum = 0;
		// Finding the greatest sum of three distinct elements
		for (int i = 0; i < greatest_value; i++) {
			for (int j = 0; j < greatest_value && obj_hash[i]; j++) {
				for (int z = 0; z < greatest_value && obj_hash[j]; z++) {
					if (obj_hash[z] && (i != j) && (j != z) && (i != z) && ((i + j + z) == greatest_value))  {
						if (obj_hash[i] && obj_hash[j] && obj_hash[z] && greatest_sum < greatest_value)
							greatest_sum = i + j + z;
					}
				}
			}
		}

		//obj_hash.printHashTable();

		// Printing the result
		if(greatest_sum != 0)
			cout << "greatest_sum: " << greatest_sum << endl;
		else
			cout << "No Solution" << endl;

		// Clean up dynamically allocated memory
    	delete[] keys;
	}

    return 0;
}

