/* func_020f2784 @ 0x020f2784, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *p, int a, int b);
extern int func_020f4038(void *p);
extern int func_020eef70(int x);
extern int NNS_SndHeapSaveState(int x);
extern void func_020f1004(void *p);

typedef struct {
    char pad_00[0x62];
    unsigned char unk_62;
} GlobalType;
extern GlobalType data_021fd1bc;

void func_020f2784(void *arg)
{
    func_020f4220(arg, 0, 0x1c);
    NNS_SndHeapSaveState(func_020eef70(func_020f4038(arg)));
    data_021fd1bc.unk_62 = 0;
    func_020f1004(&data_021fd1bc);
}
