#include <stdio.h>
#include <stdlib.h>

long long int inv_count = 0; // no of inversions as a global variable

/* merge the two sorted arrays such that final merged array is also sorted
 start is the index from where 1st array to be merged is starting 
and mid is the end of first array and second array is from mid+1 to end*/
void merge(long long int *arr, long long int *temp, long long int start, long long int end, long long int mid)
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
                //if the element of first array is larger than jth index element it is greater than all elements of second array from index j to end
                inv_count += mid - i + 1; 
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
/* this function divides the problem into smaller problems 
recursively which is the scope of merge and sort
and return the no of inversions of the input array*/
long long int NoOfInversions(long int *arr, long int *temp, long long int start, long long int end)
{

    if (end > start) // if no of elements are more than 1
    {
        long long int mid = (end - start) / 2 + start; // to divide the array into two parts to recursively divide the problem into smaller
        NoOfInversions(arr, temp, start, mid);
        NoOfInversions(arr, temp, mid + 1, end);
        merge(arr, temp, start, end, mid); // merge the above two sorted arrays such that final merged is also sorted
    }

    return inv_count;
}

int main()
{
    int NoOfTests;
    scanf("%d\n", &NoOfTests);

    while (NoOfTests--)
    {
        long long int length;
        scanf("%lld\n", &length); // no of test cases

        long long int *arr = (long long int *)malloc(length * sizeof(long long int));  //long long is used because of the range of length and elements of array
        long long int *temp = (long long int *)malloc(length * sizeof(long long int)); // temp array is used to store the sorted array and helps to copy back to original array

        for (long long int j = 0; j < length; j++)
            scanf("%lld ", &arr[j]); // scan the array

        printf("%lld\n", NoOfInversions(arr, temp, 0, length - 1));
        inv_count = 0; // after each test case sets the no of inv_count to be 0
    }
    return 0;
}
