/* func_ov003_02222cac @ 0x02222cac, 0xbc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    int a, b;
} UnkStruct_02222cac;
extern unsigned int func_0204e414(void);
extern void func_02055060(void *, int, int, int, int, int);
extern void func_02055050(void *);
extern void func_0204f794(Vec *, int, int);
extern void func_ov003_022230a0(void *, int);
extern char *data_ov003_0223cf70;
void func_ov003_02222cac(char *self, int b, UnkStruct_02222cac *c, int d, int e, int g)
{
    Vec v;
    char *t;
    int flag;
    func_0204e414();
    flag = 1;
    t = data_ov003_0223cf70 + 0x696c;
    if (d == 2) {
        flag = 0;
    }
    func_02055060(self + 8, *(int *) (0x80 + (t + (d << 4)) + (e << 2)), flag, 0x1000, 0, 0);
    if (*(int *) (self + 0xd4) == 8) {
        func_02055050(self + 8);
    }
    *(int *) (self + 0xd4) = d;
    *(int *) (self + 4) = b;
    *(int *) (self + 0xcc) = c->a;
    *(int *) (self + 0xd0) = c->b;
    func_0204f794(&v, c->a, c->b);
    *(int *) (self + 0xc0) = v.x;
    *(int *) (self + 0xc4) = v.y;
    *(int *) (self + 0xc8) = v.z;
    *(int *) (self + 0xd8) = 0x1f000;
    *(int *) (self + 0xdc) = 0;
    func_ov003_022230a0(self, g);
}
