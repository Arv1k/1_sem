#include "list_c.h"

int main() {
    list myList;

    myList.push_front(7);
    list_elem* pos = myList.push_front(6);
    myList.insert_before(11, pos);

    myList.delete_elem(pos);

    myList.list_dump();
}