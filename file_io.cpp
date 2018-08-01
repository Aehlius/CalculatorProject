#include "std_lib_facilities.h"

struct Reading {
    int integer;
    double double1;
    double double2;
};


int main()
{
    cout << "Please enter input file name: ";
    string iname;
    cin >> iname;
    ifstream ist {iname}; // ist reads from the file named iname
    if (!ist) error("can't open input file ",iname);

    string oname;
    cout << "Please enter name of output file: ";
    cin >> oname;
    ofstream ost {oname}; // ost writes to a file named oname
    if (!ost) error("can't open output file ",oname);

    vector<Reading> nums;
    int integer;
    char char1;
    double double1;
    char char2;
    double double2;
    while (ist >> integer >> char1
        >> double1 >> char2 >> double2) {
        nums.push_back(Reading{integer, double1, double2});
    }

    for (int i=0; i<nums.size(); ++i)
        ost << nums[i].integer << "\t"
              << nums[i].double1 << "\t"
                << nums[i].double2 << "\n";
    return 0;
}