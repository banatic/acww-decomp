/* func_ov003_02222f0c @ 0x02222f0c, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(void *);
extern void *func_020984e8(void);
extern int func_02099020(void *, int);
extern void func_0204f794(void *, int, int);
extern int func_ov003_02223078(void *, void *);
extern void func_01ffd070(void *, void *, void *);
extern void func_ov003_02221054(void *, int, void *, void *);

typedef struct {
    int x, y, z;
} Vec;
struct UnkStruct_02222f0c {
    int x, y;
};
struct UnkStruct_02222f0c_2 {
    Vec a, b, c, d;
};

extern unsigned char data_020ccf94[];
extern unsigned char data_ov003_02239f5c[];

void func_ov003_02222f0c(void *p0, struct UnkStruct_02222f0c *p1)
{
    int args[2];
    struct UnkStruct_02222f0c_2 t;
    Vec *tbl;
    Vec *e;
    if (func_02073d90(*(void **) data_020ccf94) != 0) {
        return;
    }
    if (func_02099020(func_020984e8(), 1) != 0) {
        return;
    }
    func_0204f794(&t.a, p1->x, p1->y);
    tbl = *(Vec **) data_ov003_02239f5c;
    e = &tbl[func_ov003_02223078(p0, &t.a)];
    func_01ffd070(&t.c, &t.a, e);
    t.b.x = t.c.x;
    t.b.y = t.c.y;
    t.b.z = t.c.z;
    t.d.x = t.c.x;
    t.d.y = t.c.y;
    t.d.z = t.c.z;
    args[0] = p1->x;
    args[1] = p1->y;
    func_ov003_02221054(p0, 0x1569, args, &t.d);
}
