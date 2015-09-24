/*
 * main.c
 * Copyright (C) 2015 Prashant A <prashant.barca@gmail.com> 2015-09-21
 *
 * Distributed under terms of the MIT license.
 */

#include "header.h"
#include "fileoperations.c"
#include "conversions.c"
int main(int argc, char *argv[])
{
    int i,r;
    int choice;
    char caption[200];
    char angle[20];
    /*
     * The below code is to make sure that the correct number of arguments are passed. 
     *
     */
    if( argc <= 2 )
    {
        printf("Usage Example: ./main photos/*.jpg \n");
        exit(42);
    }

    /*
     * Conversion operations for first alone, so that it is immediately available
     */

    convert(argv[1],"thumbnail",1);
    convert(argv[1],"medium",1);

    /*
     * The below child process erases the existing file
     *
     */

    r = fork();
    if(r==0)
    {
        filewrite();
        exit(21);
    }
    /*
     * The below child process is to convert all the images ranging from 2 to n, to medium and thumbnails
     *
     */
    r = fork();
    if(r==0)
    {
        for(i=2;i<argc;i++)
        {
            convert(argv[i],"thumbnail",i);
            convert(argv[i],"medium",i);
        }
        exit(21);
    }
    /*
     *
     * The real deal begins here. 
     * For loop does the following
     * - Display the image in a child process
     * - Ask the user for angle rotation and the caption to be entered
     * - Rotate and enter the caption into an html file using two different child processes to enable concurrency. 
     */
    for(i=1;i<argc;i++)
    {
        r= fork();
        if(r==0)
        {
            display(i);
            exit(21);
        }
gotolabel:
        printf("\nEnter 1. 90 Degrees clockwise, \n2. 180 Degrees, \n3. 270 Degrees clockwise\n4. Leave it.\nIn the next line enter a caption for the image : ");
        scanf("%d %200[0-9a-zA-Z ]",&choice,caption);
        switch(choice)
        {
            case 1: 
                strcpy(angle,"90");
                break;
            case 2:
                strcpy(angle,"180");
                break;
            case 3:
                strcpy(angle,"270");
                break;
            case 4:
                strcpy(angle,"0");
                break;
            default:
                printf("Wrong input");
                goto gotolabel;
        }
        /*
         * Child process to rotate the image based on the angle entered. 
         */
        r = fork();
        if(r==0)
        {
            rotate(i,angle);
            exit(21);
        }
        /*
         * File Write operation is going to happen in the child process below. 
         */
        r = fork();
        if(r==0)
        {
            fileappend(caption,i);
            exit(21);
        }
    }
    return 0;
}
