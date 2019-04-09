#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//going to have to code a search for item function
void callerFunction();
void checkInventory();
void makePurchase();
void loadData();
void saveData();
void getName();
int isThere(char *item);
//Use a linked list to store the item data
struct Node{ 
	char itemName[25];
	int quantity;
	double price;
	struct Node *next;
};
struct Node *first = NULL;

int main(){
	//This stores the user input value
	int response;
	char name[50];
	//Load store data from text file
	loadData();
	do{
	
		printf("Please enter the operation that you would like to perform:\n0 to make purchase\n1 to see inventory\n2 to for item lookup\n3 to exit program\n");
		scanf("%d", &response);

		switch(response){
		
			case 0:		
				makePurchase();//allows user to remove an item from inventory
				break;
			case 1: 
				checkInventory();//allows the user to check what's in stock
				break;
			case 2:
				callerFunction();//allows for item lookup
				break;
			case 3:
				break;
		}

	}while(response != 3);
	
	//call the function saveData so that it can write the struct to the txt file
	saveData();

	return 0;
}

void loadData(){
	FILE *fp = fopen("store.txt", "r");
	if(fp == NULL){
		printf("There was sometype of error opening up the file");
		exit(0);
	}
	struct Node *newNode = malloc(sizeof(struct Node));
	while(fscanf(fp, "%s %d %lf", newNode -> itemName, &newNode -> quantity, &newNode -> price) != EOF){
		newNode -> next = first;
		first = newNode;
		newNode = malloc(sizeof(struct Node));
	}

	fclose(fp);
}

void makePurchase(){
	char item[50];
	int returnValue;
	int numItems;
	double purchaseTotal;
	double userPayment;
	double change;
	checkInventory();
	printf("Please enter the name of the item you would like to purchase\n");
	scanf(" %s", item);
	
	returnValue = isThere(item);
	if(returnValue == 0){
		return;
	}

	struct Node *p;
	for(p = first; p != NULL; p = p -> next){
		if(strcmp(p -> itemName, item) == 0){
			purchaseTotal = p -> price;
			break;
		}
	}

	printf("How many of these items would you like to purchase?\n");
	scanf(" %d", &numItems);
	
	while(numItems < 0){
		printf("Please enter a number of items great than or equal to 0");
		scanf(" %d", numItems);
	}
	//write a function for editing the data that is stored in a text file. 
	purchaseTotal = purchaseTotal * numItems;

	//I need to decrease the amount of items that are in the the struct
	//to reflect the amount of items that are left
	for(p = first; p != NULL; p = p -> next){
		if(strcmp(p -> itemName, item) == 0){
			p -> quantity = p -> quantity - numItems;
			break;
		}
	}

	printf("The total for this purchase will be %lf\nPlease enter the amount that you'll be providing(amount has to be greater than or equal to total)\n", purchaseTotal);
	scanf("  %lf", &userPayment);
	
	while(userPayment < purchaseTotal){
		printf("The payment amount is less than what is required please enter in a higher amount\n");
		scanf(" %lf", &userPayment);
	}
	change = purchaseTotal - userPayment;

	printf("Your change is %lf\tThank you for doing business with us\n", change);
}

void saveData(){
	FILE *fp = fopen("store.txt", "w+");
	if(fp == NULL){
		printf("There was sometype of error opening up the file");
		exit(0);
	}
	
	struct Node *p;
	for(p = first; p != NULL; p = p -> next){
		fprintf(fp, "%s %d %lf\n", p -> itemName, p -> quantity, p -> price);
	}

	fclose(fp);

}

void checkInventory(){
	struct Node *p;	
	//This function just prints out all of the items that are in the linked list	
	printf("Item Name\tQuantity\tPrice\n");
	for(p = first; p != NULL; p = p -> next){
		printf("%s\t\t%d\t\t%lf\n", p -> itemName, p -> quantity, p -> price);
	}
}
int isThere(char item[]){
	struct Node *p;
	for(p = first; p != NULL; p = p -> next){
		if(strcmp(p -> itemName, item) == 0){
			printf("Item found\n");
			printf("%s\t%d\t%lf\n", p -> itemName, p -> quantity, p -> price);
			return 1;
			
		}
	}

	printf("The item wasn't found\n");
	return 0;
}
void callerFunction(){
	char item[50];
	printf("Please enter the name of the item that you're looking for\n");
	scanf(" %s", item);

	isThere(item);
}
