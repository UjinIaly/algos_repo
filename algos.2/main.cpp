#include <iostream>

void search(int A[],int B[],unsigned int n,unsigned int m){

    unsigned int last_pos=0;
    unsigned int head = 0;
    unsigned int tail = 0;
    unsigned int current ;
    for(unsigned int i=0;i<m;++i){
        head = last_pos;
        tail = n;
        while(head<tail&&A[current]!=B[i]){
            current = (head+tail)/2;
            if(A[current]>B[i]) {tail = current;}
            else{head = current+1;}
        }
        if(A[current] == B[i]){
            std::cout<<B[i]<<" ";
        }

    }
}

int main() {
    unsigned int n,m;
    std::cin>>n>>m;
    int A[n];
    int B[m];
    for(unsigned int i =0;i<n;++i){
        std::cin>>A[i];
    }
    for(unsigned int i =0;i<m;++i){
        std::cin>>B[i];
    }
    if(sizeof(A)>sizeof(B)){
        search(A,B,n,m);
    }
    else{
        search(B,A,m,n);
    }




}
