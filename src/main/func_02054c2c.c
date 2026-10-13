/* func_02054c2c @ 0x02054c2c, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020dd0ac;
extern char data_020dd0bc;
extern char data_020dd0cc;
extern char data_020dd184;
extern void func_02054e8c(void *);
extern void func_02056ee0(void *);

typedef struct {
    void *unk_00;       // 0x00
    char pad_04[152];   // 0x04
    void *unk_9C;       // 0x9c
    char pad_A0[24];    // 0xa0
    void *unk_B8;       // 0xb8
    char pad_BC[56];    // 0xbc
    int unk_F4;         // 0xf4
    void *unk_F8;       // 0xf8
    char pad_FC[4];     // 0xfc
    int unk_100;        // 0x100
    int unk_104;        // 0x104
    int unk_108;        // 0x108
    char pad_10C[4];    // 0x10c
    char unk_110[0x3c]; // 0x110
    int unk_14C;        // 0x14c
    int unk_150;        // 0x150
} UnkStruct_02054c2c;

UnkStruct_02054c2c *func_02054c2c(UnkStruct_02054c2c *obj)
{
    func_02054e8c(obj);
    obj->unk_00 = (void *) &data_020dd0ac;
    obj->unk_9C = (void *) &data_020dd0bc;
    obj->unk_B8 = (void *) &data_020dd0cc;
    obj->unk_F8 = (void *) &data_020dd184;
    obj->unk_100 = 0;
    obj->unk_104 = 0;
    obj->unk_108 = 0x1000;
    func_02056ee0(obj->unk_110);
    obj->unk_F4 = 0;
    obj->unk_14C = 0;
    obj->unk_150 = 0;
    return obj;
}
