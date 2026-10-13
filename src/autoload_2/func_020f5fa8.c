/* func_020f5fa8 @ 0x020f5fa8, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020f5e50(int, int);
extern int func_020f5e24(int);
extern int func_020f5c64(int, int);
extern void NNS_SndPlayerSetTrackVolume(int, int, int);
extern void func_0210b634(int, int, int);

void func_020f5fa8(int a, int b)
{
    int x;
    int y;
    y = func_020f5e24(func_020f5e50(b, 0));
    x = func_020f5c64(b, 0);
    NNS_SndPlayerSetTrackVolume(a, 15, y);
    func_0210b634(a, 15, x);
}
