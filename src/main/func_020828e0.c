/* func_020828e0 @ 0x020828e0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    unsigned int a;
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
