/* func_ov003_02228a20 @ 0x02228a20, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov003_02227e94(char *self, char *b, int k);
extern void func_ov003_02228a9c(char *self, int k, char *b, void *c);

void func_ov003_02228a20(char *self, char *b, void *c)
{
    if (*(u8 *) (self + 0x84) == 0) {
        u8 st = *(u8 *) (b + 0x1fc);
        if (st == 3) {
            if (*(u8 *) (b + 0x23c) == 0) {
                if (func_ov003_02227e94(self, b, 0)) {
                    func_ov003_02228a9c(self, 1, b, c);
                }
                *(u8 *) (self + 0x84) = 1;
            }
        } else if (st == 4) {
            if (*(u8 *) (b + 0x23c) == 0) {
                if (func_ov003_02227e94(self, b, 1)) {
                    func_ov003_02228a9c(self, 1, b, c);
                }
                *(u8 *) (self + 0x84) = 1;
            }
        }
    }
}
