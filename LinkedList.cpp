#include "LinkedList.h"

struct Node *head = NULL;
struct Node *last = NULL;
struct Node *selectedShape = head;//head is null at begining

void createShape(ShapeType shapeType)
{
   
    struct Node *ptr =(struct Node*)malloc(sizeof(struct Node));

    ptr->shape.shapetype = shapeType; 

    ptr->shape.position.x = 0.0f;
    ptr->shape.position.y = 0.0f;
    ptr->shape.position.z = 0.0f;

    ptr->shape.rotationAngle.x = 0.0f;
    ptr->shape.rotationAngle.y = 0.0f;
    ptr->shape.rotationAngle.z = 0.0f;

    ptr->shape.scale.x = 0.15f;
    ptr->shape.scale.y = 0.15f;
    ptr->shape.scale.z = 0.15f;

    ptr->shape.color[0] = 1.0f;
    ptr->shape.color[1] = 0.0f;
    ptr->shape.color[2] = 0.0f;

    ptr->next = NULL;
    ptr->pre = NULL;

    if(head == NULL)
    {
        head = ptr;
        last = ptr;
    }
    else
    {
        last->next = ptr;
        ptr->pre = last;
        ptr->next = head;
        head->pre = ptr;
        last = ptr;
    }

    selectedShape = ptr;
}

void deleteShape(struct Node *ptr)
{
    if(ptr == NULL)
        return;

    if(head == last)
    {
        head = NULL;
        last = NULL;
    }
    else if(ptr == head)
    {
        ptr->next->pre = last;
        last->next = ptr->next;
        head = ptr->next;
    }
    else if(ptr == last)
    {
        head->pre = last->pre;
        last->pre->next = head;
        last = last->pre;
    }
    else
    {
        ptr->pre->next = ptr->next;
        ptr->next->pre = ptr->pre;
    }

    if(head != NULL)
        selectedShape = selectedShape->pre;
    else   
        selectedShape = NULL;

    free(ptr);
}

void drawAllShapes(void)
{
    void drawShape(Shape *shape);

    int flag = 0;
    struct Node *ptr = head;
    
    while(ptr != NULL && flag == 0)
    {
        drawShape(&(ptr->shape));

        if(ptr->next == head)
           flag = 1;

        ptr= ptr->next;   
    }
}
