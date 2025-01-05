#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//header files
#include <stdlib.h>
#include "globalHeaders.h"
#include "Shape.h"


struct Node
{
    Shape shape;
    struct Node *pre;
    struct Node *next;
};

extern struct Node *head;
extern struct Node *last;
extern struct Node *selectedShape;

//function prototype
struct Node* createShape(ShapeType shapeType);

void drawAllShapes(void);

void deleteShape(struct Node *ptr);

#endif
