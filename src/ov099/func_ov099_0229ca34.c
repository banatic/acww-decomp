/* func_ov099_0229ca34 @ 0x0229ca34, 0x94 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov099_0229cd70(u8 *self, u8 byte);
extern int func_ov099_0229cd1c(u8 *self, u8 byte);
extern int func_0206fe54(void);
extern void func_0208aa60(void *dst, int x, int y);
extern int func_ov099_0229cf30(u8 *self, u8 byte);
extern int func_ov099_0229cf04(u8 *self, u8 byte);
extern void func_ov094_0229abb8(void *a, void *b, int c);
extern int func_ov099_0229cf20(u8 *self, u8 byte);
extern int func_ov099_0229ce14(u8 *self, u8 byte);
extern void func_ov094_0229b9b4(void *a, void *b, int c);

void func_ov099_0229ca34(u8 *self)
{
    int first;
    int second;

    first = func_ov099_0229cd70(self, self[0x2905]) - 0x6d;
    second = func_ov099_0229cd1c(self, self[0x2905]) - 0x78;
    if (func_0206fe54() != 0) {
        second -= 8;
    }

    func_0208aa60(self + 0x218c, first, second);

    if (func_ov099_0229cf30(self, self[0x2905]) != 0) {
        func_ov094_0229abb8(self + 0xcc, self + 0x218c, func_ov099_0229cf04(self, self[0x2905]));
    } else if (func_ov099_0229cf20(self, self[0x2905]) != 0) {
        func_ov094_0229b9b4(self + 0xb2c, self + 0x218c, func_ov099_0229ce14(self, self[0x2905]));
    }
}
