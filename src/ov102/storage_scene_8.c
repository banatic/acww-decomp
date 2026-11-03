/* storage_scene_8: 8 functions, module ov102
 * mwccarm 1.2/base -O4,s
 * func_ov102_0229e560 @ 0x0229e560, 0x58 bytes, Thumb
 * func_ov102_0229e55c @ 0x0229e55c, 0x4 bytes, Thumb
 * func_ov102_0229e558 @ 0x0229e558, 0x4 bytes, Thumb
 * func_ov102_0229e548 @ 0x0229e548, 0x10 bytes, Thumb
 * func_ov102_0229e4f4 @ 0x0229e4f4, 0x54 bytes, Thumb
 * func_ov102_0229e4d8 @ 0x0229e4d8, 0x1c bytes, Thumb
 * func_ov102_0229e458 @ 0x0229e458, 0x80 bytes, Thumb
 * func_ov102_0229e410 @ 0x0229e410, 0x48 bytes, Thumb
 */

struct UnkStruct_0229e458 {
    char pad_00[0xcc];
    int unk_CC;
    char pad_D0[0xb2c - 0xcc - 4];
    int unk_B2C;
    char pad_B30[0x24d0 - 0xb2c - 4];
    int unk_24D0;
};

typedef struct UnkStruct_0229e410 {
    char pad_00[0x24d0];
    int unk_24D0;
} UnkStruct_0229e410;

extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern void func_ov102_0229cb50(void *self);
extern int func_ov002_02207d24(void *self, int flag);
extern void func_ov102_0229c460(void *self, int flag);
extern void func_ov102_0229e0ec(void *self);
extern void func_ov102_0229e5b8(void *self);
extern void func_ov102_0229e0e4(void *self);
extern void func_020ee470(void *parameter0);
extern void func_ov102_0229dfa4(unsigned char *arg0);
extern void func_02002708(int);
extern void func_ov002_02207f20(int, int, int, int, int);
extern void func_ov002_02207e90(int, int);
extern void func_ov102_0229c298(int, int);
extern int func_ov002_02207f60(int);
extern void func_ov102_0229e050(void);
extern void func_ov102_0229e03c(void *);
extern void func_ov002_02208090(void *, int);
extern int func_ov102_0229df94(void *);
extern void func_ov094_0229ad20(void *);
extern void func_ov102_0229d0ec(void *);
extern void func_ov094_0229b2b0(void *);
extern void func_ov094_0229b794(void *, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f48(UnkStruct_0229e410 *p, int x);
extern void func_ov102_0229dff0(UnkStruct_0229e410 *p);

int func_ov102_0229e560(unsigned char *self)
{
    unsigned char *p;
    int v;

    func_0206f58c();
    if (func_0206f56c() == 0) {
        goto label_229e59a;
    }
    p = self + 0x8d;
    v = *p;
    if (v == 0 || v == 1 || v == 3) {
        func_ov102_0229cb50(self);
        func_ov002_02207d24(self + 0x218c, 0);
        func_ov102_0229c460(self, 0);
    }
label_229e59a:
    func_ov102_0229e0ec(self);
    func_ov102_0229e5b8(self);
    func_ov102_0229e0e4(self);
    return 1;
}

int func_ov102_0229e55c(void)
{
    return 1;
}

int func_ov102_0229e558(void)
{
    return 1;
}

int func_ov102_0229e548(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov102_0229e4f4(int r0)
{
    int r4 = r0;
    int sp0;
    int result;

    func_ov102_0229dfa4((unsigned char *) r0);
    sp0 = 0x30;
    func_ov002_02207f20(r4, 2, 0, 1, sp0);
    func_ov002_02207e90(r4, 0x90);
    func_ov102_0229c298(r4, 0x80);
    func_02002708(4);
    func_ov002_02207e80((void *) r4, 4, 0, 0);
    result = func_ov002_02207f60(r4);
    *(int *) ((char *) r4 + 0x24d4) = result;
}

void func_ov102_0229e4d8(void *p)
{
    func_ov102_0229e050();
    func_ov102_0229e03c(p);
    func_ov002_02208090(p, 1);
}

void func_ov102_0229e458(struct UnkStruct_0229e458 *ptr)
{
    func_ov102_0229df94(ptr);
    func_ov094_0229ad20(&ptr->unk_CC);
    func_ov102_0229d0ec(ptr);
    func_ov094_0229b2b0(&ptr->unk_B2C);
    func_ov094_0229b794(&ptr->unk_B2C, 0xf);
    func_ov002_02207f20((int) ptr, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(ptr, 6, 0, 0);
    func_ov002_02208090(ptr, 2);
    func_ov102_0229c298((int) ptr, 1);
    func_ov102_0229c298((int) ptr, 2);
    ptr->unk_24D0 = func_ov002_02207f60((int) ptr);
}

void func_ov102_0229e410(UnkStruct_0229e410 *p)
{
    int ret = func_ov002_02207f48(p, 0);
    func_ov002_02207e80(p, 6, 0LL, 0);
    p->unk_24D0 = func_ov002_02207f60((int) p);
    if (ret != 0) {
        func_ov102_0229dff0(p);
        func_ov102_0229e4f4((int) p);
        func_ov002_02208090((void *) p, 3);
    }
}
