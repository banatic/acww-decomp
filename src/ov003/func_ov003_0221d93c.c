/* func_ov003_0221d93c @ 0x0221d93c, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_02238f28[];
extern char data_ov003_02238fec[];

extern void func_020565b0(void *p);
extern void func_020551e0(void *p);
extern void func_ov009_0226539c(void *p);
extern void func_020edf54(void *p);

typedef struct {
    void *unk_00;
    char pad_04[0xec - 4];
    void *unk_EC;
    char pad_F0[0x2b4 - (0xec + 4)];
    char unk_2B4;
    char pad_2B5[0x36c - (0x2b4 + 1)];
    char unk_36C;
} UnkStruct_0221d93c;

UnkStruct_0221d93c *func_ov003_0221d93c(UnkStruct_0221d93c *p)
{
    p->unk_00 = data_ov003_02238f28;
    p->unk_EC = data_ov003_02238fec;
    func_020565b0(&p->unk_36C);
    func_020551e0(&p->unk_2B4);
    func_ov009_0226539c(p);
    func_020edf54(p);
    return p;
}
