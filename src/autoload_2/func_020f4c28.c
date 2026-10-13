/* func_020f4c28 @ 0x020f4c28, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eed18(void *p, int n);
extern void NNS_SndHandleReleaseSeq(void *p);

void func_020f4c28(void *p)
{
    func_020eed18((char *) p + 4, 5);
    NNS_SndHandleReleaseSeq((char *) p + 4);
}
