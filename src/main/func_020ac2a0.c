/* func_020ac2a0 @ 0x020ac2a0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020ac2a0 {
    int pad_00;
};

struct UnkStruct_020ac2a0_2 {
    void *vtable;
    char pad_04[0x1C];
    struct UnkStruct_020ac2a0 sub;
};

extern void *func_020ac9ec(struct UnkStruct_020ac2a0 *);
extern void *func_020ac954(struct UnkStruct_020ac2a0_2 *);
extern void func_020edb3c(struct UnkStruct_020ac2a0_2 *);

extern unsigned char data_020e3ffc[];

struct UnkStruct_020ac2a0_2 *func_020ac2a0(struct UnkStruct_020ac2a0_2 *this)
{
    this->vtable = (void *) data_020e3ffc;
    func_020ac9ec(&this->sub);
    func_020ac954(this);
    func_020edb3c(this);
    return this;
}
