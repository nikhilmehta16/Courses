#include <stdio.h>
#include <stdlib.h>

struct node {
        long long int data;
        struct node *prev;
        
    };
    
struct node * top = NULL;



int push(long long int data){
    struct node * t;
    t = (struct node*)malloc(sizeof(struct node));
     t->data = data;
    if(top==NULL) {
       
        top = t;
       
        return 0;
    }else{
        t->prev = top;
        top = t;
   
        return 0;
    }
    return 1;
}
int pop(){
    
    struct node * t;
    t = top;
    long long int data = t->data;
    top = top->prev;
    
    free(t);
    printf("%lld\n",data);
    return data;
}
int top1(){
   
    
    printf("%lld\n",top->data);
    return top->data;
}

int IsEmpty(){
    if(top == NULL) return 1;
    return 0;
}

/* merge the two sorted arrays such that final merged array is also sorted
 start is the index from where 1st array to be merged is starting 
and mid is the end of first array and second array is from mid+1 to end*/
void merge(long long int *arr, long long int *temp,  int start,  int end,  int mid)
{
    // i and j are basically pointers to the arrays which element is to be compared
    long long int i = start, j = mid + 1;
    for (long long int k = start; k <= end; k++)
    {

        if (i <= mid && j <= end) // when both the pointers are in array
        {
            if (arr[i] <= arr[j])
            {
                temp[k] = arr[i++];
            }
            else
            {
                temp[k] = arr[j++];
                
            }

            continue;
        }
        if (i > mid && j <= end) // if first array is completed copying the elements of second sorted array to original array
        {
            temp[k] = arr[j];
            j += 1;
            continue;
        }
        if (i <= mid && j > end) //if second array is completed copying the elements of first sorted array to original array
        {
            temp[k] = arr[i];
            i += 1;
            continue;
        }
    }

    for (int k = start; k <= end; k++) // copies the temporaly sorted array to original array
        arr[k] = temp[k];

    return;
}


int main() {
    
    int n,NoOfElements;
    scanf("%d\n",&n);
    

    while(n--){
       scanf("%d",&NoOfElements);
       
           
           
           
      
        
    }
//    printf("%d",push(5));printf("%d\n",IsEmpty());pop();printf("%d\n",IsEmpty());printf("%d",push(9));printf("%d",push(11));top1();pop();
    return 0;
}