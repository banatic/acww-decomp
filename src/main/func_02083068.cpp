/* func_02083068 @ 0x02083068, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02083068;

struct UnkStruct_02083068_2 {
    virtual void v0();
    virtual void v1();
    virtual UnkStruct_02083068 *v2();
    signed char unk_04;
};

struct UnkStruct_02083068 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3(signed char c);
};

extern "C" void func_02083068(UnkStruct_02083068_2 *this_)
{
    UnkStruct_02083068 *b;
    signed char c;
    b = this_->v2();
    if (b != 0) {
        c = this_->unk_04;
        b->m3(c);
        this_->unk_04 = -1;
    }
}
