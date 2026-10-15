/* func_ov121_0229b214 @ 0x0229b214, 0x90 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern void func_ov121_0229a53c(void *p);
extern int func_ov002_02208014(void *receiver);
extern void func_ov121_0229a358(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern int func_ov002_02208008(void *p);
extern int func_ov002_02209044(void *p, int val, void *q, int zero);
extern void func_ov121_0229a294(void *p);
extern void func_ov002_0220a1dc(void *p);
extern void func_ov121_0229a230(void *p);

typedef struct {
    char pad_00[2];
    unsigned short flags;
} Glb;
extern Glb data_021fbe40;

void func_ov121_0229b214(void *p)
{
    if (func_0206f56c() != 0) {
        func_ov121_0229a53c(p);
        return;
    }
    if (func_ov002_02208014(p) != 0) {
        func_ov121_0229a358(p);
        func_ov002_02208098(p, 3);
        return;
    }
    {
        int tmp = func_ov002_02208008(p);
        if (func_ov002_02209044((char *) p + 0x528, tmp, (char *) p + 0xb3, 0) != 0) {
            func_ov121_0229a294(p);
            return;
        }
    }
    {
        unsigned short flags = data_021fbe40.flags;
        if (flags & 1) {
            func_ov002_0220a1dc((char *) p + 0x3a8);
            func_ov002_02208098(p, 0xd);
            return;
        }
        if (flags & 2) {
            func_ov121_0229a230(p);
        }
    }
}
