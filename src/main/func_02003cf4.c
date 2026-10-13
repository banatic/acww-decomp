/* func_02003cf4 @ 0x02003cf4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Param {
    int unk_00;
    int unk_04;
    int unk_08;
};

struct Elem {
    int a;
    int b;
    int c;
};

struct UnkStruct_02003cf4 {
    int x;
    int y;
    struct Elem *arr;
};

extern struct UnkStruct_02003cf4 data_020d5b3c;
extern void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);

void func_02003cf4(struct Param *p)
{
    if (p->unk_08) {
        func_02088df8(0, data_020d5b3c.arr[p->unk_00].a, p->unk_04 + 0x80, 0x60, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}
