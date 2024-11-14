#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;
class HuffmanNode 
{
public:
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};
struct Compare
{
    bool operator()(HuffmanNode* a, HuffmanNode* b) 
    {
        return a->frequency > b->frequency;
    }
};
class HuffmanTree 
{
private:
    HuffmanNode* root;
    void deleteHuffmanTree(HuffmanNode* node) 
    {
        if (node == nullptr) 
        {
            return;
        }

        deleteHuffmanTree(node->left);
        deleteHuffmanTree(node->right);
        delete node;
    }

public:
    HuffmanTree() : root(nullptr) {}
    void buildTree(unordered_map<char, int>& frequencyMap)
    {
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
        for (auto& pair : frequencyMap) {
            pq.push(new HuffmanNode(pair.first, pair.second));
        }
        while (pq.size() > 1) {
            HuffmanNode* left = pq.top();
            pq.pop();
            HuffmanNode* right = pq.top();
            pq.pop();

            int sumFrequency = left->frequency + right->frequency;
            HuffmanNode* newNode = new HuffmanNode('\0', sumFrequency);
            newNode->left = left;
            newNode->right = right;
            pq.push(newNode);
        }
        if (!pq.empty()) 
        {
            root = pq.top();
        }
    }
    ~HuffmanTree() 
    {
        deleteHuffmanTree(root);
    }
    HuffmanNode* getRoot() const 
    {
        return root;
    }
};
class HuffmanEncoder
{
private:
    unordered_map<char, string> huffmanCodes;
    void generateHuffmanCodesHelper(HuffmanNode* node, string code) 
    {
        if (node == nullptr) 
        {
            return;
        }

        if (node->left == nullptr && node->right == nullptr) 
        {
            huffmanCodes[node->data] = code;
        }

        generateHuffmanCodesHelper(node->left, code + "0");
        generateHuffmanCodesHelper(node->right, code + "1");
    }

public:
    void generateHuffmanCodes(HuffmanNode* root) 
    {
        string code;
        generateHuffmanCodesHelper(root, code);
    }
    unordered_map<char, string> getHuffmanCodes() const 
    {
        return huffmanCodes;
    }
};

int main() {
    string input;
    cout << "Enter a text string: ";
    getline(cin, input);
    unordered_map<char, int> frequencyMap;
    for (char c : input) {
        frequencyMap[c]++;
    }
    HuffmanTree huffmanTree;
    huffmanTree.buildTree(frequencyMap);
    HuffmanEncoder huffmanEncoder;
    huffmanEncoder.generateHuffmanCodes(huffmanTree.getRoot());
    unordered_map<char, string> huffmanCodes = huffmanEncoder.getHuffmanCodes();
    string encodedString;
    for (char c : input) {
        encodedString += huffmanCodes[c];
    }

    cout << "Encoded string: " << encodedString << endl;
    string decodedString;
    HuffmanNode* currentNode = huffmanTree.getRoot();
    for (char c : encodedString) 
    {
        if (c == '0') {
            currentNode = currentNode->left;
        }
        else
        {
            currentNode = currentNode->right;
        }

        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            decodedString += currentNode->data;
            currentNode = huffmanTree.getRoot();
        }
    }

    cout << "Decoded string: " << decodedString << endl;

    return 0;
}
