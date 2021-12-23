#include <bits/stdc++.h>

using namespace std;

bool isText(char S) 
{
    return (S == '<' || S=='\000' || S==' ')? 0:1;
}

bool isOpenTag(string S) 
{
    return (S[1] != '/')? 1:0;
}

string generateCloseTag(string S) 
{
    string a = "<";
    string b = "/";
    string closedTop = a + b + S.substr(1);
    return closedTop;
}

string generateOpenTag(string S) 
{
    string a = "<";
    string openTag = a + S.substr(2);
    return openTag;
}

void correctError(string S) 
{
    int lineCount = 0;
    int userFlag = 1;
    stack < string > st;
    string temp, temp2;
    string top3;
    int stringFlag = 1;
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
                lineCount++;
                if (lineCount == 1)
                {
                    myOutput << "<users>" << endl;
                    myOutput << line << endl;
                    st.push(line);
                    continue;
                }
                int flag = 0;
                for (int i = 0; i < line.length(); i++) 
                {
                    if (line[i] != ' ')
                        stringFlag = 1;

                    if (line[i] == '<') 
                    {
                        stringFlag = 0;
                        for (int j = i; j < line.length(); j++) 
                        {
                            if (line[j] == '>') 
                            {
                                temp = line.substr(i, j - i + 1);
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
                                    if (st.empty()) // if closetag and empty stack
                                    {
                                        flag = 1;
                                        myOutput << generateOpenTag(temp) << endl;
                                        myOutput << line << endl;
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
                                        if (isText(line[i-1]))
                                        {
                                            myOutput << generateOpenTag(temp) << endl;
                                            myOutput << line << endl;
                                            goto level_2;
                                        }
                                        myOutput << closedTop << endl;
                                        st.pop();
                                        if (st.empty())
                                        {
                                            flag = 1;
                                            myOutput << generateOpenTag(temp) << endl;
                                            myOutput << line << endl;
                                            goto level_2;
                                        }
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
                    myOutput << line << endl;
                    goto level_2;
                }
                level_2: 
                int x = 0;
            }
            while (!st.empty())
            {
                top3 = st.top();
                myOutput << generateCloseTag(top3) << endl;
                st.pop();
            }
            myOutput << "</users>" << endl;
            myFile.close();
        }
        myOutput.close();
    }
}
