#include <stdio.h>

const char* errorMessages[] = {
    "Operation successful", 
    "File not found", 
    "Permission denied", 
    "Invalid input",
    // Add more error messages as needed
};


int main () {
    printf("Testing: %s", errorMessages[0]);
}