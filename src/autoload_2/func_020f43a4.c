/* func_020f43a4 @ 0x020f43a4, 0x54 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void func_020f5988(void);
extern int func_020eef70(void);
extern int func_020ef008(char *, int);
extern void NNS_SndHeapLoadState(int, int);
extern void func_020f2338(void *receiver);
extern char data_021fd054[];
extern unsigned char data_021fd1bc[];

void func_020f43a4(void *receiver)
{
    int v;

    func_020f5988();
    v = func_020eef70();
    func_020ef008(data_021fd054, 1);
    if (data_021fd1bc[0x62] != 0) {
        return;
    }
    NNS_SndHeapLoadState(v, 1);
    func_020f2338(data_021fd1bc);
}
