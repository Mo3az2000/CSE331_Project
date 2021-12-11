#include "prototype.hpp"

using namespace std;
struct node
{
    string name = "";
    string content = "";
    int index;
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

void convert_to_json(vector <node> &tags, int index, string indent, string &json)
{
    string ind_temp;
    string tag_name = "";
    bool same_inner_tags = false;
    char opening_bracket = '{';
    char closing_bracket = '}';
    for(int i = 0; i < tags[index].children_indices.size(); i++)
    {
        if(tags[tags[index].children_indices[i]].name == tag_name) same_inner_tags = true;
        tag_name = tags[tags[index].children_indices[i]].name;
    }
    if(same_inner_tags)
    {
        opening_bracket = '[';
        closing_bracket = ']';
    }
    json = json + opening_bracket;
    for(int i = 0; i < tags[index].children_indices.size(); i++)
    {
        if(i != 0) json += ',';
        json = json + '\n' + indent;
        if(!(same_inner_tags))
        {
            json = json + '"' + tags[tags[index].children_indices[i]].name + '"' + ": ";
        }
        if(tags[tags[index].children_indices[i]].content != "") json = json + '"' + tags[tags[index].children_indices[i]].content + '"' ;
        else convert_to_json(tags, tags[index].children_indices[i], indent + "\t", json);
    }
    ind_temp = indent;
    ind_temp.pop_back();
    json = json + '\n' + ind_temp + closing_bracket;
}

void xml_to_json(string xml)
{
    fstream json_file;
    json_file.open("Json.json", ios::out);
    vector <node> tags;
    string json = "\t";
    tags = make_tree(xml);
    if (json_file.is_open())
    {
        convert_to_json(tags, 0, "\t\t", json);
        json_file << "{\n\t" << '"' << tags[0].name << '"' << ": " << '\n' << json << "\n}" << endl;
        json_file.close();
    }
}

int main()
{
    string file_name;
    bool error;
    cout << "Please enter the xml file path: ";
    cin >> file_name;
    while(true)
    {
        int command;
        cout << "Please enter command number:\n1)Detect error\n2)Correct error\n3)Formating XML\n4)Convert to Jason\n5)Compress\n6)End program\nCommand number: ";
        cin >> command;
        if(command == 1) error = check_XML(file_name);
        if(command == 2) correct(file_name);
        else if(command == 3) format(file_name);
        else if(command == 4) xml_to_jason(file_name);
        else if(command == 5) compress(file_name);
        else return 0;
    }

    return 0;
}