#include <raylib.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "linkedlist.h"

#define NUM_FRAMES 3

const Vector2 BASKETSTART = {height/2, width/2};
const int BASKETMAXSPEED = 600;

Apple createApple(){
	srand(time(NULL));
	float rand_num = (float)rand()/(float)(RAND_MAX/width); 	
//	Apple * apple = malloc(sizeof(Apple));
//	apple->size = 20;
//	apple->position.x = rand_num;
//	apple->position.y = 100;
	
	Apple apple = {	
		APPLESIZE,
		(Vector2) {rand_num, 100},
		0
	};
	puts("Succesfully created Apple!!");
	return apple;

}

int main(){
	
	InitWindow( width, height, "Apple catch");	
	SetTargetFPS( 60 );

	int menu = 1;
	float appleSpeed = 20;	
	double spawnSpeed = 1.5;
	time_t spawnTime = time(NULL);

	int * score = calloc(1, sizeof(int));

	Basket mainBasket = {
		20,			//Size
		BASKETSTART,	//Position
		0			//Velocity

	};
	
//	ListAppendNode(createApple());
	//ListRemoveNode(1);

	Texture2D basketTexture = LoadTexture("basket.png");
	Texture2D appleTexture = LoadTexture("apple.png");
	Texture2D startButton = LoadTexture("start.png");	

	
	float frameHeight = (float)startButton.height;
    	Rectangle sourceRec = { 0,
	       			0,
			        (float)startButton.width, frameHeight 
	};
	
	Rectangle btnBounds = { width/2.0f - startButton.width/2.0f,
	       			height/2.0f - startButton.height/NUM_FRAMES/2.0f, 
				(float)startButton.width, 
				frameHeight 
	};

//	int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
//	int btnAction = 0;         //

	
	Vector2 mousePoint = { 0.0f, 0.0f };
	//Main game loop
	while(!WindowShouldClose()) {

		
		mousePoint = GetMousePosition();
 //       	btnAction = 0;

		BeginDrawing();
		ClearBackground(LIGHTGRAY);
		
		if(!menu){
			char scorestr[20];
			sprintf(scorestr, "%d", *score);
			DrawText(scorestr, 50, 50, 50, BLACK);	
				
			if(difftime(time(NULL), spawnTime) > spawnSpeed){
				spawnTime = time(NULL);
				spawnSpeed = spawnSpeed * 0.95;
				ListAppendNode(createApple());
			}

			//Piirto koordinaatit X, Y
			/*if(fmod(GetTime(), 5) == 0){
				puts("Moro");
				ListAddNode(createApple());
			}*/	
			//Basket Movements
			if(IsKeyDown(KEY_LEFT) && mainBasket.position.x > 0){mainBasket.position.x = mainBasket.position.x - BASKETMAXSPEED * GetFrameTime();}
			else if(IsKeyDown(KEY_RIGHT) && mainBasket.position.x < width - 40){mainBasket.position.x = mainBasket.position.x + BASKETMAXSPEED * GetFrameTime();}


			if(ListUpdateApples(GetFrameTime(), appleSpeed, &appleTexture, &mainBasket, score)){
				ListDestroyList();
				menu = 1;
				appleSpeed = 20;
				spawnSpeed = 1.5;
				*score = 0;
			}
			//ListDrawNodes(&appleTexture);
			DrawTextureEx(basketTexture, (Vector2) {mainBasket.position.x, mainBasket.position.y} , 0, (mainBasket.size * 0.002), WHITE);		
			//ListPrintPositions();		

			//printf("%d \n", ListDrawNodes(&appleTexture));

			appleSpeed = appleSpeed + 0.1;
			//ListMoveApples(GetFrameTime(), appleSpeed);		
		}else{
			DrawTextureRec(startButton, sourceRec, (Vector2) {btnBounds.x, btnBounds.y}, WHITE);
			if(CheckCollisionPointRec(mousePoint, btnBounds)){
				if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
					menu = 0;	
				}
			}

			//DrawTextureEx(startButton, 
		}
		EndDrawing();
	}

	free(score);
	UnloadTexture(basketTexture);
	UnloadTexture(startButton);	
	UnloadTexture(appleTexture);
	
	ListPrintPositions();

	ListDestroyList();	
	CloseWindow();
	return 0;
}


