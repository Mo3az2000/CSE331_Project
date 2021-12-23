#include <fstream>
#include <string>

using namespace std;

string fileToSring(string inputFile)
{
    fstream myInput;
    string myOutput = "";
    myInput.open(inputFile, ios::in);

    if (myInput.is_open())
    {
        string s;
        while (getline(myInput, s))
        {
            myOutput = myOutput +  s + "\n";
        }
        myInput.close();
        }
    return myOutput;
}
