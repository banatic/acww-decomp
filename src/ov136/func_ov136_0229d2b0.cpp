/* func_ov136_0229d2b0 @ 0x0229d2b0, 0x94 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

class Class {
  public:
    virtual void vfunc_00();
    char pad_04[0x88];
    unsigned char selector;
};
typedef void (Class::*PMF)();
extern PMF data_ov136_0229d468;
extern PMF data_ov136_0229d460;
extern PMF data_ov136_0229d470;
extern PMF data_ov136_0229d500;
extern "C" void func_ov136_0229cfb0(Class *);
extern "C" void func_ov136_0229cfa0(Class *);
extern "C" int func_ov136_0229d2b0(Class *obj)
{
    static int initialized = 0;
    static PMF table[4];
    if (!(initialized & 1)) {
        table[0] = data_ov136_0229d468;
        table[1] = data_ov136_0229d460;
        table[2] = data_ov136_0229d470;
        table[3] = data_ov136_0229d500;
        initialized |= 1;
    }
    func_ov136_0229cfb0(obj);
    (obj->*table[obj->selector])();
    func_ov136_0229cfa0(obj);
    return 1;
}
