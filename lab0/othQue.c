 #include<stdio.h> 
 #include<stdlib.h>
 struct Node
 {
        int Data;
        struct Node* next;
 }*rear, *front;

void push(int value)
{
     struct Node *temp;
     temp=(struct Node *)malloc(sizeof(struct Node));
     temp->Data=value;
     if (front == NULL)
     {
           front=temp;
           front->next=NULL;
           rear=front;
     }
     else
     {
           front->next=temp;
           front=temp;
           front->next=NULL;
     }
}

int main()
{
     int i=0;
     front=NULL;
     printf(" \n1. Push to Queue");
     printf(" \n4. Exit\n");
     while(1)
     {
          printf(" \nChoose Option: ");
          scanf("%d",&i);
          switch(i)
          {
                case 1:
                {
                     int value;
                     printf("\nEnter a valueber to push into Queue: ");
                     scanf("%d",&value);
                     push(value); 
                     break;
                }
                case 4:
                {
                     exit(0);
                }
                default:
                {
                     printf("\nwrong choice for operation");
                }
          }
     }
}
