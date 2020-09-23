#pragma once

void AddNode(char*** begin, char*** end, const char* str);//&
void DeleteElements(char** node);

void StringListRemove(char*** begin, char*** end, const char* str);
size_t StringListSize(char** begin);

void StringListRemoveDuplicates(char*** begin, char*** end);
void StringListReplaceInStrings(char** head, char* before, char* after);

void Swap(char** left, char** right);
void StringListSort(char*** list);//buble sort
//{
//
//    int swapped;
//    char** ptr1;
//    char** lptr = NULL;
//
//    /* Checking for empty list */
//    if (list == NULL)
//        return;
//    do
//    {
//        swapped = 0;
//        ptr1 = *list;
//
//        while (ptr1[1] != (char*)lptr)
//        {
//            char** next = (char**)ptr1[1];
//            if (strcmp(ptr1[0], next[0]) > 0)
//            {
//                swap(&ptr1[0], &next[0]);
//                swapped = 1;
//            }
//            ptr1 = next;
//        }
//        lptr = ptr1;
//    } while (swapped);
//}

void PrintList(char** begin, char** end);
int StringListIndexOf(char** begin, const char* str);
void StringListDestroy(char*** begin, char*** end);
