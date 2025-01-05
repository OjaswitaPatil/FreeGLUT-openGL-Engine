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

// Function to read and process the CSV file
void loadCSV(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        printf("Error: Could not open file during reading csv : %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    float data[MAX_LINE_LENGTH];      // Array to store the values (you can adjust size)
    int index = 0;
    int first_row = 1;                // Flag to skip header

    while (fgets(line, sizeof(line), file)) 
    {
        if (first_row == 1) 
        {
            // Skip the first row (header)
            first_row = 0; 
            continue;
        }

        // Tokenize the line using comma as delimiter
        char *token = strtok(line, ",");

        // Convert token to float
        ShapeType shapeType = getShapeType(atoi(token));
        struct Node* ptr = createShape(shapeType);

        if(ptr == NULL)
        {
            printf("Error: Could not create shape\n");
            return;
        }

        while (token != NULL) 
        {
            data[index] = atof(token);
            index = index + 1;

            // Get next token
            token = strtok(NULL, ",");
        }

        index = 1;
        ptr->shape.position.x = data[index++];
        ptr->shape.position.y = data[index++];
        ptr->shape.position.z = data[index++];

        ptr->shape.scale.x = data[index++];
        ptr->shape.scale.y = data[index++];
        ptr->shape.scale.z = data[index++];

        ptr->shape.rotationAngle.x = data[index++];
        ptr->shape.rotationAngle.y = data[index++];
        ptr->shape.rotationAngle.z = data[index++];

        ptr->shape.color[0] = data[index++];
        ptr->shape.color[1] = data[index++];
        ptr->shape.color[2] = data[index++];

        ptr->shape.customShapeAttributesCount = (int)data[index++];

        if( shapeType == SPHERE)
        {
            ptr->shape.customShapeAttributes[0]= data[index++];
            ptr->shape.customShapeAttributes[1]= data[index++];
            ptr->shape.customShapeAttributes[2]= data[index++];
        }
        else if( shapeType == CYLINDER)
        {
            ptr->shape.customShapeAttributes[0]= data[index++];
            ptr->shape.customShapeAttributes[1]= data[index++];
            ptr->shape.customShapeAttributes[2]= data[index++];
            ptr->shape.customShapeAttributes[3]= data[index++];
            ptr->shape.customShapeAttributes[4]= data[index++];
            ptr->shape.customShapeAttributes[5]= data[index++];
        }
        else
        {
            ptr->shape.customShapeAttributes = NULL;
        }

        //reset index for next row
        index = 0;
        for(int i=0; i < MAX_LINE_LENGTH; i++)
            data[i] = 0.0f;
    }

    fclose(file);
}

