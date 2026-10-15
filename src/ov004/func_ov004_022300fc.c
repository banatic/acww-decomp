/* func_ov004_022300fc @ 0x022300fc, 0x1fc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *data_ov004_02258558;
extern char data_ov004_022555a0[], data_ov004_022555bc[], data_ov004_022555d8[], data_ov004_022555f4[], data_ov004_02255610[],
    data_ov004_022585ac[];
extern int data_021c9b24;
extern int func_ov004_0222c600(char *, void *, void *);
extern int func_ov004_0222c3f4(char *, void *);
extern int func_ov004_0222c348(char *, void *);
extern void *func_ov004_0222c3a0(char *);
extern void *func_ov004_0222c33c(char *);
extern void *func_ov004_0222c3c4(char *, int);
extern void *func_ov004_0222c3a4(char *, int);
extern int func_02055f2c(char *, void *, int);
extern int NNS_G3dBindMdlTex(void *, void *);
extern int NNS_G3dBindMdlPltt(void *, void *);
extern int func_02055140(char *, int);
extern void func_02055060(char *, void *, int, int, u16, u16);
extern void func_02055050(char *);
extern int func_0205650c(char *, void *, int);
extern void func_02056478(char *, void *, u8, int, u16);
extern void *func_02055e00(char *);
extern void func_020563dc(char *, void *);
extern void *func_02063df4(void *);
extern void func_02063ccc(int *, int, int);
extern void func_020638d4(u16 *, int *, int, void *, u8, int, int);
extern void func_02063cc8(int *);
extern int func_0203d064(void *, u16 *, void *);
extern void *func_0203cfc8(void *);
extern int func_020b9d3c(char *, void *, void *, void *, int, int);
extern int func_ov004_0222fef4(char *);
extern void *func_02063ddc(void *);
int func_ov004_022300fc(char *self)
{
    int context[3];
    int pair[2];
    u16 item;
    void *model;
    data_ov004_02258558 = self;
    func_ov004_0222c600(self, data_ov004_022555a0, data_ov004_022555bc);
    func_ov004_0222c3f4(self + 0x348, data_ov004_022555d8);
    func_ov004_0222c348(self + 0x3ec, data_ov004_022555f4);
    func_02055f2c(self + 0x290, func_ov004_0222c3a0(self + 0x348), 0);
    model = func_ov004_0222c3a0(self + 0x348);
    NNS_G3dBindMdlTex(model, func_ov004_0222c33c(self + 0x3ec));
    model = func_ov004_0222c3a0(self + 0x348);
    NNS_G3dBindMdlPltt(model, func_ov004_0222c33c(self + 0x3ec));
    if (func_ov004_0222c3c4(self + 0x1a4, 0) && func_02055140(self + 0xec, data_021c9b24)) {
        func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0), 0, 0x1000, 0, 0);
        func_02055050(self + 0xec);
        *(int *) (self + 0x198) = 0;
    }
    if (func_0205650c(self + 0x418, *(void **) (self + 0x148), data_021c9b24)) {
        func_02056478(self + 0x418, func_ov004_0222c3a4(self + 0x1a4, 0), 0, 0x1000, 0);
        func_020563dc(self + 0x418, func_02055e00(self + 0xec));
        *(int *) (self + 0x428) = 0;
    }
    if (func_ov004_0222c3c4(self + 0x348, 0) && func_02055140(self + 0x290, data_021c9b24)) {
        func_02055060(self + 0x290, func_ov004_0222c3c4(self + 0x348, 0), 0, 0x1000, 0, 0);
        func_02055050(self + 0x290);
        *(int *) (self + 0x33c) = 0;
    }
    func_02063df4(context);
    func_02063ccc(pair, 2, 0);
    func_020638d4(&item, pair, 0, context, 1, 1, 0);
    func_02063cc8(pair);
    func_0203d064(data_ov004_022585ac, &item, 0);
    model = *(void **) (self + 0x2ec);
    func_020b9d3c(self + 0x3f0, model, data_ov004_02255610, func_0203cfc8(data_ov004_022585ac), 0, 0);
    func_ov004_0222fef4(self);
    func_02063ddc(context);
    return 1;
}
