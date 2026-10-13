/* func_0204e52c @ 0x0204e52c, 0xf8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int unk_00, unk_04, unk_08, unk_0C;
} UnkStruct_0204e52c;
typedef struct {
    u8 d[0x28];
} UnkStruct_0204e52c_2;
typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
} UnkStruct_0204e52c_3;

extern int data_021e9aac;
extern int data_020ca0ec;
extern int data_020ca0e8;
extern int func_02037e90(int a, int b, int c);
extern UnkStruct_0204e52c *func_0204e8c4(int *tbl, int key);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern void func_02037eec(UnkStruct_0204e52c_2 *e, int a, int *blk, int b, int c, int d, int f, int g, int *ip, int h);
extern void func_020e993c(int key, UnkStruct_0204e52c *q);

int func_0204e52c(UnkStruct_0204e52c_3 *p, int key)
{
    UnkStruct_0204e52c *r;
    UnkStruct_0204e52c *q;
    UnkStruct_0204e52c_2 *e;
    int arr[8];
    int result = 0;

    p->unk_1C = 1;
    if (p->unk_00 == 0) {
        p->unk_00 = func_02037e90(0x24, key, 4);
    }
    q = func_0204e8c4(&data_021e9aac, key);
    if (p->unk_00 != 0 && q != 0) {
        arr[0] = 0;
        arr[1] = 0;
        arr[2] = 0;
        arr[3] = 0;
        arr[4] = 0;
        e = (UnkStruct_0204e52c_2 *) p->unk_00;
        r = q;
        p->unk_04 = 6;
        p->unk_08 = 6;
        p->unk_14 = p->unk_04 * data_020ca0ec;
        p->unk_18 = p->unk_08 * data_020ca0e8;
        func_0204f800(&p->unk_0C, &p->unk_10, p->unk_04, p->unk_08, 0, 0);
        for (arr[1] = 0; arr[1] < p->unk_08; arr[1]++) {
            for (arr[0] = 0; arr[0] < p->unk_04; arr[0]++) {
                arr[2] = *(volatile int *) arr << 0x11;
                arr[4] = arr[1] << 0x11;
                arr[5] = arr[2];
                arr[6] = arr[3];
                arr[7] = arr[4];
                func_02037eec(e, r->unk_00, &arr[5], r->unk_04, r->unk_08, r->unk_0C, 0, 0, arr, p->unk_1C);
                e++;
                r++;
            }
        }
        result = 1;
    }
    if (q != 0) {
        func_020e993c(key, q);
    }
    return result;
}
