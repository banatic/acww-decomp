/* func_020913c8 @ 0x020913c8, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Entry {
    char pad_00[14];
    short unk_0E;
    int pad_10;
    int unk_14;
    char pad_18[4];
} Entry;

void func_020913c8(Entry *arr, int key, short value)
{
    int i;
    i = 0;
    if (key == -1) {
        return;
    }
    for (; i < 32; i++) {
        Entry *p = &arr[i];
        if (key == p->unk_14) {
            p->unk_0E = value;
        }
    }
}
