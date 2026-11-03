/* letter_storage_13: 2 functions, module ov105
 * mwccarm 1.2/base -O4,s
 * func_ov105_0229f740 @ 0x0229f740, 0x20 bytes, Thumb
 * func_ov105_0229f724 @ 0x0229f724, 0x1a bytes, Thumb
 */

extern void func_ov105_0229eb54(void *);
extern void func_ov002_02208090(void *, int);
extern unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern int func_020ee45c(void *arg0);
extern void func_ov092_0229929c(void *);
extern void func_ov105_0229eb08(void *);

int func_ov105_0229f740(void *arg)
{
    func_ov105_0229eb54(arg);
    func_ov002_02208090(arg, 0);
    func_ov002_022080a0(arg, 0);
    return 1;
}

int func_ov105_0229f724(void *p)
{
    func_ov092_0229929c((void *) func_020ee45c((void *) p));
    func_ov105_0229eb08(p);
    return 1;
}
