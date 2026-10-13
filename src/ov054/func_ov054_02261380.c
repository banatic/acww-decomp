/* func_ov054_02261380 @ 0x02261380, 0xa8 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02261380 {
    unsigned char pad_00[0x1e];
    unsigned char b;
} UnkStruct_02261380;

extern int func_020984e8(void);
extern int func_02098a18(int);
extern unsigned char *func_02097e08(int);
extern void func_02015fb0(void *, int, int, int, int, int);
extern void func_02015ed0(void *, int, int);
extern void func_02015ea0(void *, int, int);
extern int func_020a12e8(void);
extern int func_020988a4(void *, int);
extern int func_020984d4(void);
extern void *func_02098844(void *, int);
extern void *func_02099870(void *);
extern void func_02015e40(void *, void *, int);
extern unsigned char data_021dc7bc[];

void func_ov054_02261380(UnkStruct_02261380 *self)
{
    if (self->b == 0xf) {
        unsigned char *p = func_02097e08(func_02098a18(func_020984e8()));
        unsigned char a = p[1];
        unsigned char b = p[0];
        func_02015fb0(self, p[2] + 0x7d0, 1, 4, 0, 0);
        func_02015ed0(self, a, 2);
        func_02015ea0(self, b, 3);
    }
    if (func_020a12e8() != 0) {
        switch (self->b) {
            case 0x24:
            case 0x25:
            case 0x26: {
                int j = 0;
                int i = j;
                for (; i < 4; i++) {
                    if (func_020988a4(data_021dc7bc, i) != 0 && i != func_020984d4()) {
                        func_02015e40(self, func_02099870(func_02098844(data_021dc7bc, i)), j + 2);
                        j++;
                    }
                }
                break;
            }
            default:
                break;
        }
    }
}
