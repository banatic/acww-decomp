/* map_menu_scene: 7 functions, module ov118
 * mwccarm 1.2/base -O4,s
 * func_ov118_0229bf70 @ 0x0229bf70, 0x8 bytes, Thumb
 * func_ov118_0229bf3c @ 0x0229bf3c, 0x32 bytes, Thumb
 * func_ov118_0229be8c @ 0x0229be8c, 0xb0 bytes, Thumb
 * func_ov118_0229be6c @ 0x0229be6c, 0x20 bytes, Thumb
 * func_ov118_0229be54 @ 0x0229be54, 0x16 bytes, Thumb
 * func_ov118_0229be04 @ 0x0229be04, 0x50 bytes, Thumb
 * func_ov118_0229bda4 @ 0x0229bda4, 0x60 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x724];
    u8 region1[0x800];
    u8 pad_F24[0x1000];
    u8 region2[0x800];
} OverlayStruct;

extern void func_ov118_0229bfa4(void *parameter0);
extern void func_020029e8(int a, int b);
extern void func_020028bc(int a, int b, int c, int d);
extern void *data_021fbe94;
extern const u8 data_ov118_0229ccb8[];
extern const u8 data_ov118_0229ccd0[];
extern const u8 data_ov118_0229cce8[];
extern const u8 data_ov118_0229cd00[];
extern const u8 data_ov118_0229cd18[];
extern int func_02002d14(const void *a0, void *a1, int a2, int a3, int a4, int a5);
extern int func_02002c6c(const void *a0, void *a1, int a2, int a3, int a4, int a5);
extern int func_02064af4(const void *src, void *dst, int size);
extern int func_02002b40(void *buf, int val, int size, int flag);
extern void func_0206fdd4(void *buf, int a, int b, int c, int d, int e);
extern void func_ov117_02299a18(void);
extern void func_ov117_022999fc(int param1);
extern void func_ov117_022999e0(int param1);
extern void func_ov117_0229a2c8(char *);
extern void func_ov117_022999a0(char *, char *);
extern int func_02002a88(char *, int, int, int, int);
extern void func_ov118_0229b120(char *, char *);
extern unsigned char data_ov118_0229cc68[];
extern unsigned char data_ov118_0229cc80[];
extern unsigned char data_ov118_0229cc9c[];

void func_ov118_0229bf70(void *arg0)
{
    func_ov118_0229bfa4((void *) arg0);
}

void func_ov118_0229bf3c(void)
{
    func_020029e8(4, 2);
    func_020029e8(6, 2);
    func_020028bc(4, 0, 0, 0);
    func_020028bc(6, 0, 0, 0);
}

void func_ov118_0229be8c(OverlayStruct *self)
{
    void *obj = data_021fbe94;
    func_02002d14(data_ov118_0229ccb8, obj, 4, 1, 1, 0xf);
    func_02002c6c(data_ov118_0229ccd0, obj, 4, 0x11, 0x11, 0x5f);
    func_02002c6c(data_ov118_0229cce8, obj, 4, 0x230, 0x230, 0x25f);
    func_02064af4(data_ov118_0229cd00, self->region1, 0x800);
    func_02002b40(self->region1, 4, 0x800, 0);
    func_02064af4(data_ov118_0229cd18, self->region2, 0x800);
    func_0206fdd4(self->region2, 0x13, 0, 0x1c, 1, 4);
}

void func_ov118_0229be6c(void)
{
    func_ov117_02299a18();
    func_ov117_022999fc(0);
    func_ov117_022999e0(0);
    func_ov117_022999e0(1);
}

void func_ov118_0229be54(void)
{
    func_ov117_022999fc(1);
    func_ov117_022999fc(2);
}

void func_ov118_0229be04(char *p)
{
    char *p1;
    char *p2;
    func_ov117_022999fc(3);
    p1 = p + 0x2724;
    func_ov117_0229a2c8(p + 0x4724);
    p2 = p + 0x4724;
    func_ov117_022999a0(p1, p2);
    func_02002a88(p1, 4, 0x60, 0x60, 0x15f);
    func_ov118_0229b120(p, p2);
}

void func_ov118_0229bda4(void)
{
    void *ptr = data_021fbe94;
    func_02002d14((const void *) ((void *) data_ov118_0229cc68), ptr, 8, 6, 6, 0xe);
    func_02002c6c((const void *) ((void *) data_ov118_0229cc80), ptr, 8, 0xc0, 0xc0, 0xff);
    func_02002c6c((const void *) ((void *) data_ov118_0229cc9c), ptr, 8, 0x180, 0x180, 0x1ff);
}
