/* func_ov118_0229aad8 @ 0x0229aad8, 0x8c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov118_0229a460(void *, int);
extern void func_ov118_0229a440(void *, int);
extern void func_ov118_0229a450(void *, int);
extern void func_ov118_0229af64(void *, int);

typedef struct {
    unsigned char pad_00[0xa8];
    unsigned char a8;
    unsigned char pad_A9;
    unsigned char aa;
} UnkStruct_0229aad8;

void func_ov118_0229aad8(UnkStruct_0229aad8 *self)
{
    if (func_ov118_0229a460(self, 0x40) != 0) {
        if (self->a8 != 0) {
            self->a8--;
        }
        if (self->a8 == 0) {
            if (func_ov118_0229a460(self, 0x200) != 0) {
                func_ov118_0229a440(self, 0x100);
            } else {
                func_ov118_0229af64(self, self->aa);
            }
            self->a8 = 0x0F;
        } else if (self->a8 == 5) {
            if (func_ov118_0229a460(self, 0x200) != 0) {
                func_ov118_0229a450(self, 0x100);
            } else {
                func_ov118_0229af64(self, 0x0E);
            }
        }
    }
}
