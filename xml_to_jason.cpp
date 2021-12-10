#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <string>
#include <fstream>

using namespace std;

void get_opening_tag(stack<string> &tags_stack, string &line, int &index)
{
    string tag = "";
    while(line[++index] != '>') tag += line[index];
    tags_stack.push(tag);
}

void get_closing_tag(stack<string> &tags_stack, string &line, int &index)
{
    string tag = "";
    while(line[++index] != '>') tag += line[index];
    tags_stack.pop();
}

void xml_to_jason(string xml)
{
    fstream xml_file;
    fstream jason_file;
    jason_file.open("Jason.jason", ios::out);
    xml_file.open("n1.xml", ios::in);
    string jason = "{\n";
    string indent = "";
    bool first_inner_tag = true;
    bool repeated_tag = false;
    string last_added_tag;
    if (jason_file.is_open())
    {
        if (xml_file.is_open())
        {
            string xml_line;
            string content = "";
            stack <string> tags;
            while (getline(xml_file, xml_line))
            {
                int i = 0;
                while(xml_line[i] == ' ' || xml_line[i] == '\t') i++;
                if(xml_line[i] == '<' && xml_line[i+1] != '/')
                {
                    get_opening_tag(tags, xml_line, i);
                    if(i == xml_line.size() - 1)
                    {
                        indent += '\t';
                        if(tags.top() == last_added_tag) repeated_tag = true;
                        continue;
                    }
                    else while(xml_line[++i] != '<') content += xml_line[i];
                    last_added_tag = tags.top();
                    if(first_inner_tag)
                    {
                        indent += '\t';
                        jason = jason + indent + '"' + last_added_tag + '"' + ": " + '"' + content + '"';
                        first_inner_tag = false;
                    }
                    else jason = jason + ",\n" + indent + '"' + last_added_tag + '"' + ": " + '"' + content + '"';
                    get_closing_tag(tags, xml_line, ++i);
                }
                else if(xml_line[i] == '<' && xml_line[i+1] == '/')
                {
                    if(repeated_tag) jason = ",\n" + jason;
                    else
                    {
                        indent.pop_back();
                    }
                    get_closing_tag(tags, xml_line, ++i);
                }
                else while(xml_line[i] < xml_line.size()) jason += xml_line[i];
            }

            xml_file.close();
        }
        jason_file.close();
    }
}

int main()
{
    string file_name;
    xml_to_jason(file_name);
    return 0;
}