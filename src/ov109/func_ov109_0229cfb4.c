/* func_ov109_0229cfb4 @ 0x0229cfb4, 0x44 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229cfb4 {
    char pad_00[0x2274];
    char flag_2274;
    char pad_2275[0x29d3 - 0x2275];
    unsigned char byte_d3;
    char pad_29D4[2];
    unsigned char byte_d6;
};

extern int func_ov002_02209f64(void *);
extern unsigned char *func_ov002_02208098(struct UnkStruct_0229cfb4 *, unsigned char);
extern void func_ov109_0229c9f0(struct UnkStruct_0229cfb4 *object, unsigned int index);
extern void func_ov109_0229d7b4(struct UnkStruct_0229cfb4 *);

void func_ov109_0229cfb4(struct UnkStruct_0229cfb4 *self)
{
    if (func_ov002_02209f64(&self->flag_2274) != 0) {
        return;
    }
    func_ov002_02208098(self, self->byte_d6);
    if (self->byte_d6 == 5) {
        func_ov109_0229c9f0(self, self->byte_d3);
    }
    func_ov109_0229d7b4(self);
}
