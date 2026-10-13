/* func_ov004_02245744 @ 0x02245744, 0xd4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int u, v;
} Pair;
typedef struct {
    int w[8];
} M32;

class Node {
  public:
    virtual void vfunc0();
    virtual void vfunc1();
    virtual void vfunc2();
    virtual void draw();
    char pad_04[0x7c];
};

typedef struct UnkStruct_02245744 {
    char unk_00[0x9c];
    Node arr[4];
    Node last;
    char unk_31C[0x338 - 0x31c];
    M32 unk_338;
} UnkStruct_02245744;

typedef struct Src {
    char unk_00[0x5c];
    Vec3 unk_5C;
} Src;

extern "C" char data_021dc7bc;
extern "C" Pair data_ov004_0224be44[];
extern "C" Pair data_ov004_0224be1c;

extern "C" int func_020988a4(char *g, int i);
extern "C" Src *func_02096190(int i);
extern "C" void func_02094fd4(M32 *m);
extern "C" void func_02098844(char *g, int i);
extern "C" int func_02099870(void);
extern "C" void func_02095074(int h, M32 *m);
extern "C" void func_0203aa24(int *a, int *b, Vec3 *v);
extern "C" void func_0208e29c(Node *n, int a, int b);
extern "C" void func_0208e290(Node *n, M32 *m);
extern "C" void func_02094fbc(M32 *m);

extern "C" void func_ov004_02245744(UnkStruct_02245744 *self)
{
    int a;
    int b;
    Vec3 v;
    M32 m;
    unsigned char i;
    Src *s;
    Vec3 *q;
    Pair *e;
    Node *n;

    i = 0;
    do {
        if (func_020988a4(&data_021dc7bc, i) != 0) {
            s = func_02096190(i);
            if (s != 0) {
                q = &s->unk_5C;
                v.x = q->x;
                v.y = q->y;
                v.z = q->z;
                func_02094fd4(&m);
                func_02098844(&data_021dc7bc, i);
                func_02095074(func_02099870(), &m);
                func_0203aa24(&a, &b, &v);
                e = &data_ov004_0224be44[i];
                a = a + e->u;
                b = b + e->v;
                n = &self->arr[i];
                func_0208e29c(n, a, b);
                func_0208e290(n, &m);
                n->draw();
                func_02094fbc(&m);
            }
        }
        i = (unsigned char) (i + 1);
    } while (i < 4);
    func_0208e29c(&self->last, data_ov004_0224be1c.u, data_ov004_0224be1c.v);
    func_0208e290(&self->last, &self->unk_338);
    self->last.draw();
}
