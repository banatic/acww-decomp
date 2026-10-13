/* func_020f3490 @ 0x020f3490, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *p, unsigned int arg1, unsigned int arg2);
extern void func_020f41f4(void *p);
extern void func_020f4178(void *p);
extern void func_020f4130(void *p);
extern void func_020f4038(void *p);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);
extern unsigned char data_021fd1bc[];

void func_020f3490(void *p)
{
    func_020f4220(p, 0x232f4, 0xc);
    func_020f41f4(p);
    func_020f4178(p);
    func_020f4130(p);
    func_020f4038(p);
    func_020eef70();
    NNS_SndHeapSaveState();
    data_021fd1bc[0x62] = 0;
}
