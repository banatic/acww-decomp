/* func_02021ea8 @ 0x02021ea8, 0x72 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *dstp, unsigned char data, unsigned int size);
extern int func_020644cc(int count);

typedef int (*Pred)(void *self, int elem);

int func_02021ea8(void *self, int *arr, int count, Pred pred)
{
    int found;
    int i;
    int result;
    unsigned char flags[8];

    found = 0;
    result = 0;
    MI_CpuFill8(flags, found, 8);
    for (i = found; i < count; i++) {
        if (arr[i] != 0) {
            if (pred(self, arr[i]) == 1) {
                flags[i] = 1;
                found++;
            }
        }
    }
    if (found > 0) {
        int sel = func_020644cc(found);
        for (i = 0; i < count; i++) {
            if (flags[i] == 1) {
                if (sel == 0) {
                    result = arr[i];
                    break;
                } else {
                    sel--;
                }
            }
        }
    }
    return result;
}
