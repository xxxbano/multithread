
//=================================
//
// Project:	cpp program to demonstrate multithreading 
//
// Description:	
// 	- using three different callables
//
// Creator:	Zhengfan Xia
//
//=================================

#include <iostream>
#include <thread>

using namespace std;

// a dummy function
void foo(int Z) {
	for(int i=0; i<Z; i++) {
		cout << "Thread using funciont" " pointer as callable\n";
	}
}

// a callable object
class thread_obj {
	public:
		void operator()(int x){
			for(int i=0; i<x; i++)
				cout << "Thread using function" " object as callable\n";
		}
};

int main() {
	cout << "Threads 1 and 2 and 3" "operating independently" << endl;

	// This thread is launched by using function pointer as callable
	thread th1(foo, 3);

	// This thread is launched by using function object as callable
	thread th2(thread_obj(), 3);

	// Define a Lambda Expression
	auto f = [](int x) {
		for(int i=0; i<x; i++) 
			cout << "Thread using lambda" " expression as callable\n";
	};

	// This thread is launched by using lamda expression as callable
	thread th3(f, 3);

	// wait for the threads to finish
	th1.join();
	th2.join();
	th3.join();

	return 0;

}
