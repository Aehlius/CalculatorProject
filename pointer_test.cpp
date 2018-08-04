#include "std_lib_facilities.h"

int main(){
    char ch = 'x';
    int i = 1;
    double db = 3.14159;

    char* char_pointer = &ch;
    int* int_pointer = &i;
    double* double_pointer = &db;

    cout << "\n\nThis program prints out the sizes of pointers and variables\n\n";

    cout << "Character pointer = " << char_pointer << "; contents of pointer = " << *char_pointer << '\n';
    cout << "Integer pointer = " << int_pointer << "; contents of pointer = " << *int_pointer << '\n';
    cout << "Double pointer = " << double_pointer << "; contents of pointer = " << *double_pointer << '\n';

    cout << "\nThe size of character pointer is " << sizeof(char_pointer)
        << "; the size of character variable is " << sizeof(ch);
    cout << "\nThe size of integer pointer is " << sizeof(int_pointer)
        << "; the size of integer variable is " << sizeof(i);
    cout << "\nThe size of double pointer is " << sizeof(double_pointer)
        << "; the size of double variable is " << sizeof(db);

    cout << "\n\nThank you for using the program, have a great day!\n\n";

    return 0;
}