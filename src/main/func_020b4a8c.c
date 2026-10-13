/* func_020b4a8c @ 0x020b4a8c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b4a8c {
    volatile void *unk_00;
};

extern void func_020a941c(struct UnkStruct_020b4a8c *this);
extern void func_020edb3c(struct UnkStruct_020b4a8c *this);

extern unsigned char data_020e3e68[];
extern unsigned char data_020e5230[];

struct UnkStruct_020b4a8c *func_020b4a8c(struct UnkStruct_020b4a8c *this)
{
    this->unk_00 = (void *) data_020e5230;
    this->unk_00 = (void *) data_020e3e68;
    func_020a941c(this);
    func_020edb3c(this);
    return this;
}
