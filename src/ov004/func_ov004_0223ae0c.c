/* func_ov004_0223ae0c @ 0x0223ae0c, 0xfc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204bc64(u16 *);
extern int func_02064328(char *, void *, ...);
extern void *func_02064b2c(char *, void *, int, int);
extern int NNS_FndMountArchive(void *, void *, void *);
extern char *NNS_FndGetArchiveFileByName(void *);
extern char *func_02107828(void *);
extern int func_02055f40(void *, void *, int);
extern int func_02055140(void *, void *);
extern int func_ov004_0223adfc(void *);
extern void func_02055060(void *, int, int, int, int, int);
extern void func_02055050(void *);
extern void func_02055dc8(void *, int, int);
extern int func_0210285c(void *);
extern void func_ov004_0223b1b8(void *);
extern char data_ov004_022560fc, data_ov004_02256110;
extern void *data_ov004_02255f70;

int func_ov004_0223ae0c(char *self)
{
    u16 item;
    char name[0x2a];
    char buf[0x68];
    int ok;
    if (*(void **) (self + 0x10) == 0) {
        return 0;
    }
    if (*(void **) (self + 0x24) != 0) {
        return 0;
    }
    if (*(void **) (self + 0x28) != 0) {
        return 0;
    }
    item = 0x3984;
    {
        int id = func_0204bc64(&item);
        func_02064328(name, &data_ov004_022560fc, id >> 8, (id & 0xff) >> 4, id);
    }
    *(void **) (self + 0x24) = func_02064b2c(name, *(void **) (self + 0x10), 4, 0);
    if (*(void **) (self + 0x24) != 0 && NNS_FndMountArchive(buf, &data_ov004_02256110, *(void **) (self + 0x24)) != 0) {
        char *res;
        ok = 0;
        res = func_02107828(NNS_FndGetArchiveFileByName(data_ov004_02255f70));
        *(char **) (self + 0x28) = res + *(int *) (res + *(u16 *) (res + 0xe) + 0xc);
        if (func_02055f40(self + 0x2c, *(void **) (self + 0x28), ok) != 0 &&
            func_02055140(self + 0x2c, *(void **) (self + 0x10)) != 0) {
            int a = func_ov004_0223adfc(self);
            func_02055060(self + 0x2c, a, 1, 0x1000, ok, ok);
            func_02055050(self + 0x2c);
            func_02055dc8(self + 0x2c, (int) func_ov004_0223b1b8, (int) self);
            ok = 1;
        }
        func_0210285c(buf);
        return ok;
    }
    return 0;
}
