/* button_panel_2: 2 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_0220af94 @ 0x0220af94, 0x14 bytes, Thumb
 * func_ov002_0220af74 @ 0x0220af74, 0x1e bytes, Thumb
 */

extern void *data_ov002_0220ba58;
extern void GXS_LoadOBJPltt(void *a, int b, int c); // GXS_LoadOBJPltt
extern void func_ov002_0220b290(void *p);

void func_ov002_0220af94(void *receiver)
{
    GXS_LoadOBJPltt(&data_ov002_0220ba58, 0x1c, 4);
}

void func_ov002_0220af74(void *self)
{
    int i;
    char *base;
    for (i = 0, base = (char *) self + 4; i < 2; i++) {
        func_ov002_0220b290(base + i * 0x7c);
    }
}
