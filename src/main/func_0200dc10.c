/* func_0200dc10 @ 0x0200dc10, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200dc48(void);
extern int func_02064558(int);

int func_0200dc10(int r0)
{
    int r4 = r0;
    int r0_2 = func_0200dc48();
    int r1 = *(short *) ((char *) r4 + 0x8e);
    r0_2 = r0_2 - r1;
    r0_2 = (r0_2 << 16) >> 16;
    return func_02064558(r0_2);
}
