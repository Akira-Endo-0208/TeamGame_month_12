#include<math.h>
#pragma once

double easeOutBack(double start, double end, double time)
{
	double c1 = 1.70158;
	double c3 = c1 + 1.0;

	return end + c3 * (pow(time - 1, 3)) + c1 * (pow(time - 1, 2)) * (end - start);
}

double easeOutQuint(double start, double end, double time)
{
	return 1 + pow(1 - time, 5) * (end - start);
}

double easeOutCirc(double start, double end, double time) {
	return sqrt(1 - pow(time - 1, 2)) * (end - start);
}