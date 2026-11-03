/* scene_face_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201a7b4 @ 0x0201a7b4, 0x4 bytes, Thumb
 * func_0201a798 @ 0x0201a798, 0x1c bytes, Thumb
 */

extern int func_020644cc(int);

int func_0201a7b4(int *p0)
{
    return p0[1];
}

int func_0201a798(void)
{
    return (func_020644cc(4) & 1) ? 0 : 1;
}
