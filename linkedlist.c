#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "linkedlist.h"

Node * Head = NULL;
Node * First = NULL;

int ListAddNode(Apple data){
	Node * current = First;
	if(Head == NULL){
		First = (Node*)malloc(sizeof(Node));
		First->data = data;
		First->next = NULL;
		Head = First;
		//printf("Testi\n");
		return 0;
	}
	else{
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
		}
		
		
	}
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
		free(current);
		return 0;
	}

	for(int i = 0;i < index - 1;i++){
		if(current->next == NULL){
			printf("Index out of range\n");
			return 1;
		}
			

		current = current->next;
	}
	
	//puts("Moro");
	Node* temp = current->next->next;
	free(current->next);
	current->next = temp;
	return 0;	

}
int ListDestroyList(){
	if(First == NULL){
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

int ListGetNode(Apple* apple, int index){
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
int ListDrawNodes(Texture2D * texture){
	
	if(Head == NULL){
		return 1;
	}
	Node * current = First;
	DrawTextureEx(* texture, (Vector2) {current->data.position.x, current->data.position.y} , 0, 10, WHITE);		
	while(current->next != NULL){
		//printf("Node: %d\n", current->data);
		
		DrawTextureEx(* texture, (Vector2) {current->data.position.x, current->data.position.y} , 0, current->data.size, WHITE);		
		current = current->next;
	}
	return 0;	

}




	/*Node * Head = NULL;
	addNode(1);	
	addNode(2);	
	addNode(3);
	removeNode(0);
	addNode(4);
	addNode(5);
	printList();
	removeNode(1);
	printf("\n");
	printList();
	destroyList();
	printList();
	removeNode(999);

	puts("");
	addNode(1);
	addNode(2);
	printList();

	printNode(3);

	destroyList();
	destroyList();*/


