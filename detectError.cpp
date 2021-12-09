#include <bits/stdc++.h>

using namespace std;

bool isText(char S) {
    if (S == '<' || S=='\000') {
        return false;
    }
    return true;
}

bool isOpenTag(string S) {
    if (S[1] != '/') {
        return true;
    }
    return false;
}

string generateCloseTag(string S) {
    string a = "<";
    string b = "/";
    string closedTop = a + b + S.substr(1);
    return closedTop;
}

void detectError(string S) {
    stack < string > st;
    string temp;
    fstream myFile;
    fstream myOutput;
    string line;
    myFile.open(S, ios:: in ); //read only
    myOutput.open("output.txt", ios::out); // write only
    if (myOutput.is_open()) {
        if (myFile.is_open()) {
            while (getline(myFile, line)) {
                int flag = 0;
                for (int i = 0; i < line.length(); i++) {
                    if (line[i] == '<') {
                        for (int j = i; j < line.length(); j++) {
                            if (line[j] == '>') {
                                temp = line.substr(i, j - i + 1);
                                if (isText(line[j + 1])) {
                                    if(line.back() != '>')
                                    {
                                        flag = 1;
                                        myOutput << line << "     Error Here" << endl;
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
                                            myOutput << line << "     Error Here" << endl;
                                            goto level_2;
                                        }
                                    }
                                } else if (isOpenTag(temp)) {
                                    st.push(temp);
                                }
                                else
                                {
                                    if (st.empty())
                                    {
                                        flag = 1;
                                        myOutput << line << "     Error Here" << endl;
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
                                        st.pop();
                                        flag = 1;
                                        myOutput << line << "     Error Here" << endl;
                                        goto level_2;
                                    }
                                }
                                if (flag == 0)
                                    myOutput << line << endl;
                                    goto level_2;
                                
                                break;
                            }
                        }
                    }
                }level_2: cout << 'h';
            }
            if (!st.empty())
                myOutput <<"Error Here" << endl;

            myFile.close();
        }
        myOutput.close();
    }
}