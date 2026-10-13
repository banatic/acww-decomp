/* func_020bee74 @ 0x020bee74, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020bee74 {
    int unk_00;
    int unk_04;
    char unk_08;
};

extern void func_020beca4(int);

void func_020bee74(struct UnkStruct_020bee74 *s, int value, int arg2)
{
    s->unk_04++;
    if (value != s->unk_00) {
        s->unk_08 = 0;
        func_020beca4(arg2);
        s->unk_00 = value;
    }
}
