/* func_02036f94 @ 0x02036f94, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035638(int);

typedef struct {
    char pad_00[8];
    unsigned short unk_08;
} UnkStruct_02036f94;

void func_02036f94(UnkStruct_02036f94 *s)
{
    if (s->unk_08 != 0xffff) {
        func_02035638(s->unk_08);
        s->unk_08 = 0xffff;
    }
}
