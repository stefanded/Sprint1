#pragma once
#include"List.h"
void test_add(char*** begin, char*** end)
{
    AddNode(begin, end, "c");
    AddNode(begin, end, "b");
    AddNode(begin, end, "a");
    AddNode(begin, end, "d");
    AddNode(begin, end, "b");
    printf("test add = ");

    PrintList(*begin, *end);
}
void test_remove(char*** begin, char*** end)
{
    printf("test before remove = ");
    PrintList(*begin, *end);

    StringListRemove(begin, end, "b");
    StringListRemove(begin, end, "d");
    StringListRemove(begin, end, "m");

    printf("test after remove = ");

    PrintList(*begin, *end);
}

void test_remove_dublicates(char*** begin, char*** end)
{
    AddNode(begin, end, "c");
    AddNode(begin, end, "c");
    AddNode(begin, end, "c");
    AddNode(begin, end, "d");
    AddNode(begin, end, "cd");
    AddNode(begin, end, "k");
    AddNode(begin, end, "d");

    printf("test remove dublicates before = ");
    PrintList(*begin, *end);

    StringListRemoveDuplicates(begin, end);

    printf("after = ");
    PrintList(*begin, *end);

}
void test_sort(char*** begin, char*** end)
{
    AddNode(begin, end, "c");
    AddNode(begin, end, "b");
    AddNode(begin, end, "a");
    AddNode(begin, end, "d");
    AddNode(begin, end, "b");

    printf("test before sort = ");
    PrintList(*begin, *end);

    StringListSort(begin);

    printf("test after sort = ");
    PrintList(*begin, *end);

}
void test_index(char*** begin, char*** end)
{
    printf("index a == %d\n", StringListIndexOf(*begin, "a"));
    printf("index k == %d\n", StringListIndexOf(*begin, "k"));
}
void test_destroy(char*** begin, char*** end)
{
    printf(" before destroy = ");
    PrintList(*begin, *end);
    StringListDestroy(begin, end);
    printf("after destroy = ");
    PrintList(*begin, *end);

}
void test_replace_string(char*** begin, char*** end)
{
    AddNode(begin, end, "a");
    printf("before replace = ");
    PrintList(*begin, *end);
    StringListReplaceInStrings(*begin, "a", "kkk");
    printf("after replace = ");
    PrintList(*begin, *end);

}
void test()
{
    char** begin = NULL;
    char** end = NULL;
    test_add(&begin, &end);
    test_remove(&begin, &end);
    test_sort(&begin, &end);
    test_remove_dublicates(&begin, &end);
    test_index(&begin, &end);
    test_replace_string(&begin, &end);
    test_destroy(&begin, &end);
}