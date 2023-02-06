#include <iostream>

struct User{
    int id;
    int count;
    bool operator< (User& _user){
        return(count<_user.count);
    }
    bool operator> (User& _user){
        return(count>_user.count);
    }
};
template <class T>
class Heap{
private:
    T* buffer;
    size_t heap_size;
    size_t capacity;
    void sift_up(size_t index);
    void sift_down(size_t index);
    void increase();
public:
    Heap():heap_size(0),capacity(4){
        buffer = new T[capacity];
    }
    void push(T _user);
    void pop();
    T top();
};

template<class T>
void Heap<T>::push(T _user){
    buffer[++heap_size] = _user;
    sift_up(heap_size);
}

template<class T>
void Heap<T>::increase() {
    capacity*=2;
    T temp[capacity];
    for(size_t i = 0;i<heap_size;++i){
        temp[i] = buffer[i];
    }
    buffer = temp;
}


template<class T>
void Heap<T>::sift_up(size_t index) {
    size_t parent;
    parent = index / 2;
    if( parent == 0 )return;
    if(buffer[parent].count > buffer[index].count) {
        std::swap(buffer[parent],buffer[index]);
        sift_up(parent);
    }
}

template <class T>
void Heap<T>::sift_down(size_t index) {
    size_t child;
    child = 2*index;
    if( child > heap_size ) return;
    if( child+1 <= heap_size && buffer[child + 1].count < buffer[child].count ) ++child;

    if( buffer[child].count < buffer[index].count ) {
        std::swap(buffer[child],buffer[index]);
        sift_down(child);
    }
};

template<class T>
void Heap<T>::pop(){
    if(heap_size==0) return;
    buffer[1] = buffer[heap_size--];
    sift_down(1);
}

template<class T>
T Heap<T>::top(){
    return buffer[1];
}

int main(){
    /*
    int id[]={1,2,3,4,5,6,7,};
    int count[]={2,7,4,6,9,5,3};
    User user[7];
    for(size_t  i = 0;i<7;++i){
        user[i].id = id[i];
        user[i].count = count[i];
        std::cout<<user[i].id<<" "<<user[i].count<<std::endl;
    }
    Heap<User> heap;
    for(size_t i = 0;i<7;++i){
        heap.push(user[i]);
    }
    for(size_t  i = 0;i<7;++i){
        std::cout<<heap.top().count;
        heap.pop();
    }
     */

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