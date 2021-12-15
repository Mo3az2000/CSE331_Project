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

            while ((s[0] == ' ') || (s[0] == '\t'))
            {
                s.erase(0, 1);
            }
            int n = s.size() - 1;
            if(n<=0)continue;
            while ((s[n] == ' ') || (s[n] == '\t'))
            {
                s.erase(n, 1);
                n = s.size() - 1;
            }

            myOutput = myOutput +  s;
        }
        myInput.close();
        }
    return myOutput;
}
