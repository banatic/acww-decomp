/* etc_board_5: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0220c2d4 @ 0x0220c2d4, 0x1c bytes, Thumb
 * func_ov003_0220c29c @ 0x0220c29c, 0x38 bytes, Thumb
 * func_ov003_0220c260 @ 0x0220c260, 0x3c bytes, Thumb
 * func_ov003_0220c220 @ 0x0220c220, 0x40 bytes, Thumb
 */

struct SubEC {
    void *ptr;
};

struct UnkStruct_0220c260 {
    void *unk_00;
    char pad_04[0xec - 4];
    struct SubEC subEC;
    char pad_F0[0x138 - 0xf0];
    char sub138;
};

typedef struct UnkStruct_0220c220 {
    void *vt0;
    unsigned char pad_04[0xec - 4];
    void *unk_EC;
    unsigned char pad_F0[0x138 - 0xec - 4];
    unsigned char unk_138[1];
} UnkStruct_0220c220;

extern int func_020edf70(int);
extern void *func_0203f130(void *);
extern void *func_02066a30(void *);
extern void *func_020b7f70(void *);
extern char data_ov003_02238010[];
extern char data_ov003_02238078[];
extern int func_020b7f60(void *);
extern void *func_02066994(void *);
extern void *func_0203f080(void *);
extern void func_020edf54(void *p);

void *func_ov003_0220c29c(void *this);

void func_ov003_0220c2d4(void)
{
    void *condition_value_0;
    condition_value_0 = (void *) (func_020edf70(0x154));
    if (condition_value_0 != 0) {
        func_ov003_0220c29c(condition_value_0);
    }
}

void *func_ov003_0220c29c(void *this)
{
    func_0203f130(this);
    func_02066a30((char *) this + 0xec);
    *(void **) this = (void *) data_ov003_02238010;
    *(void **) ((char *) this + 0xec) = (void *) data_ov003_02238078;
    func_020b7f70((char *) this + 0x138);
    return this;
}

struct UnkStruct_0220c260 *func_ov003_0220c260(struct UnkStruct_0220c260 *this)
{
    this->unk_00 = ((char *) data_ov003_02238010);
    this->subEC.ptr = ((char *) data_ov003_02238078);
    func_020b7f60(&this->sub138);
    func_02066994(&this->subEC);
    func_0203f080(this);
    return this;
}

struct UnkStruct_0220c220 *func_ov003_0220c220(struct UnkStruct_0220c220 *this)
{
    this->vt0 = ((char *) data_ov003_02238010);
    this->unk_EC = ((char *) data_ov003_02238078);
    func_020b7f60(&this->unk_138);
    func_02066994((void *) (&this->unk_EC));
    func_0203f080(this);
    func_020edf54(this);
    return this;
}
