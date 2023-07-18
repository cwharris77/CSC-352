/**
 * pythagorean.c
 * Author: Cooper Harris 
 * Course: CSC 252
 * 
 * This program prompts the user for two int inputs
 * (in the form Enter side A length:
 *              Enter side B length:)
 * representing two sides of a right triangle.
 * It then calculates the length of the hypotenuse and
 * prints a message showing the length of the hypotenuse
 * rounded to two deicimal places. 
 */

#include <stdio.h>
#include <math.h>

int main(){
    int sideA;
    int sideB;

    printf("Enter side A length:\n");
    scanf("%d", &sideA);

    printf("Enter side B length:\n");
    scanf("%d", &sideB);

    // pyhtagorean theorem
    double hypLen = sqrt((sideA*sideA) + (sideB*sideB));

    //print the hypotenuse length as a string to round it
    printf("Length of side C: %.2f\n", hypLen);

    return 0;
}
