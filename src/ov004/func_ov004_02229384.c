/* func_ov004_02229384 @ 0x02229384, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02229414(char *src, int *b, int *c, int *a);
extern void func_ov004_02229454(char *p, int *b, int *c, int *a, int p5, int p6);

void func_ov004_02229384(char *p1, int p2)
{
    int a, b, c;
    func_ov004_02229414(p1 + 0x8f0, &b, &c, &a);
    func_ov004_02229454(p1, &b, &c, &a, 6, p2);
}
