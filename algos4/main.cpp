#include <iostream>

struct Node {
    Node *left = nullptr;
    Node *right = nullptr;
    int value = 0;
    int height = 0;
    int size = 0;

    Node() = default;

    Node(int _value, int _height, int _size) : value(_value), height(_height), size(_size) {};

    ~Node(){
        delete left;
        delete right;
    }
};

class avl_tree{
private:
    Node* root = nullptr;
    Node* insert(Node *node, int _value){
        if (node == nullptr) return new Node(_value,1,1);

        else if(_value < node->value) node->left = insert(node->left,_value);

        else node->right = insert(node->right,_value);

        return balance(node);
    }
    Node* remove(Node *node, int _value){
        if(node == nullptr) return nullptr;

        if(_value < node->value) node->left = remove(node->left,_value);

        else if(_value > node->value) node->right = remove(node->right,_value);

        else{
            if(node->right == nullptr) return node->left;

            if(node->left == nullptr) return node->right;

            Node *temp = node;
            node = find_min(temp->right);
            node->right = remove_min(temp->right);
            node->left = temp->left;
            return balance(node);
        }
        return balance(node);
    }
    //finds min element and removes it
    Node* find_min(Node* node) const {
        return node->left != nullptr ? find_min(node->left) : node;
    }
    Node* remove_min(Node* node){
        if(node->left == nullptr) return node->right;

        node->left = remove_min(node->left);
        return balance(node);
    }
    //gets height and size
    int get_height(Node* node) const{
        if(node == nullptr) return 0;

        return node->height;
    }
    int get_size(Node* node) const{
        if(node == nullptr) return 0;

        return node->size;
    }
    //difference between branches
    int diff(Node* node) const{
        if(node == nullptr) return 0;

        return get_height(node->right) - get_height(node->left);
    }
    //returns new size after rotate
    void new_size(Node* node){
        if(node == nullptr) return;

        int left_size = get_size(node->left);
        int right_size = get_size(node->right);

        node->size = left_size + right_size + 1;
    }
    void new_height(Node* node){
        if(node == nullptr) return;

        int left_height = get_height(node->left);
        int right_height = get_height(node->right);

        node->height = std::max(left_height,right_height) + 1;
    }
    //rotating
    Node* rotate_left(Node* node){
        Node *temp = node->right;
        node->right = temp->left;
        temp->left = node;

        new_height(node);
        new_height(temp);
        new_size(node);
        new_size(temp);

        return temp;
    }
    Node* rotate_right(Node* node){
        Node *temp = node->left;
        node->left = temp->right;
        temp->right = node;

        new_height(node);
        new_height(temp);
        new_size(node);
        new_size(temp);

        return temp;
    }
    //balancing the tree
    Node* balance(Node* node){
        new_height(node);
        new_size(node);

        if(diff(node) == 2){
            if(diff(node->right) < 0){
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        }
        else if(diff(node) == -2){
            if(diff(node->left) > 0){
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }
        return node;
    }

    int find_kstat(Node *node, int k){
        if(get_size(node->left)+1 == k) return node->value;

        else if(get_size(node->left) >= k) return find_kstat(node->left,k);

        else return find_kstat(node->right,k - get_size(node->left) - 1);

    }

public:
    avl_tree() = default;
    ~avl_tree() = default;
    void insert(int _value){
        root = insert(root,_value);
    }
    void remove(int _value){
        root = remove(root,_value);
    }
    int kstat(int k){
        return find_kstat(root, k);
    }

};

int main(){
    int N,a,k;
    avl_tree tree;

    std::cin>>N;
    for(size_t  i = 0;i<N;++i){
        std::cin>>a>>k;
        if(a>0) tree.insert(a);

        else tree.remove(abs(a));

        std::cout<<tree.kstat(k+1)<<std::endl;
    }
}