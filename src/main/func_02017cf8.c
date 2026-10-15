/* func_02017cf8 @ 0x02017cf8, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057bf0(int);

struct UnkStruct_02017cf8 {
    unsigned char pad_00[0x98];
    unsigned char unk_98;
};

void func_02017cf8(struct UnkStruct_02017cf8 *s, int event)
{
    if (func_02057bf0(1)) {
        s->unk_98 = 14;
    }
}
