#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

void spacing(string inputFile, string outputFile){
    fstream myInput;
    fstream myOutput;
    myOutput.open(outputFile, ios::out);
    myInput.open(inputFile, ios::in);
    if (myOutput.is_open())
    {
        if (myInput.is_open())
        {
            string s;
            stack<string> myStack;
            while (getline(myInput, s))
            {   
                int n = myStack.size();
                while((s[0]==' ')||(s[0]=='\t'))
                {
                    s.erase(0,1);
                }
                int ns = s.size()-1;
                while((s[ns]==' ')||(s[ns]=='\t')||(s[ns]=='\n')){
                    s.erase(ns,1);
                    ns = s.size()-1;
                }
                for (int i = 0; i < s.size(); i++)
                {
                    string x = "";
                    if (s[i] == '<')
                    {
                        i++;
                        while (s[i] != '>' && s[i] != '\0' && s[i]!=' ')
                        {
                            x = x + s[i];
                            i++;
                        }
                        cout << x <<"\n";
                        if (x[0] == '/')
                        {
                            myStack.pop();
                        }
                        else
                            myStack.push(x);
                    }
                }
                if (s[0] == '<' && s[1] == '/')
                {
                    n--;
                }
                string tabs(n, '\t');
                myOutput <<tabs<< s << endl;
            }

            myInput.close();
        }
        myOutput.close();
    }
}