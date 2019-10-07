#ifndef _DARDY_HISTOGRAM_H
#define _DARDY_HISTOGRAM_H

#include <stdio.h>
#include <iomanip>
#include <iostream>
/*
drawHistogram: takes array and draws an appropriate ascii histogram (horizontal) of its distribution
Arguments
* out : the ostream to write to
* HIST : the character to use in drawing
* arr : the array that is used as input
* n : the size of the previous argument
* st : the smallest value to start drawing from
* en : the biggest value to end drawing at
* pins: the number of pins to draw.
* max_width: the maximum width of the histogram
*/
template<typename T>
void drawHistogram(std::ostream& out, char HIST, T arr[], int n, int st, int en, int pins, int max_width) {
	if (n <= 0) return;

	int off = st;
	int factor = (en - st) / pins;
	if (factor < 1) factor = 1;

	int* freq = new int[pins];
	for (int i = 0; i < pins; i++) {
		freq[i] = 0;
	}
	int longest = 0;
	for (int i = 0; i < n; i++) {
		int v = (arr[i] - off) / factor;
		if (v < 0 || v > pins || arr[i] > en || arr[i] < st) continue;

		if (++freq[v] > longest) {
			longest = freq[v];
		}
	}

	const char* format = "%d - ";
	char temp[20];
	for (int i = 0; i < pins; i++) {
		std::sprintf(temp, format, factor * i + off);
		out << std::left << std::setw(20) << temp;

		int wd = 1.0 * freq[i] * max_width / longest + 0.5;


		for (int j = 0; j < wd; j++)
			out << HIST;

		out << std::endl;
	}
	out << std::endl;

	delete[] freq;
}


#endif // !_DARDY_HISTOGRAM_H
