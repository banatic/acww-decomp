/* func_020f7c1c @ 0x020f7c1c, 0x94 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void NNS_SndPlayerSetVolume(void *player, int vol);
extern void func_0210b634(void *player, int a2, int a3);
extern int func_020f5e50(int a1, int a2);
extern int func_020f5e24(int a1);
extern int func_020f5c64(int a1, int a2);

void func_020f7c1c(char *ctx, int arg1)
{
    if (arg1 == 0) {
        NNS_SndPlayerSetVolume(ctx + 4, 0);
        NNS_SndPlayerSetVolume(ctx + 8, 0);
    } else {
        int vol = func_020f5e24(func_020f5e50(arg1, 0));
        int pan = func_020f5c64(arg1, 0);
        NNS_SndPlayerSetVolume(ctx + 4, vol);
        NNS_SndPlayerSetVolume(ctx + 8, vol);
        func_0210b634(ctx + 4, 0xf, pan);
        func_0210b634(ctx + 8, 0xf, pan);
    }
}
