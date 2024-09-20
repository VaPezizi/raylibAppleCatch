#include <raylib.h>

static const int width = 800;
static const int height  = 600;

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
