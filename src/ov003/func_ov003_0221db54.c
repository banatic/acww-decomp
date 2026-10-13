/* func_ov003_0221db54 @ 0x0221db54, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0221db54 {
    unsigned int unk_00;
    char pad_04[0xEC - 4];
    unsigned int unk_EC;
    char pad_EC[0x2B4 - (0xEC + 4)];
    signed char unk_2B4;
    signed char unk_2B5;
} UnkStruct_0221db54;

extern void func_ov009_0226552c(void *p);

extern unsigned char data_ov003_022390e8[];
extern unsigned char data_ov003_022391ac[];

void *func_ov003_0221db54(void *p)
{
    UnkStruct_0221db54 *u = (UnkStruct_0221db54 *) p;
    func_ov009_0226552c(p);
    u->unk_00 = (unsigned int) data_ov003_022390e8;
    u->unk_EC = (unsigned int) data_ov003_022391ac;
    u->unk_2B5 = -1;
    u->unk_2B4 = u->unk_2B5;
    return p;
}
