/* func_ov105_0229dfd0 @ 0x0229dfd0, 0x48 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f70(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov105_0229d094(void *p, unsigned char b);
extern void func_ov105_0229c330(void *p, int x);
extern void func_ov105_0229d230(void *p);

void func_ov105_0229dfd0(void *p)
{
    if (func_ov002_02209f70((char *) p + 0x24A4) == 0) {
        func_ov105_0229d094(p, *(unsigned char *) ((char *) p + 0x2BC));
        func_ov105_0229c330(p, 0x40);
        func_ov002_02208098(p, 0x14);
        func_ov105_0229d230(p);
    } else {
        func_ov002_02208098(p, 7);
    }
}
