#pragma once

void AddNode(char*** begin, char*** end, const char* str);//&
void DeleteElements(char** node);

void StringListRemove(char*** begin, char*** end, const char* str);
size_t StringListSize(char** begin);

void StringListRemoveDuplicates(char*** begin, char*** end);
void StringListReplaceInStrings(char** head, char* before, char* after);

void Swap(char** left, char** right);
void StringListSort(char*** list);//buble sort

void PrintList(char** begin, char** end);
int StringListIndexOf(char** begin, const char* str);
void StringListDestroy(char*** begin, char*** end);
