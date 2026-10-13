/* func_0202cd78 @ 0x0202cd78, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Entry {
    int unk_00;
    u8 unk_04;
    u8 pad_05[3];
} Entry;

extern u8 data_021c1ce4[2];
extern void MI_CpuFill8(void *, int, int);
extern int func_0202ceac(int, Entry *);
extern int func_0202ce24(int, int, int, Entry *);
extern int func_020644cc(int);

int func_0202cd78(int a, int b, int key, Entry **pp)
{
    Entry *e;
    int result;
    int n;
    int i;
    int j;
    int k;

    e = *pp;
    result = 0;
    if (e != 0) {
        n = 0;
        MI_CpuFill8(data_021c1ce4, result, 2);
        for (i = 0; i < 2; i++) {
            if (func_0202ceac(key, &e[i]) > 0) {
                data_021c1ce4[i] = 1;
                n++;
            }
        }
        if (n > 0) {
            k = func_020644cc(n);
            for (j = 0; j < 2; j++) {
                if (data_021c1ce4[j] == 1) {
                    if (k == 0) {
                        result = func_0202ce24(a, b, key, e);
                        break;
                    }
                    k--;
                }
                e += 1;
            }
        }
    }
    return result;
}
