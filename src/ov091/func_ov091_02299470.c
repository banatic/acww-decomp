/* func_ov091_02299470 @ 0x02299470, 0x24 bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov091_02299064(int arg);
extern void func_ov002_02208090(int arg, int n);
extern unsigned char *func_ov002_022080a0(int arg, unsigned char value);
extern void func_020041fc(void);

int func_ov091_02299470(int arg)
{
    func_ov091_02299064(arg);
    func_ov002_02208090(arg, 0);
    func_ov002_022080a0(arg, 1);
    func_020041fc();
    return 1;
}
