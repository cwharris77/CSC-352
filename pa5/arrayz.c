/*
 * Cooper Harris
 * CSC 352
 *
 * This program defines functions to get data about long and double arrays
 * It assumes that the arrays hold the length of the remaining elements in
 * the array at index 0
 */
 
#include <stdio.h>
#include <math.h>
#include "arrayz.h"

long sum(long values[]) {
	// the length of the array remaining
	int length = values[0];
	long sum = 0;

	for (int i = 1; i <= length; i++) {
		sum += values[i];
	}

	return sum;
}


long minil(long values[]) {
	long minVal = values[1], minIndex = 1;

	for (int i = 1; i <= values[0]; i++) {
		if (values[i] < minVal) {
			minVal = values[i];
			minIndex = i;
		}
	}
	return minIndex;
}


long minid(double values[]) {
	double minVal = values[1], minIndex = 1;

	for (int i = 1; i <= values[0]; i++) {
		if (values[i] < minVal) {
			minVal = values[i];
			minIndex = i;
		}
	}
	return minIndex;
}


long maxil(long values[]) {
	double maxVal = values[1], maxIndex = 1;

	for (int i = 1; i <= values[0]; i++) {
		if (values[i] > maxVal) {
			maxVal = values[i];
			maxIndex = i;
		}
	}
	return maxIndex;
}

long maxid(double values[]) {
	double maxVal = values[1], maxIndex = 1;

	for (int i = 1; i <= values[0]; i++) {
		if (values[i] > maxVal) {
			maxVal = values[i];
			maxIndex = i;
		}
	}
	return maxIndex;
}

void printal(long values[]) {
	printf("length %ld array: ", values[0]);

	for (int i = 1; i <= values[0]; i++) {
		if (i < values[0]) {
			printf("%ld, ", values[i]);
		} else {
			printf("%ld\n", values[i]);
		}
	}
}

void printad(double values[]) {
	printf("length %lf array: ", values[0]);

	for (int i = 1; i <= values[0]; i++) {
		if (i < values[0]) {
			printf("%lf, ", values[i]);
		} else {
			printf("%lf\n", values[i]);
		}
	}
}

double mean(long values[]) {
	double mean = 0;

	for (int i = 1; i <= values[0]; i++) {
		mean += values[i];
	}

	return mean / values[0];
}

double sdev(long values[]) {
	double mean = 0, meansSqrd = 0;
	long sqrdDifferences[values[0] + 1];

	sqrdDifferences[0] = values[0];

	for (int i = 1; i <= values[0]; i++) {
		mean += values[i];
	}
	
	mean /= values[0];

	for (int i = 1; i <= values[0]; i++) {
		sqrdDifferences[i] = pow((values[i] - mean), 2);
	}
	
	for (int i = 1; i <= sqrdDifferences[0]; i++) {
		meansSqrd += sqrdDifferences[i];
	}
	
	meansSqrd /= sqrdDifferences[0];

	return sqrt(meansSqrd);
}

