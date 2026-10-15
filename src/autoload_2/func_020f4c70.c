/* func_020f4c70 @ 0x020f4c70, 0x90 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020eedb8(int a, int b, void *c);
extern int func_020f5e50(void *a, int b);
extern int func_020f5e24(int argument0);
extern int func_020f5c64(void *a, int b);
extern void NNS_SndPlayerSetVolume(void *a, int b);
extern void func_0210b634(void *a, int b, int c);

void func_020f4c70(unsigned char *p0, int p1, void *p2)
{
    int rem;
    int saved;
    int b;

    rem = p1 % 1000;
    func_020eedb8((unsigned short) rem, 1, p0 + 12);

    saved = func_020f5e24((int) func_020f5e50(p2, 0));
    b = func_020f5c64(p2, 0);
    NNS_SndPlayerSetVolume(p0 + 12, saved);
    func_0210b634(p0 + 12, 0xff, b);
}
