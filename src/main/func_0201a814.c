/* func_0201a814 @ 0x0201a814, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201a824(int, int);

struct func_0201a814_UnkStruct {
    char pad_00[0x28];
    short unk_28;
};

int func_0201a814(struct func_0201a814_UnkStruct *s, int a)
{
    return func_0201a824(a, s->unk_28);
}
