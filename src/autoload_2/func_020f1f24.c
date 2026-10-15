/* func_020f1f24 @ 0x020f1f24, 0x90 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020eedb8(unsigned short a, unsigned short b, void *c);
extern void NNS_SndPlayerSetVolume(void *a, int b);
extern void func_020f12cc(void *a, int b);

void func_020f1f24(void *ptr, int n)
{
    func_020eedb8((unsigned short) (n % 1000), (unsigned short) (n / 1000), (char *) ptr + 0x38);
    if (n == 0x862) {
        NNS_SndPlayerSetVolume((char *) ptr + 0x38, 0);
    }
    func_020f12cc(ptr, 1);
}
