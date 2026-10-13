/* func_0203ee7c @ 0x0203ee7c, 0x82 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Vec3 {
    int x, y, z;
};

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
