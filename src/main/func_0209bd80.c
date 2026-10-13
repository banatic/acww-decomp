/* func_0209bd80 @ 0x0209bd80, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    volatile unsigned short unk_08;
    volatile unsigned char unk_0A;
} UnkStruct_0209bd80;

void func_0209bd80(UnkStruct_0209bd80 *p)
{
    p->unk_00 = 0;
    p->unk_04 = 0;
    p->unk_08 = 0xfff1;
    p->unk_0A = 0x16;
    p->unk_08 = 0xfff1;
}
