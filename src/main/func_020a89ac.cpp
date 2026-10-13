/* func_020a89ac @ 0x020a89ac, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int strcmp(int, int);

class UnkStruct_020a89ac {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
};

extern "C" int func_020a89ac(UnkStruct_020a89ac *a, UnkStruct_020a89ac *b)
{
    int x = b->f3();
    int y = a->f3();
    if (strcmp(y, x) == 0) {
        return 1;
    } else {
        return 0;
    }
}
