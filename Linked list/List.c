#pragma once
#include<stdlib.h>
#include <string.h>
#include <stdio.h>

#include"List.h"
void AddNode(char*** begin, char*** end, const char* str)//&
{
    if (begin == NULL || end == NULL)return;
    char** node = (char**)malloc(2 * sizeof(char*));
    size_t length = (strlen(str)) + 1;

    node[0] = (char*)malloc((length) * sizeof(char));
    strcpy(node[0], str);
    node[1] = NULL;

    if (*begin == NULL) {
        *begin = node;
        (*end) = node;
    }

    else
    {
        char** temp_node = *end;
        (*end) = node;
        temp_node[1] = (char*)(*end);
    }
}
void DeleteElements(char** node)
{
    free(node[0]);
    free(node);
    node = NULL;
}
void StringListRemove(char*** begin, char*** end, const char* str)
{
    if (begin == NULL || end == NULL)return;
    char** node = *begin;
    char** prev_node = NULL;
    if (*end == NULL || *begin == NULL) { return; }
    while (node != NULL)
    {
        if (!strcmp(node[0], str))
        {
            if (*end == node)//if deleted element is end ,end elements is previous 
            {
                *end = prev_node;
            }
            if (prev_node != NULL) {//if previos not end,then he is next
                prev_node[1] = node[1];

            }
            else
            {
                (*begin) = (char**)node[1];///if previos is begin,then begin is next
                prev_node = *begin;

            }

            DeleteElements(node);
            node = (prev_node == NULL) ? NULL : (char**)prev_node[1];
            continue;
        }
        prev_node = node;
        node = (char**)node[1];

    }
}
size_t StringListSize(char** begin)
{
    size_t size = 0;
    char** node = begin;

    while (node != NULL) {
        size++;
        node = (char**)node[1];

    }
    return size;
}
void StringListRemoveDuplicates(char*** begin, char*** end)
{
    if (begin == NULL || end == NULL)return;

    if (*end == NULL) { return; }

    char** node = *begin;
    while (node[1] != NULL)
    {
        char** node_next = (char**)node[1];
        if (!strcmp(node[0], node_next[0])) {
            node[1] = node_next[1];
            DeleteElements(node_next);
        }
        else {
            StringListRemove(&node_next, end, node[0]);
            node = (char**)node[1];

        }


    }
}
void StringListReplaceInStrings(char** head, char* before, char* after)
{

    for (char** list = head; list != NULL; list = (char**)list[1])
    {

        if (!strcmp(list[0], before)) {

            free(list[0]);
            list[0] = (char*)malloc((strlen(after) + 1) * sizeof(char));
            strcpy(list[0], after);
        }

    }
}

void Swap(char** left, char** right)
{
    char* node = *right;
    *right = *left;
    *left = node;
}

void StringListSort(char*** list)//buble sort
{

    int swapped;
    char** ptr1;
    char** lptr = NULL;

    /* Checking for empty list */
    if (list == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = *list;

        while (ptr1[1] != (char*)lptr)
        {
            char** next = (char**)ptr1[1];
            if (strcmp(ptr1[0], next[0]) > 0)
            {
                Swap(&ptr1[0], &next[0]);
                swapped = 1;
            }
            ptr1 = next;
        }
        lptr = ptr1;
    } while (swapped);
}
void PrintList(char** begin, char** end)
{
    char** node = begin;
    printf("[");
    while (node != NULL) {
        if (node[1] != NULL) {
            printf("%s,", node[0]);
        }
        else {
            printf("%s", node[0]);
        }
        node = (char**)node[1];
    }
    printf("]\nlist size= %d\n", StringListSize(begin));

}
int StringListIndexOf(char** begin, const char* str)
{
    int res = 0;

    char** node = begin;
    while (node != NULL) {
        if (!strcmp(node[0], str))
        {
            return res;
        }
        res++;
        node = (char**)node[1];

    }
    return -1;
}
void StringListDestroy(char*** begin, char*** end)
{
    if (begin == NULL || end == NULL)return;
    char** node = *begin;
    while (node != NULL)
    {
        node = (char**)node[1];
        free((*begin)[0]);
        free(*begin);
        *begin = node;
    }
    *end = NULL;
}