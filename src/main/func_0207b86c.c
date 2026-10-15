/* func_0207b86c @ 0x0207b86c, 0x164 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct Rec {
    u16 w;
    u8 d[0xc];
    u8 pad_0E;
    u8 unk_0F;
} Rec;

extern Rec *func_0208150c(void *p);
extern void *func_020984e8(void);
extern char *func_02099640(void *p);
extern int func_0209ad9c(char *p, int i);
extern int func_0209b4d4(int c);
extern int func_0209bd44(int h);
extern Rec *func_0209b4cc(int c, int i);
extern int memcmp(const void *a, const void *b, unsigned int n);
extern int func_0209bc40(int h);
extern void *func_0209a778(void *record);
extern Rec *func_0209a774(void *p);
extern int func_0209aebc(char *p, Rec *r);
extern int func_0207f1c8(void *p);
extern int func_0209b5e8(int a);
extern int func_0209b91c(void *);

int func_0207b86c(char *self, void *a1, void *a2)
{
    Rec *me;
    Rec *o;
    char *p;
    int c0;
    int ret;
    int c1;

    me = func_0208150c(a1);
    ret = 0x16;
    if (a2 == 0) {
        a2 = func_020984e8();
    }
    if (a2 == 0) {
        goto out;
    }

    p = func_02099640(a2);
    c0 = func_0209ad9c(p, 0);
    c1 = func_0209ad9c(p, 1);
    p += 0xa4;

    if (func_0209bd44(func_0209b4d4(c0)) != 0) {
        o = func_0209b4cc(c0, 0);
        if (o->w == me->w && memcmp(o->d, me->d, 0xc) == 0 && o->unk_0F == me->unk_0F) {
            ret = func_0209bc40(func_0209b4d4(c0));
            goto out;
        }
    }
    if (func_0209bd44(func_0209b4d4(c1)) != 0) {
        o = func_0209b4cc(c1, 0);
        if (o->w == me->w && memcmp(o->d, me->d, 0xc) == 0 && o->unk_0F == me->unk_0F) {
            ret = func_0209bc40(func_0209b4d4(c1));
            goto out;
        }
    }
    if (func_0209bd44((int) func_0209a778(self + 0x3f90)) != 0) {
        o = func_0209a774(self + 0x3f90);
        if (o->w == me->w && memcmp(o->d, me->d, 0xc) == 0 && o->unk_0F == me->unk_0F) {
            ret = func_0209bc40((int) func_0209a778(self + 0x3f90));
            goto out;
        }
    }
    if (func_0209aebc(p, me) != 0) {
        p += 0x10;
        ret = func_0209bc40((int) p);
        goto out;
    }
    if (func_0209bd44((func_0209b91c((void *) func_0209b5e8(func_0207f1c8(a1))))) != 0) {
        ret = func_0209bc40((func_0209b91c((void *) func_0209b5e8(func_0207f1c8(a1)))));
    }

out:
    return ret;
}
