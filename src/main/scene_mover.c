/* scene_mover: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201af48 @ 0x0201af48, 0xe bytes, Thumb
 * func_0201af28 @ 0x0201af28, 0x20 bytes, Thumb
 * func_0201af24 @ 0x0201af24, 0x2 bytes, Thumb
 * func_0201af1c @ 0x0201af1c, 0x6 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[85];
    unsigned char unk_55;
} UnkStruct_0201af1c;

void func_0201af48(void *r0)
{
    unsigned int *p = (unsigned int *) r0;
    p[0x11] = p[0x0e];
    p[0x12] = p[0x0f];
    p[0x13] = p[0x10];
}

void func_0201af28(int *base, int index, int a, int b, int c)
{
    char *p;
    if (index < 1 || index >= 3) {
        return;
    }
    p = (char *) base + 12;
    p += index * 12;
    *(int *) p = a;
    *(int *) (p + 4) = b;
    *(int *) (p + 8) = c;
}

void *func_0201af24(void *object)
{
    return object;
}

void func_0201af1c(UnkStruct_0201af1c *p, unsigned char v)
{
    p->unk_55 = v;
}
