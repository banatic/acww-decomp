/* func_ov142_0229b4cc @ 0x0229b4cc, 0x32 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229b4cc {
    char pad_00[0xc0];
    unsigned char unk_C0;
    char pad_C1[0xe8 - 0xc1];
    int unk_E8;
};

extern int func_0208e484(void *ptr);
extern int func_ov142_0229a298(void *self, unsigned char byte);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov142_0229aec4(void *self);

void func_ov142_0229b4cc(struct UnkStruct_0229b4cc *p)
{
    if (func_0208e484(&p->unk_E8)) {
        if (func_ov142_0229a298(p, p->unk_C0) == 0) {
            func_ov002_02208098((void *) (p), 4);
            func_ov142_0229aec4(p);
        }
    }
}
