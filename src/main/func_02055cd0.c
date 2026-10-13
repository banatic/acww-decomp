/* func_02055cd0 @ 0x02055cd0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *this);

struct UnkStruct_02055cd0 {
    void *vtable;
};

extern unsigned char data_020dd12c[];

struct UnkStruct_02055cd0 *func_02055cd0(struct UnkStruct_02055cd0 *this)
{
    this->vtable = (void *) data_020dd12c;
    func_020edb3c(this);
    return this;
}
