/* func_ov068_0226ac40 @ 0x0226ac40, 0x68 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0226ac40 {
    int pad_00;
};
extern char data_021ed278[];

extern void *func_02072a48(struct UnkStruct_0226ac40 *, u8);
extern int func_02072dd4(void *, void *);
extern unsigned int func_0207cc54(u16, int, int);

void *func_ov068_0226ac40(void *unused, void *arg)
{
    unsigned int i;
    u16 mask;
    int count;
    unsigned int k;

    if ((struct UnkStruct_0226ac40 *) data_021ed278 != 0) {
        mask = 0;
        count = 0;
        i = 0;
        goto test;
    body:
        if (arg != 0) {
            if (func_02072dd4(func_02072a48((struct UnkStruct_0226ac40 *) data_021ed278, (u8) i), arg) != 0) {
                goto next;
            }
        }
        mask = (u16) (mask | (1 << i));
        count++;
    next:
        i++;
    test:
        if (i < 8) {
            goto body;
        }
        k = func_0207cc54(mask, count, 8);
        if (k < 8) {
            return func_02072a48((struct UnkStruct_0226ac40 *) data_021ed278, (u8) k);
        }
    }
    return 0;
}
