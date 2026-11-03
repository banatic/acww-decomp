/* bells_panel_5: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208bbbc @ 0x0208bbbc, 0x50 bytes, Thumb
 * func_0208bb8c @ 0x0208bb8c, 0x30 bytes, Thumb
 * func_0208bb58 @ 0x0208bb58, 0x34 bytes, Thumb
 * func_0208bad4 @ 0x0208bad4, 0x84 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    char pad_04[8];
    char sub_c[20];
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    int unk_38;
    char sub_3c[64];
    int unk_7C;
    unsigned char unk_80;
    unsigned char unk_81;
    unsigned char unk_82;
} UnkStruct_0208bbbc;

typedef struct {
    void *unk_00;
    char pad_04[8];
    char unk_0C[0x30];
    char unk_3C;
} UnkStruct_0208bb8c;

typedef struct UnkStruct_0208bad4 UnkStruct_0208bad4;

struct UnkStruct_0208bad4 {
    char pad_00[0xc];
    char sub[0x14];
    int unk_20;
    int unk_24;
    int unk_28;
};

extern void func_0208af30(UnkStruct_0208bbbc *obj);
extern void func_0208a1f8(char *p);
extern void *func_020b5630(char *p);
extern unsigned char data_020e21fc[];
extern void func_0208ba10(void *obj);
extern void *func_020b5618(void *p);
extern void func_0208a1f4(void *p);
extern void func_0208af00(void *obj);
extern void func_020edb3c(void *self);
extern void *func_0208a1d0(void *);
extern int func_0208aef0(UnkStruct_0208bad4 *);
extern int func_0208a1b0(void *, int);
extern int func_0208aeec(UnkStruct_0208bad4 *);
extern int func_0208a198(void *, int);
extern void func_02088df8(int, void *, int, int, int, int, int, int, int, int, int, int);

UnkStruct_0208bbbc *func_0208bbbc(UnkStruct_0208bbbc *obj)
{
    char *p;
    func_0208af30(obj);
    obj->unk_00 = (void *) data_020e21fc;
    p = (char *) obj;
    p += 0xc;
    func_0208a1f8(p);
    obj->unk_20 = 0;
    obj->unk_24 = 0;
    obj->unk_28 = 0;
    obj->unk_2C = 0;
    obj->unk_30 = 0;
    obj->unk_34 = -1;
    obj->unk_38 = 0;
    p = (char *) obj;
    p += 0x3c;
    func_020b5630(p);
    obj->unk_7C = 0;
    p = (char *) obj;
    p += 0x80;
    *p = 0;
    p = (char *) obj;
    p += 0x81;
    *p = 0;
    p = (char *) obj;
    p += 0x82;
    *p = 0;
    return obj;
}

UnkStruct_0208bb8c *func_0208bb8c(UnkStruct_0208bb8c *obj)
{
    obj->unk_00 = ((char *) data_020e21fc);
    func_0208ba10(obj);
    func_020b5618(&obj->unk_3C);
    func_0208a1f4(&obj->unk_0C);
    func_0208af00(obj);
    return obj;
}

void *func_0208bb58(void *self)
{
    *(void **) self = ((char *) data_020e21fc);
    func_0208ba10(self);
    func_020b5618((char *) self + 0x3c);
    func_0208a1f4((char *) self + 0xc);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}

void func_0208bad4(UnkStruct_0208bad4 *p)
{
    void *v;
    int sum1;
    int shifted;
    int total;

    if (p->unk_20 == 0) {
        return;
    }
    v = func_0208a1d0(p->sub);
    if (v == 0) {
        return;
    }
    sum1 = func_0208aef0(p) + func_0208a1b0(p->sub, -1);
    shifted = (p->unk_28 + 0x800) >> 12;
    total = func_0208aeec(p) + func_0208a198(p->sub, -1) + p->unk_24 + shifted;
    func_02088df8(0, v, sum1, total, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
}
