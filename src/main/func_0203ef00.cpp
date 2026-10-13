/* func_0203ef00 @ 0x0203ef00, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Vec3 {
    int x, y, z;
};

class UnkStruct_0203ef00 {
  public:
    virtual void f00();
    virtual void f01();
    virtual void f02();
    virtual void f03();
    virtual void f04();
    virtual void f05();
    virtual void f06();
    virtual void f07();
    virtual void f08();
    virtual void f09();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void f16();
    virtual void f17();
    virtual void f18();
    virtual void f19();
    virtual Vec3 *getVec();
    unsigned char pad_04[0x8a];
    short unk_8E;
};

extern "C" int func_0200322c(const Vec3 *a, const Vec3 *b);

extern "C" int func_0203ef00(UnkStruct_0203ef00 *a, UnkStruct_0203ef00 *b, int min, int max)
{
    Vec3 v1;
    Vec3 v2;
    Vec3 *p;
    short diff;

    p = b->getVec();
    v1.x = p->x;
    v1.y = p->y;
    v1.z = p->z;

    p = a->getVec();
    v2.x = p->x;
    v2.y = p->y;
    v2.z = p->z;

    diff = (short) (func_0200322c(&v1, &v2) - b->unk_8E);
    if (diff >= min && diff <= max) {
        return 1;
    }
    return 0;
}
