//
//  ObjModelLoader.cpp
//  SimpleParticleSystem
//
//  Created by James Milton on 11/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "ObjModelLoader.h"
#include <CoreFoundation/CoreFoundation.h>

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
        printf("%i is file size\n", fileSize);
        buffer = (char*)malloc(fileSize);
        fseek(curFile, 0, SEEK_SET);
        fread(buffer, 1, fileSize, curFile);
        for (int i = 0; i < fileSize; i++){
            printf("%c\n", buffer[i]);
        }
    } else {
        printf("NO FILE!!!!\n");
    }
    
    
    CFRelease(name);
}