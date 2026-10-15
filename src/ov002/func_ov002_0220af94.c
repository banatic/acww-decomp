/* func_ov002_0220af94 @ 0x0220af94, 0x14 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov002_0220ba58;
extern void GXS_LoadOBJPltt(void *a, int b, int c); // GXS_LoadOBJPltt

void func_ov002_0220af94(void *receiver)
{
    GXS_LoadOBJPltt(&data_ov002_0220ba58, 0x1c, 4);
}
