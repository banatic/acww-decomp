/* func_020693d4 @ 0x020693d4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x24];
    unsigned int unk_24;
} UnkStruct_020693d4;

extern int func_0206b97c(UnkStruct_020693d4 *a, unsigned int b, unsigned int c);

int func_020693d4(UnkStruct_020693d4 *a)
{
    unsigned int t = a->unk_24 + 0x14b8;
    return func_0206b97c(a, t + 0x398, t);
}
