/* mes_choice_window_4: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ac2ec @ 0x020ac2ec, 0x2c bytes, Thumb
 * func_020ac2c8 @ 0x020ac2c8, 0x24 bytes, Thumb
 * func_020ac2a0 @ 0x020ac2a0, 0x28 bytes, Thumb
 */

struct UnkStruct_020ac2ec {
    void *vtable;
    char pad_04[0x1c];
    char sub[0x4c];
    int unk_6C;
    int unk_70;
    char unk_74;
};

struct UnkStruct_020ac2c8 {
    char *unk_00;
    char pad_04[0x1c];
    char unk_20;
};

struct UnkStruct_020ac2a0 {
    int pad_00;
};

struct UnkStruct_020ac2a0_2 {
    void *vtable;
    char pad_04[0x1C];
    struct UnkStruct_020ac2a0 sub;
};

extern void func_020ac9a4(void *);
extern void *func_020aca04(void *);
extern char data_020e3ffc[];
extern void *func_020ac9ec(void *p);
extern void *func_020ac954(void *p);
extern void func_020edb3c(struct UnkStruct_020ac2a0_2 *);

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

struct UnkStruct_020ac2c8 *func_020ac2c8(struct UnkStruct_020ac2c8 *this)
{
    this->unk_00 = ((char *) data_020e3ffc);
    func_020ac9ec(&this->unk_20);
    func_020ac954(this);
    return this;
}

struct UnkStruct_020ac2a0_2 *func_020ac2a0(struct UnkStruct_020ac2a0_2 *this)
{
    this->vtable = (void *) ((unsigned char *) data_020e3ffc);
    func_020ac9ec((void *) (&this->sub));
    func_020ac954((void *) this);
    func_020edb3c(this);
    return this;
}
