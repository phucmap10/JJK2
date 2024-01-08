#include "main.h"

int MAXSIZE;

int *fact = new int;
void calculateFact(int fact[], int N)
{
    fact[0] = 1;
    for (int i = 1; i < N; i++)
    {
        fact[i] = fact[i - 1] * i;
    }
}
int nCr(int fact[], int N, int R)
{
    if (R > N)
        return 0;

    // nCr= fact(n)/(fact(r)*fact(n-r))
    int res = fact[N] / fact[R];
    res /= fact[N - R];

    return res;
}
int countWays(vector<int> &arr, int fact[])
{
    int N = arr.size();

    // Base case
    if (N <= 2)
    {
        return 1;
    }

    vector<int> leftSubTree;

    vector<int> rightSubTree;

    // Store the root node
    int root = arr[N - 1];

    for (int i = 0; i < N - 1; i++)
    {

        if (arr[i] <= root)
        {
            leftSubTree.push_back(arr[i]);
        }

        else
        {
            rightSubTree.push_back(arr[i]);
        }
    }

    int N1 = leftSubTree.size();

    int countLeft = countWays(leftSubTree,
                              fact);
    int countRight = countWays(rightSubTree,
                               fact);

    return nCr(fact, N - 1, N1) * countLeft * countRight;
}
class Sukuna_res
{
    class Node;

private:
    vector<Node *> areaTable;
    list<Node *> Recently;

private:
    void ReHeap_down(int index)
    {
        int smallest = index;
        unsigned int leftChild = 2 * index + 1;
        unsigned int rightChild = 2 * index + 2;
        if(leftChild >= areaTable.size())return;

        if (leftChild < areaTable.size() && areaTable[leftChild]->size() < areaTable[smallest]->size())
            smallest = leftChild;
        else if (leftChild < areaTable.size() && areaTable[leftChild]->size() == areaTable[smallest]->size())
        {
            auto it_smallest = find(Recently.begin(), Recently.end(), areaTable[smallest]);
            auto it_leftChild = find(Recently.begin(), Recently.end(), areaTable[leftChild]);
            if (*it_smallest > *it_leftChild)
                smallest = leftChild;
        }

        if (rightChild < areaTable.size() && areaTable[rightChild]->size() < areaTable[smallest]->size())
            smallest = rightChild;
        else if (rightChild < areaTable.size() && areaTable[rightChild]->size() == areaTable[smallest]->size())
        {
            auto it_smallest = find(Recently.begin(), Recently.end(), areaTable[smallest]);
            auto it_rightChild = find(Recently.begin(), Recently.end(), areaTable[rightChild]);
            if (*it_smallest > *it_rightChild)
                smallest = rightChild;
        }

        if (smallest != index)
        {
            swap(areaTable[index], areaTable[smallest]);
            ReHeap_down(smallest);
        }
    };
    void ReHeap_up(int index)
    {
        if (index == 0)
        {
            return;
        }
        int parentIndex = (index - 1) / 2;
        if (areaTable[index]->size() < areaTable[parentIndex]->size())
        {
            swap(areaTable[index], areaTable[parentIndex]);
            ReHeap_up(parentIndex);
        }
    };
    void print_preorder(int index, int number)
    {
        if ((unsigned int)index >= this->areaTable.size())
            return;

        this->areaTable[index]->print(number);
        print_preorder(index * 2 + 1, number);
        print_preorder(index * 2 + 2, number);
    }
    void moveTop(Node *node)
    {
        // Find the node in the list
        auto it = find(Recently.begin(), Recently.end(), node);

        // If the node is not found, insert it at the beginning
        if (it == Recently.end())
        {
            Recently.push_front(node);
        }
        else
        {
            // If the node is found, move it to the beginning
            Recently.splice(Recently.begin(), Recently, it);
        }
    };
    void removeNode(Node *node)
    {

        for (auto it = Recently.begin(); it != Recently.end(); ++it)
        {
            if (*it == node)
            {
                Recently.erase(it);
                break;
            }
        }
    };
public:
    void insertAreaTable(int result)
    {
        int ID = result % MAXSIZE + 1;
        int index = -1;

        // check xem id co trong heap chua, neu co thi cap nhat index thanh id
        for (unsigned int i = 0; i < areaTable.size(); i++)
        {
            if (areaTable[i]->ID == ID)
            {
                index = i;
                break;
            } // If the area already exists, update its NUM value
        }
        if (index == -1)
        {
            areaTable.push_back(new Node(ID));
            index = areaTable.size() - 1; // If the area doesn't exist, create a new Node and add it to the areaTable
            
        }
        areaTable[index]->insert(result);
        this->moveTop(areaTable[index]);
        this->ReHeap_down(index);
    };
    void KEITEIKEN(int num)
    {
        if (areaTable.size() <= 0)
            return;

        //* đuổi num khách hàng tại num khu vực
        int numberRemove = num;
        while (areaTable.size() != 0 && num != 0)
        {
            cout << "remove customers in the area ID = " << areaTable[0]->ID << ": ";
            areaTable[0]->remove(numberRemove);
            cout << "\n";

            //* trường hợp xóa hết thì xóa nó trong heap sau đó reheap down khác

            if (areaTable[0]->size() == 0)
            {
                swap(areaTable[0], areaTable[areaTable.size() - 1]);
                this->removeNode(areaTable[areaTable.size() - 1]);
                delete areaTable[areaTable.size() - 1];
                areaTable.pop_back();
            }
            this->ReHeap_down(0);
            num--;
        }
    };
    void CLEAVE(int num){
        print_preorder(0, num);
    };

private:
    class Node
    {
    private:
        int ID;
        list<int> head;
        friend class Sukuna_res;

