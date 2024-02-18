#include<iostream>
using namespace std;

#include "./include/disk/File.h"
int main() {

log::File a("which");
 
char *x = "mostaaa";
a.WriteFile(4, x, 4);

 char *y = (char*)malloc(4);
 a.ReadFile(0, y, 4);

for (int i = 0; i < 4; i++) {
    cout << y[i];
}

}