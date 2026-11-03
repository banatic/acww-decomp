/* actor_table_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020828e0 @ 0x020828e0, 0x24 bytes, Thumb
 * func_020828c0 @ 0x020828c0, 0x20 bytes, Thumb
 */

struct Entry {
    unsigned int a;
    unsigned short b;
};

struct UnkStruct_020828c0 {
    int a;
    unsigned short b;
};

void func_020828e0(int param0, struct Entry *arr, int n)
{
    int i;
    int v;
    i = 0;
    v = i;
    for (; i < n; i++) {
        arr[i].a = v;
        arr[i].b = 0xFFF1;
    }
}

int func_020828c0(int unused, struct UnkStruct_020828c0 *p)
{
    if (p->a) {
        if (((p->b & 0xF000) >> 12) == 0xD) {
            return 1;
        }
    }
    return 0;
}
