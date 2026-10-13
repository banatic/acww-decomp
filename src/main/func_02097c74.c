/* func_02097c74 @ 0x02097c74, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02097c74 {
    unsigned char pad_00[0x50];
    unsigned short unk_50;
};

extern void func_02097c14(struct UnkStruct_02097c74 *s, int arg);

int func_02097c74(struct UnkStruct_02097c74 *s)
{
    s->unk_50 = 0;
    func_02097c14(s, 1);
    return 1;
}
