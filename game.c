#include <raylib.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "linkedlist.h"

const Vector2 BASKETSTART = {height/2, width/2};
const int BASKETMAXSPEED = 300;


Apple createApple(){
	srand(time(NULL));
	float rand_num = (float)rand()/(float)(RAND_MAX/width); 	
	Apple apple = {	
		20,
		(Vector2) {rand_num, 100},
		0
	};
	return apple;

}

int main(){
	
	InitWindow( width, height, "Apple catch");	
	SetTargetFPS( 60 );

	float appleSpeed = 20;	
	double spawnSpeed = 1.5;
	time_t spawnTime = time(NULL);

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

	Apple testApple3 = {
		20,			//Size
		(Vector2) {300, 100},	//Position
		0
	};
	Apple testApple2 = {
		20,
		(Vector2) {200, 100},
		0
	};

	
	ListAddNode(testApple);
	ListAddNode(testApple2);
	ListAddNode(testApple3);
	ListAddNode(createApple());
	//ListRemoveNode(1);

	Texture2D basketTexture = LoadTexture("basket.png");
	Texture2D appleTexture = LoadTexture("apple.png");
	
	Apple * ptr = ListGetNode(1);
	printf("X: %f, Y: %f\n", ptr->position.x, ptr->position.y);	

	//Main game loop
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
		
			
		if(difftime(time(NULL), spawnTime) > spawnSpeed){
			spawnTime = time(NULL);
			spawnSpeed = spawnSpeed - 0.05;
			ListAddNode(createApple());
		}

		//Piirto koordinaatit X, Y
		/*if(fmod(GetTime(), 5) == 0){
			puts("Moro");
			ListAddNode(createApple());
		}*/	
		//Basket Movements
		if(IsKeyDown(KEY_LEFT) && mainBasket.position.x > 0){mainBasket.position.x = mainBasket.position.x - BASKETMAXSPEED * GetFrameTime();}
		else if(IsKeyDown(KEY_RIGHT) && mainBasket.position.x < width - 40){mainBasket.position.x = mainBasket.position.x + BASKETMAXSPEED * GetFrameTime();}


		ListUpdateApples(GetFrameTime(), appleSpeed, &appleTexture);
		//ListDrawNodes(&appleTexture);
		DrawTextureEx(basketTexture, (Vector2) {mainBasket.position.x, mainBasket.position.y} , 0, (mainBasket.size * 0.002), WHITE);		
		//ListPrintPositions();		

		//printf("%d \n", ListDrawNodes(&appleTexture));

		appleSpeed = appleSpeed + 0.1;
		//ListMoveApples(GetFrameTime(), appleSpeed);		

		EndDrawing();
	}
	UnloadTexture(basketTexture);
	
	UnloadTexture(appleTexture);
	
	ListPrintPositions();

	ListDestroyList();	
	CloseWindow();
	return 0;
}


