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
    vector <int> children_indices;
};

struct post
{
    string body = "";
    vector <string> topics;
};

struct identity
{
    int index = -1;
    string id = "-1";
};

struct user
{
    identity i;
    string name = "";
    vector <post> posts;
    vector <identity> followers;
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

vector <user> make_graph(vector <node> tags)
{
    vector <user> users;
    int user_index = -1;
    for(int i = 0; i < tags.size(); i++)
    {
        if(tags[i].name == "user") user_index++;
        if(tags[i].content == "") continue; //skips tags with no content inside it
        if(tags[i].name == "id") //handles id tags
        {
            if(user_index == users.size() - 1) //then this is a follower id
            {
                users[user_index].followers.push_back({-1,tags[i].content}); //we still dont't know the index of the follower we only knoe the id
            }
            else //then this a new user id
            {
                users.push_back(user());
                users[user_index].i.id = tags[i].content; //set user id
                users[user_index].i.index = user_index; //set user index in the vector
            }

        }
        else if(tags[i].name == "name") //hanles the name tags
        {
            users[user_index].name = tags[i].content;
        }
        else if(tags[i].name == "body") //hanles the body tags
        {
            users[user_index].posts.push_back(post()); //make a new post
            users[user_index].posts[users[user_index].posts.size() - 1].body = tags[i].content; //assign the body content to the new made post which is located at the end of the posts vector
        }
        else if(tags[i].name == "topic") //handles the topic tags
        {
            users[user_index].posts[users[user_index].posts.size() - 1].topics.push_back(tags[i].content); //add a new topic to the last post
        }
        //now everything is ready except for the indices of the followers
    }
    for(int i = 0; i < users.size(); i++)
    {
        for(int j = 0; j < users.size(); j++)
        {
            for(int k = 0; k < users[j].followers.size(); k++)
            {
                if(users[j].followers[k].id == users[i].i.id)
                {
                    users[j].followers[k].index = users[i].i.index;
                    break; //if found a follower then for the same user you won't find another follower with the same id since no parallel edges
                }
            }
        }
    }
    return users;
}

void print_graph(vector <user> users)
{
    cout << "Graph:\n";
    for(int i = 0; i < users.size(); i++)
    {
        cout << "id: " << users[i].i.id << "\n";
        cout << "index: " << users[i].i.index << "\n";
        cout << "name: " << users[i].name << "\n";
        for(int j = 0; j < users[i].posts.size(); j++)
        {
            cout << "\npost:\nbody: " << users[i].posts[j].body << "\ntopics: ";
            for(int k = 0; k < users[i].posts[j].topics.size(); k++)
            {
                cout << users[i].posts[j].topics[k] << " ";
            }
            cout << "\n";
        }
        cout << "\nfollowers:\n\n";
        for(int j = 0; j < users[i].followers.size(); j++)
        {
            cout << "follower id: " << users[i].followers[j].id << "\n";
            cout << "follower index: " << users[i].followers[j].index << "\n\n";
        }
        cout << "____________________________\n";
    }
}

int main()
{
    string file_name = "sample.xml";
    print_graph(make_graph(make_tree(file_name)));
    return 0;
}