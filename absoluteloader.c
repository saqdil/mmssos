#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
  char name[20], name1[20], staddr[50], line[50];
  int i, j, straddr1;
  printf("enter program name\n");
  scanf("%s", name);

  FILE *f1;
  f1 = fopen("RLIN3.txt", "r");

  fscanf(f1, "%s", line);

  for (i = 2, j = 0; i < 8 && j < 6; i++, j++)
  {
    name1[j] = line[i];
  }
  name1[j] = '\0';

  printf("Program name from object file: %s\n", name1);

  if (strcmp(name, name1) == 0)
  {
    while (fscanf(f1, "%s", line) != EOF)
    {
      if (line[0] == 'T')
      {
        for (i = 2, j = 0; i < 8 && j < 6; i++, j++)
        {
          staddr[j] = line[i];
        }
        staddr[j] = '\0';

        straddr1 = strtol(staddr, NULL, 16);

        i = 12;
        while (line[i] != '$' && line[i] != '\0')
        {
          if (line[i] != '^')
          {
            printf("00%04X\t%c%c\n", straddr1, line[i], line[i + 1]);
            straddr1++;
            i += 2;
          }
          else
          {
            i++;
          }
        }
      }
      else if (line[0] == 'E')
      {
        printf("\nEND OF THE PROGRAM");
        break;
      }
    }
  }
  else
  {
    printf("program name does not match\n");
  }
  fclose(f1);
}