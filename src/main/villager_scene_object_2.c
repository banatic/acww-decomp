/* villager_scene_object_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202e194 @ 0x0202e194, 0xc bytes, Thumb
 * func_0202e188 @ 0x0202e188, 0xc bytes, Thumb
 * func_0202e174 @ 0x0202e174, 0x14 bytes, Thumb
 */

void func_0202e194(unsigned char *ptr)
{
    ptr[0x838] = 1;
}

void func_0202e188(unsigned char *r0)
{
    unsigned char r2 = 0;
    unsigned int r1 = 0x00000838;
    r0[r1] = r2;
}

int func_0202e174(unsigned char *arg0)
{
    if (arg0[0x838] != 0) {
        return 1;
    }
    return 0;
}
