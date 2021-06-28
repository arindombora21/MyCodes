#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
struct node
{
    int stock_price;
    char compname[30];
    struct node *left;
    struct node *right;
};
int count2;
int count3;
int bank_balance=10000;
struct customer
{
    char compname[30];
    int stock_price;
    int exp_SP;
    int minm_loss;
    struct customer *next;
};
struct stack{
	char compname1[30];
	int stock_price1;
	int profit;
	struct stack *next;
};
struct stack1{
    char compname[30];
    int stock_price;
    struct stack1 *next;
};
struct stack *transaction=NULL;
struct stack1 *bought=NULL;
struct customer *start=NULL;
struct node *treeMON=NULL;
struct node *treeTUES=NULL;
struct node *treeWED=NULL;
struct node *treeTHUR=NULL;
struct node *treeFRI=NULL;
struct node *treeSAT=NULL;
struct node *treeSUN=NULL;

struct node *insert(struct node *tree,char str[],int val)
{
    struct node *ptr,*node,*parent;
    ptr=(struct node*)malloc(sizeof(struct node));
    ptr->stock_price=val;
    strcpy(ptr->compname,str);
    ptr->left=NULL;
    ptr->right=NULL;
    if(tree==NULL)
    {
        tree=ptr;
        tree->left=NULL;
        tree->right=NULL;
    }
    else
    {
        parent=NULL;
        node=tree;
        while(node!=NULL)
        {
            parent=node;
            if(val<node->stock_price)
            node=node->left;
            else
            node=node->right;
        }
        if(val<parent->stock_price)
          parent->left=ptr;
          else
          parent->right=ptr;
    }
    return tree;
}
void preorder(struct node *tree)
{
    if(tree!=NULL)
    {
        printf("%s    ",tree->compname);
        printf("%d ",tree->stock_price);
        printf("\n");
        preorder(tree->left);
        preorder(tree->right);
    }
}
struct customer *push(struct customer *start,char str[],int price)
{
    struct customer *new_node,*ptr;
    new_node=(struct customer*)malloc(sizeof(struct customer));
    int a,b;
    a=price+(0.25*price);
    b=price-(0.05*price);
    if(start==NULL)
    {
        new_node->next=NULL;
        new_node->stock_price=price;
        strcpy(new_node->compname,str);
        new_node->exp_SP=a;
        new_node->minm_loss=b;
        start=new_node;
    }
    else
     {
         ptr=start;
         while(ptr->next!=NULL)
         {
             ptr=ptr->next;
         }
         strcpy(new_node->compname,str);
         new_node->stock_price=price;
         new_node->exp_SP=a;
         new_node->minm_loss=b;
         ptr->next=new_node;
         new_node->next=NULL;
     }
     return start;
}
int count_members(struct customer *start)
{
    struct customer *ptr;
    int count=0;
    ptr=start;
    while(ptr!=NULL){
            count++;
        ptr=ptr->next;
    }
    return count;
}
struct customer *delete_beg(struct customer *start)
{
struct customer *ptr;
ptr = start;
start = start -> next;
free(ptr);
return start;
}
struct customer *delete_end(struct customer *start)
{
struct customer *ptr, *preptr;
ptr = start;
while(ptr -> next != NULL)
{
 preptr = ptr;
 ptr = ptr -> next;
}
preptr -> next = NULL;
free(ptr);
return start;
}
struct stack *push_stack(struct stack *transaction, int price, char str[],int profit)
{
	struct stack *ptr,*ptr1;
	ptr= (struct stack *)malloc(sizeof(struct stack));
	strcpy(ptr->compname1,str);
	ptr->stock_price1= price;
	ptr->profit=profit;
	if(transaction==NULL){
		ptr->next=NULL;
		transaction=ptr;
	}
	else{
		ptr1=transaction;
		while(ptr1->next!=NULL)
        {
            ptr1=ptr1->next;
        }
        ptr1->next=ptr;
        ptr->next=NULL;
	}
	return transaction;
}
struct stack *display_stack(struct stack *transaction){
	struct stack *ptr;
	ptr= transaction;
	if(ptr==NULL){
		printf("NO SELL!\n\n");
	}
	else{
		int i=1;
		while(ptr!=NULL){
			printf("Sold stock : %s   price per stock: %d profit: %d\n",ptr->compname1,ptr->stock_price1,ptr->profit);
			ptr=ptr->next;
			i++;
		}
	}
	return transaction;
}
struct stack1 *display_stack1(struct stack1 *bought){
	struct stack1 *ptr;
	ptr= bought;
	if(ptr==NULL){
		printf("NOTHING BOUGHT!\n\n");
	}
	else{
		int i=1;
		printf("Transaction History:\n");
		while(ptr!=NULL){
			printf("Bought stock : %s   price per stock: %d\n",ptr->compname,ptr->stock_price);
			ptr=ptr->next;
			i++;
		}
	}
	return bought;
}
struct stack1 *push_stack1(struct stack1 *bought,char str[],int price){
	struct stack1 *ptr,*ptr1;
	ptr= (struct stack1 *)malloc(sizeof(struct stack1));
	strcpy(ptr->compname,str);
	ptr->stock_price= price;
	if(bought==NULL){
		ptr->next=NULL;
		bought=ptr;
	}
	else{
		ptr1=bought;
		while(ptr1->next!=NULL)
        {
            ptr1=ptr1->next;
        }
        ptr1->next=ptr;
        ptr->next=NULL;
	}
	return bought;
}
struct customer *sell(struct customer *start,struct node *tree)
{
    int count;
	struct customer *ptr,*preptr1,*preptr2;
	struct node *tree_ptr;
	int x,z,t;
	z=count_members(start);
	count=z;
	ptr=start;
	tree_ptr=tree;
	if(ptr==NULL){
		printf("Stock Empty, can't sell!\n\n");
		printf("Would you like to buy?\n");
		return start;
	}
	else{
		while(ptr!=NULL){
                while(tree_ptr!=NULL){
                        x=strcmp(tree_ptr->compname,ptr->compname);
                        if(x==0 && tree_ptr->stock_price>= ptr->exp_SP){
                                count--;
                                t=tree_ptr->stock_price-ptr->stock_price;
				              transaction= push_stack(transaction,ptr->stock_price,ptr->compname,t);
                              bank_balance=bank_balance+t+ptr->stock_price;
				              printf("Sold stock : %s  at price per stock: %d  profit per stock: %d\n",ptr->compname,tree_ptr->stock_price,t);
				              printf("Bank Balance: %d",bank_balance);
				              if(ptr==start){
                                start=delete_beg(start);
                                break;
				              }
                              else if(ptr->next==NULL){
                                start=delete_end(start);
                                break;
                              }
                              else
                              {
                                  preptr1=start;
                                  while(preptr1->stock_price!=ptr->stock_price)
                                  {
                                      preptr2=preptr1;
                                      preptr1=preptr1->next;
                                  }
                                  preptr2->next=preptr1->next;
                                  free(ptr);
                                  break;
                              }

			              }
			            else
				              tree_ptr=tree_ptr->right;
                }
                ptr=ptr->next;
                if(count==z)
                    count2++;
                tree_ptr=tree;
		}
		return start;
	}
}
struct customer *sell_at_less(struct customer *start,struct node *tree){
    int count1;
	struct customer *ptr,*preptr1,*preptr2;
	struct node *tree_ptr;
	ptr=start;
	tree_ptr=tree;
	int y,k,t;
	k=count_members(start);
	count1=k;
	if(ptr==NULL){
		printf("Stock Empty, can't sell!\n\n");
		printf("Would you like to buy?\n");
		return start;
	}
	else{
		while(ptr!=NULL){
                while(tree_ptr!=NULL){
                        y=strcmp(tree_ptr->compname,ptr->compname);
                        if(y==0 && tree_ptr->stock_price>= ptr->stock_price){
                                count1--;
				               t=tree_ptr->stock_price-ptr->stock_price;
				              transaction= push_stack(transaction,ptr->stock_price,ptr->compname,t);
                               bank_balance=bank_balance+t+ptr->stock_price;
				              printf("Sold stock : %s  at price per stock: %d  profit per stock: %d\n",ptr->compname,tree_ptr->stock_price,t);
				              printf("Bank Balance: %d\n",bank_balance);

				              if(ptr==start){
                                start=delete_beg(start);
                                break;
				              }
                              else if(ptr->next==NULL){
                                start=delete_end(start);
                                break;
                              }
                              else
                              {
                                  preptr1=start;
                                  while(preptr1->stock_price!=ptr->stock_price)
                                  {
                                      preptr2=preptr1;
                                      preptr1=preptr1->next;
                                  }
                                  preptr2->next=preptr1->next;
                                  free(ptr);
                                  break;
                              }

			              }
			              else if(y==0 && tree_ptr->stock_price>= ptr->minm_loss)
                          {
                               count1--;
				               t=tree_ptr->stock_price-ptr->stock_price;
				              transaction= push_stack(transaction,ptr->stock_price,ptr->compname,t);
                               bank_balance=bank_balance+t;
				              printf("Sold stock : %s  at price per stock: %d  profit per stock: %d\n",ptr->compname,tree_ptr->stock_price,t);
				              printf("Bank Balance: %d\n",bank_balance);

				              if(ptr==start){
                                start=delete_beg(start);
                                break;
				              }
                              else if(ptr->next==NULL){
                                start=delete_end(start);
                                break;
                              }
                              else
                              {
                                  preptr1=start;
                                  while(preptr1->stock_price!=ptr->stock_price)
                                  {
                                      preptr2=preptr1;
                                      preptr1=preptr1->next;
                                  }
                                  preptr2->next=preptr1->next;
                                  free(ptr);
                                  break;
                              }

                          }
			            else
				              tree_ptr=tree_ptr->right;
                }
                ptr=ptr->next;
                if(count1==k)
                    count3++;
                tree_ptr=tree;
		}
		return start;
	}
}
void create_stocks()
{
    char str1[]="Tata";
    char str2[]="Maruti";
    char str3[]="Honda";
    char str4[]="Toyota";
    char str5[]="amazon";
   treeMON=insert(treeMON,str1,10);
   treeMON=insert(treeMON,str2,20);
   treeMON=insert(treeMON,str3,30);
   treeMON=insert(treeMON,str4,40);
   treeMON=insert(treeMON,str5,25);
   treeTUES=insert(treeTUES,str1,15);
   treeTUES=insert(treeTUES,str2,25);
   treeTUES=insert(treeTUES,str3,35);
   treeTUES=insert(treeTUES,str4,45);
   treeTUES=insert(treeTUES,str5,30);
   treeWED=insert(treeWED,str1,20);
   treeWED=insert(treeWED,str2,30);
   treeWED=insert(treeWED,str3,40);
   treeWED=insert(treeWED,str4,50);
   treeWED=insert(treeWED,str5,35);
   treeTHUR=insert(treeTHUR,str1,25);
   treeTHUR=insert(treeTHUR,str2,35);
   treeTHUR=insert(treeTHUR,str3,45);
   treeTHUR=insert(treeTHUR,str4,55);
   treeTHUR=insert(treeTHUR,str5,40);
   treeFRI=insert(treeFRI,str1,30);
   treeFRI=insert(treeFRI,str2,40);
   treeFRI=insert(treeFRI,str3,50);
   treeFRI=insert(treeFRI,str4,60);
   treeFRI=insert(treeFRI,str5,45);
   treeSAT=insert(treeSAT,str1,35);
   treeSAT=insert(treeSAT,str2,45);
   treeSAT=insert(treeSAT,str3,55);
   treeSAT=insert(treeSAT,str4,65);
   treeSAT=insert(treeSAT,str5,50);
   treeSUN=insert(treeSUN,str1,40);
   treeSUN=insert(treeSUN,str2,50);
   treeSUN=insert(treeSUN,str3,60);
   treeSUN=insert(treeSUN,str4,70);
   treeSUN=insert(treeSUN,str5,55);
}
int main()
{
    create_stocks();
    int i=1,j;
    int choice,val,price,choice1;
    int d;
    char comp[30];
    do
    {
        switch(i%7)
        {
            case 1:
                   preorder(treeMON);
                   printf("1.Buy a stock\n");
                   printf("2.Sell Stocks\n");
                   printf("3.Display Transaction History\n");
                   printf("4.Exit\n");
                   do
                   {
                        printf("Enter your choice:");
                        scanf("%d",&choice1);
                        printf("\n");
                        switch(choice1)
                        {
                            case 1:
                                  printf("Enter the name of the company and price per stock of the stock you would like to buy:\n");
                                  scanf("%s",comp);
                                  scanf("%d",&price);
                                  bank_balance=bank_balance-price;
                                  printf("\nBank Balance: %d\n",bank_balance);
                                  start=push(start,comp,price);
                                  bought=push_stack1(bought,comp,price);
                                  break;
                            case 2:
                                d=count_members(start);
                                  start=sell(start,treeMON);
                                  if(count2==d)
                                  {
                                      count2=0;
                                      printf("Expected Selling Price not achieved\n");
                                      printf("Would you like to sell it at a lesser value?\n");
                                      printf("1.Yes 2.No\n");
                                      printf("Enter choice:");
                                      scanf("%d",&j);
                                      switch(j)
                                      {
                                          case 1: printf("You chose to sell at a lower price\n");
                                                  sell_at_less(start,treeMON);
                                                  break;
                                          case 2: printf("You chose not to sell\n");
                                                  break;
                                      }
                                      if(count3==d){
                                        printf("Expected Price not achieved again\n");
                                        count3=0;
                                      }
                                  }
                                  break;
                            case 3: bought=display_stack1(bought);
                                 transaction=display_stack(transaction);
                                   break;
                            case 4: printf("Market closed\n\n");
                                   break;

                        }
                   }while(choice1!=4);
                   break;
            case 2:
                   preorder(treeTUES);
                   printf("1.Buy a stock\n");
                   printf("2.Sell Stocks\n");
                   printf("3.Display Transaction History\n");
                   printf("4.Exit\n");
                   do
                   {
                        printf("\nEnter your choice:");
                        scanf("%d",&choice1);
                        printf("\n");
                        switch(choice1)
                        {
                            case 1:
                                  printf("Enter the name of the company and price per stock of the stock you would like to buy:\n");
                                  scanf("%s",comp);
                                  scanf("%d",&price);
                                  bank_balance=bank_balance-price;
                                  printf("\nBank Balance: %d\n",bank_balance);
                                  start=push(start,comp,price);
                                  bought=push_stack1(bought,comp,price);
                                  break;
                            case 2:
                                    d=count_members(start);
                                   start=sell(start,treeTUES);
                                  if(count2==d)
                                  {
                                      count2=0;
                                      printf("Expected Selling Price not achieved\n");
                                      printf("Would you like to sell it at a lesser value?\n");
                                      printf("1.Yes 2.No\n");
                                      printf("Enter choice:");
                                      scanf("%d",&j);
                                      switch(j)
                                      {
                                          case 1: printf("You chose to sell at a lower price\n");
                                                  sell_at_less(start,treeTUES);
                                                  break;
                                          case 2: printf("You chose not to sell\n");
                                                  break;
                                      }
                                      if(count3==d){
                                            count3=0;
                                        printf("Expected Price not achieved again\n");
                                      }
                                  }
                                  break;
                            case 3: bought=display_stack1(bought);
                                 transaction=display_stack(transaction);
                            break;
                            case 4: printf("Market closed\n");
                                   break;

                        }
                   }while(choice1!=3);
                   break;
            case 3:
                   preorder(treeWED);
                   printf("1.Buy a stock\n");
                   printf("2.Sell Stocks\n");
                   printf("3.Display Transaction History\n");
                   printf("4.Exit\n");
                   do
                   {
                        printf("Enter your choice:");
                        scanf("%d",&choice1);
                        printf("\n");
                        switch(choice1)
                        {
                            case 1:
                                 printf("Enter the name of the company and price per stock of the stock you would like to buy:\n");
                                  scanf("%s",comp);
                                  scanf("%d",&price);
                                  bank_balance=bank_balance-price;
                                  printf("\nBank Balance: %d\n",bank_balance);
                                  start=push(start,comp,price);
                                  bought=push_stack1(bought,comp,price);
                                  break;
                            case 2:
                                    d=count_members(start);
                                   start=sell(start,treeWED);
                                  if(count2==d)
                                  {
                                      count2=0;
                                      printf("Expected Selling Price not achieved\n");
                                      printf("Would you like to sell it at a lesser value?\n");
                                      printf("1.Yes 2.No\n");
                                      printf("Enter choice:");
                                      scanf("%d",&j);
                                      switch(j)
                                      {
                                          case 1: printf("You chose to sell at a lower price\n");
                                                  sell_at_less(start,treeWED);
                                                  break;
                                          case 2: printf("You chose not to sell\n");
                                                  break;
                                      }
                                      if(count3==d){
                                            count3=0;
                                        printf("Expected Price not achieved again\n");
                                      }
                                  }
                                  break;
                                  case 3: bought=display_stack1(bought);
                                 transaction=display_stack(transaction);
                                   break;
                            case 4: printf("Market closed\n");
                                  break;

                        }
                   }while(choice1!=3);
                   break;
            case 4:
                   preorder(treeTHUR);
                   printf("1.Buy a stock\n");
                   printf("2.Sell Stocks\n");
                   printf("3.Display Transaction History\n");
                   printf("4.Exit\n");
                   do
                   {
                        printf("Enter your choice:");
                        scanf("%d",&choice1);
                        printf("\n");
                        switch(choice1)
                        {
                            case 1:
                                 printf("Enter the name of the company and price per stock of the stock you would like to buy:\n");
                                  scanf("%s",comp);
                                  scanf("%d",&price);
                                  bank_balance=bank_balance-price;
                                  printf("\nBank Balance: %d\n",bank_balance);
                                  start=push(start,comp,price);
                                  bought=push_stack1(bought,comp,price);
                                  break;
                            case 2:
                                    d=count_members(start);
                                   start=sell(start,treeTHUR);
                                  if(count2==d)
                                  {
                                      count2=0;
                                      printf("Expected Selling Price not achieved\n");
                                      printf("Would you like to sell it at a lesser value?\n");
                                      printf("1.Yes 2.No\n");
                                      printf("Enter choice:");
                                      scanf("%d",&j);
                                      switch(j)
                                      {
                                          case 1: printf("You chose to sell at a lower price\n");
                                                  sell_at_less(start,treeTHUR);
                                                  break;
                                          case 2: printf("You chose not to sell\n");
                                                  break;
                                      }
                                      if(count3==d){
                                            count3=0;
                                        printf("Expected Price not achieved again\n");
                                      }
                                  }
                                  break;
                             case 3: bought=display_stack1(bought);
                                 transaction=display_stack(transaction);
                                   break;
                            case 4: printf("Market closed\n");
                                   break;


                        }
                   }while(choice1!=3);
                   break;
            case 5:
                   preorder(treeFRI);
                   printf("1.Buy a stock\n");
                   printf("2.Sell Stocks\n");
                   printf("3.Display Transaction history\n");
                   printf("4.Exit\n");
                   do
                   {
                        printf("Enter your choice:");
                        scanf("%d",&choice1);
                        printf("\n");
                        switch(choice1)
                        {
                            case 1:
                                  printf("Enter the name of the company and price per stock of the stock you would like to buy:\n");
                                  scanf("%s",comp);
                                  scanf("%d",&price);
                                  bank_balance=bank_balance-price;
                                  printf("\nBank Balance: %d\n",bank_balance);
                                  start=push(start,comp,price);
                                  bought=push_stack1(bought,comp,price);
                                  break;
                            case 2:
                                    d=count_members(start);
                                   start=sell(start,treeFRI);
                                  if(count2==d)
                                  {
                                      printf("Expected Selling Price not achieved\n");
                                      printf("Would you like to sell it at a lesser value?\n");
                                      printf("1.Yes 2.No\n");
                                      printf("Enter choice:");
                                      scanf("%d",&j);
                                      switch(j)
                                      {
                                          case 1: printf("You chose to sell at a lower price\n");
                                                  sell_at_less(start,treeFRI);
                                                  break;
                                          case 2: printf("You chose not to sell\n");
                                                  break;
                                      }
                                      if(count3==d)
                                        printf("Expected Price not achieved again\n");
                                  }
                                  break;
                             case 3: bought=display_stack1(bought);
                                 transaction=display_stack(transaction);
                                   break;
                            case 4: printf("Market closed\n");
                                   break;


                        }
                   }while(choice1!=3);
                   break;
            case 6:
                   preorder(treeSAT);
                   printf("1.Buy a stock\n");
                   printf("2.Sell Stocks\n");
                   printf("3.Display Transaction History\n");
                   printf("4.Exit\n");
                   do
                   {
                        printf("Enter your choice:");
                        scanf("%d",&choice1);
                        printf("\n");
                        switch(choice1)
                        {
                            case 1:
                                 printf("Enter the name of the company and price per stock of the stock you would like to buy:\n");
                                  scanf("%s",comp);
                                  scanf("%d",&price);
                                  bank_balance=bank_balance-price;
                                  printf("\nBank Balance: %d\n",bank_balance);
                                  start=push(start,comp,price);
                                  bought=push_stack1(bought,comp,price);
                                  break;
                            case 2:
                                    d=count_members(start);
                                   start=sell(start,treeSAT);
                                  if(count2==d)
                                  {
                                      printf("Expected Selling Price not achieved\n");
                                      printf("Would you like to sell it at a lesser value?\n");
                                      printf("1.Yes 2.No\n");
                                      printf("Enter choice:");
                                      scanf("%d",&j);
                                      switch(j)
                                      {
                                          case 1: printf("You chose to sell at a lower price\n");
                                                  sell_at_less(start,treeSAT);
                                                  break;
                                          case 2: printf("You chose not to sell\n");
                                                  break;
                                      }
                                      if(count3==d)
                                        printf("Expected Price not achieved again\n");
                                  }
                                  break;
                             case 3: bought=display_stack1(bought);
                                 transaction=display_stack(transaction);
                                   break;
                            case 4: printf("Market closed\n");
                                   break;


                        }
                   }while(choice1!=3);
                   break;
            case 0:
                   preorder(treeSUN);
                   printf("1.Buy a stock\n");
                   printf("2.Sell Stocks\n");
                   printf("3.Display Transaction History\n");
                   printf("4.Exit\n");
                   do
                   {
                        printf("Enter your choice:");
                        scanf("%d",&choice1);
                        printf("\n");
                        switch(choice1)
                        {
                            case 1:
                                  printf("Enter the name of the company and price per stock of the stock you would like to buy:\n");
                                  scanf("%s",comp);
                                  scanf("%d",&price);
                                  bank_balance=bank_balance-price;
                                  printf("\nBank Balance: %d\n",bank_balance);
                                  start=push(start,comp,price);
                                  bought=push_stack1(bought,comp,price);
                                  break;
                            case 2:
                                    d=count_members(start);
                                   start=sell(start,treeSUN);
                                  if(count2==d)
                                  {
                                      printf("Expected Selling Price not achieved\n");
                                      printf("Would you like to sell it at a lesser value?\n");
                                      printf("1.Yes 2.No\n");
                                      printf("Enter choice:");
                                      scanf("%d",&j);
                                      switch(j)
                                      {
                                          case 1: printf("You chose to sell at a lower price\n");
                                                  sell_at_less(start,treeSUN);
                                                  break;
                                          case 2: printf("You chose not to sell\n");
                                                  break;
                                      }
                                      if(count3==d)
                                        printf("Expected Price not achieved again\n");
                                  }
                                  break;

                             case 3:
                                 bought=display_stack1(bought);
                                 transaction=display_stack(transaction);
                                   break;
                            case 4: printf("Market closed\n");
                                   break;


                        }
                   }while(choice1!=3);
                   break;
        }
        i++;
    }while(i>0);
    return 0;
}
