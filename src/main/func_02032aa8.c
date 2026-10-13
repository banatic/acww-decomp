/* func_02032aa8 @ 0x02032aa8, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02033678(unsigned int p1, unsigned int p2, void *p3, unsigned int p4, unsigned int p5, unsigned int p6);

typedef struct {
    unsigned char pad_00[4];
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned char unk_0C[16];
    unsigned int unk_1C;
    unsigned int unk_20;
} UnkStruct_02032aa8;

int func_02032aa8(UnkStruct_02032aa8 *arg1, unsigned int arg2)
{
    return func_02033678(arg2, arg1->unk_08, arg1->unk_0C, arg1->unk_1C, arg1->unk_04, arg1->unk_20);
}
