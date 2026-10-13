/* func_020a7d68 @ 0x020a7d68, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    volatile unsigned int unk_00;
    char pad_04[0x20];
    unsigned int unk_24;
    char unk_28[0x14];
    unsigned int unk_3C;
    unsigned int unk_40;
    unsigned int unk_44;
    unsigned int unk_48;
    unsigned int unk_4C;
    unsigned int unk_50;
    unsigned int unk_54;
    unsigned char unk_58;
} UnkStruct_020a7d68;

extern void func_020a9484(void *);
extern void func_020a8754(void *);

extern unsigned char data_020e3e44[];
extern unsigned char data_020e3e68[];

void *func_020a7d68(UnkStruct_020a7d68 *p)
{
    func_020a9484(p);
    p->unk_00 = (unsigned int) data_020e3e68;
    p->unk_00 = (unsigned int) data_020e3e44;
    p->unk_24 = 0;
    func_020a8754(p->unk_28);
    p->unk_3C = 0;
    p->unk_40 = -1;
    p->unk_44 = -1;
    p->unk_48 = 0;
    p->unk_4C = 0;
    p->unk_50 = 0;
    p->unk_54 = 0;
    p->unk_58 = 0;
    return p;
}
