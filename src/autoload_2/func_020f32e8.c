/* func_020f32e8 @ 0x020f32e8, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

#define global_232f4 (*(char *) 0x000232f4)
extern char data_021fd1bc[];

extern void func_020f4220(void *p, void *q, int n);
extern void func_020f41f4(void *p);
extern void func_020f4178(void *p);
extern void func_020f4130(void *p);
extern void func_020f4038(void *p);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);

void func_020f32e8(void *p)
{
    func_020f4220(p, &global_232f4, 14);
    func_020f41f4(p);
    func_020f4178(p);
    func_020f4130(p);
    func_020f4038(p);
    func_020eef70();
    NNS_SndHeapSaveState();
    data_021fd1bc[0x62] = 0;
}
