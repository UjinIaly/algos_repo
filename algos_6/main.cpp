//6_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.


#include <iostream>

template <class T,class Comp = std::less<T>>
int partition(T *buffer, int begin, int end,Comp comp = Comp()){
    if (end == begin)
        return 0;
    int pos = (begin+(random()%(end-begin)));
    int pivot = buffer[pos];

    int i = begin;
    int j = begin;

    std::swap(buffer[pos], buffer[end - 1]);
    while (j != end - 1){
        if (comp(pivot,buffer[j])){
            j++;
        } else{
            std::swap(buffer[i], buffer[j]);
            i++;
            j++;
        }
    }
    std::swap(buffer[end - 1], buffer[i]);
    return i;
}
template <class T,class Comp = std::less<T>>
int statistics(T *buffer, size_t size, int k,Comp comp = Comp()){
    int begin = 0;
    int end = (int)size;

    while (true){
        int pivot = partition(buffer, begin, end);
        if (pivot == k) return buffer[k];
        else if(comp(pivot,k)) begin = pivot + 1;
        else end = pivot;
    }
}

int main(){
    int n;
    std::cin >> n;
    int buffer[n];
    for (int i = 0; i < n; i++){
        std::cin >> buffer[i];
    }
    std::cout << statistics(buffer, n, n/10) << std::endl ;
    std::cout<< statistics(buffer, n, n/2) << std::endl ;
    std::cout<< statistics(buffer, n, n*9/10)<<std::endl;
    return 0;
}