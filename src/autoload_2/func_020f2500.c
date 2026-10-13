/* func_020f2500 @ 0x020f2500, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *p, void *q, int n);
extern void *func_020f4038(void *p);
extern void *func_020eef70(void *p);
extern void NNS_SndHeapSaveState(void *p);
#define gSource ((unsigned char *) 0x0002a824)
extern unsigned char data_021fd1bc[];

void func_020f2500(void *param)
{
    func_020f4220(param, gSource, 29);
    NNS_SndHeapSaveState(func_020eef70(func_020f4038(param)));
    data_021fd1bc[0x62] = 0;
}
