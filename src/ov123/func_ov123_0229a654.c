/* func_ov123_0229a654 @ 0x0229a654, 0x180 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 a, b, c, d;
} QE;

extern u8 func_ov123_0229a8dc(int, u8, u8);
extern void func_ov123_02299d9c(int);
extern int func_ov123_0229a82c(int, int, int, int);
extern int func_ov123_0229a7d4(int, int, int, int);
extern int func_ov123_0229adc8(int, u8, u8, int);
extern int func_ov123_0229a884(int, int, int, int, int);

extern unsigned int data_ov123_0229d2e4;
extern QE data_ov123_0229d3b4[];
extern int data_ov123_0229ce2c;

void func_ov123_0229a654(int board, u8 x, u8 y, int newval)
{
    int old;
    int head;
    int j;
    int yy1;
    int x2;
    int mask;
    int lx;
    int s;
    int s2;
    int tail;
    int x1, yy, yy2;
    int rx;
    int cur, cur2, e;

    func_ov123_02299d9c(board);
    old = func_ov123_0229a8dc(board, x, y);
    if (old == newval) {
        return;
    }

    if ((data_ov123_0229d2e4 & 1) == 0) {
        data_ov123_0229d2e4 |= 1;
    }

    head = 0;
    tail = 1;
    data_ov123_0229d3b4[0].a = x;
    data_ov123_0229d3b4[0].b = x;
    data_ov123_0229d3b4[0].c = y;
    mask = data_ov123_0229ce2c;

    do {
        x1 = data_ov123_0229d3b4[head].a;
        x2 = data_ov123_0229d3b4[head].b;
        yy = data_ov123_0229d3b4[head].c;
        head = head + 1;
        head = head & mask;
        if (newval == func_ov123_0229a8dc(board, (u8) x1, (u8) yy)) {
            continue;
        }

        lx = func_ov123_0229a82c(board, x1, yy, old);
        rx = func_ov123_0229a7d4(board, x2, yy, old);
        j = lx;
        while (j <= rx) {
            func_ov123_0229adc8(board, (u8) j, (u8) yy, newval);
            j = j + 1;
        }

        if (yy > 0) {
            cur = lx;
            yy1 = yy - 1;
            do {
                s = func_ov123_0229a884(board, cur, rx, yy1, old);
                if (s < 0) {
                    cur = 0xff;
                } else {
                    e = func_ov123_0229a7d4(board, s, yy1, old);
                    data_ov123_0229d3b4[tail].a = (u8) s;
                    data_ov123_0229d3b4[tail].b = (u8) e;
                    data_ov123_0229d3b4[tail].c = (u8) yy1;
                    tail = tail + 1;
                    tail = tail & mask;
                    cur = e + 2;
                }
            } while (cur <= rx);
        }

        if (yy < 0x1f) {
            yy2 = yy + 1;
            cur2 = lx;
            do {
                s2 = func_ov123_0229a884(board, cur2, rx, yy2, old);
                if (s2 < 0) {
                    cur2 = 0xff;
                } else {
                    e = func_ov123_0229a7d4(board, s2, yy2, old);
                    data_ov123_0229d3b4[tail].a = (u8) s2;
                    data_ov123_0229d3b4[tail].b = (u8) e;
                    data_ov123_0229d3b4[tail].c = (u8) yy2;
                    tail = tail + 1;
                    tail = tail & mask;
                    cur2 = e + 2;
                }
            } while (cur2 <= rx);
        }
    } while (head != tail);
}
