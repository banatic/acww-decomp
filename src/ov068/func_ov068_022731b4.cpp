/* func_ov068_022731b4 @ 0x022731b4, 0x7c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
class UnkStruct_022731b4 {
  public:
    virtual void method();
};
typedef void (UnkStruct_022731b4::*PMF)();
extern const PMF data_ov068_022778bc;
extern const PMF data_ov068_022778ac;
extern const PMF data_ov068_022778b4;
void func_ov068_022731b4(UnkStruct_022731b4 *p)
{
    static PMF arr[3] = {data_ov068_022778bc, data_ov068_022778ac, data_ov068_022778b4};
    int idx = *(int *) ((char *) p + 0x594);
    if (idx >= 3) {
        return;
    }
    (p->*arr[idx])();
}
}
