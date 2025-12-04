/*
 * Name1: Samaa Mehrez Abdelhamid
 * ID1: 20230177
 * Name2: Mariam Ayman Mosaad
 * ID2: 20230390
 */
#include <iostream>
using namespace std;

template<class T,int M>
struct Node
{
    T* keys;               // Array of keys in the node
    Node** children;       // Array of pointers to children (size = M+1)
    int nkeys;             // Number of keys currently stored
    int position;          // Index of last inserted key

    Node()
    {
        keys = new T[M];               // Allocate keys array
        children = new Node*[M+1];     // Allocate children array
        for(int i=0;i<=M;i++) children[i]=nullptr;
        nkeys = 0;
        position = -1; // Starting position: The tree is empty
    }

    // Insert a value into the subtree of this node
    int Insert(T value)
    {
        // The node is a leaf
        if(children[0] == nullptr)
        {
            // Insert the key
            position++;
            keys[position] = value;
            nkeys++;

            // Sort keys
            for(int i = position; i > 0; i--)
            {
                if(keys[i] < keys[i-1])
                {
                    T tmp = keys[i];
                    keys[i] = keys[i-1];
                    keys[i-1] = tmp;
                }
            }
        }
        else
        {
            // Internal node: Find the correct child
            int i = 0;
            for(; i < nkeys; i++)
            {
                if(value <= keys[i]) break;
            }

            // Insert recursively in the correct child
            int split_check = children[i]->Insert(value);

            // If child is full, we need to split it
            if(split_check)
            {
                T mid;
                int split_index = i;

                // Split the child and returns a new right sibling
                Node* newNode = split(children[i], &mid);

                // Insert the middle key into this node
                for(; i < nkeys; )
                {
                    if(mid <= keys[i]) break;
                    i++;
                }

                // Shift keys to make space for mid
                for(int j = nkeys; j > i; j--)
                    keys[j] = keys[j-1];

                keys[i] = mid;
                nkeys++;
                position++;

                // Shift children pointers
                int k;
                for(k = nkeys; k > split_index + 1; k--)
                    children[k] = children[k-1];

                // Add the new right child
                children[k] = newNode;
            }
        }

        // If node becomes full we return split flag
        if(nkeys == M) return 1;
        return 0;
    }

    // Split a full node into two nodes
    Node* split(Node* node, T* med)
    {
        int n = node->nkeys;
        Node* newNode = new Node;
        int midValue = n / 2;      // The index of the key that will be a parent

        // The median key to be promoted
        *med = node->keys[midValue];

        int i;
        // Move right half keys + children to the new node
        for(i = midValue + 1; i < n; i++)
        {
            newNode->keys[++newNode->position] = node->keys[i];
            newNode->children[newNode->position] = node->children[i];
            newNode->nkeys++;

            // Clear moved data from old node
            node->children[i] = nullptr;
            node->position--;
            node->nkeys--;
        }

        // Move last child pointer
        newNode->children[newNode->position + 1] = node->children[i];
        node->children[i] = nullptr;

        node->nkeys--;
        node->position--;

        return newNode;
    }

    // Print the tree level by level (recursive)
    void PrintTree(int level)
    {
        int i, j;

        // Print keys of this node
        for(i = 0; i < nkeys; i++)
        {
            if(i > 0) cout << ",";
            cout << keys[i];
        }
        cout << endl;

        // Print children, each in a new indented line
        if(children[0] != nullptr)
        {
            for(i = 0; i <= nkeys; i++)
            {
                for(j = 0; j <= level; j++)
                    cout << "  ";

                if(children[i])
                    children[i]->PrintTree(level + 1);
            }
        }
    }

    void Print()
    {
        PrintTree(0); // Print the whole tree start from level 0
    }

    ~Node()
    {
        delete[] keys;
        for(int i = 0; i <= nkeys; i++)
            delete children[i];
        delete[] children;
    }
};

template<class T,int M>
class BTree
{
    Node<T,M>* root;

public:
    BTree()
    {
        root = nullptr;
    }

    void Insert(T value)
    {
        if(root == nullptr)
        {
            // First node created
            root = new Node<T,M>;
            root->keys[++root->position] = value;
            root->nkeys = 1;
            return;
        }

        // Insert normally
        int split = root->Insert(value);

        // If root is full, split it and create new root
        if(split)
        {
            T mid;
            Node<T,M>* splitNode = root->split(root, &mid);

            Node<T,M>* newRoot = new Node<T,M>;
            newRoot->keys[++newRoot->position] = mid;
            newRoot->nkeys = 1;
            newRoot->children[0] = root;
            newRoot->children[1] = splitNode;

            root = newRoot;
        }
    }

    void Print()
    {
        if(root)
            root->Print();
        else
            cout << "The B-Tree is Empty" << endl;
    }

    ~BTree()
    {
        delete root;
    }
};

int main()
{
    // Construct a BTree of order 3, which stores int data
    BTree<int,3> t1;

    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);

    t1.Print(); // Should output the following on the screen:

    /*
    1,4
      0
      2,3
      5
    */

    // Construct a BTree of order 5, which stores char data
    BTree<char,5> t;

    // Look at the example in our lecture:
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');

    t.Print(); // Should output the following on the screen:

    /*
    K
      C,G
        A,B
        D,E,F
        H,I,J
      N,R
        L,M
        P,Q
        S,T
    */

    return 0;
}
