/* func_ov004_022209b4 @ 0x022209b4, 0xf4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204bcdc(char *p);
extern int func_0204bc64(void *p);
extern int func_0208150c(int a);
extern int func_020804e8(int a);
extern void func_02081ac0(int a, char *b);
extern void func_0207df18(int a, char *b);
extern void func_ov004_0223bb14(int a);

void func_ov004_022209b4(char *self)
{
    // DECLS
    u16 t;
    char *e;
    char *o;
    int ok;
    int r;
    int i;
    // ENDDECLS

    e = *(char **) (self + 0x1a4) + 0x898;
    if (func_0204bcdc(e) != 0) {
        t = 0xfff1;
        ok = (func_0204bc64(e) == func_0204bc64(&t)) ? 1 : 0;
    } else {
        ok = (*(u16 *) e == 0xfff1) ? 1 : 0;
    }
    if (ok != 0) {
        return;
    }
    o = *(char **) (self + 0x1a4);
    if (*(int *) (o + 0x8a8) == -1) {
        return;
    }
    if (func_0208150c(*(int *) (o + 0x830)) != 0) {
        r = func_020804e8(*(int *) (*(char **) (self + 0x1a4) + 0x830));
        if (r != 0) {
            func_02081ac0(r, *(char **) (self + 0x1a4) + 0x898);
        }
        func_0207df18(*(int *) (*(char **) (self + 0x1a4) + 0x830), *(char **) (self + 0x1a4) + 0x898);
    }
    func_ov004_0223bb14(*(int *) (*(char **) (self + 0x1a4) + 0x8a8));
    *(int *) (*(char **) (self + 0x1a4) + 0x8a8) = -1;
    *(u16 *) (*(char **) (self + 0x1a4) + 0x898) = 0xfff1;
    (*(u8 *) (*(char **) (self + 0x1a4) + 0xae0))++;
    for (i = 0; i < 0x64; i++) {
        *(u8 *) (*(char **) (self + 0x1a4) + i + 0x8ac) = 0xff;
    }
}
