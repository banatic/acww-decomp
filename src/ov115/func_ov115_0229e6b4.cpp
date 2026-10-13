/* func_ov115_0229e6b4 @ 0x0229e6b4, 0x94 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229e6b4 {
  public:
    virtual void vfunc();
    char pad_04[0x88];
    unsigned char index;
};

typedef void (UnkStruct_0229e6b4::*PMF)();

extern PMF data_ov115_0229e840;
extern PMF data_ov115_0229e8a8;
extern PMF data_ov115_0229e868;
extern PMF data_ov115_0229e898;
extern PMF data_ov115_0229e928[4];

extern "C" void func_ov115_0229e334(UnkStruct_0229e6b4 *);
extern "C" void func_ov115_0229e328(UnkStruct_0229e6b4 *);

extern "C" int func_ov115_0229e6b4(UnkStruct_0229e6b4 *p)
{
    static unsigned int state = 0;
    if (!(state & 1)) {
        data_ov115_0229e928[0] = data_ov115_0229e840;
        data_ov115_0229e928[1] = data_ov115_0229e8a8;
        data_ov115_0229e928[2] = data_ov115_0229e868;
        data_ov115_0229e928[3] = data_ov115_0229e898;
        state |= 1;
    }
    func_ov115_0229e334(p);
    (p->*data_ov115_0229e928[p->index])();
    func_ov115_0229e328(p);
    return 1;
}
