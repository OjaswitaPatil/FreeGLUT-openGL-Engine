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

    ptr->shape.scale.x = 0.35f;
    ptr->shape.scale.y = 0.35f;
    ptr->shape.scale.z = 0.35f;

    ptr->shape.color[0] = 1.0f;
    ptr->shape.color[1] = 0.0f;
    ptr->shape.color[2] = 0.0f;

    ptr->shape.customShapeAttributesCount = 0;

    switch(shapeType)
    {
        case SPHERE:
            ptr->shape.customShapeAttributesCount = 3;
            ptr->shape.customShapeAttributes = (float*)malloc(sizeof(float) * ptr->shape.customShapeAttributesCount);
            ptr->shape.customShapeAttributes[0] = 1.0f;   //glu fill
            ptr->shape.customShapeAttributes[1] = 20.0f;  //slices
            ptr->shape.customShapeAttributes[2] = 20.0f;  //stacks
            break;

        case CYLINDER:
            ptr->shape.customShapeAttributesCount = 6;
            ptr->shape.customShapeAttributes = (float*)malloc(sizeof(float) * ptr->shape.customShapeAttributesCount);
            ptr->shape.customShapeAttributes[0] = 1.0f;   //glu fill
            ptr->shape.customShapeAttributes[1] = 0.5f;   //1st opening
            ptr->shape.customShapeAttributes[2] = 0.5f;   //2nd opening
            ptr->shape.customShapeAttributes[3] = 4.0f;   //length
            ptr->shape.customShapeAttributes[4] = 20.0f;  //slices
            ptr->shape.customShapeAttributes[5] = 20.0f;  //stacks
            break;
            
        default:
            ptr->shape.customShapeAttributes = NULL;
    }

             

    ptr->next = NULL;
    ptr->pre = NULL;

    if(head == NULL)
    {
        ptr->next = ptr;
        ptr->pre = ptr;
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

    //delete customShapeAttrubute heap memory if its not null
    if(ptr->shape.customShapeAttributes != NULL)  
    {
        free(ptr->shape.customShapeAttributes);
    }  
  
    //free structre shape heap memory
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

    if(selectedShape!= NULL)
        drawGridAroundSelectedShape(&(selectedShape->shape));
}
