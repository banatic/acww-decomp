/* func_ov076_02279034 @ 0x02279034, 0x58 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern void func_02019c20(void *a, int b, int c, int d, int e, int f);
extern void func_0201addc(void *a);
extern void func_0201aff4(void *a);

int func_ov076_02279034(void *p)
{
    func_02019c20((char *) p + 0x564, 1, 0xfa, 0, 0, 0);
    func_0201addc((char *) p + 0x3b0);
    *(unsigned short *) ((char *) p + 0x8e) = 0;
    *(unsigned short *) ((char *) p + 0x94) = 0;
    func_0201aff4((char *) p + 0x350);
    *(unsigned int *) ((char *) p + 0x64) += 0x4000;
    return 1;
}
