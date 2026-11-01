
#include <iostream>
#include <queue>
#include <map>
#include <string>
using namespace std;

// Structure for Huffman Tree Node
struct Node
{
    char ch;
    int freq;

    Node *left, *right;

    Node(char c, int f)
    {
        ch = c;
        freq = f;
        left = right = NULL;
    }
};

// Comparator for Min Priority Queue
struct Compare
{
    bool operator()(Node* a, Node* b)
    {
        return a->freq > b->freq;
    }
};

// Generate Huffman Codes
void generateCodes(Node* root, string code,
                   map<char, string>& huffmanCode)
{
    if (root == NULL)
        return;

    // Leaf node
    if (root->left == NULL && root->right == NULL)
    {
        huffmanCode[root->ch] =
            (code == "") ? "0" : code;
        return;
    }

    generateCodes(root->left, code + "0",
                  huffmanCode);

    generateCodes(root->right, code + "1",
                  huffmanCode);
}

// Build Huffman Tree using Greedy Strategy
Node* buildHuffmanTree(string text)
{
    map<char, int> freq;

    // Calculate frequency
    for (char ch : text)
    {
        freq[ch]++;
    }

    // Min Priority Queue
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create leaf nodes
    for (auto p : freq)
    {
        pq.push(new Node(p.first, p.second));
    }

    // Combine two minimum frequency nodes
    while (pq.size() > 1)
    {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node(
            '\0', left->freq + right->freq
        );

        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    return pq.top();
}

// Display Huffman Codes
void displayCodes(map<char, string>& codes)
{
    cout << "\nHuffman Codes:\n";

    for (auto p : codes)
    {
        cout << p.first << " : " << p.second << endl;
    }
}

// Encode the input string
string encodeText(string text,
                  map<char, string>& codes)
{
    string encoded = "";

    for (char ch : text)
    {
        if (codes.find(ch) == codes.end())
            return "";

        encoded += codes[ch];
    }

    return encoded;
}

int main()
{
    Node* root = NULL;
    map<char, string> huffmanCode;
    string text;
    int choice;

    do
    {
        cout << "\n\n--- HUFFMAN ENCODING MENU ---";
        cout << "\n1. Enter Text and Build Huffman Tree";
        cout << "\n2. Display Huffman Codes";
        cout << "\n3. Encode Text";
        cout << "\n4. Exit";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter text: ";
                cin.ignore();
                getline(cin, text);

                if (text.empty())
                {
                    cout << "Text cannot be empty!";
                    break;
                }

                root = buildHuffmanTree(text);

                huffmanCode.clear();

                generateCodes(root, "", huffmanCode);

                cout << "Huffman Tree created successfully!";
                break;

            case 2:
                if (root == NULL)
                {
                    cout << "Build the tree first!";
                }
                else
                {
                    displayCodes(huffmanCode);
                }
                break;

            case 3:
                if (root == NULL)
                {
                    cout << "Build the tree first!";
                }
                else
                {
                    cout << "Enter text to encode: ";
                    cin.ignore();
                    getline(cin, text);

                    string result =
                        encodeText(text, huffmanCode);

                    if (result == "")
                        cout << "Error: Character not found!";
                    else
                        cout << "Encoded Text: " << result;
                }
                break;

            case 4:
                cout << "Exiting program...";
                break;

            default:
                cout << "Invalid choice!";
        }

    } while (choice != 4);

    return 0;
}
