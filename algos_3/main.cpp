#include <iostream>

class Deque{
private:
    int *buffer;
    int curr_size;
    int head;
    int tail;
    void increase(){
        curr_size *= 2;
        int new_head = 0, new_tail = 1;
        int *temp_buffer;
        int j = 1;
        temp_buffer = new int[curr_size];
        head++;
        if (head == curr_size)
            head = 0;
        for(int i = head; i != tail; i++){
            if (i == curr_size / 2)
                i = -1;
            else {
                temp_buffer[j] = buffer[i];
                j++;
                new_tail = j;
            }
        }
        delete[] buffer;
        tail = new_tail;
        head = new_head;
        buffer= temp_buffer;
    }
public:
    Deque():head(0),tail(1),curr_size(5){
        buffer = new int[curr_size];
    }
    ~Deque(){
        delete[] buffer;
    }

    void push_front(int number){
        buffer[head] = number;
        head = (head-1+curr_size)%curr_size;
        if (head == tail)
            increase();
    }
    int pop_front(int number){
        head = (head+1)%curr_size;
        if (head == tail) {
            --head;
            return -1;
        }
        if (buffer[head] == number)
            return number;
        else
            return 0;
    }
    void push_back(int number){
        buffer[tail] = number;
        tail = (tail+1)%curr_size;
        if (head == tail)
            increase();
    }
    int pop_back(int number){
        tail = (tail-1+curr_size)%curr_size;
        if (head == tail) {
            tail++;
            return -1;
        }
        if (buffer[tail] == number)
            return number;
        else
            return 0;
    }

};



int main() {
    Deque deq;
    int commands_count;
    int command;
    int number;
    bool is_matched = true;
    std::cin >> commands_count;
    for (int i = 0; i < commands_count; i++){
        std::cin >> command >> number;

        if (command == 1){
            deq.push_front(number);
        }
        else if (command == 2){
            if (deq.pop_front(number) != number) {
                is_matched = false;
            }
        }
        else if (command == 3){
            deq.push_back(number);
        }
        else if (command == 4){
            if (deq.pop_back(number) != number) {
                is_matched = false;
            }
        }
        else{
            is_matched = false;
        }
    }
    std::cout <<(is_matched?"YES":"NO");
    return 0;
}