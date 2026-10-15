/* func_ov103_0229d1d4 @ 0x0229d1d4, 0x48 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f70(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov103_0229c8a4(void *p, unsigned char val);
extern void func_ov103_0229c2e4(void *p, int val);
extern void func_ov103_0229ca48(void *p);

void func_ov103_0229d1d4(void *p)
{
    if (func_ov002_02209f70((char *) p + 0x2274) == 0) {
        func_ov103_0229c8a4(p, *(unsigned char *) ((char *) p + 0x2da6));
        func_ov103_0229c2e4(p, 0x40);
        func_ov002_02208098(p, 0x12);
        func_ov103_0229ca48(p);
    } else {
        func_ov002_02208098(p, 5);
    }
}
