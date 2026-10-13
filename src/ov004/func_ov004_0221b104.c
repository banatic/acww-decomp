/* func_ov004_0221b104 @ 0x0221b104, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b7f60(void *);
extern void func_02066994(void *);
extern void func_0203f080(void *);
extern char data_ov004_0225328c;
extern char data_ov004_022532f4;

struct SubEC {
    void *ptr;
};

struct UnkStruct_0221b104 {
    void *unk_00;
    char pad_04[0xec - 4];
    struct SubEC subEC;
    char pad_F0[0x138 - 0xf0];
    char sub138;
};

struct UnkStruct_0221b104 *func_ov004_0221b104(struct UnkStruct_0221b104 *this)
{
    this->unk_00 = &data_ov004_0225328c;
    this->subEC.ptr = &data_ov004_022532f4;
    func_020b7f60(&this->sub138);
    func_02066994(&this->subEC);
    func_0203f080(this);
    return this;
}
