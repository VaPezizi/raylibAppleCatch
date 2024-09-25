#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "linkedlist.h"

Node * Head = NULL;
Node * First = NULL;

int ListAppendNode(Apple data){
//	Node * current = First;
	if(Head == NULL){
		First = (Node*)malloc(sizeof(Node));
		if(First){
			First->data = data;
			First->next = NULL;
			Head = First;
		}else puts("VIRHE");
		//printf("Testi\n");
		return 0;
	}
	else{/*
		while(1){
			if(current->next==NULL){
				Node* added = (Node*)malloc(sizeof(Node));
				added->data = data;
				added->next = NULL;
				current->next = added;
				return 0;
			}else{
				current = current->next;
			}
		}*/
		//I'm too drunk to understand why this doesn't work
		//Edit: nvm figured it out and fixed
		Node * added = (Node*) malloc(sizeof(Node));
		if(added){
			added->data = data;
			added->next = NULL;
			Head->next = added;
			Head = added;
		}else{
			puts("VIRHE");
		}
	}
	puts("Succesfully added apple!");
	return 0;	
}
int ListRemoveNode(int index){
	if(First == NULL){
		puts("List is empty!");
		return 1;
	}
	Node* current = First;

	if(index == 0){
		First = current->next;
		if(Head == current)Head = current->next;
		free(current);
		//Head = NULL;
		puts("Succesfully destroyed Apple!");
		return 0;
	}

	for(int i = 0;i < index - 1;i++){
		if(current->next == NULL){
			printf("Index out of range\n");
			return 1;
		}
		/*if(current->next == Head){
			Head = current;
			
		}*/
		//puts("Testi");		

		current = current->next;
	}
	
		
	//puts("Moro");
	if(current->next == Head){		
		free(current->next);
		Head = current;

	}
	puts("Succesfully destroyed Apple!");
	Node* temp = current->next;
	current->next = temp->next;
	free(temp);

	return 0;	

}
int ListDestroyList(){
	if(First == NULL){
		return 0;
	}
	if(First->next == NULL){
		free(First);
		return 0;
	}
	Node* next = First->next;
	Node* current = First;
	while(current->next != NULL){
		next = current->next;
		free(current);
		current = next;
	}
	Head = NULL;
	First = NULL;
	free(current);
	return 0;
}

int ListCpNode(Apple* apple, int index){
	Node * current = First;
	for(int i = 0; i < index; i++){
		if(current->next != NULL){
			current = current->next;
		}else{
			return 1;	//Index out of range
		}
	}
	apple = &current->data;
	return 0;
}
/*int ListDrawNodes(Texture2D * texture){
	
	if(First == NULL){
		return 1;
	}
	Node * current = First;

	if(current->next == NULL){
		DrawTextureEx(* texture, (Vector2) {current->data.position.x, current->data.position.y} , 0, current->data.size * 0.007, WHITE);
		return 0;
	}

	while(current->next != NULL){
		//printf("Node: %d\n", current->data);
		//puts("Testi");	
		DrawTextureEx(* texture, (Vector2) {current->data.position.x, current->data.position.y} , 0, current->data.size * 0.007, WHITE);		
		current = current->next;
	}
	
	DrawTextureEx(* texture, (Vector2) {current->data.position.x, current->data.position.y} , 0, current->data.size * 0.007, WHITE);		
	return 0;	

}*/

int ListUpdateApples(float DeltaTime, float AppleSpeed, Texture2D * texture, Basket * basket, int * score){

	int index = 0;	
	if(First == NULL){
		puts("FIRST=NULL!!");
		return 0;
	}
	Node * current = First;
	printf("currentX: %f\n", current->data.position.x);

	Rectangle rect = {
		basket->position.x,
		basket->position.y,
		50,
		50
	};

	if(current->next == NULL){
		DrawTextureEx(* texture, (Vector2) {current->data.position.x, current->data.position.y} , 0, current->data.size * 0.007, WHITE); //Drawing apple
		current->data.position.y = current->data.position.y + AppleSpeed * DeltaTime;	//Moving apple
		
		Rectangle appleRect = {
			current->data.position.x,
			current->data.position.y,
			20,
			20
		};
		//printf("Apple x:%f, y:%f\n", current->data.position.x, current->data.position.y);
		if(CheckCollisionRecs(rect, appleRect)){
			ListRemoveNode(index);
			*score = *score + 1;
			return 0;
		}

		else if(current->data.position.y >= height)ListRemoveNode(index);	//Checking if apple is too low
		return 0;
	}

	while(current->next != NULL){
		//printf("Node: %d\n", current->data);
		//puts("Testi");	
		DrawTextureEx(* texture, (Vector2) {current->data.position.x, current->data.position.y} , 0, current->data.size * 0.007, WHITE);	//Drawing		
		current->data.position.y = current->data.position.y + AppleSpeed * DeltaTime;	//Moving
			
		//printf("Apple x:%f, y:%f\n", current->data.position.x, current->data.position.y);
		
		Rectangle appleRect = {
			current->data.position.x,
			current->data.position.y,
			50,
			50
		};

		if(CheckCollisionRecs(rect, appleRect)){
			current = current->next;
			ListRemoveNode(index);
			*score = *score + 1;
		}
		
		else if(current->data.position.y >= height){
			current = current->next;
			ListRemoveNode(index);
		}else{

		
			current = current->next;	
		}

		index++;

	}
	
	current->data.position.y = current->data.position.y + AppleSpeed * DeltaTime;
	
	//printf("Apple x:%f, y:%f\n", current->data.position.x, current->data.position.y);
	DrawTextureEx(* texture, (Vector2) {current->data.position.x, current->data.position.y} , 0, current->data.size * 0.007, WHITE);		
	return 0;	
}
int ListPrintPositions(){
	int index = 0;
	if(First==NULL){
		return 1;
	}
	Node * current = First;
	if(current->next==NULL){	
		printf("Position X: %f, Position Y: %f, Index: %d \n", current->data.position.x, current->data.position.y, index);
		return 0;
		//index++;
	}	
	while(current->next != NULL){
		printf("Position X: %f, Position Y: %f, Index: %d \n", current->data.position.x, current->data.position.y, index);
		current = current->next;
		index++;
	}
	
	//printf("Position X: %f, Position Y: %f, Index: %d \n", current->data.position.x, current->data.position.y, index);
	return 0;
}

Apple * ListGetNode(int index){
	Node * current = First;
	for(int i = 0; i < index; i++){
		if(current->next != NULL){
			current = current->next;
		}else{
			Apple * ptr = NULL;
			return ptr;	//Index out of range
		}
	}
	return &current->data;
}

int ListGetHead(Node* node){
	if(Head==NULL){
		return 1;
	}
	else{
		node = Head;
		return 0;
	}
}
