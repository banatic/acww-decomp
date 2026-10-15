/* func_ov120_0229bedc @ 0x0229bedc, 0xbc bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229bedc {
    unsigned char pad_00[0x94];
    unsigned int unk_94;
    unsigned short unk_98;
} UnkStruct_0229bedc;

extern void func_ov120_0229b97c(void);
extern void *func_020641c8(void *p);
extern void func_02064210(unsigned char *s, void *p);
extern void *func_020b496c(int a, void *p);
extern void *func_ov120_0229b400(UnkStruct_0229bedc *self);
extern void func_02070adc(void *p, int a, int b, int c, int d, int e, int f);
extern int func_0207094c(void *p, int a);
extern void func_02070a04(void *p, int a, int b);
extern void *func_020641b0(void *p);
extern void func_ov002_02207f20(UnkStruct_0229bedc *self, int a, int b, int c, int d);
extern void func_02002708(int a);
extern void func_ov002_02207e80(UnkStruct_0229bedc *self, int a, int b, int c);
extern void func_ov120_0229a438(UnkStruct_0229bedc *self, int a);
extern unsigned int func_ov002_02207f60(UnkStruct_0229bedc *self);
extern void func_ov002_02208090(UnkStruct_0229bedc *self, int a);
extern unsigned char data_021dc7aa[];

void func_ov120_0229bedc(UnkStruct_0229bedc *self)
{
    void *p;
    unsigned char local[0x20];

    func_ov120_0229b97c();
    func_020641c8(local);
    func_02064210(data_021dc7aa, local);
    func_020b496c(0, local);

    p = func_ov120_0229b400(self);
    func_02070adc(p, 8, 0x1ab, 0x12, 0xf, 0, 0);
    func_0207094c(p, 0xa9);
    func_02070a04(p, 1, 0);
    func_020641b0(local);

    func_ov002_02207f20(self, 0xa, 0, 0, 0x30);
    func_02002708(4);
    func_ov002_02207e80(self, 4, 0, 0);
    func_02002708(6);
    func_ov002_02207e80(self, 6, 0, 0x50 - self->unk_98);
    func_ov120_0229a438(self, 4);

    self->unk_94 = func_ov002_02207f60(self);
    func_ov002_02208090(self, 4);
}
