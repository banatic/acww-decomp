/* func_0204d8b0 @ 0x0204d8b0, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    unsigned short *ptr;
    int count;
};

extern int func_0204d924(struct Entry *a, int b);

unsigned short func_0204d8b0(struct Entry *a, int b, int c)
{
    unsigned short result = 0;
    if (func_0204d924(a, b)) {
        struct Entry *e = &a[b];
        if (e->ptr != 0 && c < e->count) {
            result = e->ptr[c];
        }
    }
    return result;
}
