/* func_ov122_022a2474 @ 0x022a2474, 0x26 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

#pragma arm
extern int func_020ee45c(int arg);
#pragma thumb

extern unsigned char func_ov090_0229936c(int arg);
extern void func_ov090_022990d0(int arg);
extern void func_ov122_022a18c4(int arg);

int func_ov122_022a2474(int arg)
{
    int x = func_020ee45c(arg);
    func_ov090_0229936c(x);
    func_ov090_022990d0(x);
    func_ov122_022a18c4(arg);
    return 1;
}
