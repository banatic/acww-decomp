/* func_ov143_0229a5cc @ 0x0229a5cc, 0xb0 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229a5cc UnkStruct_0229a5cc;
struct UnkStruct_0229a5cc {
    unsigned char pad_00[0xa0];
    unsigned char *array; // 0xa0
    unsigned char unk_A4; // 0xa4
    unsigned char pad_A5[0xac - 0xa5];
};

extern unsigned short data_021fbe40; // 0x021fbe40
extern void *func_ov002_02208008(UnkStruct_0229a5cc *self);
extern int func_ov002_022088cc(void *p);
extern int func_ov002_022088bc(void *p);
extern unsigned char func_ov143_022997d8(UnkStruct_0229a5cc *self, unsigned char b);
extern unsigned char func_ov143_022997b0(UnkStruct_0229a5cc *self, unsigned char b);
extern void func_0206e9ac(unsigned char b);
extern int func_ov143_0229a0b0(UnkStruct_0229a5cc *self);
extern int func_ov143_0229a030(UnkStruct_0229a5cc *self);
extern void func_ov002_0220a0b4(void *s, int a, int b);
extern void func_ov143_0229a2e0(UnkStruct_0229a5cc *self);
extern void func_ov143_02299f48(UnkStruct_0229a5cc *self);

void func_ov143_0229a5cc(UnkStruct_0229a5cc *self)
{
    if (data_021fbe40 & 1) {
        void *p = func_ov002_02208008(self);
        if (p) {
            unsigned char r6 = self->unk_A4;
            unsigned char r4 = func_ov143_022997d8(self, self->array[r6]);
            unsigned char r7 = r4;

            if (func_ov002_022088cc(p)) {
                if (r4 < 15) {
                    r4 = (unsigned char) (r4 + 1);
                }
            } else if (func_ov002_022088bc(p)) {
                if (r4 != 0) {
                    r4 = (unsigned char) (r4 - 1);
                }
            }

            if (r4 != r7) {
                self->array[r6] = func_ov143_022997b0(self, r4);
                func_0206e9ac(self->array[r6]);
                {
                    int a = func_ov143_0229a0b0(self);
                    int b = func_ov143_0229a030(self);
                    func_ov002_0220a0b4((char *) self + 0xac, a, b);
                }
            }
        }
    } else {
        func_ov143_0229a2e0(self);
        func_ov143_02299f48(self);
    }
}
