/* func_0208e438 @ 0x0208e438, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e22f8;
extern void func_0208af30(void *);
extern void func_0208a1f8(void *);
extern void *func_0203a404(void *);

struct Sub1 {
    char data[0x14];
};
struct Sub2 {
    char data[0x34];
};

struct UnkStruct_0208e438 {
    char *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    struct Sub1 sub1;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    struct Sub2 sub2;
    int unk_6C;
    int unk_70;
    int unk_74;
    int unk_78;
    char unk_7C;
};

struct UnkStruct_0208e438 *func_0208e438(struct UnkStruct_0208e438 *this)
{
    func_0208af30(this);
    this->unk_00 = &data_020e22f8;
    this->unk_0C = 0;
    this->unk_10 = 10;
    func_0208a1f8(&this->sub1);
    this->unk_28 = 0;
    this->unk_2C = 0;
    this->unk_30 = 0;
    this->unk_34 = 0;
    func_0203a404(&this->sub2);
    this->unk_6C = 0;
    this->unk_70 = 0;
    this->unk_74 = 0;
    this->unk_78 = 0;
    this->unk_7C = 0;
    return this;
}
