//1.3 Если в числе содержится только один бит со значением 1,
// записать в выходной поток OK. Иначе записать FAIL
#include <iostream>

bool check(size_t number){
    while(number>0 &&(number & 1) ==0){
        number>>=1;
    }
    return number == 1 ;


}

int main() {
    size_t number;
    std::cin>>number;
    bool result = check(number);
    if(result)
        std::cout<<"OK";
    else
        std::cout<<"FAIL";
}
