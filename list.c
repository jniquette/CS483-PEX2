#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Linked List Implementation
 * Author: C2C Justin Niquette
 * Course: CS483, USAF Academy
 * Date: 22 January 2015
 * Github: https://github.com/jniquette/CS483-PEX1
 * Documentation: No help received
 */


node* list_insert_tail(node* list, char* string)
{
  //Recursive Method - first see if the list is empty
  if(list == NULL){
    struct s_node *list = malloc(sizeof(struct s_node));
    (*list).data = malloc(((strlen(string) + 1) * sizeof(char)));
    strcpy((*list).data, string);
    return list;    
  }
  
  //If we're the last node in the list, add a node to next
  if((*list).next == NULL){
    struct s_node *newNode = malloc(sizeof(struct s_node));
    (*list).next = newNode;
    (*newNode).data = malloc(((strlen(string) + 1) * sizeof(char)));
    strcpy((*newNode).data, string);
    return list;
  }

  //Otherwise, look further down the list for the end
  (*list).next = list_insert_tail((*list).next, string);
  return list;
	
}

node* list_insert_head(node* list, char* string)
{
  //Create a new node to put the new string in
  struct s_node *newNode = malloc(sizeof(struct s_node));
  (*newNode).next = list;
  (*newNode).data = malloc(((strlen(string) + 1) * sizeof(char)));
  strcpy((*newNode).data, string);
  return newNode;
}

node* list_insertn(node* list, char* string, int n)
{
  //Since the head is at position 1, see if we're there and then insert it
  //Let's make it work on 0 also, since that makes sense too.
  if(n <= 1){ 
    struct s_node *newNode = malloc(sizeof(struct s_node));//Create a new node to put the new string in
    (*newNode).next = list; //Put that old next node after the new node
    (*newNode).data = malloc(((strlen(string) + 1) * sizeof(char)));
    strcpy((*newNode).data, string);
    return newNode;
  }

  //Additionally, let's save the user if they specify a higher position than the current size
  if((*list).next == NULL){
    printf("[Notice]\tInsertation point exceeds size of list, \"%s\" placed at end of list.\n", string);
    (*list).next = list_insert_tail(NULL, string);
    return list;
  }

  //Otherwise keep looking until we get to position 1
  (*list).next = list_insertn((*list).next, string, n-1);
  return list;

}

node* list_remove(node* list, char* string)
{
  //Only work if we aren't dealing with an empty array
  if(list != NULL){
    //Is the data in this node?
    if((*list).data == string){
      //Free what we have, and then point to the next node
      node *newNextNode = (*list).next;
      free((*list).data);
      free(list);
      return newNextNode;
    }

    //Not found, keep searching
    else{
      (*list).next = list_remove((*list).next, string);
      return list;
    }
  }

  else{
    printf("\"%s\" not found in the list", string);
    return NULL;
  }
}

node* list_removen(node* list, int n)
{
  //Since the head is at position 1, see if we're there and then remove it
  //Let's make it work on 0 also, since that makes sense too.
  if(n <= 1){ 
    node *newHead = (*list).next; //Move the old next to a temp pointer
    free((*list).data);
    free(list);
    return newHead;
  }

  //Additionally, let's save the user if they specify a higher position than the current size
  if((*list).next == NULL){
    printf("[Notice]\tRemoval point exceeds size of list, nothing was removed.\n");
    return list;
  }

  //Otherwise keep looking until we get to position 1
  (*list).next = list_removen((*list).next, n-1);
  return list;

}

void list_print(node* list)
{
  //This Subroutine is recursive, prints a node then calls itself until a null node is reached
  if(list != NULL){
    printf("%s\n", (*list).data);

    if((*list).next != NULL)
      list_print((*list).next);
  }

  //If initial call is to empty list
  else
    printf("[Notice]\tEmpty List\n");
}

void list_printn(node* list, int n)
{
  //Is the list not empty
  if(list != NULL){
    if(n <= 1)
      printf("%s\n", (*list).data);
    else
      list_printn((*list).next, n-1);
  }
  else{
    printf("[Notice]\tSearch point exceeds size of list.\n");  
  }
}

char* list_get(node* list, int n)
{
  //Is the list not empty
  if(list != NULL){
    if(n <= 1)
      return (*list).data;
    else
      return list_get((*list).next, n-1);
  }
  else{
    printf("[Notice]\tSearch point exceeds size of list.\n");  
    return NULL;
  }
}

void list_destroy(node* list)
{
  //Destroy one node at a time
  while(list != NULL){
    node *nextNode = (*list).next;
    free((*list).data);
    free(list);
    list = nextNode;
  }
}
