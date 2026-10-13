/* func_02034f14 @ 0x02034f14, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int key;
    unsigned char pad_04[0x18];
} UnkStruct_02034f14;
int func_02034f14(unsigned char *p, int key)
{
    int r = -1;
    int i;
    int v;
    UnkStruct_02034f14 *arr = (UnkStruct_02034f14 *) p;
    int n = *(int *) (p + 0x1c0);
    for (i = 0; i < n; i++) {
        v = arr[i].key;
        if (v == key) {
            r = i;
            break;
        }
    }
    return r;
}
