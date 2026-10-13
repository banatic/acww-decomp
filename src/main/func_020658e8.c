/* func_020658e8 @ 0x020658e8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void VEC_Normalize(void *dst, void *src);

void func_020658e8(void *param0, void *param1)
{
    VEC_Normalize(param0, param1);
    VEC_Normalize((char *) param0 + 0xc, (char *) param1 + 0xc);
    VEC_Normalize((char *) param0 + 0x18, (char *) param1 + 0x18);
}
