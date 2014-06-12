//
//  ObjModelLoader.cpp
//  SimpleParticleSystem
//
//  Created by James Milton on 11/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "ObjModelLoader.h"
#include <CoreFoundation/CoreFoundation.h>

typedef struct {
    float x;
    float y;
    float z;
} vector;

typedef struct {
    int x;
    int y;
    int z;
} iVector;

typedef struct {
    iVector xVec;
    iVector yVec;
    iVector zVec;
} element;


char* getSubstringUpToDelimiter(int startIndex, const char *substr, char delimiter) {
    int j = startIndex;
    // we have found a vertex. lets get it!
    int end = 0;
    while (!end) {
        if (substr[j] == delimiter){
            end = 1;
        } else {
            j++;
        }
    }
    
    int length = j-startIndex;
    
    char *newStr = (char*)malloc(length+1);
    strncpy(newStr, substr+startIndex, length);
    newStr[length] = '\0';
    return newStr;
}

vector getVectorFromSubstring(char *substr, const char* delimiter){
    vector vVector;
    
    const char *x = strtok(substr, delimiter);
    if (x == NULL)x = "0";
    const char *y = strtok(NULL, delimiter);
    if (y == NULL)y = "0";
    const char *z = strtok(NULL, delimiter);
    if (z == NULL)z = "0";

    vVector.x = strtof(x, NULL);
    vVector.y = strtof(y, NULL);
    vVector.z = strtof(z, NULL);
    return vVector;
}

iVector getIVectorFromSubstring(char *substr, const char* delimiter){
    iVector vVector;
    
    const char *x = strtok(substr, delimiter);
    if (x == NULL)x = "0";
    const char *y = strtok(NULL, delimiter);
    if (y == NULL)y = "0";
    const char *z = strtok(NULL, delimiter);
    if (z == NULL)z = "0";
    
    printf("%s %s %s\n", x,y,z);
    
    vVector.x = (int)strtol(x, NULL, 10);
    vVector.y = (int)strtol(y, NULL, 10);
    vVector.z = (int)strtol(z, NULL, 10);
    
    return vVector;
}

ObjModelLoader::ObjModelLoader(const char* objFileName) {
    
    CFStringRef name;
    CFMutableStringRef filePath;
    CFURLRef url;
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    
    // Get the URL to the bundle resource.
    name = CFStringCreateWithCString (NULL, objFileName, kCFStringEncodingUTF8);
    url = CFBundleCopyResourceURL(mainBundle, name, CFSTR("obj"), NULL);
    filePath = CFStringCreateMutableCopy(NULL, INT16_MAX, CFURLGetString(url));
    CFStringReplace(filePath, CFRangeMake(0, 7), CFSTR(""));
    char str[INT16_MAX];
    CFStringGetCString(filePath, str, INT16_MAX, kCFStringEncodingASCII);
    
    char *buffer = 0;
    
    FILE *curFile = fopen(str, "r");
    
    if (curFile){
        fseek(curFile, 0, SEEK_END);
        size_t fileSize = ftell(curFile);
        buffer = (char*)malloc(fileSize);
        fseek(curFile, 0, SEEK_SET);
        fread(buffer, 1, fileSize, curFile);
        
        int vertexCount = 0;
        int elementCount = 0;
        int normalCount = 0;
        int textureCount = 0;
        
        int hasPositions = 0;
        int hasNormals = 0;
        int hasTextures = 0;
        
        for (int i = 0; i < fileSize-1; i++){
            char c = buffer[i];
            char cc = buffer[i+1];
            if (c == 'v' && cc == ' '){
                printf("%c\n", c);
                vertexCount++;
                hasPositions = 1;
            }
            
            if (c == 'v' && cc == 'n'){
                printf("%c%c\n", c, cc);
                normalCount++;
                hasNormals = 1;
            }
            
            if (c == 'v' && cc == 't'){
                printf("%c%cc\n", c, cc);
                textureCount++;
                hasTextures = 1;
            }
            
            if (c == 'f' && cc == ' '){
                printf("%c\n", c);
                elementCount+=3; // each face has 3 vertices
            }
        }
        
        mPositions = (GLfloat*)malloc((sizeof(GL_FLOAT) * 3) * vertexCount);
        mNormals = (GLfloat*)malloc((sizeof(GL_FLOAT) * 3) * vertexCount);
        mElements = (GLuint*)malloc(sizeof(GLuint) * elementCount);
        float faceNormals[normalCount * 3];
        int vIndex = 0;
        int nIndex = 0;
        int eIndex = 0;
        
        for (int i = 0; i < fileSize; i++){
            char c = buffer[i];
            char cc = buffer[i+1];
            if (c == 'v' && cc == ' '){
                char *substr = getSubstringUpToDelimiter(i+2, buffer, 10);
                vector vVector = getVectorFromSubstring(substr, " ");
                mPositions[vIndex] = vVector.x;
                vIndex++;
                mPositions[vIndex] = vVector.y;
                vIndex++;
                mPositions[vIndex] = vVector.z;
                vIndex++;
                free(substr);
            }
            
            if (c == 'v' && cc == 'n'){
                char *substr = getSubstringUpToDelimiter(i+2, buffer, 10);
                vector vVector = getVectorFromSubstring(substr, " ");
                faceNormals[nIndex] = vVector.x;
                nIndex++;
                faceNormals[nIndex] = vVector.y;
                nIndex++;
                faceNormals[nIndex] = vVector.z;
                nIndex++;
                free(substr);
            }
            
            if (c == 'f' && cc == ' '){
                char *substr = getSubstringUpToDelimiter(i+2, buffer, 10);
                printf("%s\n", substr);
                
                element eElement;
                
                char *xStr = strtok(substr, " ");
                char *yStr = strtok(NULL, " ");
                char *zStr = strtok(NULL, " ");
                
                eElement.xVec = getIVectorFromSubstring(xStr, "/");
                eElement.yVec = getIVectorFromSubstring(yStr, "/");
                eElement.zVec = getIVectorFromSubstring(zStr, "/");
                
                mElements[eIndex] = eElement.xVec.x;
                eIndex++;
                mElements[eIndex] = eElement.yVec.x;
                eIndex++;
                mElements[eIndex] = eElement.zVec.x;
                eIndex++;
                
                free(substr);
            }
        }
        
//        if (hasNormals){
//            for (int i = 0; i < vertexCount * 3; i+=3){
//                if (!hasTextures){
//                    mNormals[i] = eElement.xVec.y;
//                    mNormals[i + 1] = eElement.yVec.y;
//                    mNormals[i + 2] = eElement.zVec.y;
//                } else {
//                    mNormals[i] = eElement.xVec.z;
//                    mNormals[i + 1] = eElement.yVec.z;
//                    mNormals[i + 2] = eElement.zVec.z;
//                }
//            }
//        }
        
        printf("vertices: %i\nnormals:%i\nelements:%i\n", vertexCount, normalCount, elementCount);
        
        for (int i = 0; i < vertexCount * 3; i+=3){
            printf("%f %f %f\n", mPositions[i], mPositions[i + 1], mPositions[i + 2]);
            printf("%f %f %f\n", mNormals[i], mNormals[i + 1], mNormals[i + 2]);
        }
        for (int i = 0; i < normalCount * 3; i++){
            printf("%f\n", faceNormals[i]);
        }
        
        for (int i = 0; i < elementCount; i++){
            printf("%i\n", mElements[i]);
        }
        
    } else {
        printf("NO FILE!!!!\n");
    }
    
    CFRelease(mainBundle);
    CFRelease(filePath);
    CFRelease(url);
    CFRelease(name);
}


