//2_3. Обход дерева в порядке post-order
#include <iostream>
#include <stack>

struct Node{
    int data;
    Node *left;
    Node *right;
    Node(const int &_data):data(_data),left(nullptr),right(nullptr){}

};

class Btree{
private:
    Node *root;
public:
    Btree():root(nullptr){};
    ~Btree() = default;
    bool insert(const int &_data){
        Node *node = new Node(_data);

        if(root == nullptr){
            root = node;
            return true;
        }
        Node *next = root;
        while(true){
             if(_data<next->data){
                 if(next->left != nullptr) next = next->left;

                 else{
                     next->left = node;
                     return true;
                 }

             }
             else{
                 if(next->right != nullptr) next = next->right;

                 else {
                     next->right = node;
                     return true;
                 }

             }
        }
    }

    void post_order(){
        Node *node = root;
        std::stack<Node*> st;
        std::stack<int> out;
        st.push(node);
        while (!st.empty())
        {
            Node* curr = st.top();
            st.pop();
            out.push(curr->data);

            if (curr->left) st.push(curr->left);


            if (curr->right) st.push(curr->right);

        }

        while (!out.empty())
        {
            std::cout << out.top() << " ";
            out.pop();
        }
    }
};

int main(){
    int count;
    int number;

    Btree tree;
    std::cin>>count;
    for(size_t  i = 0;i<count;++i){
        std::cin>>number;
        tree.insert(number);
    }
    tree.post_order();

}