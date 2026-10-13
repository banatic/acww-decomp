/* func_0208fae8 @ 0x0208fae8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208fae8 {
    void *vtable;
    char pad_04[8];
    char sub[20];
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    char unk_38;
    char unk_39;
};

extern void func_0208af30(struct UnkStruct_0208fae8 *);
extern void func_0208a1f8(void *);
extern char data_020e2400[];

struct UnkStruct_0208fae8 *func_0208fae8(struct UnkStruct_0208fae8 *this)
{
    func_0208af30(this);
    this->vtable = data_020e2400;
    func_0208a1f8(&this->sub);
    this->unk_20 = 0;
    this->unk_24 = 0;
    this->unk_28 = 0;
    this->unk_2C = 0;
    this->unk_30 = 0;
    this->unk_34 = 0;
    this->unk_38 = 0;
    this->unk_39 = 0;
    return this;
}
