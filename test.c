
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct infostu
{
	char no[20];				//学号
	char name[20];
	char sex[7];
	int age;
	char major[20];				//专业班级
};
int main()
{
	int i=0,j;
	char c[1024];
	struct infostu student[500];
	FILE *fp;
	if((fp=fopen("./student.txt","r"))==NULL)			// 打开文件并且让fp指向 文件
	{
		printf("Can not open file\n");
		exit(1);
	}

	fscanf(fp,"%[^\n]", c);
	while(!feof(fp))                     //读取一组数据后指针指向下一组数据，并且判断是否指向最后一行
	{
		fscanf(fp,"%[^ ] %[^ ] %[^ ] %d %s ",&student[i].no,&student[i].name,&student[i].sex,&student[i].age,&student[i].major);
		i++;
	}             //%[^,]  字符串以，为结束标志
	j=i;
	printf("j = %d.", j);
	printf("file contains:\n");
	for(i=0;i<j;i++)
		printf("%s,%s,%s,%d,%s\n",student[i].no,student[i].name,student[i].sex,student[i].age,student[i].major);
	fclose(fp);				//关闭文件；
	return 0;
}
