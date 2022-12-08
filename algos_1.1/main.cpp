//Вариант 1. Для разрешения коллизий используйте квадратичное пробирование.
//i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
#include <iostream>
#include <vector>

const size_t DEFAULT_SIZE = 8;
const size_t MAX_ALPHA = 2;

class hash_table{
private:
    std::string *buffer;
    int capacity;
    int size;
    int prime = 71;
    std::string nil = "NIL";
    std::string deleted = "DELETED";

    int first_hash(const std::string &data){
        int hash = 0 ;
        for(char i : data) hash = (hash * prime + (int)i) % capacity;
        return hash;

    }
    int new_hash(const std::string &data, int i, int prev){
        return (prev + i)%capacity;
    }
    void resize(){
        std::string *temp = buffer;
        int temp_capacity = capacity;

        capacity *=2;
        size = 1;
        buffer = new std::string[capacity];
        for(size_t i = 0;i<capacity;++i){
            buffer[i] = nil;
        }

        for(size_t i = 0;i<temp_capacity;++i){
            if(temp[i]!=nil&&temp[i]!=deleted)insert(temp[i]);
        }

    }
public:
    hash_table():size(0),capacity(DEFAULT_SIZE){
        buffer = new std::string [capacity];
        for(size_t i = 0;i<capacity;++i){
            buffer[i] = nil;
        }
    }
    void print_table(){
        for(size_t i = 0;i<capacity;++i){
            std::cout<<buffer[i]<<" "<<i<<std::endl;
        }
        std::cout<<std::endl;
    }
    bool insert(const std::string &data){
        if(data.empty()) return false;

        if((double)size/(double)capacity >=0.75) resize();

        int hash = first_hash(data);
        int pos = -1;

        for(size_t i = 0;i<capacity;++i){
            hash = new_hash(data,i,hash);
            if(buffer[hash] == data) return false;
            if(buffer[hash] == nil){
                if(pos == -1)pos = hash;
                ++size;
                buffer[pos] = data;
                return true;
            }
            if(buffer[hash] == deleted && pos == -1){
                pos = hash;
            }
        }
        if(pos!=-1){
            ++size;
            buffer[pos] = data;
            return true;
        }
        return false;
    }
    bool remove(const std::string &data){
        if(data.empty()) return false;

        int hash = first_hash(data);

        for(size_t i = 0;i<capacity;++i){
            hash = new_hash(data,i,hash);
            if(buffer[hash] == nil) return false;
            if(buffer[hash] == data){
                --size;
                buffer[hash] = deleted;
                return true;
            }
        }
        return false;
    }
    bool exist(const std::string &data){
        if(data.empty())return false;

        int hash = first_hash(data);
        for(size_t i = 0;i<capacity;++i){
            hash = new_hash(data,i,hash);
            if(buffer[hash] == data) return true;
            if(buffer[hash] == nil) return false;
        }
        return false;
    }


};
int main(){
    hash_table table;
    std::string data;
    char command;
    while(std::cin>>command){
        switch(command){
            case'?':{
                std::cin>>data;
                std::cout<<(table.exist(data)?"OK":"FAIL")<<std::endl;
                break;
            }
            case'+':{
                std::cin>>data;
                std::cout<<(table.insert(data)?"OK":"FAIL")<<std::endl;
                break;
            }
            case'-':{
                std::cin>>data;
                std::cout<<(table.remove(data)?"OK":"FAIL")<<std::endl;
                break;
            }
        }

    }

}

