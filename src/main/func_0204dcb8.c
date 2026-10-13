/* func_0204dcb8 @ 0x0204dcb8, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
} UnkStruct_0204dcb8;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_0204dcb8_2;

extern int func_02037e90(int a, int b, int c);
extern UnkStruct_0204dcb8_2 *func_02060eac(int *table, int key1, int key2);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern void func_02030ddc(int a, int b, int c, int d);
extern void func_02037f28(int a, int b, int *local, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_020e993c(int a, UnkStruct_0204dcb8_2 *b);
extern int data_021ebcd4;
extern int data_020ca0ec;
extern int data_020ca0e8;

int func_0204dcb8(UnkStruct_0204dcb8 *p, int key1, int key2)
{
    UnkStruct_0204dcb8_2 *q;
    int arr[6];
    int result = 0;

    p->unk_1C = key1 + 2;
    if (p->unk_00 == 0) {
        p->unk_00 = func_02037e90(1, key2, 4);
    }
    q = func_02060eac(&data_021ebcd4, key1, key2);
    if (p->unk_00 != 0 && q != 0) {
        arr[0] = 0;
        arr[1] = 0;
        arr[2] = 0;
        p->unk_04 = 1;
        p->unk_08 = 1;
        p->unk_14 = data_020ca0ec;
        p->unk_18 = data_020ca0e8;
        func_0204f800(&p->unk_0C, &p->unk_10, p->unk_04, p->unk_08, 0, 0);
        func_02030ddc(p->unk_04, p->unk_08, 0, p->unk_1C);
        arr[0] = 0;
        arr[2] = 0;
        arr[3] = 0;
        arr[4] = arr[1];
        arr[5] = 0;
        func_02037f28(p->unk_00, q->unk_00, &arr[3], q->unk_04, q->unk_08, q->unk_0C, 0, 0, 0, 0, p->unk_1C);
        func_020e993c(key2, q);
        result = 1;
    }
    return result;
}
