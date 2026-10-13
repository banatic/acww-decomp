/* func_ov003_02227680 @ 0x02227680, 0xf8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
} UnkStruct_02227680;

typedef struct {
    int unk_00;
    int unk_04;
    char unk_08[0x50];
    UnkStruct_02227680 a;
    char pad_B8[0x64];
    int unk_11C;
} UnkStruct_02227680_2;

extern void *data_ov003_0223bdb0;
extern void *data_ov003_0223bdb4;
extern void *data_ov003_0223bdbc;

extern void *func_0209d238(void *p, int *q);
extern int func_0209d0ac(void *p, void *h, void *g);
extern void *func_0209d088(void *p);
extern void func_02055f2c(UnkStruct_02227680 *a, void *x, int f);
extern void *func_0209d324(void *h);
extern void *func_02064b2c(void *g, void *m, int n, int f);
extern void *NNS_G3dGetJntAnmSet(void *p);
extern void *func_02107b44(void *p, int i);
extern int func_02055140(UnkStruct_02227680 *a, void *m);
extern void func_02055060(UnkStruct_02227680 *a, void *p, int b, int c, int d, int e);
extern void func_02055050(UnkStruct_02227680 *a);
extern void *NNS_G3dGetTexSRTAnmSet(void *p);
extern void *func_02107bbc(void *p, int i);
extern int func_0205650c(int *p, int q, void *m);
extern void func_02056478(int *p, void *q, int b, int c, int d);
extern void *func_02055e00(UnkStruct_02227680 *a);
extern void func_020563dc(int *p, void *q);

int func_ov003_02227680(UnkStruct_02227680_2 *self, void *p1)
{
    int ok;
    void *h;
    void *m;
    void *j;
    UnkStruct_02227680 *a;
    char *p8;

    ok = 0;
    h = func_0209d238(p1, &self->unk_04);
    p8 = self->unk_08;
    if (func_0209d0ac(p8, h, data_ov003_0223bdb0) != 0) {
        a = &self->a;
        func_02055f2c(a, func_0209d088(p8), 0);
        m = func_0209d324(h);
        j = func_02107b44(NNS_G3dGetJntAnmSet(func_02064b2c(data_ov003_0223bdb4, m, 4, 0)), 0);
        if (func_02055140(a, m) != 0) {
            func_02055060(a, j, 0, 0x1000, 1, 0);
            func_02055050(a);
        } else {
            return 0;
        }
        j = func_02107bbc(NNS_G3dGetTexSRTAnmSet(func_02064b2c(data_ov003_0223bdbc, m, 4, 0)), 0);
        if (func_0205650c(&self->unk_11C, a->unk_5C, m) != 0) {
            func_02056478(&self->unk_11C, j, 0, 0x1000, 1);
            func_020563dc(&self->unk_11C, func_02055e00(a));
        } else {
            return 0;
        }
        ok = 1;
    }
    return ok;
}
