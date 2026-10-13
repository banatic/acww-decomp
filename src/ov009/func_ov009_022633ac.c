/* func_ov009_022633ac @ 0x022633ac, 0x64 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b23ec(unsigned short a, int b);
extern void func_020b23c8(void);
extern void func_020b5e10(void);
extern void func_020b5e90(void);
extern void func_ov009_022639a0(void *p, int arg);

typedef struct {
    char pad_00[0x136];
    unsigned short unk_136;
    char pad_138[0x234 - 0x138];
    unsigned char unk_234;
} UnkStruct_022633ac;

void func_ov009_022633ac(UnkStruct_022633ac *self, unsigned int idx)
{
    switch (idx) {
        case 6:
            func_020b23ec(self->unk_136, 0);
            func_020b23c8();
            func_020b5e10();
            func_020b5e90();
            self->unk_234 = 1;
            break;
        case 0:
        case 1:
            func_ov009_022639a0(self, 1);
            break;
        case 8:
            func_ov009_022639a0(self, 0);
            break;
        default:
            break;
    }
}
