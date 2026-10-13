/* func_ov144_0229add8 @ 0x0229add8, 0x18 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov144_0229ad90(void *p);

class UnkStruct_0229add8 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

class UnkStruct_0229add8_2 {
  public:
    char pad_00[0xC4];
    UnkStruct_0229add8 sub;
};

extern "C" void func_ov144_0229add8(UnkStruct_0229add8_2 *self)
{
    func_ov144_0229ad90(self);
    self->sub.f3();
}
