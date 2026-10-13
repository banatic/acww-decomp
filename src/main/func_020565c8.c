/* func_020565c8 @ 0x020565c8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    volatile unsigned int unk_00;
    unsigned int unk_04;
    volatile unsigned int unk_08;
    volatile unsigned int unk_0C;
    volatile unsigned int unk_10;
    unsigned int unk_14;
    volatile unsigned int unk_18;
    volatile unsigned int unk_1C;
} UnkStruct_020565c8;

extern unsigned char data_020dd154[];
extern unsigned char data_020dd184[];

void func_020565c8(UnkStruct_020565c8 *p)
{
    p->unk_00 = (unsigned int) data_020dd184;
    p->unk_08 = 0;
    p->unk_0C = 0;
    p->unk_10 = 0x1000;
    p->unk_00 = (unsigned int) data_020dd154;
    p->unk_1C = 0;
    p->unk_18 = 0;
}
