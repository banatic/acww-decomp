/* func_02035a30 @ 0x02035a30, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035638(unsigned int);
extern void func_02035624(int);

typedef struct {
    unsigned char pad_00[8];
    unsigned short unk_08;
    unsigned char unk_0A;
} UnkStruct_02035a30;

void func_02035a30(UnkStruct_02035a30 *s)
{
    if (s->unk_08 != 0xffff) {
        func_02035638(s->unk_08);
        s->unk_08 = 0xffff;
    }
    if (s->unk_0A != 0) {
        func_02035624(10);
        s->unk_0A = 0;
    }
}
