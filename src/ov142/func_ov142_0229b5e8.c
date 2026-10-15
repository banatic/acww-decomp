/* func_ov142_0229b5e8 @ 0x0229b5e8, 0x88 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern void *func_ov002_02208008(void *p);
extern int func_ov142_02299c64(void *p, void *a);
extern void func_ov142_0229af4c(void *p);
extern void func_ov142_0229b278(void *p);
extern void func_ov142_0229aee8(void *p);
extern void func_ov142_0229af94(void *p);
extern void func_ov142_0229b10c(void *p);
extern int func_ov142_02299668(void *p, int a);
extern void func_ov142_0229b138(void *p);
extern unsigned short data_021fbe40[2];

void func_ov142_0229b5e8(void *p)
{
    if (func_ov002_02208014(p)) {
        func_ov142_0229b278(p);
        return;
    }

    if (func_ov142_02299c64(p, func_ov002_02208008(p))) {
        func_ov142_0229af4c(p);
        return;
    }

    {
        unsigned short flags = data_021fbe40[1];

        if ((flags & 1) != 0) {
            func_ov142_0229aee8(p);
            return;
        }

        if ((flags & 2) != 0) {
            func_ov142_0229af94(p);
            func_ov142_0229b10c(p);
            return;
        }

        if ((flags & 8) != 0) {
            if (func_ov142_02299668(p, 0x20)) {
                func_ov142_0229af94(p);
                func_ov142_0229b138(p);
            }
        }
    }
}
