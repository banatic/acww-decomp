/* func_020bb99c @ 0x020bb99c, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    char pad_04[0x1510];
    int unk_1514;
    int unk_1518;
    int unk_151C;
    int unk_1520;
    char pad_1524[0x10];
    int unk_1534;
    char pad_1538[0x2c];
    int unk_1564;
    int unk_1568;
    int unk_156C;
    char pad_1570[0x8];
    int unk_1578;
    int unk_157C;
    char pad_1580[0x4];
    int unk_1584;
    char pad_1588[0x4];
    int unk_158C;
} UnkStruct_020bb99c;

extern void func_020bbc90(UnkStruct_020bb99c *p);

UnkStruct_020bb99c *func_020bb99c(UnkStruct_020bb99c *p)
{
    p->unk_00 = 0;
    p->unk_1520 = 0;
    p->unk_157C = 0;
    p->unk_1584 = 0;
    p->unk_158C = 0;
    p->unk_1578 = -1;
    p->unk_1514 = 0;
    p->unk_1518 = 0;
    p->unk_151C = 0;
    p->unk_1564 = 0;
    p->unk_1568 = 0;
    p->unk_156C = 0;
    p->unk_1534 = 0;
    func_020bbc90(p);
    return p;
}
