#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <string>
#include <fstream>

using namespace std;
struct node
{
    string name = "";
    string content = "";
    int index;
    int parent_index;
    vector <int> children_indices;
};

string get_tag(string &line, int &index)
{
    string tag = "";
    while(line[++index] != '>') tag += line[index];
    return tag;
}

vector <node> make_tree(string file_name)
{
    vector <node> tags;
    string xml_string = "";
    fstream xml_file;
    stack <int> tags_stack_indices;
    xml_file.open(file_name, ios::in);
    if (xml_file.is_open())
    {
        string xml_line;
        int tag_index = -1;
        while (getline(xml_file, xml_line))
        {
            int i = 0;
            while(xml_line[i] == ' ' || xml_line[i] == '\t') i++;
            if(xml_line[i] == '<' && xml_line[i+1] != '/')
                {
                    tag_index++;
                    tags.push_back(node());
                    tag_index = tags.size() - 1;
                    tags[tag_index].name = get_tag(xml_line, i);
                    tags[tag_index].index = tag_index;
                    if(tag_index != 0)
                    {
                        tags[tag_index].parent_index = tags[tags_stack_indices.top()].index;
                        tags[tags_stack_indices.top()].children_indices.push_back(tag_index);
                    }
                    tags_stack_indices.push(tag_index);
                    i++;
                }
            if(xml_line[i] != '<' && i < xml_line.length())
            {
                while(xml_line[i] != '<' && i < xml_line.length()) 
                tags[tag_index].content += xml_line[i++];
            }
            if(xml_line[i] == '<' && xml_line[++i] == '/' && i < xml_line.length())
            {
                tags_stack_indices.pop();
                while(xml_line[++i] != '>');
            }
        }
        xml_file.close();
    }
    return tags;
}

// void print_tree(vector <node> &tags, int index)
// {
//     cout << "entered print_tree" << endl;
//     for(int i = 0; i < tags[index].children_indices.size(); i++)
//     {
//         print_tree(tags, tags[index].children_indices[i]);
//     }
//     cout << tags[index].name << endl;
//     if(tags[index].content != "") cout << tags[index].content << endl;
// }

void xml_to_json(string xml)
{
    fstream json_file;
    json_file.open("Json.json", ios::out);
    vector <node> tags;
    string json = "";
    tags = make_tree(xml);
    if (json_file.is_open())
    {
        json_file.close();
    }
    //print_tree(tags, 0);
}

int main()
{
    string file_name = "fileWithSpaces.xml";
    xml_to_json(file_name);
    return 0;
}