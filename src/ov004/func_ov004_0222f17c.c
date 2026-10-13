/* func_ov004_0222f17c @ 0x0222f17c, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int unk_00;
    unsigned int unk_04;
} UnkStruct_0222f17c;
extern UnkStruct_0222f17c *func_ov004_0222f320(void *);
int func_ov004_0222f17c(u8 *self, int c)
{
    unsigned int i, n;
    UnkStruct_0222f17c *p;
    p = func_ov004_0222f320(*(void **) (self + 8));
    i = 0;
    n = p->unk_04;
    while (i < n) {
        if (c == (*(signed char **) (self + 0x290))[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}
