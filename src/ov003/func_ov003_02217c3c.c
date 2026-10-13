/* func_ov003_02217c3c @ 0x02217c3c, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02217c3c {
    int a;
    int b;
    int c;
    int d;
    short e;
    char unk_12;
};

void func_ov003_02217c3c(struct UnkStruct_02217c3c *out, int a, int b, int c, int d, short e, int f)
{
    int *p = (int *) &d - 4;
    out->a = a;
    out->unk_12 = (char) b;
    out->b = c;
    out->c = d;
    out->e = *((short *) ((char *) p + 20));
    out->d = f;
}
