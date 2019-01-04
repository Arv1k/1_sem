#include "list_p.h"

bool ListCtor(list* nameList) {
    assert(nameList);

    nameList->count = 0;

    assert_list(nameList);
    return true;
}

bool ListPop_front(list* nameList) {
    assert_list(nameList);

    if (nameList->count == 0) {
        printf("There isn't any element to pop from front!!!\n");

        assert(nameList);
        return true;
    }

    else if (nameList->Head == nameList->Tail) {
        free(nameList->Head);

        nameList->Head = nullptr;
        nameList->Tail = nullptr;
        nameList->count = 0;

        assert_list(nameList);
        return true;
    }

    nameList->Head = (nameList->Head)->Next;

    ((nameList->Head)->Prev)->Next = nullptr;
    ((nameList->Head)->Prev)->Info = yad_elem;

    free((nameList->Head)->Prev);

    (nameList->Head)->Prev = nullptr;

    nameList->count--;

    assert_list(nameList);
    return true;
}

bool ListPop_back(list* nameList) {
    assert_list(nameList);

    if (nameList->count == 0) {
        printf("There isn't any element to pop from back!!!\n");

        assert_list(nameList);
        return true;
    }

    else if (nameList->Head == nameList->Tail) {
        free(nameList->Tail);

        nameList->Tail = nullptr;
        nameList->Head = nullptr;
        nameList->count = 0;

        assert_list(nameList);
        return true;
    }

    nameList->Tail = (nameList->Tail)->Prev;

    ((nameList->Tail)->Next)->Prev = nullptr;
    ((nameList->Tail)->Next)->Info = yad_elem;

    free((nameList->Tail)->Next);

    (nameList->Tail)->Next = nullptr;

    nameList->count--;

    assert_list(nameList);
    return true;
}

list_elem* ListPush_front(list* nameList, data_t elem) {
    assert_list(nameList);
    assert_var(elem);

    list_elem* element = (list_elem*) calloc(1, sizeof(list_elem));

    element->Info = elem;

    if (nameList->count == 0) {
        nameList->Head = element;
        nameList->Tail = element;

        nameList->count = 1;

        assert_list(nameList);
        return element;
    }

    (nameList->Head)->Prev = element;

    element->Next = nameList->Head;

    nameList->Head = element;

    nameList->count++;

    assert_list(nameList);
    return element;
}

list_elem* ListPush_back(list* nameList, data_t elem) {
    assert_list(nameList);
    assert_var(elem);

    list_elem* element = (list_elem*) calloc(1, sizeof(list_elem));

    element->Info = elem;

    if (nameList->count == 0) {
        nameList->Head = element;
        nameList->Tail = element;

        nameList->count = 1;

        assert_list(nameList);
        return element;
    }

    (nameList->Tail)->Next = element;

    element->Prev = nameList->Tail;

    nameList->Tail = element;

    nameList->count++;

    assert_list(nameList);
    return element;
}



list_elem* ListInsert_before(list* nameList, data_t elem, list_elem* position) {
    assert_list(nameList);
    assert_var(elem);
    assert(position);

    if (nameList->count == 0) {
        printf("There aren't any elements!!!\n");

        assert_list(nameList);
        return nullptr;
    }

    if (position->Prev == nullptr) return ListPush_front(nameList, elem);

    list_elem* element = (list_elem*) calloc(1, sizeof(list_elem));

    element->Info = elem;

    (position->Prev)->Next = element;
    element->Prev = position->Prev;
    position->Prev = element;

    element->Next = position;

    if (element->Prev == nullptr) nameList->Head = element;

    nameList->count++;

    assert_list(nameList);
    return element;
}

list_elem* ListInsert_after(list* nameList, data_t elem, list_elem* position) {
    assert_list(nameList);
    assert_var(elem);
    assert(position);

    if (nameList->count == 0) {
        printf("There aren't any elements!!!\n");

        assert_list(nameList);
        return nullptr;
    }

    if (position->Next == nullptr) return ListPush_back(nameList, elem);

    list_elem* element = (list_elem*) calloc(1, sizeof(list_elem));

    element->Info = elem;

    (position->Next)->Prev = element;
    element->Next = position->Next;
    position->Next = element;

    element->Prev = position;

    if (element->Next == nullptr) nameList->Tail = element;

    nameList->count++;

    assert_list(nameList);
    return element;
}

