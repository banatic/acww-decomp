/* func_ov003_02212a14 @ 0x02212a14, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010d88(void *p, void *q, int a, int b);
extern void func_02089fc8(void *p);

struct Triple {
    int a, b, c;
};

struct UnkStruct_02212a14 {
    char pad_00[0x1c4];
    int sub;
    char pad_1C8[0x60c];
    struct Triple triple;
};

void func_ov003_02212a14(struct UnkStruct_02212a14 *s)
{
    struct Triple *p = &s->triple;
    struct Triple local;
    local.a = p->a;
    local.b = p->b;
    local.c = p->c;
    func_02010d88(s, &local, 0xf33, 0x1000);
    func_02089fc8(&s->sub);
}
