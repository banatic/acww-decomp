/* func_ov004_0222301c @ 0x0222301c, 0xfc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef void (*VF)(char *);

extern int func_0201c0e0(char *self);
extern int func_0201c040(char *self, int *p, int *q);
extern void func_0201c054(char *self, int a, int b, int c);
extern int func_0201c2a4(char *self, int n);
extern void func_02016108(char *a, int b);
extern void func_ov004_02223388(char *self, int n);
extern int func_020a7278(void);
extern int func_02016884(char *a, int b, char *c);
extern int func_ov004_0222fd70(void);
extern void func_ov004_0222fdb8(void);
extern void func_ov004_0222fd58(u16 v);
extern void func_ov004_0222fd94(void);
extern char *data_020ccf94;

int func_ov004_0222301c(char *self)
{
    // DECLS
    int p, q;
    char *o;
    int k;
    // ENDDECLS

    if (func_0201c0e0(self) != 0) {
        p = 4;
        q = 4;
        if (func_0201c040(self, &p, &q) != 0 && p == *(int *) (data_020ccf94 + 0x64) && p == q) {
            func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), *(int *) (data_020ccf94 + 0x64));
            o = self + 0x658;
            (*(VF *) (*(char **) o + 8))(o);
            func_02016108(self + 0x658, func_0201c2a4(self, 4));
            func_ov004_02223388(self, 1);
        } else if (func_020a7278() != 0 && q == 4) {
            func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), 4);
            func_ov004_02223388(self, 0);
        }
    } else if (func_020a7278() == 0) {
        if (func_02016884(self + 0x334, 0xe4, self + 0x2a0) != 0) {
            if (func_ov004_0222fd70() != 0) {
                func_ov004_0222fdb8();
                k = *(u8 *) (self + 0x712) * 0x38;
                func_ov004_0222fd58((u16) (k + (u16) (*(int *) (self + 0x190) >> 12)));
            }
        } else if (func_ov004_0222fd70() == 0) {
            func_ov004_0222fd94();
        }
    }
    return 1;
}
