/* func_0205467c @ 0x0205467c, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02054c2c(void *p);
extern void func_02056ee0(void *p);
extern int data_020dd07c;
extern int data_020dd08c;
extern int data_020dd09c;
extern int data_020dd184;

typedef struct UnkStruct_0205467c {
    unsigned int unk_00;
    unsigned char pad_04[0x98];
    unsigned int unk_9C;
    unsigned char pad_A0[0x18];
    unsigned int unk_B8;
    unsigned char pad_BC[0x98];
    unsigned int unk_154;
    unsigned int unk_158;
    unsigned char pad_15C[0x4];
    unsigned int unk_160;
    unsigned int unk_164;
    unsigned int unk_168;
    unsigned char pad_16C[0x4];
    unsigned char arr170[0x3c];
    unsigned int unk_1AC;
    unsigned int unk_1B0;
} UnkStruct_0205467c;

UnkStruct_0205467c *func_0205467c(UnkStruct_0205467c *p)
{
    func_02054c2c(p);
    p->unk_00 = (unsigned int) &data_020dd07c;
    p->unk_9C = (unsigned int) &data_020dd08c;
    p->unk_B8 = (unsigned int) &data_020dd09c;
    p->unk_158 = (unsigned int) &data_020dd184;
    p->unk_160 = 0;
    p->unk_164 = 0;
    p->unk_168 = 0x1000;
    func_02056ee0(p->arr170);
    p->unk_154 = 0;
    p->unk_1AC = 0;
    p->unk_1B0 = 0;
    return p;
}
