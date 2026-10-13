/* func_020f7d14 @ 0x020f7d14, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eed18(void *ptr, int val);
extern void NNS_SndHandleReleaseSeq(void *ptr);

void func_020f7d14(void *self)
{
    func_020eed18((char *) self + 4, 0);
    func_020eed18((char *) self + 8, 0);
    NNS_SndHandleReleaseSeq((char *) self + 4);
    NNS_SndHandleReleaseSeq((char *) self + 8);
}
