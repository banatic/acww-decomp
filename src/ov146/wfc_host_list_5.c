/* wfc_host_list_5: 2 functions, module ov146
 * mwccarm 1.2/base -O4,s
 * func_ov146_0229b344 @ 0x0229b344, 0x1e bytes, Thumb
 * func_ov146_0229b328 @ 0x0229b328, 0x1a bytes, Thumb
 */

extern void func_ov146_0229acfc(void *);
extern unsigned char *func_ov002_022080a0(void *, unsigned char arg1);
extern int func_020ee45c(void *arg0);
extern void func_ov092_0229929c(void *);
extern void func_ov146_0229ace8(int arg);

int func_ov146_0229b344(void *self)
{
    func_ov146_0229acfc(self);
    ((unsigned char *) self)[0x8c] = 0;
    func_ov002_022080a0(self, 0);
    return 1;
}

int func_ov146_0229b328(int arg)
{
    func_ov092_0229929c((void *) func_020ee45c((void *) arg));
    func_ov146_0229ace8(arg);
    return 1;
}
