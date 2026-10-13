/* func_020fa034 @ 0x020fa034, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eed18(void *arg, int value);
extern void NNS_SndHandleReleaseSeq(void *arg);

void func_020fa034(void *arg)
{
    func_020eed18(arg, 0);
    NNS_SndHandleReleaseSeq(arg);
}
