/* func_0208ef7c @ 0x0208ef7c, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021d361c[];
extern unsigned char data_020d0b78[];
extern void DC_FlushRange(unsigned short *p, int a);
extern void GX_LoadOBJPltt(unsigned short *p, int a, int b);
extern void GXS_LoadOBJPltt(unsigned short *p, int a, int b);

struct Func0208ef7cStr {
    unsigned char pad_00[0x18];
    unsigned int index;
    unsigned char pad_1C[0x70 - 0x1C];
    unsigned short value;
    unsigned char pad_72[0x75 - 0x72];
    unsigned char flag;
};

void func_0208ef7c(struct Func0208ef7cStr *self)
{
    if (self->flag == 0) {
        if (self->value != data_021d361c[self->index]) {
            self->flag = 1;
        }
    }
    if (self->flag != 0) {
        unsigned int tmp = data_020d0b78[self->index] * 2;
        DC_FlushRange(&self->value, 2);
        GX_LoadOBJPltt(&self->value, tmp, 2);
        GXS_LoadOBJPltt(&self->value, tmp, 2);
        data_021d361c[self->index] = self->value;
        self->flag = 0;
    }
}
