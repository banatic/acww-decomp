/* func_ov003_0220c260 @ 0x0220c260, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b7f60(void *);
extern void *func_02066994(void *);
extern void *func_0203f080(void *);
extern char data_ov003_02238010;
extern char data_ov003_02238078;

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

struct UnkStruct_0220c260 *func_ov003_0220c260(struct UnkStruct_0220c260 *this)
{
    this->unk_00 = &data_ov003_02238010;
    this->subEC.ptr = &data_ov003_02238078;
    func_020b7f60(&this->sub138);
    func_02066994(&this->subEC);
    func_0203f080(this);
    return this;
}
