/* scene_standard_anims: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201b394 @ 0x0201b394, 0xe bytes, Thumb
 * func_0201b390 @ 0x0201b390, 0x2 bytes, Thumb
 * func_0201b38c @ 0x0201b38c, 0x4 bytes, Thumb
 * func_0201b388 @ 0x0201b388, 0x4 bytes, Thumb
 * func_0201b384 @ 0x0201b384, 0x4 bytes, Thumb
 * func_0201b380 @ 0x0201b380, 0x4 bytes, Thumb
 * func_0201b37c @ 0x0201b37c, 0x4 bytes, Thumb
 * func_0201b378 @ 0x0201b378, 0x4 bytes, Thumb
 */

void func_0201b394(int *p)
{
    p[0] = 0;
    p[1] = 1;
    p[2] = 2;
}

void func_0201b390(void *object) {}

void func_0201b38c(int *p0, int p1)
{
    p0[0] = p1;
}

void func_0201b388(int *p0, int p1)
{
    p0[1] = p1;
}

void func_0201b384(int *p0, int p1)
{
    p0[2] = p1;
}

int func_0201b380(int *p0)
{
    return p0[0];
}

int func_0201b37c(int *p0)
{
    return p0[1];
}

int func_0201b378(int *p0)
{
    return p0[2];
}
