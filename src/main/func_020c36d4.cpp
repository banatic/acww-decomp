/* func_020c36d4 @ 0x020c36d4, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class CObj {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
};

extern "C" void func_020c3690(void *self, int value);
extern "C" int func_0201c2a4(void *self, int value);
extern "C" void func_02016108(void *obj, int value);

extern "C" void func_020c36d4(void *p, int index)
{
    switch (index) {
        case 1:
            ((CObj *) ((char *) p + 0x658))->m2();
            func_02016108((char *) p + 0x658, func_0201c2a4(p, 4));
            func_020c3690(p, 1);
            break;
        case 0:
            func_020c3690(p, 1);
            break;
        case 3:
            ((CObj *) ((char *) p + 0x658))->m2();
            func_02016108((char *) p + 0x658, func_0201c2a4(p, 4));
            func_020c3690(p, 9);
            break;
        case 8:
            func_020c3690(p, 0);
            break;
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
    }
}
