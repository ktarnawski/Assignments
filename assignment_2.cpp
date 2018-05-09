// assignment_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
	int test_cases, elements;
	string final;

	cout << "Number of test cases: " << endl;
	cin >> test_cases;
	cin.ignore();

	for (int i = 0; i < test_cases; i++)
	{
		cout << "Number of elements: " << endl;
		cin >> elements;
		cin.ignore();

		string line;
		cout << "Number sequence: " << endl;
		getline(cin, line);
		istringstream os(line);

		vector<int> sequence;

		int k;
		while (os >> k)
			sequence.push_back(k);

		bool check = false;

		int sum = 0;
		if (sequence.size() > 1)
		{
			for (int j = 0; j < sequence.size(); j++)
				sum += sequence[j];

			int left = 0, right = sum;

			for (int j = 0; j < sequence.size(); j++)
			{
				right -= sequence[j];

				if (left == right)
					check = true;

				left += sequence[j];
			}

			if (check)
				final += "Yes\n";
			else
				final += "No\n";
		}
		else
			final += "Yes\n";
	}

	cout << endl << final;

	getchar();
	return 0;
}