/* func_020aa28c @ 0x020aa28c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020aa28c {
    unsigned int unk_00;
    unsigned char pad_04[4];
    unsigned int unk_08;
    unsigned char unk_0C[0x148];
    unsigned int unk_154;
    unsigned char pad_158[0x34];
    unsigned int unk_18C;
    unsigned int unk_190;
    unsigned int unk_194;
    unsigned char unk_198;
} UnkStruct_020aa28c;

extern int data_020e404c;
extern void func_020aa82c(UnkStruct_020aa28c *p);
extern void *func_020ac0ac(void *p);
extern void func_020aaeb4(void *dst, void *src);

UnkStruct_020aa28c *func_020aa28c(UnkStruct_020aa28c *p)
{
    func_020aa82c(p);
    p->unk_00 = (unsigned int) &data_020e404c;
    p->unk_08 = 0;
    func_020ac0ac(p->unk_0C);
    func_020aaeb4(&p->unk_154, &p->unk_0C);
    p->unk_18C = 0;
    p->unk_190 = 0;
    p->unk_194 = 0;
    p->unk_198 = 0;
    return p;
}
