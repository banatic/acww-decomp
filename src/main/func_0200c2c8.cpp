/* func_0200c2c8 @ 0x0200c2c8, 0x72 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern "C" {
extern void *func_0203dfac(void);
extern int func_0200f290(void *, int);
extern int func_020e8ed8(int, int);
extern int func_020113e0(short *, short);
extern void func_020110a0(void *s, short *src);
}

struct Vec {
    int x;
    int pad_04;
    int z;
};

struct UnkStruct_0200c2c8_2 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
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
    virtual Vec *v20();
};

struct UnkStruct_0200c2c8_3 {
    char pad_00[0x5c];
    Vec vec;
    char pad_68[0x26];
    short unk_8E;
};

struct UnkStruct_0200c2c8 {
    short x;
    short y;
    int dx;
    int spare;
    int dz;
};

extern "C" void func_0200c2c8(UnkStruct_0200c2c8_3 *obj)
{
    UnkStruct_0200c2c8 s;
    UnkStruct_0200c2c8_2 *e;
    UnkStruct_0200c2c8 *pp;
    Vec *q;

    e = (UnkStruct_0200c2c8_2 *) func_0203dfac();
    pp = 0;
    if (func_0200f290(obj, 14) != 0) {
        e = 0;
    }
    if (e != 0) {
        q = &obj->vec;
        Vec *p = e->v20();
        s.dx = p->x - obj->vec.x;
        s.dz = p->z - q->z;
        s.x = (short) func_020e8ed8(s.dx, s.dz);
        pp = &s;
    }
    if (pp != 0) {
        s.y = obj->unk_8E;
        func_020113e0(&s.y, pp->x);
        func_020110a0(obj, &s.y);
    }
}
