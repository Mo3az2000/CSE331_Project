#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

void eraseSpacing(string inputFile, string outputFile){
    fstream myInput;
    fstream myOutput;
    myOutput.open(outputFile, ios::out);
    myInput.open(inputFile, ios::in);
    if (myOutput.is_open())
    {
        if (myInput.is_open())
        {
            string s;
            while (getline(myInput, s))
            {   
                while((s[0]==' ')||(s[0]=='\t')||(s[0]=='\n'))
                {
                    s.erase(0,1);
                }
                int n = s.size()-1;
                while((s[n]==' ')||(s[n]=='\t')||(s[n]=='\n')){
                    s.erase(n,1);
                    n = s.size()-1;
                }
                myOutput <<s;
            }

            myInput.close();
        }
        myOutput.close();
    }
}