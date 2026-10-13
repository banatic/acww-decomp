/* func_ov004_02242df8 @ 0x02242df8, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

void func_ov004_02242df8(Vec3 *out, unsigned int k)
{
    switch (k) {
        case 0:
            out->x = 0x11e00;
            out->y = 0x800;
            out->z = 0xda00;
            break;
        case 1:
            out->x = 0x12300;
            out->y = 0x800;
            out->z = 0xf400;
            break;
        case 2:
            out->x = 0x13800;
            out->y = 0x800;
            out->z = 0xf600;
            break;
        case 3:
            out->x = 0x14100;
            out->y = 0x800;
            out->z = 0xe800;
            break;
        default:
            out->x = 0x14000;
            out->y = 0x800;
            out->z = 0xd900;
            break;
    }
}
