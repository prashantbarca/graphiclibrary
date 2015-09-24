/*
 * conversions.c
 * Copyright (C) 2015 Prashant A <prashant.barca@gmail.com> 2015-09-23
 *
 * Distributed under terms of the MIT license.
 */

/*
 * This function is to display the thumbnail
 */

void display(int i)
{

    char command[100];
    sprintf(command,"thumbnail%d.jpg",i);
    execl("/usr/bin/display","display","-backdrop",command,NULL);
}
/* 
 * This function is to rotate the image image number and angle given as puts. 
 *
 */
void rotate(int x,char *angle)
{
    int i,r,r1;
    char newfile[100];
    char currentfile[100];
    int status;
    r = fork();
    if(r==0)
    {
        sprintf(newfile,"medium%d.jpg",x);
        printf("%d",execl("/usr/bin/convert","convert",newfile,"-rotate",angle,newfile,NULL));
        exit(21);
    }
    r1 = fork();
    if(r1==0)
    {
        sprintf(newfile,"thumbnail%d.jpg",x);
        printf("%d",execl("/usr/bin/convert","convert",newfile,"-rotate",angle,newfile,NULL));
        exit(21);
    }
    //Making sure the two 
    waitpid(r,&status,1);
    waitpid(r1,&status,1);
}
/*
 * The below function is to convert an image to thumbnail and medium formats
 */
void convert(char *filename,char *flag,int x)
{
    int i,r;
    char newfile[100];
    int status;
    r = fork();
    if(r==0)
    {
        if(strcmp(flag,"medium")==0)
        {
            sprintf(newfile,"medium%d.jpg",x);
            execl("/usr/bin/convert","convert",filename,"-resize","25%",newfile,NULL);
            exit(21);
        }
        else if(strcmp(flag,"thumbnail")==0)
        {
            sprintf(newfile,"thumbnail%d.jpg",x);
            execl("/usr/bin/convert","convert",filename,"-resize","10%",newfile,NULL);
            exit(21);
        }
    }
    waitpid(r,&status,NULL);
}
