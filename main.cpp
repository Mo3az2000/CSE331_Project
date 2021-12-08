
#include "prototype.hpp"

using namespace std;


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