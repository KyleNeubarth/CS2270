#include <chrono>
#include <thread>
#include <iostream>
using namespace std;

void update() {
	int i=0;
	while(i<5) {
		cout << i << "\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

int main() {
	update();
}