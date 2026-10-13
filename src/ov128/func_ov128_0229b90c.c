/* func_ov128_0229b90c @ 0x0229b90c, 0xe4 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x2cdc];
    char unk_2CDC;
    char pad_2CDD[0x2d60 - 0x2cdd];
    int unk_2D60;
    int unk_2D64;
    char pad_2D68[0x2d6e - 0x2d68];
    u8 unk_2D6E;
    char pad_2D6F;
    u8 unk_2D70;
} UnkStruct_0229b90c;

extern void *func_020b1530(int a);
extern void func_02051bf8(u16 *buf, int n);
extern void func_02051c08(void *p, u16 *buf, int n);
extern int func_02051ca8(void *p, int n);
extern void func_020708e4(void *p, u16 *buf, int n);
extern int func_0207096c(void *p);
extern void func_02070adc(void *p, int a, int b, int c, int d, int e, int f);
extern void func_02070a04(void *p, int a, int b);

void func_ov128_0229b90c(UnkStruct_0229b90c *self)
{
    u16 buf[10];
    void *h;
    int n;

    if (self->unk_2D60 == -1) {
        self->unk_2D6E = 0;
    } else {
        self->unk_2D6E = 1;
        if (self->unk_2D60 != self->unk_2D64) {
            h = func_020b1530(self->unk_2D60);
            func_02051bf8(buf, 8);
            func_02051c08((char *) h + 0x1e, buf, 6);
            n = func_02051ca8((char *) h + 0x1e, 6);
            func_02051c08((char *) h + 0x1e, buf, n);
            buf[n] = 0xc790;
            buf[n + 1] = 0xb9ac;
            func_020708e4(&self->unk_2CDC, buf, n + 2);
            self->unk_2D70 = (func_0207096c(&self->unk_2CDC) + 7) >> 3;
            if (self->unk_2D70 < 2) {
                self->unk_2D70 = 2;
            }
            func_02070adc(&self->unk_2CDC, 8, 0xc6, self->unk_2D70, 0xf, 0, 0);
            func_02070a04(&self->unk_2CDC, 1, 0);
            self->unk_2D64 = self->unk_2D60;
        }
    }
}
