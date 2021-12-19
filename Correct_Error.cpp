#include <bits/stdc++.h>

using namespace std;

bool isText(char S) 
{
    if (S == '<' || S=='\000') 
        return false;

    return true;
}

bool isOpenTag(string S) 
{
    if (S[1] != '/') 
        return true;

    return false;
}

string generateCloseTag(string S) 
{
    string a = "<";
    string b = "/";
    string closedTop = a + b + S.substr(1);
    return closedTop;
}

void correctError(string S) 
{
    stack < string > st;
    string temp;
    string top3;
    int stringFlag = 1;
    int dontStackFlag = 0;
    fstream myFile;
    fstream myOutput;
    string line, line2;
    myFile.open(S, ios:: in ); //read only
    myOutput.open("output.xml", ios::out); // write only
    if (myOutput.is_open()) 
    {
        if (myFile.is_open()) 
        {
            while (getline(myFile, line)) 
            {
                int flag = 0;
                for (int i = 0; i < line.length(); i++) 
                {
                    if (line[i] != ' ')
                    {
                        stringFlag = 1;
                    }
                    if (line[i] == '<') 
                    {
                        stringFlag = 0;
                        for (int j = i; j < line.length(); j++) 
                        {
                            if (line[j] == '>') 
                            {
                                temp = line.substr(i, j - i + 1);
                                if (dontStackFlag)
                                {
                                    dontStackFlag = 0;
                                    flag = 1;
                                    myOutput << generateCloseTag(st.top()) << endl;
                                    st.pop();
                                    goto level_2;
                                }
                                if (isText(line[j + 1])) 
                                {
                                    if(line.back() != '>')
                                    {
                                        flag = 1;
                                        myOutput << line << generateCloseTag(temp) << endl;
                                        goto level_2;
                                    }
                                    for(int k = j; k < line.length(); k++)
                                    {
                                        if(line[k] != '<')
                                        {
                                            continue;
                                        }
                                        string temp2 = line.substr(k);
                                        if(generateCloseTag(temp) != temp2)
                                        {
                                            flag = 1;
                                            myOutput << line.substr(0,k) << generateCloseTag(temp) << endl;
                                            goto level_2;
                                        }
                                    }
                                } else if (isOpenTag(temp)) 
                                {
                                    if(!st.empty())
                                    {
                                        string top2 = st.top();
                                        if(temp == top2)
                                        {
                                            flag = 1;
                                            myOutput << generateCloseTag(temp) << endl;
                                            myOutput << temp << endl;
                                            goto level_2;
                                        }
                                    }
                                    st.push(temp);
                                }
                                else
                                {
                                    if (st.empty())
                                    {
                                        flag = 1;
                                        myOutput << line << "Fatal Error" << endl;
                                        goto level_2;
                                    }
                                    string top = st.top();
                                    string closedTop = generateCloseTag(top);
                                    if(closedTop == temp)
                                    {
                                        st.pop();
                                    }
                                    else
                                    {
                                        while(true)
                                        {
                                        myOutput << closedTop << endl;
                                        st.pop();
                                        top = st.top();
                                        closedTop = generateCloseTag(top);
                                        if (closedTop == temp)
                                        {
                                            st.pop();
                                            break;
                                        }
                                        }
                                        flag = 1;
                                        myOutput << line << endl;
                                        goto level_2;
                                    }
                                }
                                if (!flag)
                                {
                                    myOutput << line << endl;
                                    goto level_2;
                                }
                                break;
                            }
                        }
                    }
                }
                if (stringFlag)
                {
                    stringFlag = 0;
                    dontStackFlag = 1;
                    myOutput << line << endl;
                    goto level_2;
                }
                level_2: 
                int x = 0;
                while( x++ < 1 );
            }
            while (!st.empty())
            {
                top3 = st.top();
                myOutput << generateCloseTag(top3) << endl;
                st.pop();
            }
            myFile.close();
        }
        myOutput.close();
    }
}
