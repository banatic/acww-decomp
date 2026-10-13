/* func_02042730 @ 0x02042730, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0209e380(void *, void *);

typedef struct {
    unsigned int a;
    unsigned int b;
} UnkStruct_02042730;

int func_02042730(int unused, u8 *p1, u8 *p2)
{
    UnkStruct_02042730 local;
    int result = 0;
    int b = p1[2];

    if (b == 0xff && p1[1] == 0xff && p1[0] == 0xff) {
        result = 1;
    } else if (b == p2[5] && p1[1] == p2[4] && p1[0] == p2[3]) {
        ;
    } else {
        result = 0;
        local.a = result;
        local.b = result;
        local.a = result;
        local.b = result;
        ((u8 *) &local)[5] = p1[2];
        ((u8 *) &local)[4] = p1[1];
        ((u8 *) &local)[3] = p1[0];
        result = func_0209e380(&local, p2);
        if (result > 0x1f) {
            result = 0x1f;
        } else if (result < 0) {
            result = 1;
        }
    }
    return result;
}
