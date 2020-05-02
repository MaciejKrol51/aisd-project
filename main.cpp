#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>


struct Node
{
        Node *top, *left, *right;
        int value;
};

void Print(Node * node)
{
        if (node)
        {
                Print(node->right);
                printf("%d\n", node->value);
                Print(node->left);
        
}
}

void Insert(Node *& root, int key)
{
        Node *father;
        Node *pointer;

        father = new Node;           

        father->left = father->right = nullptr; 
        father->value = key;                
        pointer = root;                  
        if (!pointer)                     
                root = father;                
        else
                while (true)              
                        if (key < pointer->value)       
                        {                      
                                if (!pointer->left)         
                                {
                                        pointer->left = father;       
                                        break;
                                
}
                                else pointer = pointer->left;
                        
}
                        else
                        {
                                if (!pointer->right)        
                                {
                                        pointer->right = father;      
                                        break;
                                
}
                                else pointer = pointer->right;
                        
}
        father->top = pointer;             
}

Node *Search(Node *node, int key)
{
        while (node && node->value != key)
                node = (key < node->value) ? node->left : node->right;

                return node;
}

Node *Maximal(Node *node)
{
        if (node)
                while (node->right)
                        node = node->right;

        return node;
}

Node *Consequent(Node *node)  //"Nastepnik"
{
        Node *pointer;

        if (node)
        {
                if (node->right)
                        return Maximal(node->right);
                else
                {
                        pointer = node->top;
                        while (pointer && (node == pointer->right))
                        {
                                node = pointer;
                                pointer = pointer->top;
                        
}
                        return pointer;
                
}
        
}
        return node;
}

void Remove(Node *& root, Node *node)
{
        Node *firstPointer, *secondPointer;

        if (node)
        {
                firstPointer = !node->left || !node->right ? node : Consequent(node);

                secondPointer = firstPointer->left ? firstPointer->left : firstPointer->right;

                if (secondPointer)
                        secondPointer->top = firstPointer->top;

                if (!firstPointer->top)
                        root = secondPointer;
                else if (firstPointer == firstPointer->top->left)
                        firstPointer->top->left = secondPointer;
                else
                        firstPointer->top->right = secondPointer;

                if (firstPointer != node)
                        node->value = firstPointer->value;

                delete firstPointer;
        
}
}

void Connect(Node *& firstGroup, Node *secondGroup)
{
        if (secondGroup)
        {
                Connect(firstGroup, secondGroup->right);
                Insert(firstGroup, secondGroup->value);
                Connect(firstGroup, secondGroup->left);
        
}
        
}

int main()
{
        Node *root;
        Node *result;
        Node *arrayOfHeaps[1000];
        for (int i = 0; i < 1000; i++)
                arrayOfHeaps[i] = nullptr;
        int n, max;
        char operation;
        int group1, group2, value1, value2;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) 
        {
                scanf(" %c", &operation);
                switch (operation)
                {
                case 'a': 
                        scanf("%d %d", &group1, &value1); 
                        Insert(arrayOfHeaps[group1], value1);
                        break;
                case 'e': 
                        scanf("%d", &group1);
                        if (arrayOfHeaps[group1] == nullptr)
                                printf("na\n");
                        else
                        {
                                result = Maximal(arrayOfHeaps[group1]);
                                printf("%d\n", result->value);
                                Remove(arrayOfHeaps[group1], result);
                        
}
                        break;
                case 'p':
                        scanf("%d", &group1);
                        if (arrayOfHeaps[group1] == nullptr)
                                printf("");
                        else
                                Print(arrayOfHeaps[group1]);
                        break;
                case 'm':  
                        scanf("%d %d", &group1, &group2);
                        Connect(arrayOfHeaps[group1], arrayOfHeaps[group2]);
                        arrayOfHeaps[group2] = nullptr;
                        break;
                case 'i':
                        scanf("%d %d %d", &group1, &value1, &value2);
                                if (value1 <= value2)
                                {
                                        result = Search(arrayOfHeaps[group1], value1);
                                        if (result == nullptr)
                                                printf("na\n");
                                        else
                                        {
                                                Remove(arrayOfHeaps[group1], result);
                                                Insert(arrayOfHeaps[group1], value2);
                                        
}
                                
}
                        break;
                default:
                        return 0;
                
}
        
}

        return 0;
}
