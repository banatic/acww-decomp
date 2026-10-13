/* func_ov105_0229df20 @ 0x0229df20, 0x5c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209d8c(void *);
extern int func_ov105_0229c340(void *, int);
extern void func_ov105_0229c320(void *, int);
extern void func_ov105_0229d154(void *);
extern void func_ov105_0229d0d4(void *, unsigned char);
extern void func_ov105_0229db14(void *);
extern void func_ov094_022999d8(void);

void func_ov105_0229df20(unsigned char *self)
{
    if (func_ov002_02209d8c(self + 0x248c) != 0) {
        if (func_ov105_0229c340(self, 0x2000) != 0) {
            func_ov105_0229c320(self, 0x2000);
            func_ov105_0229d154(self);
        } else {
            func_ov105_0229d0d4(self, self[0x2b7]);
            func_ov105_0229db14(self);
            func_ov094_022999d8();
        }
    } else {
        func_ov105_0229d154(self);
    }
}
