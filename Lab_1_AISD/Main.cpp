#include <iostream>
#include "Set.h"
#include <chrono>
#include <array>
#include<random>
using namespace std;
using hrc= std::chrono::high_resolution_clock;
using namespace std::chrono;

int main()
{
	try {
		Set r;
		//r.insert(19);
		//r.insert(25);
		//r.insert(40);
		//r.insert(57);
		//r.insert(23);
		//r.insert(8);
		//r.insert(1);
		//r.insert(14);
		//r.print();
		//std::cout<< endl<<"========" << endl;
		//std::cout<< r.find(1000) << endl;
		//std::cout<< r.find(57) << endl;
		//std::cout<< "========" << endl;
		//r.erase(50);
		//r.erase(555);
		//r.print();
		Set r;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		for (int i = 0; i < 10; i++)
		{
			begin = std::chrono::steady_clock::now();
			for (int j = 1; j < 100000; j++)
			{
				r.insert(i * 100000 + j);
			}
			end = std::chrono::steady_clock::now();
			std::cout << "Diff(ms) = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
		}
	}
	catch (const char* err) {
		std::cout << err<<endl;
 	};
	return 0;
}