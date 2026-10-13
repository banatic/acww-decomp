/* func_020f3140 @ 0x020f3140, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020f4220(void *p, int a, int b);
extern void func_020f41f4(void *p);
extern void func_020f4178(void *p);
extern void func_020f4130(void *p);
extern int func_020f4038(void *p);
extern int func_020eef70(int a);
extern void NNS_SndHeapSaveState(int a);

extern struct {
    char pad[0x62];
    char byte;
} data_021fd1bc;

void func_020f3140(void *p)
{
    func_020f4220(p, 0x232f4, 0x10);
    func_020f41f4(p);
    func_020f4178(p);
    func_020f4130(p);
    NNS_SndHeapSaveState(func_020eef70(func_020f4038(p)));
    data_021fd1bc.byte = 0;
}
