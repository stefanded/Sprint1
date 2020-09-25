#pragma once
#include<stdlib.h>
#include <string.h>
#include <stdio.h>
#include"List.h"

enum { prev, next};
void AddNode(char*** begin, char*** end, const char* str)//&
{
    if (begin == NULL || end == NULL)return;
    char** node = (char**)malloc(2 * sizeof(char*));
    size_t length = (strlen(str)) + next;

    node[prev] = (char*)malloc((length) * sizeof(char));
    strcpy(node[prev], str);
    node[next] = NULL;

    if (*begin == NULL) {
        *begin = node;
        (*end) = node;
    }

    else
    {
        char** temp_node = *end;
        (*end) = node;
        temp_node[next] = (char*)(*end);
    }
}
void DeleteElements(char** node)
{
    free(node[prev]); //
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
        if (!strcmp(node[prev], str))
        {
            if (*end == node)//if deleted element is end ,end elements is previous 
            {
                *end = prev_node;
            }
            if (prev_node != NULL) {//if previos not end,then he is next
                prev_node[next] = node[next];

            }
            else
            {
                (*begin) = (char**)node[next];///if previos is begin,then begin is next
                prev_node = *begin;

            }

            DeleteElements(node);
            node = (prev_node == NULL) ? NULL : (char**)prev_node[next];
            continue;
        }
        prev_node = node;
        node = (char**)node[next];

    }
}
size_t StringListSize(char** begin)
{
    size_t size = 0;
    char** node = begin;

    while (node != NULL) {
        size++;
        node = (char**)node[next];

    }
    return size;
}
void StringListRemoveDuplicates(char*** begin, char*** end)
{
    if (begin == NULL || end == NULL)return;

    if (*end == NULL) { return; }

    char** node = *begin;
    while (node[next] != NULL)
    {
        char** node_next = (char**)node[next];
        if (!strcmp(node[prev], node_next[prev])) {
            node[next] = node_next[next];
            DeleteElements(node_next);
        }
        else {
            StringListRemove(&node_next, end, node[prev]);
            node = (char**)node[next];

        }


    }
}
void StringListReplaceInStrings(char** head, char* before, char* after)
{

    for (char** list = head; list != NULL; list = (char**)list[next])
    {

        if (!strcmp(list[prev], before)) {

            free(list[prev]);
            list[prev] = (char*)malloc((strlen(after) + next) * sizeof(char));
            strcpy(list[prev], after);
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
    char** ptrnext;
    char** lptr = NULL;

    /* Checking for empty list */
    if (list == NULL)
        return;
    do
    {
        swapped = prev;
        ptrnext = *list;

        while (ptrnext[next] != (char*)lptr)
        {
            char** next_ = (char**)ptrnext[next];
            if (strcmp(ptrnext[prev], next_[prev]) > prev)
            {
                Swap(&ptrnext[prev], &next_[prev]);
                swapped = 1;
            }
            ptrnext = next_;
        }
        lptr = ptrnext;
    } while (swapped);
}
void PrintList(char** begin, char** end)
{
    char** node = begin;
    printf("[");
    while (node != NULL) {
        if (node[next] != NULL) {
            printf("%s,", node[prev]);
        }
        else {
            printf("%s", node[prev]);
        }
        node = (char**)node[next];
    }
    printf("]\nlist size= %d\n", StringListSize(begin));

}
int StringListIndexOf(char** begin, const char* str)
{
    int res = 0;

    char** node = begin;
    while (node != NULL) {
        if (!strcmp(node[prev], str))
        {
            return res;
        }
        res++;
        node = (char**)node[next];

    }
    return -1;
}
void StringListDestroy(char*** begin, char*** end)
{
    if (begin == NULL || end == NULL)return;
    char** node = *begin;
    while (node != NULL)
    {
        node = (char**)node[next];
        free((*begin)[prev]);
        free(*begin);
        *begin = node;
    }
    *begin= NULL;
    *end = NULL;
}

//'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead.
// The potential null pointer is passed into 'strcpy' function. Inspect the first argument. Check lines: 15.
// Line 32. Possible memory leak if we have more than two elements in the list. Need to verify number of elements in the list.   
