/* func_ov118_0229be04 @ 0x0229be04, 0x50 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov117_022999fc(int);
extern void func_ov117_0229a2c8(char *);
extern void func_ov117_022999a0(char *, char *);
extern int func_02002a88(char *, int, int, int, int);
extern void func_ov118_0229b120(char *, char *);

void func_ov118_0229be04(char *p)
{
    char *p1;
    char *p2;
    func_ov117_022999fc(3);
    p1 = p + 0x2724;
    func_ov117_0229a2c8(p + 0x4724);
    p2 = p + 0x4724;
    func_ov117_022999a0(p1, p2);
    func_02002a88(p1, 4, 0x60, 0x60, 0x15f);
    func_ov118_0229b120(p, p2);
}
