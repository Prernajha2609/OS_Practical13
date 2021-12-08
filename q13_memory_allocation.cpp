#include <iostream>
#include <algorithm>
using namespace std;

class Memory_block{
  public:
    int block_size;
    int free_block;
    int block_no;
    bool operator<(Memory_block m);
};

bool Memory_block::operator<(Memory_block m){
    return (this->free_block<m.free_block);
}


class Process{
  public:
    int pid;
    int p_size;
    int block_allocated;
    bool allocated = false;
};

//First fit memory allocation
void first_fit(Process p[],int m,Memory_block mb[],int n){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(p[i].p_size<=mb[j].free_block){
                p[i].block_allocated = mb[j].block_no;
                p[i].allocated = true;
                mb[j].free_block-=p[i].p_size;
                break;
            }
        }
    }
}

//Best-fit memory allocation
void best_fit(Process p[],int m, Memory_block mb[],int n){
    for(int i=0; i<m; i++){
        sort(mb,mb+n);
        for(int j=0; j<n; j++){
            if(p[i].p_size<=mb[j].free_block){
                p[i].allocated = true;
                p[i].block_allocated=mb[j].block_no;
                mb[j].free_block-=p[i].p_size;
                //cout<<p[i].block_allocated<<"\t\t"<<mb[j].free_block<<endl;
                break;
            }
        }
    }
}

//Worst-fit memory allocation
void worst_fit(Process p[],int m, Memory_block mb[],int n){
    for(int i=0; i<m; i++){
        sort(mb,mb+n);
        for(int j=n-1; j>0; j--){
            if(p[i].p_size<=mb[j].free_block){
                p[i].allocated = true;
                p[i].block_allocated=mb[j].block_no;
                mb[j].free_block-=p[i].p_size;
                //cout<<p[i].block_allocated<<"\t\t"<<mb[j].free_block<<endl;
                break;
            }
        }
    }
}

void print(Process p[],int m,Memory_block mb[],int n){
    cout<<"\nProcess\t\tProcess size\tBlock no\tFree Memory\n";
    for(int i=0; i<m; i++){
        cout<<"P"<<(i+1)<<"\t\t"<<p[i].p_size<<"\t\t";
        if(p[i].allocated){
            cout<<p[i].block_allocated<<"\t\t";
            for(int j=0; j<n; j++){
                if(p[i].block_allocated == mb[j].block_no){
                    cout<<mb[j].free_block<<"\n";
                    break;
                }
            }
        }else{
             cout<<"Not allocated"<<"\t  ----\n";
        }
    }
}

int main(){
    int n,m,ch;
    cout<<"\nEnter number of Memory blocks: ";
    cin>>n;
    Memory_block mb[n];
    cout<<"\nEnter size of each block:\n";
    for(int i=0; i<n; i++){
        cout<<"Block "<<(i+1)<<" : ";
        cin>>mb[i].block_size;
        mb[i].free_block = mb[i].block_size;
        mb[i].block_no = i+1;
    }
    
    cout<<"\nEnter number of process: ";
    cin>>m;
    Process p[m];
    cout<<"\nEnter size of each process:\n";
    for(int i=0; i<m; i++){
        cout<<"Process P"<<(i+1)<<" : ";
        cin>>p[i].p_size;
        p[i].pid = i+1;
    }
    
    //first fit;
    cout<<"\nSelect Memory Allocation strategy:\n";
    cout<<"1. First fit\n";
    cout<<"2. Best fit\n";
    cout<<"1. Worst fit\n";
    cout<<"\nEnter (1,2,3): ";
    cin>>ch;
    switch(ch){
        case 1:
            first_fit(p,m,mb,n);
            cout<<"\n\n===================== First fit ==========================\n";
            print(p,m,mb,n);
            break;
        case 2:
            best_fit(p,m,mb,n);
            cout<<"\n\n===================== Best fit ==========================\n";
            print(p,m,mb,n);
            break;
        case 3:
            worst_fit(p,m,mb,n);
            cout<<"\n\n===================== Worst fit ==========================\n";
            print(p,m,mb,n);
            break;
        default:
            cout<<"\nInvalid choice!\n";
    }
    return 0;
}