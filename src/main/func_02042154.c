/* func_02042154 @ 0x02042154, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned short unk_04;
    unsigned short vcount;
    unsigned char pad_08[0x38];
    unsigned short win0h;
    unsigned char pad_42[0x1040 - 0x42];
    unsigned short subWin0h;
} IO;
extern unsigned short *data_021c75b4;
void func_02042154(void)
{
    volatile IO *io = (volatile IO *) 0x04000000;
    int y;
    unsigned short v;
    y = io->vcount;
    if (y >= 0xc0) {
        return;
    }
    if (y >= 0x60) {
        y = 0xbf - y;
    }
    v = data_021c75b4[y];
    if ((*(volatile unsigned short *) 0x04000004 & 2) != 0) {
        io->win0h = v;
        io->subWin0h = v;
    }
}
