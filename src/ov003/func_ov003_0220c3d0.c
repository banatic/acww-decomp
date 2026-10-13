/* func_ov003_0220c3d0 @ 0x0220c3d0, 0x1ac bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;

typedef struct UnkStruct_0220c3d0 UnkStruct_0220c3d0;
struct UnkStruct_0220c3d0 {
    char pad_00[0x5c];
    Vec unk_5C;
};

extern int func_020eaa6c(Vec *, Vec *);
extern int func_020ea990(Vec *, Vec *);
extern void func_0200fa8c(Vec *, UnkStruct_0220c3d0 *);
extern int func_0200ff28(UnkStruct_0220c3d0 *, Vec *, int, int);
extern int func_0200ffec(UnkStruct_0220c3d0 *);
extern void func_ov003_0220fb30(UnkStruct_0220c3d0 *, int, int, int, int, int, int);
extern void func_ov003_02217234(UnkStruct_0220c3d0 *, int, int);
extern void func_ov003_02212c58(UnkStruct_0220c3d0 *, int, int);
extern void func_ov003_02214644(UnkStruct_0220c3d0 *, int, int);
extern int func_ov003_0220ced4(UnkStruct_0220c3d0 *, Vec *, Vec *);
extern void func_ov003_02215f00(UnkStruct_0220c3d0 *, Vec *, int, int);
extern void func_ov003_02215ce4(UnkStruct_0220c3d0 *, int, int);
extern void func_ov003_0221066c(UnkStruct_0220c3d0 *, int, int);
extern void func_ov003_02210354(UnkStruct_0220c3d0 *, int, int);
extern void func_ov003_0220d8bc(UnkStruct_0220c3d0 *, int, int);
extern void func_ov003_0220ddb0(UnkStruct_0220c3d0 *, int, int);
extern void func_ov003_0220dbb4(UnkStruct_0220c3d0 *, int, int);
extern void func_ov003_02217450(UnkStruct_0220c3d0 *, int, int);

int func_ov003_0220c3d0(UnkStruct_0220c3d0 *self, int ev, Vec *arg)
{
    Vec b;
    Vec a;
    Vec c;
    Vec d;
    Vec e;
    Vec g;
    Vec *q;
    int f;

    switch (ev) {
        case 2:
            func_ov003_02217234(self, 6, -1);
            return 1;
        case 1:
            func_ov003_02212c58(self, 6, -1);
            return 1;
        case 4:
            func_ov003_02214644(self, 6, -1);
            return 1;
        case 3:
            a.x = 0;
            a.y = 0;
            a.z = 0;
            if (func_020eaa6c(arg, &a) != 0) {
                q = &self->unk_5C;
                arg->x = self->unk_5C.x;
                arg->y = q->y;
                arg->z = q->z;
            }
            if (func_ov003_0220ced4(self, &b, arg) != 0) {
                c.x = b.x;
                c.y = b.y;
                c.z = b.z;
                func_ov003_02215f00(self, &c, 6, -1);
            } else {
                func_ov003_02215ce4(self, 6, -1);
            }
            return 1;
        case 5:
            func_ov003_0221066c(self, 6, -1);
            return 1;
        case 6:
            func_ov003_02210354(self, 6, -1);
            return 1;
        case 7:
            func_ov003_0220d8bc(self, 6, -1);
            return 1;
        case 8:
            func_ov003_0220ddb0(self, 6, -1);
            return 1;
        case 9:
            func_ov003_0220dbb4(self, 6, -1);
            return 1;
        case 0:
        case 10:
            d.x = 0;
            d.y = 0;
            d.z = 0;
            if (func_020eaa6c(arg, &d) != 0) {
                func_0200fa8c(&e, self);
                arg->x = e.x;
                arg->y = e.y;
                arg->z = e.z;
            }
            func_0200fa8c(&g, self);
            b.x = g.x;
            b.y = g.y;
            b.z = g.z;
            if (func_020ea990(&self->unk_5C, arg) < 0x2334) {
                if (func_0200ff28(self, &b, 1, 0) != 0) {
                    if (func_0200ffec(self) == 1) {
                        f = 0;
                    } else {
                        f = 1;
                    }
                    func_ov003_0220fb30(self, b.x, b.z, f, 0, 6, -1);
                    return 1;
                }
            }
            if (ev == 10) {
                func_ov003_02217450(self, 6, -1);
                return 1;
            }
            break;
    }
    return 0;
}
