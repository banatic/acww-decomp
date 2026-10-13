/* func_ov147_022996b4 @ 0x022996b4, 0xc8 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x40];
    void *unk_40;
} UnkStruct_022996b4;

typedef struct {
    int b[8];
} UnkStruct_022996b4_2;

extern char data_021dc7bc[];

extern void *func_0206837c(void *h);
extern void func_02068388(void *h, int a);
extern void func_020ab5e4(void *g);
extern int func_020988a4(char *t, int i);
extern void func_02094fd4(UnkStruct_022996b4_2 *c);
extern void func_02094fbc(UnkStruct_022996b4_2 *c);
extern void *func_02098844(char *t, int i);
extern void *func_02099870(void *p);
extern void func_02095074(void *p, UnkStruct_022996b4_2 *c);
extern void *func_020ab550(void *g, int n);
extern void func_020ab76c(void *e, u8 *p);
extern void func_020ab778(void *e, u8 *p);
extern void *func_020ab798(void *e);
extern void func_020a8bb8(void *h, UnkStruct_022996b4_2 *c);
extern void *func_020ab39c(int a);
extern void func_020ab774(void *e, void *p);
extern void func_020ab71c(void *e);
extern void func_020ab4bc(void *g, int n);
extern void func_020ab4a8(void *g);

void func_ov147_022996b4(UnkStruct_022996b4 *self)
{
    u8 b[3];
    UnkStruct_022996b4_2 ctx;
    void *h0;
    void *g;
    void *e;
    void *e2;
    int n;
    int i;

    h0 = self->unk_40;
    g = func_0206837c(h0);
    func_020ab5e4(g);
    n = 0;
    for (i = 0; i < 4; i++) {
        if (func_020988a4(data_021dc7bc, i) != 0) {
            func_02094fd4(&ctx);
            func_02095074(func_02099870(func_02098844(data_021dc7bc, i)), &ctx);
            e = func_020ab550(g, n);
            b[0] = 4;
            func_020ab76c(e, &b[0]);
            func_020a8bb8(func_020ab798(e), &ctx);
            n++;
            func_02094fbc(&ctx);
        }
    }
    e2 = func_020ab550(g, n);
    b[1] = 0x10;
    func_020ab778(e2, &b[1]);
    func_020ab774(e2, func_020ab39c(1));
    b[2] = 0;
    func_020ab76c(e2, &b[2]);
    func_020ab71c(e2);
    func_020ab4bc(g, n + 1);
    func_020ab4a8(g);
    func_02068388(h0, 1);
}
