/*
 * fileoperations.c
 * Copyright (C) 2015 Prashant A <prashant.barca@gmail.com> 2015-09-23
 *
 * Distributed under terms of the MIT license.
 */

void fileappend(char *caption,int i)
{
    FILE *fp;
    char htmlcontent[200];
    char command[200];
    sprintf(htmlcontent,"<a href=\"medium%d.jpg\" target=\"_blank\"><img src=\"thumbnail%d.jpg\"/></a><br/><br/><p>%s</p><hr></hr>",i,i,caption);
    strncpy(command,"index.html",20);
    fp=fopen(command,"a");
    fprintf(fp,"%s",htmlcontent);
    fclose(fp);
}
void filewrite()
{
    FILE *fp;
    char command[200];
    strncpy(command,"index.html",20);
    fp=fopen(command,"w");
    fprintf(fp,"%s","");
    fclose(fp);
}
