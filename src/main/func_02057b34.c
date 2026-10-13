/* func_02057b34 @ 0x02057b34, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f5948(void *p);
extern void func_020ee62c(void *p);

struct UnkStruct_02057b34 {
    unsigned int unk_00;
    char pad_04[0xdc - 4];
    char unk_DC;
};

extern unsigned char data_020da13c[];
extern unsigned char data_020dd33c[];

void *func_02057b34(struct UnkStruct_02057b34 *obj)
{
    obj->unk_00 = (unsigned int) data_020dd33c;
    func_020f5948(&obj->unk_DC);
    obj->unk_00 = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    return (void *) obj;
}
