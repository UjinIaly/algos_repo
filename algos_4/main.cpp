#include <iostream>

struct User{
    int id;
    int count;
    bool operator< (const User& _user)const{
        return(this->count<_user.count);
    }
    bool operator> (const User& _user)const{
        return(this->count>_user.count);
    }
};

template<class T>
struct comparator{
    bool operator() (const T& first,const T& second){
        return first>second;
    }
};

template <class T,class Comp = comparator<T>>
class Heap{
private:
    T* buffer;
    size_t heap_size;
    size_t capacity;
    void sift_up(size_t index);
    void sift_down(size_t index);
    void increase();
    Comp comp;
public:
    Heap(Comp comp = Comp()):heap_size(0),capacity(4){
        buffer = new T[capacity];
        this->comp = comp;
    }
    void push(const T &_user);
    void pop();
    T top();
};

template<class T,class Comp>
void Heap<T,Comp>::push(const T &_user){
    buffer[++heap_size] = _user;
    sift_up(heap_size);
}

template<class T,class Comp>
void Heap<T,Comp>::increase() {
    capacity*=2;
    T temp[capacity];
    for(size_t i = 0;i<heap_size;++i){
        temp[i] = buffer[i];
    }
    buffer = temp;
}


template<class T,class Comp>
void Heap<T,Comp>::sift_up(size_t index) {
    size_t parent;
    parent = index / 2;
    if( parent == 0 )return;
    if(comp(buffer[parent],buffer[index])) {
        std::swap(buffer[parent],buffer[index]);
        sift_up(parent);
    }
}

template <class T, class Comp>
void Heap<T,Comp>::sift_down(size_t index) {
    size_t child;
    child = 2*index;
    if( child > heap_size ) return;
    if( child+1 <= heap_size && comp(buffer[child],buffer[child+1]) ) ++child;

    if( comp(buffer[index],buffer[child]) ) {
        std::swap(buffer[child],buffer[index]);
        sift_down(child);
    }
};

template<class T, class Comp>
void Heap<T, Comp>::pop(){
    if(heap_size==0) return;
    buffer[1] = buffer[heap_size--];
    sift_down(1);
}

template<class T, class Comp>
T Heap<T, Comp>::top(){
    return buffer[1];
}

int main(){
    int id_count;
    int visits;
    std::cin >>id_count>>visits;
    if(id_count==0 || visits ==0)
        return 0;
    User user[id_count];
    for(size_t i = 0;i<id_count;++i){
        std::cin>>user[i].id>>user[i].count;
    }
    Heap<User> heap;
    for(size_t i = 0;i<id_count;++i){
        if(i>=visits){
            heap.push(user[i]);
            heap.pop();
        }
        else
            heap.push(user[i]);
    }
    size_t temp = (id_count<visits?id_count:visits);
    for(size_t i = 0;i<temp;++i){
        std::cout<<heap.top().id<<" ";
        heap.pop();
    }






}