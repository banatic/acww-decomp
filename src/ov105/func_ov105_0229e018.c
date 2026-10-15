/* func_ov105_0229e018 @ 0x0229e018, 0x58 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov094_022999d8(void);
extern void func_ov105_0229d17c(void *);
extern int func_ov105_0229d650(void *, int arg1);
extern void func_ov105_0229d230(void *);
extern void func_ov105_0229d870(void *, int, int);

void func_ov105_0229e018(unsigned char *p)
{
    if (func_ov002_02209f9c(p + 0x24a4) == 0) {
        unsigned char bc = p[0x2bc];
        unsigned char ba = p[0x2ba];
        if (ba == bc) {
            func_ov105_0229d650(p, bc);
            func_ov105_0229d230(p);
            func_ov002_02208098(p, 7);
            func_ov094_022999d8();
        } else {
            func_ov105_0229d870(p, bc, 4);
        }
    } else {
        func_ov105_0229d17c(p);
    }
}
