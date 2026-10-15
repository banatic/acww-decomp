/* func_020ac2c8 @ 0x020ac2c8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3ffc;
extern void *func_020ac9ec(void *p);
extern void *func_020ac954(void *p);

struct UnkStruct_020ac2c8 {
    char *unk_00;
    char pad_04[0x1c];
    char unk_20;
};

struct UnkStruct_020ac2c8 *func_020ac2c8(struct UnkStruct_020ac2c8 *this)
{
    this->unk_00 = &data_020e3ffc;
    func_020ac9ec(&this->unk_20);
    func_020ac954(this);
    return this;
}
