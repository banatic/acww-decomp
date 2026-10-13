/* func_020f3214 @ 0x020f3214, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(int, const char *, int);
extern void func_020f41f4(int);
extern void func_020f4178(int);
extern void func_020f4130(int);
extern void func_020f4038(int);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);

#define g_232f4 ((char *) 0x000232f4)
extern char data_021fd1bc[0x63];

void func_020f3214(int param)
{
    func_020f4220(param, g_232f4, 15);
    func_020f41f4(param);
    func_020f4178(param);
    func_020f4130(param);
    func_020f4038(param);
    func_020eef70();
    NNS_SndHeapSaveState();
    data_021fd1bc[0x62] = 0;
}
