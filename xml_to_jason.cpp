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
    bool put_comma = false;
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
                    if(i == xml_line.size() - 1) continue;
                    else while(xml_line[++i] != '<') content += xml_line[i];
                    indent += '\t';
                    if(!put_comma) jason = jason + indent + '"' + tags.top() + '"' + ": " + '"' + content + '"';
                    else jason = jason + ",\n" + indent + '"' + tags.top() + '"' + ": " + '"' + content + '"';
                    put_comma = true;
                    get_closing_tag(tags, xml_line, ++i);
                }
                // else if(xml_line[i] == '<' && xml_line[i+1] != '/') get_closing_tag(tags, xml_line, ++i);
                // else
                // {

                // }
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