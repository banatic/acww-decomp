/* func_ov103_0229d3b4 @ 0x0229d3b4, 0x7c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(char *p);
extern int func_ov002_02209044(char *p, int a, char *q, int b);
extern void func_ov103_0229c4fc(char *p);
extern void func_ov103_0229c720(char *p);
extern void func_ov002_0220a1dc(char *p);
extern unsigned char *func_ov002_02208098(char *p, unsigned char value);
extern unsigned short data_021fbe40[];

void func_ov103_0229d3b4(char *p)
{
    if (func_ov002_02208014(p)) {
        func_ov103_0229c4fc(p);
        return;
    }
    if (func_ov002_02209044(p + 0x22d8, func_ov002_02208008(p), p + 0x2da9, 0)) {
        func_ov103_0229c720(p);
        return;
    }
    if (data_021fbe40[1] & 1) {
        func_ov002_0220a1dc(p + 0x2274);
        func_ov002_02208098(p, 0xA);
        return;
    }
    if (data_021fbe40[1] & 2) {
        func_ov103_0229c4fc(p);
    }
}
