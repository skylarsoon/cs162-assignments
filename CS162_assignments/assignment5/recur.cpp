#include <iostream>
using namespace std;

//print (num_spaces) white spaces
void print_spaces(int num_spaces) {
    for (int i = 0; i < num_spaces; i++) {
        cout << " ";
    }
}

//print stars, with white spaces in between
void print_stars(int num_stars) { //num stars - 2 is how many spaces are in between
    for (int i = 0; i < num_stars; i++) {
        if (i == 0 || i == num_stars - 1) {
            cout << "*";
        } else {
            cout << " ";
        }
    }
    cout << endl;
}

void top_half(int n, int col){
    if(n < 1){
        return;
    }
    top_half(n - 2, col + 1);
    print_spaces(col + 1);
    print_stars(n);
}

void bottom_half(int n, int col){
    if(n < 1){
        return;
    }
    print_spaces(col + 1);
    print_stars(n);
    bottom_half(n - 2, col + 1);
}

//n+(n-3) + 2 = 2n - 1
//3+(3-3) + 2 = 5
//5+(5-3) + 2 = 9
//7+(7-3) + 2 = 13


void pattern(int n, int col) {    
    //calculate n for middle row
    n = 2*n - 1;
    //top
    top_half(n - 2, col);

    //middle row
    print_spaces(col); // print leading spaces 
    print_stars(n); // print stars

    //bottom
    bottom_half(n-2, col);
}

int main() {
    int n, col;
    cout << "Enter the number of rows (odd number): ";
    cin >> n;
    cout << "Enter the leading white spaces: ";
    cin >> col;

    pattern(n, col);

    return 0;
}