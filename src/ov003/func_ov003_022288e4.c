/* func_ov003_022288e4 @ 0x022288e4, 0xcc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_ov003_0225f220[];
extern int func_ov003_02227680(char *p, char *q);
extern void func_ov003_0222be40(char *obj);
extern void func_ov003_022286ac(char *self, char *a, char *b, short h);
extern void func_ov003_02229da4(char *obj);

void func_ov003_022288e4(char *self, char *obj)
{
    if (*(u8 *) (obj + 0x7f) != 0) {
        char *p = data_ov003_0225f220;
        if (func_ov003_02227680(p, self + 0x68)) {
            short h;
            char *q;
            func_ov003_0222be40(obj);
            *(int *) (obj + 0x80) = 3;
            *(u8 *) (obj + 0x1fd) = 0x1f;
            q = obj + 0x120;
            h = *(short *) (obj + 0x138);
            func_ov003_022286ac(self, q, obj + 0x144, h);
            p += 0x58;
            func_ov003_022286ac(self, q, p, h);
        }
    } else {
        func_ov003_0222be40(obj);
        if (*(u8 *) (obj + 0x201) > 3 || *(u8 *) (obj + 0x200) == 3) {
            *(int *) (obj + 0x80) = 3;
            *(u8 *) (obj + 0x1fd) = 0x1f;
            *(u8 *) (obj + 0x201) = 0;
            func_ov003_022286ac(self, obj + 0x120, obj + 0x144, *(short *) (obj + 0x138));
            if (*(s8 *) (obj + 0x7e) == 0xb) {
                func_ov003_02229da4(obj);
            }
        }
    }
}
