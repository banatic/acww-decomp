/* func_ov118_0229be8c @ 0x0229be8c, 0xb0 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_021fbe94;

extern const u8 data_ov118_0229ccb8[];
extern const u8 data_ov118_0229ccd0[];
extern const u8 data_ov118_0229cce8[];
extern const u8 data_ov118_0229cd00[];
extern const u8 data_ov118_0229cd18[];

extern void func_02002d14(const void *a0, void *a1, int a2, int a3, int a4, int a5);
extern void func_02002c6c(const void *a0, void *a1, int a2, int a3, int a4, int a5);
extern void func_02064af4(const void *src, void *dst, int size);
extern void func_02002b40(void *buf, int val, int size, int flag);
extern void func_0206fdd4(void *buf, int a, int b, int c, int d, int e);

typedef struct {
    u8 pad_00[0x724];
    u8 region1[0x800];
    u8 pad_F24[0x1000];
    u8 region2[0x800];
} OverlayStruct;

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
