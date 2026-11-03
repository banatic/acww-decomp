/* scene_object_base_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203ef00 @ 0x0203ef00, 0x5c bytes, Thumb
 * func_0203ee7c @ 0x0203ee7c, 0x82 bytes, Thumb
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

class UnkStruct_0203ee7c {
  public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual Vec3 *getVec();
    char pad_04[0xe0];
    int e4;
};

extern "C" long long func_020ea970(int *diff);

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

extern "C" int func_0203ee7c(UnkStruct_0203ee7c *a, UnkStruct_0203ee7c *b)
{
    int diff[3];

    if (a->e4 == 0) {
        return 1;
    }

    {
        Vec3 *vb = b->getVec();
        Vec3 *va = a->getVec();
        diff[0] = vb->x - va->x;
    }

    {
        Vec3 *vb = b->getVec();
        Vec3 *va = a->getVec();
        diff[1] = vb->y - va->y;
    }

    {
        Vec3 *vb = b->getVec();
        Vec3 *va = a->getVec();
        diff[2] = vb->z - va->z;
    }

    if (func_020ea970(diff) < a->e4) {
        return 1;
    }

    return 0;
}
