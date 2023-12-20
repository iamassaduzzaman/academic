#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// for every folder
typedef struct Directory
{
  int directory_no;
  char directory_name[10];
  int creating_date;
  int creating_time;
  FILE *fp;
  struct Directory *child;
} node;

node *folder_list[11][11];
int is_visited[11];

// dfs (depth first search) for searching which folder parent which one
void dfs(int i)
{
  is_visited[i] = 1;
  for (int j = 1; j <= 10; ++j)
  {
    if (folder_list[i][j] != NULL && !is_visited[j])
    {
      printf("Parent_folder %d: child_folder %d\n", i, j);
      dfs(j);
    }
  }
}

// create new directories
node *create_new_directories(int dir_no, char dir_name[], int _time, int _date)
{
  node *new_dir = (node *)malloc(sizeof(node));
  new_dir->directory_no = dir_no;
  strcpy(new_dir->directory_name, dir_name);
  new_dir->creating_time = _time;
  new_dir->creating_date = _date;
  new_dir->child = NULL;
  return new_dir;
}

// add new directory
void add_new_directory(int parent_folder, int child_folder, node *child_f)
{
  folder_list[parent_folder][child_folder] = child_f; // since it is a directed path
}

// deleting directories
void delete_directories(int parent, int child, node *folder)
{
  folder_list[parent][child] = NULL;
  free(folder);
}

// renaming a directoris
void renaming(node *folder)
{
  strcpy(folder->directory_name, "new_name");
}

// writing content in file with in a folder
void write_contents(node *folder)
{
  char ch;
  folder->fp = fopen("hello.txt", "w");
  printf("Enter data: ");
  while ((ch = getchar()) != '1') // to end the writing in file type 1
  {
    putc(ch, folder->fp);
  }
  fclose(folder->fp);
}

// reding content from a file with in folder
void reading_content(node *folder)
{
  FILE *fp = NULL;
  char ch;
  folder->fp = fopen("hello.txt", "r");
  while (!feof(folder->fp))
  {
    ch = fgetc(folder->fp);
    printf("%c", ch);
  }

  fclose(folder->fp);
}

// set every folder to NULL
void setup()
{
  for (int i = 1; i <= 10; ++i)
  {
    for (int j = 1; j <= 10; ++j)
    {
      folder_list[i][j] = NULL;
    }
  }
}

int main()
{
  setup();

  // creating new folder
  node *root_one = create_new_directories(1, "F_1", 9, 20);
  node *folder_two = create_new_directories(2, "F_2", 10, 20);
  node *folder_three = create_new_directories(3, "F_3", 11, 20);
  node *folder_four = create_new_directories(4, "F_4", 12, 20);

  // connecting folder with its parent folder
  add_new_directory(1, 2, folder_two);
  add_new_directory(1, 3, folder_three);
  add_new_directory(2, 4, folder_four);

  // deleting directoris
  delete_directories(2, 4, folder_four);

  // renaming directoris
  renaming(folder_two);

  // check whether every folder is conencted with it's parent folder
  dfs(1);

  // writing content in file with in a folder
  write_contents(folder_three);

  // reding content from a file with in folder
  reading_content(folder_three);

  return 0;
}