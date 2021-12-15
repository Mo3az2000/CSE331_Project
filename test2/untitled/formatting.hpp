#include <string>
#include <stack>

using namespace std;

string formatting(string s)
{
    string MyOutput = "";
    stack<string> myStack;
    int n = myStack.size();
    for (int i = 0; s[i] != '\0';)
    {
        int n = myStack.size();
        string x = "";
        if (s[i] == '<')
        {
            // i++;

            while (s[i] != '>' && s[i] != '\0')
            {
                x = x + s[i];
                i++;
            }
            i++;
            x = x + ">";
            // cout << x << "\n";
            if (x[1] == '/')
            {
                myStack.pop();
                n--;
            }
            else if (x[1] != '!' && x[1] != '?')
                myStack.push(x);
        }

        else
        {
            while (s[i] != '<' && s[i] != '\0')
            {
                x = x + s[i];
                i++;
            }

            while ((x[0] == ' ') || (x[0] == '\t'))
            {
                x.erase(0, 1);
            }
            int ns = x.size() - 1;
            if (ns > 0)
            {
                while ((x[ns] == ' ') || (x[ns] == '\t'))
                {
                    x.erase(ns, 1);
                    ns = x.size() - 1;
                }
            }
            // cout << x << "\n";
        }
        string tabs(n, '\t');
        if (x.size())
        {
            MyOutput = MyOutput + tabs + x + "\n";
        }
    }
    return MyOutput;
}
