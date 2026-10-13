/* func_ov129_0229c094 @ 0x0229c094, 0x54 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fc8c(void *p);
extern void *func_020b1530(int idx);

typedef struct Entry {
    unsigned char pad_00[0x2a];
    unsigned short arr[16];
} Entry;

void func_ov129_0229c094(void *arg)
{
    int count = func_0206fc8c(arg);
    int i;
    for (i = 0; i < 16; i++) {
        Entry *p;
        int j;
        if (i == count) {
            continue;
        }
        p = (Entry *) func_020b1530(i);
        if (p == 0) {
            continue;
        }
        for (j = 0; j < 16; j++) {
            unsigned short h = p->arr[j];
            if (h != 0xffff) {
                *((unsigned char *) arg + 0x2f98 + h) = 1;
            }
        }
    }
}
