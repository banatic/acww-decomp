/* scene_look: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201a824 @ 0x0201a824, 0x12 bytes, Thumb
 * func_0201a814 @ 0x0201a814, 0x10 bytes, Thumb
 * func_0201a7fc @ 0x0201a7fc, 0x16 bytes, Thumb
 */

struct func_0201a814_UnkStruct {
    char pad_00[0x28];
    short unk_28;
};

int func_0201a824(int r0, int r1)
{
    if (r0 < 0) {
        r0 = -r0;
    }
    if (r0 < r1) {
        return 1;
    }
    return 0;
}

int func_0201a814(struct func_0201a814_UnkStruct *s, int a)
{
    return func_0201a824(a, s->unk_28);
}

int func_0201a7fc(unsigned char *s)
{
    if (s[0x18] == 0) {
        s += 0x2a;
        if (*s == 1) {
            return 1;
        }
    }
    return 0;
}
