#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <queue>
#include <unordered_map>
#include <tuple>
using namespace std;

//CLASSES:

class Node
{
public:
    double probability;
    Node *left;
    Node *right;
    char character;
public:
    Node()
    {
        probability=0;
        left=nullptr;
        right=nullptr;
        character='\0';
    }
    Node(double prob,Node * left_node,Node * right_node, char charr)
    {
        probability = prob;
        left = left_node;
        right = right_node;
        character = charr;
    }
    bool operator < (Node const other) const
    {
        if (probability < other.probability)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

// Comparison object to be used to order the heap(Priority Queue)
struct compare
{
    bool operator()(const Node* l, const Node* r) const
    {
        // the highest priority item has the lowest frequency
        return l->probability > r->probability;
    }
};

/*******************************************************************************************/

/******************************************************************************************/

// GLOBALS:
unordered_map<char, string> HuffmanDict;
unordered_map<char, double> freqDict;
unordered_map<char, double> probabilitiesDict;
Node *Tree;

/*******************************************************************************************/

//FUNCTIONS:

//Params:
    //node:Head node of a tree.
    //str: an empty string that would be used in the recursion process to build up the codeword.
void traverse_huff(Node *node,string str)  // O(n), O(1)
{
    if (node->character == '\0')
    {
        //cout<<node->character<<"\n";
        traverse_huff(node->left, str + "0");
        traverse_huff(node->right, str + "1");
        return;
    }
    //print(node.char + " => " + str)
    //cout<<node->character<<" => "<<str<<"\n";
    HuffmanDict[node->character] = str;
    return;
} 

//Converts a string of bits to an array of bytes
vector<unsigned char> bitstring_to_bytes(string s) //O(n), O(n)
{
    long long size = s.length();
    vector<unsigned char> arrayOfByte(size/8);
    long long index = 0;
    //cout<<"size:  "<<size<<"\n";
    int rem = size % 8;
    //cout<<"rem:  "<<rem<<"\n";
    for(long long i=0;i < size-rem;i=i+8)
    {
        //string one_byte = s.substr(i,i+8);
        string one_byte = "";
        for(int bit=i;bit<i+8;bit++)
        {
            if(s[bit] == '\0')
            {
                break;
            }
            one_byte=one_byte+s[bit];
        }
        //cout<<one_byte<<"\n";
        unsigned int integer = stoi(one_byte,0,2);
        unsigned char c = static_cast<unsigned char>(integer);
        arrayOfByte[index] = c;
        //cout<<arrayOfByte[index];
        index++;
    }
    return arrayOfByte;
}

//params:
//b: 1 byte integer
//Returns a string of 8 bits
string one_byte_to_bitstring(unsigned char byte) //O(1), O(1)
{
    string binary = bitset<8>(byte).to_string();
    return binary;
}

//params:
//byteArr: array of integers each is 1 byte
//Function to push each character in an array of characters
long long string_to_byteArr(string file_string , vector<unsigned char> &fileByteArr) //O(n), O(n), n: no. of chars
{
    long long Num_of_Bytes = file_string.length();
    fileByteArr.reserve(Num_of_Bytes);
    for(long long i=0;i<Num_of_Bytes;i++)
    {
        fileByteArr.push_back(file_string[i]);
    }
    return Num_of_Bytes;
}

string eraseSpacing(string inputFile){ //O(n), O(1)  //best: O(m), o(1),  n: no. of chars, m: no. of lines
    fstream myInput;
    string ns;
    myInput.open(inputFile, ios::in);
    if (myInput.is_open())
    {
    	string s;
        while (getline(myInput, s))
        {
            while((s[0]==' ')||(s[0]=='\t')||(s[0]=='\n'))
            {
                s.erase(0,1);
            }
            int n = s.size()-1;
            while((s[n]==' ')||(s[n]=='\t')||(s[n]=='\n')){
                s.erase(n,1);
                n = s.size()-1;
            }
            ns += s;
        }
        myInput.close();
    }
    return ns;
}

string read_huff_file(string huff_file){ // O(n), O(1), n: no. of lines
	string st;
	fstream huff;
		huff.open(huff_file, ios::in);
		    if (huff.is_open())
		    {
		    	string s;
		        while (getline(huff, s)){
		        	st += '\n' + s;
		        }
		    }
	st = st.substr(1);
	return st;
}

/*****************************************************************************************************/

//MAIN:
Node * PrintCompressedTree(string file_string)         //O(n), O(1), n: no. of chars in input string
{
    long long fileByteArr_Size = file_string.length();

    //Construct frequencies dictionary
    for(int i = 0; i<fileByteArr_Size;i++)
    {
        char key = file_string[i];
        auto result = freqDict.find(key);
        if(result != freqDict.end()) //Found
        {
            freqDict[key] = (result->second) + 1;
        }
        else //not found
        {
            freqDict[key] = 1;
        }
    }

    //Calculate the sum of frequencies
    double total=0;
    for(auto &it: freqDict)
    {
        total = total + it.second;
    }

    //Calculate Probability dictionary
    for(auto &it: freqDict)
    {
        probabilitiesDict[it.first] = it.second/total;
    }

    //Construct probabilities priority queue
    priority_queue<Node*, vector<Node*>, compare> q;
    for(auto &it: probabilitiesDict)
    {
        Node* node = new Node(it.second,nullptr,nullptr,it.first);
        q.push(node);
    }

    //Construct huffman tree from probabilities queue
    while(q.size() > 1)
    {
        Node* obj1 = q.top();
        q.pop();
        Node* obj2 = q.top();
        q.pop();
        Node* newOb = new Node((obj1->probability + obj2->probability), obj1, obj2, '\0');
        q.push(newOb);
    }
    Tree = q.top();

    //Set huffman codes for each symbol(leaf) in the huffman tree.
    traverse_huff(Tree,"");


    //Print Huffman dictionary
    //for(auto &it: HuffmanDict)
    //	cout<<it.first<<" => "<<it.second<<"\n";


    //Constructing the new file's bit-string
    string outStr = "";
    for(long long i = 0; i<fileByteArr_Size;i++)
    {
        //int ch = fileByteArr[i];
        char ch = file_string[i];
        outStr = outStr + HuffmanDict[ch];
    }


    //After constructing the new file's bit-string. This string might not be divisible by 8.
    //Since we want the bit string to be a specific number of bytes, so we will add zeros to the last byte.
    //But the number of added zeros has to be known for decoding.
    //So we add one byte at the beginning of the string to indicate the number of redundant bits in the last Byte.

    //Calculating the number of bits of the encoded string before adding redundant bits.
    long long encodedStringLen = outStr.length();

    //Calculating the number of redundant bits in the last byte.
    string redundantBitsNum = one_byte_to_bitstring(8 - (encodedStringLen % 8));

    //Adding redundant bits to the encoded string.
    string addedZeros = "";
    int num_of_zeros = 8 - (encodedStringLen % 8);
    for(int i = 0; i < num_of_zeros ; i++)
    {
        addedZeros = addedZeros + "0";
    }
    outStr = redundantBitsNum + outStr + addedZeros;

    //Converting the bit string to byte array.
    vector<unsigned char> outByteArr = bitstring_to_bytes(outStr);

//    cout<<"\nOriginal Length (in Bits) = "<<( file_string.length()*8 )<<"\n";
//    cout<<"Encoded Length Without redundant bits (in bits) = "<<encodedStringLen<<"\n";
//    cout<<"Encoded Length (in bits) = "<<outStr.length()<<"\n";

    //Writing the bytes to the output file.
    fstream encodedFile;
    encodedFile.open("encodedFile.huff",ios::out);
    if(encodedFile.is_open())
    {
        long long size_of_vect = outByteArr.size();
        for (int i = 0; i < size_of_vect; i++)
        {
            encodedFile << outByteArr[i];
        }
    }
    return Tree;
}

string decode_file(Node* Tree, string ffs)   // O(n), O(1), n: no. of chars
{
	vector<unsigned char> fileByteArray;
	long long num_of_bytes = string_to_byteArr(ffs , fileByteArray);
	string fs;
	for(auto element : fileByteArray) fs += one_byte_to_bitstring(element);
	string sub = fs.substr(0,7);
	unsigned int num_of_added_zeros = stoi(sub, 0, 2);
	int size = fs.size() - num_of_added_zeros - 8;
	string s = fs.substr(8, size);
        string ans = "";
        struct Node* curr = Tree;
        int ssize = s.size();
        for (int i=0;i<ssize;i++)
        {
            if (s[i] == '0')
               curr = curr->left;
            else
               curr = curr->right;

            // reached leaf node
            if (curr->left==NULL and curr->right==NULL)
            {
                ans += curr->character;
                curr = Tree;
            }
        }
        // cout<<ans<<endl;
        return ans+'\0';
}


int main(){
	string file_string = eraseSpacing("sample.xml");
	Node * tree = PrintCompressedTree(file_string);
	string st = read_huff_file("encodedFile.huff");
	cout << st << endl;
        cout << file_string << endl;
	cout << decode_file(tree, st);
	return 0;
}
