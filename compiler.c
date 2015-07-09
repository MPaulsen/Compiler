#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "parser.c"

void ParseLex();
void CleanArray();

int main() 
{
  parse();
  vector aryLexList = GetLexList();
  
  ParseLex();
  return 0;
}

void ParseLex()
{
  int token, i;
  int c = 0;
  char input[12];
  char prev[12];
  int conditional = 0;
  int openParen = 0;
  
  CleanArray(prev, 12);
  CleanArray(input, 12);
  
  for(i = 0; i < aryLexList.size; i++)
  {
    
    if (aryLexList.data[i] != ' ')
    {
      input[c] = aryLexList.data[i];
      c++;
    }
    else
    {
      // Here, input holds the individual token it's currently parsing, and prev holds the previous.

      
      if (strcmp(input, "23") == 0) // If token found
        conditional = 1;
      
      if (strcmp(input, "24") == 0) //Then found
        conditional = 0;
      
      if (strcmp(input, "15") == 0)
        openParen++;
      
      if (strcmp(input, "16") == 0)
        openParen--;
      
      if (strcmp(prev, "28") == 0 || strcmp(prev, "29") == 0 || strcmp(prev, "30") == 0)
        if (strcmp(input, "2") != 0)
          printf("Error 04: const, var, and procedure must be followed by identifier.");
      
      if (strcmp(prev, "9") == 0) // Last symbol was =; Catching error 02
      {
        if (strcmp(input, "2") != 0 && strcmp(input, "3") != 0) // Current symbol is indentifier or number
          printf("Error 02: = must be followed by a number.");
      }
      
      if (strcmp(input, "9") == 0 && conditional == 0) //Catching Error 01
        printf("Error 01: = used instead of =:\n"); //don't actually print error, just keep track of which error we got, possibly return as int?
      
      printf("%s  ", input);
      c = 0;
      CleanArray(prev, 12);
      strcpy(prev, input);
      CleanArray(input, 12);
      
    }
    
  }
  
  printf("\n");
  if (openParen > 0)
    printf("Error 22: Right parenthesis missing.");
  
}

void CleanArray(char* input, int size)
{
  int i;
  
  for (i = 0; i < size; i++)
  {
    input[i] = '\0';
  }
}