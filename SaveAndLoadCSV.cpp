#include "SaveAndLoadCSV.h"

int saveToCSV(char *fileName, struct Node *head)
{
    // create csv file
    char filePath[11] = "resources/";
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s%s", filePath,fileName);
    FILE *file = fopen(fullPath, "w");  
    if (file == NULL)
    {
        printf("Error : File cannot be opened !\n");
        return -1;
    }

    // write data to file   
    fprintf(file, "shapetype, posX, posY, posZ, scaleX, scaleY, scaleZ, rotX, rotY, rotZ , colorR, colorG, colorB, customShapeAttributesCount, CSA0, CSA1, CSA2, CSA3, CSA4, CSA5\n");

    // write data of each SHAPE to file
    int flag = 0;
    struct Node *ptr = head;
    int maxCountOfCustomShapeAttributes = 6;
    
    while(ptr != NULL && flag == 0)
    {
        fprintf(
            file, 
            "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%d,", 
            ptr->shape.shapetype, 
            ptr->shape.position.x, ptr->shape.position.y, ptr->shape.position.z, 
            ptr->shape.scale.x, ptr->shape.scale.y, ptr->shape.scale.z, 
            ptr->shape.rotationAngle.x, ptr->shape.rotationAngle.y, ptr->shape.rotationAngle.z, 
            ptr->shape.color[0], ptr->shape.color[1], ptr->shape.color[2], 
            ptr->shape.customShapeAttributesCount
        );

        for(int i=0; i < ptr->shape.customShapeAttributesCount; i++)
        {
            fprintf(file, "%lf", ptr->shape.customShapeAttributes[i]);

            if(i != maxCountOfCustomShapeAttributes-1)
                fprintf(file, ",");
        }

        for(int i=ptr->shape.customShapeAttributesCount; i < maxCountOfCustomShapeAttributes; i++)
        {
            fprintf(file, "0.0");

            if(i != maxCountOfCustomShapeAttributes-1)
                fprintf(file, ",");
        }

    fprintf(file, "\n");

        if(ptr->next == head)
           flag = 1;

        ptr= ptr->next;   
    }

    // close file
    fclose(file);
}
