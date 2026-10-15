/* func_ov131_0229b274 @ 0x0229b274, 0x90 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void);
extern int func_ov002_02208008(void *p);
extern int func_ov130_0229a0a4(void *p, int a);
extern int func_ov130_02299d98(void *p);
extern void func_ov131_0229b10c(void *p);
extern void func_ov131_0229af74(void *p);
extern int func_ov131_0229b07c(void *p);
extern void func_ov131_0229afbc(void *p);
extern void func_ov131_0229af0c(void *p);
extern void func_ov131_0229b04c(void *p);

struct UnkStruct_0229b274 {
    char pad_00[2];
    unsigned short flags;
};
extern struct UnkStruct_0229b274 data_021fbe40;

void func_ov131_0229b274(void *p)
{
    unsigned short flags;

    if (func_ov002_02208014() != 0) {
        func_ov131_0229b10c(p);
        return;
    }

    if (func_ov130_0229a0a4((void *) ((char *) p + 0x2c4), func_ov002_02208008(p)) != 0) {
        func_ov131_0229af74(p);
        return;
    }

    flags = data_021fbe40.flags;
    if (flags & 8) {
        if (func_ov131_0229b07c(p) != 0) {
            func_ov131_0229afbc(p);
        }
        return;
    }
    if (flags & 1) {
        func_ov131_0229af0c(p);
        return;
    }
    if (flags & 2) {
        if (func_ov130_02299d98((void *) ((char *) p + 0x2c4)) == 0) {
            func_ov131_0229afbc(p);
            func_ov131_0229b04c(p);
        }
        return;
    }
}
