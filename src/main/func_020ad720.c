/* func_020ad720 @ 0x020ad720, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void VEC_Normalize(void *a, void *b);

void func_020ad720(void *a, void *b)
{
    VEC_Normalize(a, b);
    VEC_Normalize((char *) a + 0xc, (char *) b + 0xc);
    VEC_Normalize((char *) a + 0x18, (char *) b + 0x18);
}
