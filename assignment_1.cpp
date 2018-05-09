// assignment_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned char byte;

string filter(string&);
byte asciihex(byte MSB, byte LSB);
void divide(vector<byte>&, vector<byte>&, vector<byte>&);
bool descending(byte i, byte j);

int main()
{
	fstream file, output;
	string name, line, text;
	vector<byte> bytes, odd, even;
	int bytes_lenght;

	cout << "Type the name of the file (example data.txt): ";
	cin >> name;

	file.open(name.c_str(), ios::in);

	if (file.good())
	{
		while (!file.eof())
		{
			getline(file, line);
			text.append(filter(line));
		}
	}
	else
	{
		cout << "Could not open a file" << endl;
		return 1;
	}

	output.open("output_file.txt", fstream::out);
	output << "Filtered text: \n" << text << endl << endl;

	if (text.length() % 2)
		bytes_lenght = (text.length() + 1) / 2;
	else
		bytes_lenght = text.length() / 2;

	output << "One-byte elements:" << endl;
	for (int i = 0; i < bytes_lenght; i++)
	{
		bytes.push_back(asciihex(text[2 * i], text[2 * i + 1]));
		//cout << hex << (int)bytes[i] << " " << bitset<8>(bytes[i]).count() << " ";    // for testing
		output << hex << (int)bytes[i] << " ";

	}
	output << endl << endl;

	//cout << endl << text << endl;   // for testing

	divide(bytes, odd, even);

	output << "Divided by odd number of ones:" << endl;
	for (int i = 0; i < odd.size(); i++)
	{
		//cout << hex << (int)odd[i] << " ";    // for testing
		output << hex << (int)odd[i] << " ";

	}

	//cout << " | | | " << endl;  // for testing

	output << endl << endl << "Divided by even number of ones:" << endl;
	for (int i = 0; i < even.size(); i++)
	{
		//cout << hex << (int)even[i] << " ";    // for testing
		output << hex << (int)even[i] << " ";
	}

	//cout << endl << "____________________" << endl;   // for testing

	sort(even.begin(), even.end());
	sort(odd.begin(), odd.end(), descending);

	output << endl << endl << "Odds sorted by descending order:" << endl;
	for (int i = 0; i < odd.size(); i++)
	{
		//cout << hex << (int)odd[i] << " ";    // for testing
		output << hex << (int)odd[i] << " ";
	}

	//cout << " | | | " << endl;   // for testing
	output << endl << endl << "Evens sorted by ascending order:" << endl;
	for (int i = 0; i < even.size(); i++)
	{
		//cout << hex << (int)even[i] << " ";   // for testing
		output << hex << (int)even[i] << " ";
	}

	cout << endl << "Calculations saved in output_file.txt." << endl;

	file.close();
	output.close();
	getchar();
	getchar();
    return 0;
}

string filter(string &from)
{
	string filtered;

	for (string::const_iterator i = from.begin(); i != from.end(); i++)
		if ((*i >= '0' && *i <= '9') || (*i >= 'A' && *i <= 'F')) 
		//if ((*i >= '0' && *i <= '9') || (*i >= 'A' && *i <= 'F') || (*i >= 'a' && *i <= 'f'))				// if filter is supposed to pass lower case letters too then
		{																									// uncoment the commented section and comment the if statament
			/*if (*i >= 'a' && *i <= 'f')
			{
				filtered += *i - 'a' + 'A';
				continue;
			}*/

			filtered += *i;
		}

	return filtered;
}

byte asciihex(byte MSB, byte LSB) 
{
	if (MSB > '9') 
		MSB -= 7;
	if (LSB > '9') 
		LSB -= 7;

	return (MSB << 4) | (LSB & 0x0F);
}
 
void divide(vector<byte> &bytes, vector<byte> &odd, vector<byte> &even)
{
	for (int i = 0; i < bytes.size(); i++)
		if (bitset<8>(bytes[i]).count() % 2)
			odd.push_back(bytes[i]);
		else
			even.push_back(bytes[i]);
}

bool descending(byte i, byte j)
{
	return i > j;
}
