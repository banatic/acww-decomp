/* func_ov004_02245d30 @ 0x02245d30, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct VA {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
struct VB {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    char pad_04[0x7c];
};
struct UnkStruct_02245d30 {
    char pad_00[0x50];
    VA a;
    char pad_54[0x48];
    VB arr[5];
};

extern "C" int func_ov004_02245d30(UnkStruct_02245d30 *self)
{
    unsigned char i;
    self->a.v2();
    for (i = 0; i < 5; i++) {
        self->arr[i].v2();
    }
    return 1;
}