bool ListDelete(list* nameList, list_elem* position) {
    assert_list(nameList);
    assert(position);

    if (nameList->count == 0) {
        printf("There aren't any elements!!!\n");

        assert_list(nameList);
        return false;
    }

    if (position->Next == nullptr) {
        ListPop_back(nameList);

        assert_list(nameList);
        return true;
    }

    else if (position->Prev == nullptr) {
        ListPop_front(nameList);

        assert_list(nameList);
        return true;
    }

    (position->Prev)->Next = position->Next;
    (position->Next)->Prev = position->Prev;

    position->Info = yad_elem;
    position->Next = nullptr;
    position->Prev = nullptr;

    nameList->count--;

    free(position);

    assert_list(nameList);
    return true;
}

//$do(wtf)  { printf ("%s:\n", #wtf); wtf; }

bool ListDtor(list* nameList) {
    assert_list(nameList);

    if (nameList->count != 0) {
        size_t iskan = nameList->count;

        for (int i = 0; i < iskan; i++) ListPop_back(nameList);
    }

    nameList->count = yad_count;

    assert(nameList);
    return true;
}

bool ListOK(list* nameList) {
    if (nameList == nullptr)                                        return false;

    if (nameList->Tail == nullptr && nameList->Head == nullptr) {
        if (nameList->count == 0)                                   return true;
        else                                                        return false;
    }

    if (nameList->Tail == nullptr || nameList->Head == nullptr)     return false;

    if (nameList->count == 0)                                       return false;

    return true;
}

void DumpList(list* nameList) {
    FILE* Dump = fopen("../DumpList.txt", "a+");

    fprintf(Dump ,"#----------------------------------------------------------\n");
    fprintf(Dump ,"# List [%p] ", nameList);
    if (nameList == nullptr) {
        fprintf(Dump, "(!!!ERROR!!!)\n"
               "#----------------------------------------------------------\n");

        return;
    }

    fprintf(Dump ,"{\n");

    fprintf(Dump, "#     Head [%p] ", nameList->Head);
    if (nameList->Head == nullptr)              fprintf(Dump, "nullptr; (?)\n");
    else {
        if ((nameList->Head)->Info == yad_elem) fprintf(Dump, "%d; (!!!)\n", (nameList->Head)->Info);
        else                                    fprintf(Dump, "%d;\n", (nameList->Head)->Info);
    }

    fprintf(Dump, "#     Tail [%p] ", nameList->Tail);

    if (nameList->Tail == nullptr)              fprintf(Dump, "nullptr; (?)\n");
    else {
        if ((nameList->Tail)->Info == yad_elem) fprintf(Dump, "%d; (!!!)\n", (nameList->Tail)->Info);
        else                                    fprintf(Dump, "%d;\n", (nameList->Tail)->Info);
    }

    fprintf(Dump, "#     Count ");

    if (nameList->count == yad_count) {
        fprintf(Dump, "%lu; (!!!yad!!!)\n", nameList->count);
        fprintf(Dump, "# }\n");

        fprintf(Dump, "#----------------------------------------------------------\n");

        return;
    }

    else if (nameList->count == 0) {
        fprintf(Dump, "%lu; (?)\n", nameList->count);
        fprintf(Dump, "# }\n");

        fprintf(Dump, "#----------------------------------------------------------\n");

        return;
    }

    fprintf(Dump, "%lu;\n", nameList->count);

    fprintf(Dump, "#     Elements {\n");

    list_elem* prom = nameList->Head;
    for (int i = 1; i <= nameList->count; i++) {
        fprintf(Dump, "#         %d:  [%p]  %d\n", i, prom, prom->Info);

        prom = prom->Next;
    }

    fprintf(Dump, "#     }\n");
    fprintf(Dump, "# }\n");
    fprintf(Dump, "#----------------------------------------------------------\n\n");

    fclose(Dump);
}