    public:
        Node(int ID) : ID(ID)
        {
        }
        int size() const
        {   if(head.empty())return 0;
            else
            return head.size();
        }

        void insert(int result)
        {
            if (head.empty())
            {
                head.push_front(result);
            }
            else
            {
                head.push_back(result);
            }
        };

        void remove(int number)
        {
            if (this->head.size() == 0)
                return;
            while (number != 0 && this->head.size() != 0)
            {
                int res = head.front();
                cout << res << "-" << this->ID << "\n";
                head.pop_front();
                --number;
            }
        };

        void print(int number)
        {
            for (list<int>::reverse_iterator it = head.rbegin(); number > 0 && it != head.rend();
                 ++it, --number)
            {
                cout << ID << "-" << *it << "\n";
            }
        };
    };
};

class Gojo_res
{
    class Tree_BST;

private:
    vector<Tree_BST*> areaTable;

public:
    Gojo_res() : areaTable(MAXSIZE + 1)
    {
    }
    void insertAreaTable(int result)
    {   
        int ID = result % MAXSIZE + 1;
        if(areaTable[ID] == nullptr){
            areaTable[ID] = new Tree_BST;
        }
        areaTable[ID]->insert(result);
    };
    void KOKUSEN()
    {
        for (int i = 0; i < MAXSIZE; i++)
            if(areaTable[i] == nullptr)continue;
            else areaTable[i]->remove();
    };
    void LIMITLESS(int number){
        if(areaTable[number] == nullptr)return;
        else areaTable[number]->print();
    };
    void initialize(){
    areaTable.resize(MAXSIZE + 1);
    fill(areaTable.begin(), areaTable.end(), nullptr );
}

private:
    class Tree_BST
    {   class Node;

    public:
        Node *root;
        queue<int> queueTime;
        vector<int> postorder;
        int N;

