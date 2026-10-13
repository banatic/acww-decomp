/* func_ov118_0229c2a0 @ 0x0229c2a0, 0xbc bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov118_0229bda4(void *self);
extern void func_020641c8(void *obj);
extern void func_02064210(const void *str, void *obj);
extern void func_020b496c(int value, void *obj);
extern int func_ov118_0229b630(void *self);
extern void func_02070adc(int a, int b, int c, int d, int e, int f, int g);
extern void func_0207094c(int a, int b);
extern void func_02070a04(int a, int b, int c);
extern void func_020641b0(void *obj);
extern void func_ov002_02207f20(void *self, int a, int b, int c, int d);
extern void func_02002708(int n);
extern void func_ov002_02207e80(void *self, int a, int b, int c);
extern unsigned int func_ov002_02207f60(void *self);
extern void func_ov118_0229a450(void *self, int n);
extern void func_ov002_02208090(void *self, int n);

extern const char data_021dc7aa[];

typedef struct UnkStruct_0229c2a0 {
    unsigned char pad_00[0x94];
    unsigned int unk_94;
    unsigned short unk_98;
} UnkStruct_0229c2a0;

void func_ov118_0229c2a0(UnkStruct_0229c2a0 *self)
{
    char obj[0x20];
    int r;

    func_ov118_0229bda4(self);
    func_020641c8(obj);
    func_02064210(data_021dc7aa, obj);
    func_020b496c(0, obj);
    r = func_ov118_0229b630(self);
    func_02070adc(r, 8, 0x1ab, 0x12, 0xf, 0, 0);
    func_0207094c(r, 0xa9);
    func_02070a04(r, 1, 0);
    func_020641b0(obj);
    func_ov002_02207f20(self, 0xa, 3, 0, 0x30);
    func_02002708(4);
    func_ov002_02207e80(self, 4, 0, 0);
    func_02002708(6);
    func_ov002_02207e80(self, 6, 0, 0x50 - self->unk_98);
    func_ov118_0229a450(self, 4);
    self->unk_94 = func_ov002_02207f60(self);
    func_ov002_02208090(self, 6);
}
