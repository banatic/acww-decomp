/* func_ov004_0223362c @ 0x0223362c, 0x98 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b;
} UnkStruct_0223362c;
typedef struct {
    int a, b, c;
} UnkStruct_0223362c_2;
typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[0x94 - 8];
} Elem;

extern void *data_021c80bc;
extern void func_ov004_02233a00(Elem *p, int b, UnkStruct_0223362c *c, UnkStruct_0223362c_2 *d, UnkStruct_0223362c_2 *e,
                                int ff, unsigned short g, void *glob, short h, unsigned char i);

int func_ov004_0223362c(Elem *base, int b, UnkStruct_0223362c *c, UnkStruct_0223362c_2 *d, UnkStruct_0223362c_2 *e, int ff,
                        unsigned short g, short h, unsigned char i)
{
    UnkStruct_0223362c cc;
    UnkStruct_0223362c_2 dd, ee;
    void *glob;
    Elem *p;
    int found;
    int k;

    glob = data_021c80bc;
    if (glob == 0) {
        return 0;
    }
    p = &base[b * 3];
    found = 0;
    for (k = 0; k < 3; k++) {
        if (p->unk_04 == 0) {
            dd.a = d->a;
            dd.b = d->b;
            dd.c = d->c;
            ee.a = e->a;
            ee.b = e->b;
            ee.c = e->c;
            cc.a = c->a;
            cc.b = c->b;
            func_ov004_02233a00(p, b, &cc, &dd, &ee, ff, g, glob, h, i);
            p->unk_04 = 2;
            found = 1;
            break;
        }
        p++;
    }
    return found;
}