    public:
        Tree_BST() : root(nullptr)
        {
        }
        int size()
        {
            return queueTime.size();
        }
        void insert(int result)
        {
            Node *newNode = new Node(result);
            queueTime.push(result);
            if (this->root == nullptr)
            {
                this->root = newNode;
                return;
            }
            else
            {
                Node *current = this->root;
                Node *parent = nullptr;
                while (true)
                {
                    parent = current;
                    if (result < current->result)
                    {
                        current = current->left;
                        if (current == nullptr)
                        {
                            parent->left = newNode;
                            return;
                        }
                    }
                    else
                    {
                        current = current->right;
                        if (current == nullptr)
                        {
                            parent->right = newNode;
                            return;
                        }
                    }
                }
            }
        };
        Node *findMin(Node *root)
        {
            while (root->left != nullptr)
            {
                root = root->left;
            }
            return root;
        }
        void remove_recursive(Node **root, Node *nodeDelete)
        {
            if (*root == nullptr)
            {
                return;
            }
            if ((*root)->result > nodeDelete->result)
            {
                remove_recursive(&((*root)->left), nodeDelete);
            }
            else if ((*root)->result < nodeDelete->result)
            {
                remove_recursive(&((*root)->right), nodeDelete);
            }
            else
            {
                // Node found
                if ((*root)->left == nullptr)
                {
                    Node *temp = *root;
                    *root = (*root)->right;
                    delete temp;
                }
                else if ((*root)->right == nullptr)
                {
                    Node *temp = *root;
                    *root = (*root)->left;
                    delete temp;
                }
                else
                {
                    // Node with two children, find inorder successor
                    Node *temp = findMin((*root)->right);
                    (*root)->result = temp->result;
                    remove_recursive(&((*root)->right), temp);
                }
            }
        };
        void DFS(Node *node, vector<int> &postorder)
        {
            if (node == nullptr)
            {
                return;
            }
            DFS(node->left, postorder);        // Traverse left subtree
            DFS(node->right, postorder);       // Traverse right subtree
            postorder.push_back(node->result); // Visit the node
        }
        void remove()
        {   
            DFS(root, postorder);
            int Y;
            N = postorder.size();
            calculateFact(fact, N);
            Y = countWays(postorder, fact);
            while (Y != 0 && !queueTime.empty())
            {
                int tmpp = queueTime.front();
                Node *tmp = new Node(tmpp);
                queueTime.pop();
                remove_recursive(&root, tmp);
                delete tmp;
                --Y;
            }
        };
        void print_recursive(Node *node)
        {
            if (node == nullptr)
                return;
            print_recursive(node->left);
            cout << node->result << "\n";
            print_recursive(node->right);
        };
        void print()
        {
            if (this->size() == 0)
                return;
            print_recursive(root);
        };

    private:
        class Node
        {
        private:
            int result;
            Node *left;
            Node *right;
            friend class Tree_BST;

        public:
            Node(int result) : result(result), left(NULL), right(NULL)
            {
            }
        };
    };
};


Gojo_res Gojo;
Sukuna_res Sukuna;

class HuffNode
{
public:
    char ch;
    int freq;
    HuffNode *left;
    HuffNode *right;
    int order;
    int height()
    {
        if (left == nullptr && right == nullptr)
        {
            return 0;
        }
        int leftHeight = left ? left->height() : -1;
        int rightHeight = right ? right->height() : -1;
        return 1 + max(leftHeight, rightHeight);
    }
};

int getHeight(HuffNode *node)
{
    if (node == nullptr)
    {
        return -1;
    }
    return node->height();
}

