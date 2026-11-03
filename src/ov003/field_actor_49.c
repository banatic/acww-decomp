/* field_actor_49: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02217c3c @ 0x02217c3c, 0x20 bytes, Thumb
 * func_ov003_02217c14 @ 0x02217c14, 0x28 bytes, Thumb
 * func_ov003_02217bf0 @ 0x02217bf0, 0x24 bytes, Thumb
 */

struct UnkStruct_02217c3c {
    int a;
    int b;
    int c;
    int d;
    short e;
    char unk_12;
};

extern void func_020779b8(char *ptr, int a, int b);
extern void func_02077910(char *ptr, short val);
extern void func_02077978(unsigned char *a, int c, int d);
extern int func_020778f8(unsigned char *a);

void func_ov003_02217c3c(struct UnkStruct_02217c3c *out, int a, int b, int c, int d, short e, int f)
{
    out->a = a;
    out->unk_12 = (char) b;
    out->b = c;
    out->c = d;
    out->e = e;
    out->d = f;
}

void func_ov003_02217c14(char *ptr, char byte, int a, int b, short c)
{
    ptr[7] = byte;
    func_020779b8(ptr, a, b);
    func_02077910(ptr + 5, c);
}

void func_ov003_02217bf0(unsigned char *a, unsigned char *b, int c, int d, unsigned short *e)
{
    *b = a[7];
    func_02077978(a, c, d);
    *e = func_020778f8(a + 5);
}
