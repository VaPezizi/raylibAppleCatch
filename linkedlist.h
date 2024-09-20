#include "game.h"
#include <raylib.h>

Apple * ListGetNode(int index);

int ListUpdateApples(float DeltaTime, float AppleSpeed, Texture2D * texture);
//int ListMoveApples(float DeltaTime, float AppleSpeed);
int ListGetHead(Node* node);
//int ListDrawNodes(Texture2D * texture);
int ListRemoveNode();
int ListDestroyList();
int ListAddNode(Apple data);
int ListPrintPositions();
int ListCpNode(Apple* apple, int index); 
