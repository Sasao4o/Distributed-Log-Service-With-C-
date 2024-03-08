#include<iostream>
using namespace std;

#include "../../include/disk/File.h"
int main() {

logModule::File a("which");
 
char *x = "mostaaa";
a.WriteFile(0, x, 7);

 char *y = (char*)malloc(7);
 a.ReadFile(0, y, 7);

for (int i = 0; i < 7; i++) {
    cout << y[i];
}
cout << endl;
cout<<a.GetFileSize("which")<< endl;

}