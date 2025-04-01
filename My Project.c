#include<stdio.h>
#define size 1000
int main()
{

    int arr[size];
    int choice,n;
    printf("How many Elements do you want to Enter(%d):",size);
    scanf("%d",&n);
    printf("Enter %d elements:",n);
    for(int i=0; i<n; i++)
    {
        scanf("%d",&arr[i]);

    }
    do
    {
        printf("\n     ||Array Operations Menu||    \n");
        printf("1. Insert\n");
        printf("2. Update\n");
        printf("3. Delete\n");
        printf("4. Search\n");
        printf("5. Sort\n");
        printf("6. Display\n");
        printf("7. Exit\n");

        printf("What's your choice (1-7):");
        scanf("%d", &choice);

        switch(choice)
        {
        //Insert
        case 1:
        {
            if(n>size)
            {
                printf("Array is Full!!");
                break;
            }
            int position,value;
            printf("Enter position (1 to %d):",n+1);
            scanf("%d",&position);
            if(position<1 || position>n+1)
            {
                printf("Invalid Position\n");
                break;
            }
            printf("Enter value to Insert:");
            scanf("%d",&value);
            for(int i=n; i>=position; i--)
            {
                arr[i]=arr[i-1];

            }
            arr[position-1]=value;
            n++;
            printf("Element Inserted successfully.");
            break;
        }
        //Update
        case 2:
        {
            int pos, val;
            printf("Enter position (1-%d) to update: ", n);
            scanf("%d", &pos);
            if(pos < 1 || pos > n)
            {
                printf("Invalid position!\n");
                break;
            }
            printf("Enter new value: ");
            scanf("%d", &val);
            arr[pos - 1] = val;
            printf("Element updated successfully.\n");
            break;
        }
        //Delete
        case 3:
        {
            int pos,val;
            if(n==0)
            {
                printf("Nothing to delete\n");
                break;
            }
            printf("Enter the number(1-%d) you want to delete:",n);
            scanf("%d",&pos);
            if(pos<1 || pos>n)
            {
                printf("Invalid position");
                break;
            }
            for(int i = pos - 1; i < n - 1; i++)
            {
                arr[i] = arr[i + 1];
            }
            n--;
            printf("Element deleted successfully.\n");
            break;
        }
        //Search
        case 4:
        {
            int val, found = 0;
            printf("Enter value to search: ");
            scanf("%d", &val);
            for(int i = 0; i < n; i++)
            {
                if(arr[i] == val)
                {
                    printf("Value found at position %d.\n", i + 1);
                    found = 1;
                    break;
                }
            }
            if(found==0)
            {
                printf("Value not found in the array.\n");
            }
            break;
        }
        //Sort
        case 5:
        {
            for(int i = 0; i < n - 1; i++)
            {
                for(int j = 0; j < n - i - 1; j++)
                {
                    if(arr[j] > arr[j+1])
                    {
                        int temp = arr[j];
                        arr[j] = arr[j+1];
                        arr[j+1] = temp;
                    }
                }
            }
            printf("Array sorted successfully.\n");
            break;
        }
        //Display
        case 6:
        {
            if(n == 0)
            {
                printf("Array is empty.\n");
                break;
            }
            printf("Array elements: ");
            for(int i = 0; i < n; i++)
            {
                printf("%d ", arr[i]);
            }
            printf("\n");
            break;
        }
        //Exit
        case 7:
        {
            printf("Exit Program\t");
            printf("Thank you\n");
            break;
        }
        default:
        {
            printf("Invalid Input!!");
        }


        }

    }
    while(choice!=7);

    return 0;
}