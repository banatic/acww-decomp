/* func_ov003_0222902c @ 0x0222902c, 0xd4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_0213efe8[];
extern char data_0213f020[];
extern void func_020f5958(char *self);
extern void func_02032c64(char *p);
extern void func_0209d34c(char *p);
extern void func_0205577c(char *p);
extern void func_02055210(char *p);
extern void func_ov003_02228f48(char *p);

char *func_ov003_0222902c(char *self)
{
    func_020f5958(self);
    *(void **) (self + 0x40) = data_0213efe8;
    *(void **) (self + 0x40) = data_0213f020;
    func_02032c64(self + 0x4c);
    func_0209d34c(self + 0x7c);
    func_0205577c(self + 0x84);
    func_02055210(self + 0x144);
    *(int *) (self + 0x208) = 0;
    *(int *) (self + 0x20c) = 0;
    func_ov003_02228f48(self + 0x248);
    *(s8 *) (self + 0x7e) = -1;
    *(int *) (self + 0x244) = -1;
    *(int *) (self + 0x80) = 0;
    *(u8 *) (self + 0x1fc) = 2;
    *(u8 *) (self + 0x201) = 0;
    *(int *) (self + 0x204) = -1;
    *(s8 *) (self + 0x227) = -1;
    *(int *) (self + 0x22c) = 0;
    *(u8 *) (self + 0x224) = 0;
    *(u8 *) (self + 0x23c) = 0;
    *(int *) (self + 0x120) = 0x1000;
    *(int *) (self + 0x124) = 0x1000;
    *(int *) (self + 0x128) = 0x1000;
    return self;
}
