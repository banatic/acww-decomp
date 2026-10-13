/* func_ov009_02265598 @ 0x02265598, 0x14 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_G3dGetJntAnmSet(int);
extern int func_02107b44(int, int);

int func_ov009_02265598(int arg)
{
    return func_02107b44(NNS_G3dGetJntAnmSet(arg), 0);
}
