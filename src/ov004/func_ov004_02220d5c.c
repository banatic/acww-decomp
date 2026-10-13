/* func_ov004_02220d5c @ 0x02220d5c, 0x98 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int gt2GetIncomingBufferSize(void *p);
extern int func_0201c314(void *self, int h);
extern void func_020147fc(void *p, int a, int b, int c);
extern void func_020e8858(void *p);
extern void func_0209e474(void *p);
extern int func_02014868(void *p);
extern void func_0203e020(void *s);
extern void func_ov004_02221550(void *s, int a);

int func_ov004_02220d5c(char *s)
{
    u8 v;
    int h;
    int n;
    v = *(u8 *) (s + 0xadd);
    if (v != 0) {
        if (v == 1) {
            h = gt2GetIncomingBufferSize(s + 0x918);
            n = 0;
            if (h != 0) {
                n = func_0201c314(s, h);
            }
            func_020147fc(s + 0x618, 0, n, 1);
        }
        func_020e8858(s + 0xadd);
        return 1;
    }
    func_0209e474(s + 0xad0);
    if (func_02014868(s + 0x618) == 0) {
        func_0203e020(s);
        if (*(u8 *) (s + 0xac8) == 1) {
            *(u8 *) (s + 0xac8) = 2;
            *(int *) (s + 0xae8) = 0;
        }
        func_ov004_02221550(s, 8);
    }
    return 1;
}
