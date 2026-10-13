/* func_ov113_0229a398 @ 0x0229a398, 0x64 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229a398 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
};

extern "C" void func_02070b84(void *p);

extern "C" void func_ov113_0229a398(void *arg0)
{
    char *base = (char *) arg0;
    ((UnkStruct_0229a398 *) (base + 0x2b20))->vf3();
    func_02070b84(base + 0x26e8);
    func_02070b84(base + 0x2754);
    func_02070b84(base + 0x27c0);
    func_02070b84(base + 0x282c);
    int i = 0;
    char *arr = base + 0x2898;
    do {
        func_02070b84(arr + i * 0x6c);
        i++;
    } while (i < 6);
}
