/* func_ov118_0229afd4 @ 0x0229afd4, 0xb4 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa9];
    unsigned char b_a8;
    unsigned char b_a9;
} UnkStruct_0229afd4;

extern void func_ov118_0229aa98(UnkStruct_0229afd4 *self);
extern void func_ov118_0229aab4(UnkStruct_0229afd4 *self);
extern unsigned char func_ov118_0229aef8(UnkStruct_0229afd4 *self, unsigned int idx);
extern unsigned char func_ov118_0229ae90(UnkStruct_0229afd4 *self, unsigned int idx);
extern void func_ov118_0229a440(UnkStruct_0229afd4 *self, unsigned int val);
extern int func_ov118_0229a460(UnkStruct_0229afd4 *self, unsigned int val);
extern void func_ov118_0229b454(UnkStruct_0229afd4 *self);
extern void func_ov118_0229ae64(UnkStruct_0229afd4 *self);
extern void func_ov118_0229b43c(UnkStruct_0229afd4 *self);
extern void func_ov118_0229a450(UnkStruct_0229afd4 *self, unsigned int val);
extern void func_ov118_0229ae0c(UnkStruct_0229afd4 *self);
extern void func_ov118_0229af64(UnkStruct_0229afd4 *self, unsigned char val);

void func_ov118_0229afd4(UnkStruct_0229afd4 *self, unsigned int idx)
{
    if (idx == 0) {
        self->b_a8 = 0xe;
        self->b_a9 = 0xe;
        func_ov118_0229aa98(self);
        return;
    }
    func_ov118_0229aab4(self);
    self->b_a9 = func_ov118_0229aef8(self, idx);
    self->b_a8 = func_ov118_0229ae90(self, idx);
    if (idx >= 1 && idx < 0xf) {
        func_ov118_0229a440(self, 0x200);
        if (func_ov118_0229a460(self, 1)) {
            if (idx >= 1 && idx <= 9) {
                func_ov118_0229b454(self);
                func_ov118_0229ae64(self);
                return;
            }
        } else {
            if (idx < 1 || idx > 9) {
                func_ov118_0229b43c(self);
                func_ov118_0229ae64(self);
                return;
            }
        }
    } else {
        func_ov118_0229a450(self, 0x200);
    }
    func_ov118_0229ae0c(self);
    func_ov118_0229af64(self, 0xe);
    func_ov118_0229af64(self, self->b_a9);
}
