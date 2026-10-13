/* func_020f4f80 @ 0x020f4f80, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fd234;
extern void func_020f4d00(int, void *);
extern void func_020eed18(void *, int);
extern void NNS_SndHandleReleaseSeq(void *);

void func_020f4f80(char *arg)
{
    func_020f4d00(data_021fd234, arg);
    func_020eed18(arg + 8, 5);
    NNS_SndHandleReleaseSeq(arg + 8);
}
