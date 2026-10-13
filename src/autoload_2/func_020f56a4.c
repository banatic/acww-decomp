/* func_020f56a4 @ 0x020f56a4, 0xa4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 unk_00[0x4e];
} GFlags;
extern GFlags data_021fd1bc;
extern void func_020f564c(void *);
extern int func_020ef2a4(void *, int, int, int, int);

int func_020f56a4(void *p1, int freq, int p3, int p4)
{
    int rem;
    void *padj;
    if (data_021fd1bc.unk_00[0x4d] == 1) {
        return 0;
    }
    if (freq == 0x7f6) {
        func_020f564c(p1);
    }
    padj = p1;
    if (p1 != 0) {
        padj = (u8 *) p1 + 4;
    }
    rem = freq % 1000;
    return func_020ef2a4(padj, freq / 1000, rem, p3, p4);
}
