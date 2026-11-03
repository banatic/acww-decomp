/* scene_value_3aa: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201b370 @ 0x0201b370, 0x8 bytes, Thumb
 * func_0201b354 @ 0x0201b354, 0x1c bytes, Thumb
 * func_0201b350 @ 0x0201b350, 0x4 bytes, Thumb
 */

void func_0201b370(unsigned short *p0)
{
    p0[0] = 0;
    p0[1] = 0;
}

int func_0201b354(unsigned short *ptr)
{
    int result = 2;
    unsigned short v = *ptr;
    if (v < 100) {
        result = 0;
    } else if (v < 800) {
        result = 1;
    }
    return result;
}

void func_0201b350(unsigned short *p0, int p1)
{
    p0[1] = p1;
}
