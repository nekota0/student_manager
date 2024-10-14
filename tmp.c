#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Student struct Stud

void add(FILE *fp);
void modify(FILE *fp);
FILE *del(FILE *fp);
void show(FILE *fp);
void individual(FILE *fp);


struct Stud {
  char name[100];
  int age;
  float gpa;
  char dept[100];
};


int main() {
  FILE *fp;
  int option;
 
  if((fp=fopen("db.txt","rb+"))==NULL)
    {
      if((fp=fopen("db.txt","wb+"))==NULL)
    {
      printf("Can't create or open Database.");  
      return 0;
    }
  }

  while(1) {
    printf("\n\n\t\t\t\t1. Add Student");
    printf("\n\n\t\t\t\t2. Modify Student");
    printf("\n\n\t\t\t\t3. Show All Student");
    printf("\n\n\t\t\t\t4. Individual View");
    printf("\n\n\t\t\t\t5. Remove Student");
    printf("\n\n\t\t\t\t0. Exit Program");
    printf("\n\n\t\t\t\tEnter your option : ");
    scanf("%d", &option);

    switch(option) {
      case 1:
        add(fp);
        break;
      case 2:
        modify(fp);
        break;
      case 3:
        show(fp);
        break;
      case 4:
        individual(fp);
        break;
      case 5:
        del(fp);
        break;
      case 0:
        fclose(fp);
        return 0;
      default:
        continue;
    }
  }
  return 0;
}


void add(FILE *fp) {
  Student s;

  
  printf("\n\n\t\tEnter Full name of Student : ");
  fflush(stdin);
  fgets(s.name, sizeof(s.name), stdin);
  s.name[strlen(s.name)-1]='\0';

  printf("\n\n\t\tEnter DEPT of Student : ");
  fflush(stdin);
  fgets(s.dept, sizeof(s.dept), stdin);
  s.dept[strlen(s.dept)-1]='\0';

  printf("\n\n\t\tEnter age of Student : ");
  scanf("%d", &s.age);

  printf("\n\n\t\tEnter GPA of Student : ");
  scanf("%f", &s.gpa);


  fwrite(&s, sizeof(s), 1, fp);

  return;
}


FILE *del(FILE *fp) {
  Student s;
  char name[100];
  int siz=sizeof(s),flag=0;
  FILE *ft;

  rewind(fp);


  if((ft=fopen("tmp.txt","wb+"))==NULL) {    
    printf("Cannot create the file!");
    return fp;
  }

  printf("Enter Student's name to delete : ");
  fflush(stdin);
  fgets(name,sizeof(name),stdin);
  name[strlen(name)-1]='\0';

  while((fread(&s,siz,1,fp))==1) {
    if ((strcmp(s.name,name))==0) {
      flag=1;
      continue;
    }
    fwrite(&s,siz,1,ft);
  }

  fclose(fp);
  fclose(ft);

  remove("db.txt");
  rename("tmp.txt","db.txt");

  if ((fp=fopen("db.txt","rb+"))==NULL) {
    printf("fatal error occured");
    return NULL;
  }

  if (flag==0) {
    printf("fatal error occurred");
  }

  return fp;
}


void modify(FILE *fp) {

  Student s;
  char name[100];
  int complete_flag = 0;
  int siz=sizeof(s);

  rewind(fp);

  printf("Enter Student's name to modify : ");
  fflush(stdin);
  fgets(name, sizeof(name), stdin);
  name[strlen(name)-1]='\0';

  while((fread(&s,siz,1,fp))==1) {
    if ((strcmp(s.name,name))==0) {
      complete_flag = 1;
      break;
    }
  }

  if (complete_flag==1) {

    fseek(fp,-siz,SEEK_CUR);

    printf("--------------------------------------------");
    printf("\nrecord found");
    printf("\n\t\tname : %s", s.name);
    printf("\n\t\tdept : %s", s.dept);
    printf("\n\t\tage : %d", s.age);
    printf("\n\t\tGPA : %f", s.gpa);
    printf("\n--------------------------------------------");
  
    printf("\n\t\t\t\tEnter name of Student : ");
    fflush(stdin);
    fgets(s.name,sizeof(s.name),stdin);
    s.name[strlen(s.name)-1]='\0';
    printf("\n\t\t\t\tEnter dept of Student : ");
    fflush(stdin);
    fgets(s.dept,sizeof(s.dept),stdin);
    s.dept[strlen(s.dept)-1]='\0';
    printf("\n\t\t\t\tEnter age of Student : ");
    scanf("%d", &s.age);
    printf("\n\t\t\t\tEnter GPA of Student : ");
    scanf("%f", &s.gpa);
  
    fwrite(&s,sizeof(s),1,fp);
  } else {
    printf("Error");
  }

  return;
}


void show(FILE *fp) {
  Student s;
  int siz=sizeof(s);

  rewind(fp);

  while((fread(&s,siz,1,fp))==1) {
    printf("\n\n\tStudent--------------");
    printf("\n\n\t\tname : %s",s.name);
    printf("\n\t\tdept : %s",s.dept);
    printf("\n\t\tage : %d", s.age);
    printf("\n\t\tGPA : %f", s.gpa);
    printf("\n\n\t---------------------");
  }

  return;
}


void individual(FILE *fp) {
  Student s;
  char name[100];
  int siz=sizeof(s),flag=0;
  
  printf("Enter Student's name to check : ");
  fflush(stdin);
  fgets(name,sizeof(name),stdin);
  name[strlen(name)-1]='\0';

  rewind(fp);

  while((fread(&s,siz,1,fp))==1) {
    if ((strcmp(s.name,name))==0) {
      flag = 1;
      printf("%s | %s | %d | %f", s.name, s.dept, s.age, s.gpa);
      break;
    }
  }

  if (flag==0) {
    printf("cannot find the student");
  }

  return;
}
