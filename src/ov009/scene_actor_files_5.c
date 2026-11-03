/* scene_actor_files_5: 2 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_022655ac @ 0x022655ac, 0x16 bytes, Thumb
 * func_ov009_02265598 @ 0x02265598, 0x14 bytes, Thumb
 */

extern void *func_02107828(void *p0);
extern int NNS_G3dGetJntAnmSet(int);
extern int func_02107b44(int, int);

void *func_ov009_022655ac(void *a0)
{
    char *p = (char *) func_02107828(a0);
    return p + *(int *) (p + *(unsigned short *) (p + 0xe) + 0xc);
}

int func_ov009_02265598(int arg)
{
    return func_02107b44(NNS_G3dGetJntAnmSet(arg), 0);
}
