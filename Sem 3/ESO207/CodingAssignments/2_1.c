#include <stdio.h>
#include <stdlib.h>

struct node {
        long long int data;
        struct node *prev;
        
    };
    
struct node * top1 = NULL;

int push(long long int data){
    struct node * t;
    t = (struct node*)malloc(sizeof(struct node));
     t->data = data;
    if(top1==NULL) {
       
        top1 = t;
       // printf("%lld",top->data);
        return 0;
    }else{
        t->prev = top1;
        top1 = t;
   //  printf("%lld",top->prev->data);
        return 0;
    }
    return 1;
}
int pop(){
    
    struct node * t;
    t = top1;
    long long int data = t->data;
    top1 = top1->prev;
    
    free(t);
    printf("%lld\n",data);
    return data;
}
int top(){
   
    
    printf("%lld\n",top1->data);
    return top1->data;
}

int IsEmpty(){
    if(top1 == NULL) return 1;
    return 0;
}
int main() {
    
    int n;
    scanf("%d\n",&n);
    
    


    int operation;
    long long int number;
    while(n--){
       scanf("%d",&operation);
       if(operation==1){
           scanf(" %lld",&number);
           printf("%d\n",push(number));
           
           }
       else if(operation == 2 ) pop();
       else if(operation == 3) top();
       else printf("%d\n",IsEmpty());
       scanf("\n");
        
    }
//    printf("%d",push(5));printf("%d\n",IsEmpty());pop();printf("%d\n",IsEmpty());printf("%d",push(9));printf("%d",push(11));top1();pop();
    return 0;
}