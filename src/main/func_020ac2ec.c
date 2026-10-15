/* func_020ac2ec @ 0x020ac2ec, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ac9a4(void *);
extern void *func_020aca04(void *);
extern char data_020e3ffc[];

struct UnkStruct_020ac2ec {
    void *vtable;
    char pad_04[0x1c];
    char sub[0x4c];
    int unk_6C;
    int unk_70;
    char unk_74;
};

void *func_020ac2ec(struct UnkStruct_020ac2ec *this)
{
    func_020ac9a4(this);
    this->vtable = data_020e3ffc;
    func_020aca04(this->sub);
    this->unk_6C = 0;
    this->unk_70 = 0;
    this->unk_74 = 0;
    return this;
}
