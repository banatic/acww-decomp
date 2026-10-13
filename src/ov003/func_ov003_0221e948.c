/* func_ov003_0221e948 @ 0x0221e948, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_0226552c(void *p);
extern void func_020565c8(void *p);
extern void func_020b7f70(void *p);
extern int data_ov003_0223948c;
extern int data_ov003_02239550;

typedef struct {
    int *unk_00;        // offset 0x00
    char pad_04[0xE8];  // offset 0x04 to 0xEC
    int *unk_EC;        // offset 0xEC
    char pad_F0[0x1C8]; // offset 0xF0 to 0x2B8
    char unk_2B8[0x20]; // offset 0x2B8
    char unk_2D8[0x20]; // offset 0x2D8
} UnkStruct_0221e948;

void *func_ov003_0221e948(UnkStruct_0221e948 *p)
{
    func_ov009_0226552c(p);
    p->unk_00 = &data_ov003_0223948c;
    p->unk_EC = &data_ov003_02239550;
    func_020565c8(&p->unk_2B8);
    func_020b7f70(&p->unk_2D8);
    return p;
}
