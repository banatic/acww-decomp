/* func_020b8d08 @ 0x020b8d08, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b91c4(void *);

typedef struct UnkStruct_020b8d08 {
    void *unk_00;          // 0x00
    int unk_04;            // 0x04
    char sub8[0xec];       // 0x08
    int unk_F4;            // 0xf4
    unsigned short unk_F8; // 0xf8
    int unk_FC;            // 0xfc
    int unk_100;           // 0x100
    int unk_104;           // 0x104
    int unk_108;           // 0x108
    char unk_10C;          // 0x10c
    char unk_10D;          // 0x10d
} UnkStruct_020b8d08;

extern unsigned char data_020e5848[];

UnkStruct_020b8d08 *func_020b8d08(UnkStruct_020b8d08 *self)
{
    self->unk_00 = (void *) data_020e5848;
    self->unk_04 = 0;
    func_020b91c4(self->sub8);
    self->unk_F4 = 0;
    self->unk_F8 = 0xfff1;
    self->unk_FC = 0;
    self->unk_100 = 0;
    self->unk_104 = 0;
    self->unk_108 = 0;
    self->unk_10C = 0;
    self->unk_10D = 0;
    return self;
}
