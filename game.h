#include <raylib.h>

typedef struct{
	float size;
	Vector2 position;
	int speed;
}Basket;

typedef struct{
	float size;
	Vector2 position;
	int speed;
}Apple;


typedef struct Node{
	Apple data;
	struct Node* next;
} Node;
