/* func_ov004_0221f334 @ 0x0221f334, 0x104 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x830];
    void *unk_830;
    char pad_834[0xa54 - 0x834];
    u8 unk_A54;
} UnkStruct_0221f334;
extern int func_020160b4(void *arg0);
extern int func_020ab504(void *);
extern int func_020644cc(int);
extern int func_0208150c(void *);
extern int func_0200366c(int a, void *b, int c, void *d);
extern void func_0208b520(void);
extern void func_ov004_0221f71c(void *self);
extern void func_0206844c(int, u8 *, void *);
extern char data_ov004_02257d08;
extern char data_ov004_02253c74;
extern char data_ov004_02253c80;
extern char data_ov004_02253c88;
extern char data_ov004_02253c90;
void func_ov004_0221f334(char *self)
{
    u8 buf;
    int have;
    void *tbl;
    u8 state;
    u8 code;
    char *tblEarly;
    have = func_020ab504((void *) func_020160b4((void *) self));
    code = 0xff;
    if ((*((UnkStruct_0221f334 **) (self + 0x1a4)))->unk_A54 == 1) {
        state = *((u8 *) (self + 0x1e));
        tblEarly = &data_ov004_02257d08;
        if (state == 0) {
            goto mode1_ok;
        }
        if (state == 1) {
            goto mode1_ok;
        }
        if (state == 2) {
            goto mode1_ok;
        }
        goto tail;
    mode1_ok:
        tbl = tblEarly;

        code = (u8) func_020644cc(3);
        if (have == 0) {
            func_0200366c(func_0208150c((*((UnkStruct_0221f334 **) (self + 0x1a4)))->unk_830), tbl, 0x28,
                          &data_ov004_02253c74);
            func_0208b520();
            (*((UnkStruct_0221f334 **) (self + 0x1a4)))->unk_A54 = 2;
        } else {
            func_0200366c(func_0208150c((*((UnkStruct_0221f334 **) (self + 0x1a4)))->unk_830), tbl, 0x28,
                          &data_ov004_02253c80);
        }
    } else if ((*((UnkStruct_0221f334 **) (self + 0x1a4)))->unk_A54 == 2) {
        state = *((u8 *) (self + 0x1e));
        if (state == 0) {
            goto mode2_ok;
        }
        if (state == 1) {
            goto mode2_ok;
        }
        if (state == 2) {
            goto mode2_ok;
        }
        goto tail;
    mode2_ok:
        if (have == 0) {
            func_0200366c(func_0208150c((*((UnkStruct_0221f334 **) (self + 0x1a4)))->unk_830), &data_ov004_02257d08, 0x28,
                          &data_ov004_02253c88);
            func_ov004_0221f71c(self);
        } else {
            func_0200366c(func_0208150c((*((UnkStruct_0221f334 **) (self + 0x1a4)))->unk_830), &data_ov004_02257d08, 0x28,
                          &data_ov004_02253c90);
        }

        tbl = &data_ov004_02257d08;
        code = (u8) func_020644cc(3);
    }
tail:
    if (code != 0xff) {
        buf = code;
        func_0206844c(*((int *) (self + 0x40)), &buf, tbl);
    }
}
