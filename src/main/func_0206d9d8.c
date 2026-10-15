/* func_0206d9d8 @ 0x0206d9d8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8cac(void *);
extern void func_020a8c1c(void *);

struct UnkStruct_0206d9d8 {
    void *unk_00;
};

extern unsigned char data_020df1d0[];

struct UnkStruct_0206d9d8 *func_0206d9d8(struct UnkStruct_0206d9d8 *this)
{
    func_020a8cac(this);
    this->unk_00 = (void *) data_020df1d0;
    func_020a8c1c(this);
    return this;
}
