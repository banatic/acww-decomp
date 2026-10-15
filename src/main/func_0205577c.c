/* func_0205577c @ 0x0205577c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02056044(void *p);
extern char data_020dd03c;

struct UnkStruct_0205577c {
    void *unk_00;
    unsigned char pad_04[0x94];
    unsigned int unk_98;
};

struct UnkStruct_0205577c *func_0205577c(struct UnkStruct_0205577c *p)
{
    func_02056044(p);
    p->unk_00 = &data_020dd03c;
    p->unk_98 = 0x4e554c4c;
    return p;
}
