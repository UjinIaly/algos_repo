#include <iostream>

int search(int A[], int B[], int n, int m){
    int pos;
    unsigned int last_pos = 0;
    for(int i = 0;i<m;++i){
        pos = (i == 0?1:i);
        while(pos < n && A[pos] < B[i]){
            pos *=2;
        }
        unsigned int head = last_pos;
        unsigned int tail = pos;
        unsigned int current = (head+tail)/2;
        while(head<=tail&&A[current]!=B[i]){
            current = (head+tail)/2;
            if(A[current]>B[i]) {tail = current;}
            else{head = current+1;}
        }
        if(A[current] == B[i]){
            last_pos = current;
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
