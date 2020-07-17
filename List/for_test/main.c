#include "string.h"
#include "stdio.h"

static char* buffer = "111"; // buffer for word
static int pc = 3; // current number of elements in buffer

static char buf_send[20] = "";
static int pc_send = 0;

void push_ASCII(int pseudo_num);

int main() {
    printf("%s\n", buffer);

    int pseudo_num = 0;
    for (int i = 0; i <= pc; i++) {
        if (buffer[i] - 48 == 3 || !buffer[i]) {
            push_ASCII(pseudo_num);

            pseudo_num = 0;
            continue;
        }

        pseudo_num = pseudo_num*10 + (buffer[i] - 48);
    }

    buf_send[pc_send] = 0;

    printf("%s\n", buf_send);
}

void push_ASCII(int pseudo_num) {
    switch (pseudo_num) {
        case 12:    buf_send[pc_send++] = 'A' + 7;
                    break;

        case 2111:  buf_send[pc_send++] = 'B' + 7;
                    break;

        case 2121:  buf_send[pc_send++] = 'C' + 7;
                    break;

        case 211:   buf_send[pc_send++] = 'D' + 7;
                    break;

        case 1:     buf_send[pc_send++] = 'E' + 7;
                    break;

        case 1121:  buf_send[pc_send++] = 'F' + 7;
                    break;

        case 221:   buf_send[pc_send++] = 'G' + 7;
                    break;

        case 1111:  buf_send[pc_send++] = 'H' + 7;
                    break;

        case 11:    buf_send[pc_send++] = 'I' + 7;
                    break;

        case 1222:  buf_send[pc_send++] = 'J' + 7;
                    break;

        case 212:   buf_send[pc_send++] = 'K' + 7;
                    break;

        case 1211:  buf_send[pc_send++] = 'L' + 7;
                    break;

        case 22:    buf_send[pc_send++] = 'M' + 7;
                    break;

        case 21:    buf_send[pc_send++] = 'N' + 7;
                    break;

        case 222:   buf_send[pc_send++] = 'O' + 7;
                    break;

        case 1221:  buf_send[pc_send++] = 'P' + 7;
                    break;

        case 2212:  buf_send[pc_send++] = 'Q' + 7;
                    break;

        case 121:   buf_send[pc_send++] = 'R' + 7;
                    break;

        case 111:   buf_send[pc_send++] = 'S' + 7;
                    break;

        case 2:     buf_send[pc_send++] = 'A'; // T
                    break;

        case 1122:  buf_send[pc_send++] = 'B'; // U
                    break;

        case 1112:  buf_send[pc_send++] = 'C'; // V
                    break;

        case 122:   buf_send[pc_send++] = 'D'; // W
                    break;

        case 2112:  buf_send[pc_send++] = 'E'; // X
                    break;

        case 2122:  buf_send[pc_send++] = 'F'; // Y
                    break;

        case 2211:  buf_send[pc_send++] = 'G'; // Z
                    break;

        case 12222: buf_send[pc_send++] = '1' + 7;
                    break;

        case 11222: buf_send[pc_send++] = '2' + 7;
                    break;

        case 11122: buf_send[pc_send++] = '0'; // 3
                    break;

        case 11112: buf_send[pc_send++] = '1'; // 4
                    break;

        case 11111: buf_send[pc_send++] = '2'; // 5
                    break;

        case 21111: buf_send[pc_send++] = '3'; // 6
                    break;

        case 22111: buf_send[pc_send++] = '4'; // 7
                    break;

        case 22211: buf_send[pc_send++] = '5'; // 8
                    break;

        case 22221: buf_send[pc_send++] = '6'; // 9
                    break;

        case 22222: buf_send[pc_send++] = '7'; // 10
                    break;
    }
}