HuffNode *
rightRotate(HuffNode *y)
{
    HuffNode *x = y->left;
    HuffNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

HuffNode *
leftRotate(HuffNode *x)
{
    HuffNode *y = x->right;
    HuffNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

int getBalance(HuffNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    int leftHeight = node->left ? node->left->height() : -1;
    int rightHeight = node->right ? node->right->height() : -1;
    return leftHeight - rightHeight;
}

// Function to allocate a new tree node
HuffNode *
getNode(char ch, int freq, HuffNode *left, HuffNode *right, int order)
{
    HuffNode *node = new HuffNode();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    node->order = order;
    return node;
}

HuffNode *balancetree(HuffNode *root, int &count)
{
    if (root == NULL)
        return root;
    if (count == 3)
        return root;
    while(count < 3){
    int balance = getHeight(root->left) - getHeight(root->right);
    if (balance > 1)
    {

        if (getHeight(root->left->left) - getHeight(root->left->right) >= 0)
        {   
            root = rightRotate(root);
            ++count;
            
        }
        else
        {   
            root->left = leftRotate(root->left);
            root = rightRotate(root);
            ++count;
           
           
        }
    }
    else if (balance < -1)
    {

        if (getHeight(root->right->left)- getHeight(root->right->right) <= 0)
        {   
            root = leftRotate(root);
            ++count;
            
        }
        else
        {   
            root->right = rightRotate(root->right);
            root = leftRotate(root);
            ++count;
        }
    }
    else break;
    }
    root->left = balancetree(root->left, count);
    root->right = balancetree(root->right, count);
    return root;
}
void HAND(HuffNode* node)
{
    if (node == NULL)
        return;
 
    // First recur on left subtree
    HAND(node->left);
 
    // Now deal with the node
    if ( node ->ch == '\0'){
        cout << node->freq<< '\n';
    }
    cout << node->ch << "\n";
    // Then recur on right subtree
    HAND(node->right);
}
int binaryToDecimal(string n)
{
    string num = n;
    int dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--)
    {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}

bool cmp(pair<char, int> &a, pair<char, int> &b)
{
    if (a.second == b.second)
    {
        if (islower(a.first) && isupper(b.first))
        {
            return true; // lowercase a should come before uppercase b
        }
        if (isupper(a.first) && islower(b.first))
        {
            return false; // uppercase a should come after lowercase b
        }
        return tolower(a.first) < tolower(b.first); // sort in alphabetical order if frequencies and cases are the same
    }
    return a.second < b.second; // sort by frequency
}

bool hasOnlyOneNode(HuffNode *root)
{
    if (root == nullptr)
    {
        return false;
    }
    if (root->left == nullptr && root->right == nullptr)
    {
        return true;
    }
    return false;
}

char caesar_cipher(char c, int shift)
{ // Ma hoa string voi caesar cipher
    if (isalpha(c))
    {
        char base = islower(c) ? 'a' : 'A';
        return (c - base + shift) % 26 + base;
    }
    return c;
}

void encode(HuffNode *root, string str, map<char, string> &HuffmanCode)
{
    if (root == nullptr)
        return;

    // found a leaf node
    if (!root->left && !root->right)
    {
        HuffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", HuffmanCode);
    encode(root->right, str + "1", HuffmanCode);
}

HuffNode* last = NULL;
void LAPSE(string name)
{
    map<char, string> HuffmanCode;
    map<char, int> mp;
    int len = name.length();
    for (int i = 0; i < len; i++)
    {
        mp[name[i]]++;
    }
    string encoded_name;
    if (mp.size() < 3) return;
    // Declare vector of pairs
    vector<pair<char, int>> A;
    // Copy key-value pair from Map
    // to vector of pairs
    for (auto &it : mp)
    {
        A.push_back(it);
    }
    for (int i = 0; i < len; i++)
    {   
        int Shift = mp[name[i]] % 26;
        char new_char = caesar_cipher(name[i], Shift);
        encoded_name += new_char;
    }

    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);
    for (auto &p : A)
    { // encode the value
        p.first = caesar_cipher(p.first, p.second);
    }

    map<char, int> merged;
    for (const auto &p : A)
    {
        merged[p.first] += p.second; // Tong hop lai cac key bi duplicate
    }

    // Print the sorted value
    vector<pair<char, int>> B;
    for (auto &it : merged)
    {
        B.push_back(it);
    }
    sort(B.begin(), B.end(), cmp);

    // Create a priority queue to store live nodes of Huffman tree
    vector<HuffNode *> vec;

    for (auto &p : B)
    {
        HuffNode *node = getNode(p.first, p.second, nullptr, nullptr, 0);
        vec.push_back(node);
    }
    sort(vec.begin(), vec.end(), [](HuffNode *a, HuffNode *b)
         {
        if(a->freq != b->freq)return a->freq < b->freq;
        else if (a->freq == b->freq && a->ch != '\0' && b->ch != '\0') {
        if (islower(a->ch) && isupper(b->ch)) {
            return true;
        }
        if (isupper(a->ch) && islower(b->ch)) {
            return false;
        }
        else return a->ch < b->ch;
    }
    if(a->ch == '\0' && b->ch == '\0' && a->freq == b->freq )
        return a->order < b->order;
    else if(a->ch != '\0' && b->ch =='\0' && a->freq == b->freq) {return true;}
    else if(a->ch == '\0' && b->ch !='\0' && a->freq == b->freq) {return false;}
    else
        return a->freq < b->freq; });

    while (vec.size() > 1)
{   int order = 0;
    HuffNode *leftNode = vec.front();
    vec.erase(vec.begin());

    HuffNode *rightNode = vec.front();
    vec.erase(vec.begin());
    order++;
    int frequencySum = leftNode->freq + rightNode->freq;
    HuffNode *newNode = getNode('\0', frequencySum, leftNode, rightNode,order);
    int balanceFactor = 0;
    newNode = balancetree(newNode, balanceFactor);
    newNode->order = order;


    vec.insert(upper_bound(vec.begin(), vec.end(), newNode, [](HuffNode *a, HuffNode *b)
    {
        if(a->freq != b->freq){
            return a->freq < b->freq;
        }else if(a->ch != '\0' && b->ch != '\0' && a->freq == b->freq){
            if(islower(a->ch) && isupper(b->ch)){
                return true;
            }
            if(islower(b->ch) && isupper(a->ch)){
                return false;
            }
            else return a->freq < b->freq;
        }
        else return a->order < b->order;
    }), newNode);
    order++;
}

    HuffNode *root = vec.front();
    last = root;
    if (root->ch != '\0') return;

    map<char, string> huffmanCode; // store the binary
    encode(root, "", huffmanCode);
    string encoded_name1;
    for (char c : encoded_name)
    {
        encoded_name1 += huffmanCode[c];
    }
    unsigned int n = 10; // lay 10 ki tu cuoi cua binary string
    string binary_code;
    if(encoded_name1.size() < n){
        binary_code = encoded_name1;
    }else binary_code = encoded_name1.substr(encoded_name1.size() - n);
    
    reverse(binary_code.begin(), binary_code.end());
    
    int result = binaryToDecimal(binary_code); // chuyen ve decimal value cua string binary
    if (hasOnlyOneNode(root))
        result = 0;

    if (result % 2 == 0)
    {
        Sukuna.insertAreaTable(result);
    }
    else if (result % 2 == 1)
    {
        Gojo.insertAreaTable(result);
    }
}
void simulate(string filename)
{
	ifstream ss(filename);
	string str, maxsize, name, num;
	while(ss >> str)
	{ 
		if(str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize); 
            Gojo.initialize();
    	}
        else if(str == "LAPSE") // LAPSE <NAME> 
        {
            ss >> name;
            LAPSE(name);
    	}
    	else if(str == "KOKUSEN") // KOKUSEN
    	{
    		Gojo.KOKUSEN();
		}
    	else if(str == "KEITEIKEN") // KEITEIKEN
    	{
			ss>>num;
    		Sukuna.KEITEIKEN(stoi(num));
		}
		else if(str == "HAND") // HAND
		{
    		HAND(last);	
		}
    	else if(str == "LIMITLESS") // LIMITLESS <NUM>
     	{   	
			ss>>num;
    		Gojo.LIMITLESS(stoi(num));
    	}
    	else if(str == "CLEAVE") // CLEAVE <NUM>
    	{
			ss>>num;
    		Sukuna.CLEAVE(stoi(num));
    	}
    }
    
}