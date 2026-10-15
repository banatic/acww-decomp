/* func_ov147_0229a374 @ 0x0229a374, 0x2c bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001b34(int);
extern int func_02001b60(void);

void func_ov147_0229a374(void)
{
    unsigned int v;
    unsigned int *p;
    int val;

    val = ((void) (func_02001b34(8)), func_02001b60());
    p = (unsigned int *) 0x04000000;
    v = *p & 0xffffe0ff;
    v |= (val << 8);
    *p = v;
}
