#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "linkedlist.h"

const int width = 800;
const int height  = 600;
const Vector2 BASKETSTART = {height/2, width/2};
const int BASKETMAXSPEED = 5;


int main(){

	

	InitWindow( width, height, "Apple catch");	
	SetTargetFPS( 60 );

	Basket mainBasket = {
		20,			//Size
		BASKETSTART,	//Position
		0			//Velocity

	};
	Apple testApple = {
		20,			//Size
		(Vector2) {100, 100},	//Position
		0
	};
	Apple testApple2 = {
		40,
		(Vector2) {0, 100},
		0
	};

	
	ListAddNode(testApple);
	ListAddNode(testApple2);

	Texture2D basketTexture = LoadTexture("basket.png");
	Texture2D appleTexture = LoadTexture("apple.png");

	//Main game loop
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
		//Piirto koordinaatit X, Y
	
		//Basket Movements
		if(IsKeyDown(KEY_LEFT) && mainBasket.position.x > 0){mainBasket.position.x = mainBasket.position.x - BASKETMAXSPEED;}
		else if(IsKeyDown(KEY_RIGHT) && mainBasket.position.x < width){mainBasket.position.x = mainBasket.position.x + BASKETMAXSPEED;}


		ListDrawNodes(&appleTexture);
		DrawTextureEx(basketTexture, (Vector2) {mainBasket.position.x, mainBasket.position.y} , 0, (mainBasket.size * 0.002), WHITE);		
		ListPrintPositions();		

		//printf("%d \n", ListDrawNodes(&appleTexture));

		

		EndDrawing();
	}
	UnloadTexture(basketTexture);
	
	UnloadTexture(appleTexture);
	
	ListDestroyList();	
	CloseWindow();
	return 0;
}

