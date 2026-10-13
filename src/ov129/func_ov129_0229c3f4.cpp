/* func_ov129_0229c3f4 @ 0x0229c3f4, 0x24 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229c3f4 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
};

extern "C" void func_ov002_0220a374(void *obj, int n);

extern "C" void func_ov129_0229c3f4(void *p)
{
    func_ov002_0220a374((void *) ((char *) p + 0x3a0), 0);
    ((UnkStruct_0229c3f4 *) ((char *) p + 0x3a0))->vf3();
}
