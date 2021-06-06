#include "DenovoMFPM.h"

int main() {
	clock_t start, finish;
	double duration;

	start = clock();
	DenovoMFPM test;
	test.MergeShortRead();
	finish = clock();

	test.print();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << endl <<duration << "ÃÊ ¼Ò¿ä" << endl;
	test.GetAccuracy();
}