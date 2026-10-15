/* func_020161ac @ 0x020161ac, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    char pad_04[68];
    int unk_48;
    int unk_4C;
    int unk_50;
    char pad_54[8];
    int unk_5C;
    char pad_60[4];
    int unk_64;
    char pad_68[22];
    unsigned short unk_7E;
} UnkStruct_020161ac;

extern void *func_02066a30(void *);
extern void func_020159f0(void *);

extern unsigned char data_020d8bd4[];

UnkStruct_020161ac *func_020161ac(UnkStruct_020161ac *r4)
{
    func_02066a30(r4);
    r4->unk_00 = (void *) data_020d8bd4;
    r4->unk_7E = 0xfff1;
    r4->unk_48 = 0;
    r4->unk_4C = 0;
    r4->unk_50 = 0;
    r4->unk_5C = 0;
    r4->unk_64 = 12;
    func_020159f0(r4);
    return r4;
}
