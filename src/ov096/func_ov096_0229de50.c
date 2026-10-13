/* func_ov096_0229de50 @ 0x0229de50, 0x54 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ad4(void *p);
extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char c);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a374(void *p, int a);

void func_ov096_0229de50(char *base)
{
    int result2;
    int result3;

    ((unsigned char *) (base + 0xbc))[0] = (unsigned char) (func_ov002_02208ad4(base + 0x2564) - 1);
    result2 = func_ov002_02208ae4(base + 0x2564);
    result3 = func_ov002_02208ad8(base + 0x2564, *(unsigned char *) (base + 0xbc));
    func_ov002_0220a0b4(base + 0x2500, result2, result3);
    func_ov002_0220a374(base + 0x2500, 7);
}
