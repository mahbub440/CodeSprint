#include<stdio.h>
int main()
{

    int row1,col1,row2,col2;
    printf("Enter rows for 1st matrix:");
    scanf("%d",&row1);
    printf("Enter columns for 1st matrix:");
    scanf("%d",&col1);
    printf("Enter rows for 2nd matrix:");
    scanf("%d",&row2);
    printf("Enter columns for 2nd matrix:");
    scanf("%d",&col2);
    int arr1[row1][col1],arr2[row2][col2];

    //input for matrix 1
    for(int i=0; i<row1; i++)
    {
        for (int j=0; j<col1; j++)
        {
            printf("Enter Array1[%d][%d]:",i,j);
            scanf("%d",&arr1[i][j]);
        }
    }

    //output for matrix 1
    printf("\n  ||Matrix 1 [%dX%d]||  \n",row1,col1);

    for(int i=0; i<row1; i++)
    {
        for (int j=0; j<col1; j++)
        {
            printf("%d ",arr1[i][j]);

        }
        printf("\n");
    }

    //input for matrix 2
    for(int i=0; i<row2; i++)
    {
        for (int j=0; j<col2; j++)
        {
            printf("Enter Array2[%d][%d]:",i,j);
            scanf("%d",&arr2[i][j]);
        }
    }

    //output for matrix 2
    printf("\n  ||Matrix 2 [%dX%d]||  \n",row2,col2);

    for(int i=0; i<row2; i++)
    {
        for (int j=0; j<col2; j++)
        {
            printf("%d ",arr2[i][j]);

        }
        printf("\n");
    }
    //Sum of 2 matrix
    printf("   ||Sum of two matrix:||   \n");
    if(row1==row2 && col1==col2)
    {

        for(int i=0; i<row1; i++)
        {
            for (int j=0; j<col1; j++)
            {
                printf("%d ",arr1[i][j]+arr2[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Matrix summation is not possible.\n");
        printf("Matrix 1: %d x %d\n", row1, col1);
        printf("Matrix 2: %d x %d\n", row2, col2);
        printf("Dimensions must be same for summation.\n");
    }

    //subtraction of 2 matrix
    printf("\n   ||Subtraction of two matrix:||   \n");
    if(row1==row2 && col1==col2)
    {

        for(int i=0; i<row1; i++)
        {
            for (int j=0; j<col1; j++)
            {
                printf("%d ",arr1[i][j]-arr2[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Matrix Subtraction is not possible.\n");
        printf("Matrix 1: %d x %d\n", row1, col1);
        printf("Matrix 2: %d x %d\n", row2, col2);
        printf("Dimensions must be same for subtraction.\n");
    }

    //multiplication of 2 matrix
    printf("\n   ||Multiplication of two matrix:||   \n");

    if(col1 == row2)
    {
        int result[row1][col2];

        for(int i = 0; i < row1; i++)
        {
            for(int j = 0; j < col2; j++)
            {
                result[i][j] = 0;
            }
        }

        for(int i = 0; i < row1; i++)
        {
            for(int j = 0; j < col2; j++)
            {
                for(int k = 0; k < col1; k++)
                {
                    result[i][j] += arr1[i][k] * arr2[k][j];
                }
            }
        }

        for(int i = 0; i < row1; i++)
        {
            for(int j = 0; j < col2; j++)
            {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }

    }
    else
    {
        printf("Matrix multiplication is not possible.\n");
        printf("Because columns of Matrix 1 != rows of Matrix 2 [%dX%d]\n", col1, row2);
    }
    return 0;
}
