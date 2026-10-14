/* func_ov144_022995a0 @ 0x022995a0, 0x5c bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220ba0c(void *p);
extern void func_ov002_0220afdc(void *p);
extern void func_ov002_0220a5e4(void *p);
extern void func_ov002_02209cb4(void *p);
extern void func_ov002_0220826c(void *p);
extern void __cxa_vec_cleanup(void *p, int a, int b, void (*cb)(void));
extern void func_02070be8(void);
extern unsigned char data_ov144_0229b3f8;

typedef struct {
    void *vtbl;                  // 0x00
    unsigned char pad_04[192];   // 0x04
    unsigned char sub_c4;        // 0xc4
    unsigned char pad_C5[99];    // 0xc5
    unsigned char sub_128;       // 0x128
    unsigned char pad_129[71];   // 0x129
    unsigned char sub_170;       // 0x170
    unsigned char pad_171[459];  // 0x171
    unsigned char sub_33c;       // 0x33c
    unsigned char pad_33D[1043]; // 0x33d
    unsigned char sub_750;       // 0x750
} UnkStruct_022995a0;

void *func_ov144_022995a0(UnkStruct_022995a0 *self)
{
    self->vtbl = &data_ov144_0229b3f8;
    func_ov002_0220ba0c(&self->sub_750);
    __cxa_vec_cleanup(&self->sub_33c, 9, 0x6c, func_02070be8);
    func_ov002_0220afdc(&self->sub_170);
    func_ov002_0220a5e4(&self->sub_128);
    func_ov002_02209cb4(&self->sub_c4);
    func_ov002_0220826c(self);
    return self;
}
