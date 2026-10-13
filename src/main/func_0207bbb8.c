/* func_0207bbb8 @ 0x0207bbb8, 0x170 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    unsigned char a, b;
} El;
typedef struct {
    int x, y;
} Pt;
typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_0207bbb8;
typedef struct {
    char pad_00[0xc];
    UnkStruct_0207bbb8 sub;
} UnkStruct_0207bbb8_2;

extern int data_021d1244;
extern El data_021d13a8[];
extern char data_021d1298[];
extern void func_02081fa0(void);
extern void func_02081f9c(void);
extern void func_0207bd28(void);

extern UnkStruct_0207bbb8_2 *func_0204e414(void);
extern void func_02138d6c(void *arr, int n, int sz, void *ctor, void *dtor);
extern void __register_global_object(int a, void *f, void *node);
extern void func_02081f94(El *e);
extern void *func_0204f5e0(UnkStruct_0207bbb8_2 *o, int cx, int cy, int fx, int fy, int k);
extern void func_02081f60(El *e, Pt *p);
extern void *func_0208150c(void *self);
extern int func_02003704(void *p);
extern int func_020800dc(void *self);
extern int func_020644cc(int n);
extern int func_0207bd48(El *arr, int n, int m);
extern int func_0204bbbc(int i);
extern int func_0204e404(UnkStruct_0207bbb8_2 *o, unsigned short *h, int a, int b);
extern void func_020800b8(void *self, El *e);

void func_0207bbb8(char *self)
{
    int n;
    UnkStruct_0207bbb8_2 *obj;
    int i;
    int j;
    int cx, cy;
    int px, py;
    void *t;
    int m;
    // DECLS
    int w;
    int h;
    El *e;
    int k;
    unsigned short hv;
    Pt p;
    // ENDDECLS

    obj = func_0204e414();
    if ((data_021d1244 & 1) == 0) {
        func_02138d6c(data_021d13a8, 0x1e, 2, (void *) func_02081fa0, (void *) func_02081f9c);
        __register_global_object(0, (void *) func_0207bd28, data_021d1298);
        data_021d1244 |= 1;
    }
    if (obj == 0) {
        return;
    }
    n = 0;
    {
        UnkStruct_0207bbb8 *q = &obj->sub;
        w = obj->sub.unk_00;
        h = q->unk_04;
    }
    p.x = 0;
    p.y = 0;
    i = n;
    do {
        func_02081f94(&data_021d13a8[i]);
        i++;
    } while (i < 0x1e);
    for (p.y = 0; p.y < h; p.y++) {
        for (p.x = 0; p.x < w; p.x++) {
            px = p.x;
            py = p.y;
            cx = px >> 4;
            cy = py >> 4;
            t = func_0204f5e0(obj, cx, cy, px - (cx << 4), py - (cy << 4), 0);
            if (t != 0 && *(unsigned short *) t == 0x500a) {
                func_02081f60(&data_021d13a8[n], &p);
                n++;
            }
        }
    }
    if (n <= 0) {
        return;
    }
    hv = 0xfff1;
    for (j = 0; j < 8; self += 0x7ec, j++) {
        if (func_02003704(func_0208150c(self)) != 0 && func_020800dc(self) == 0) {
            m = func_020644cc(n);
            k = func_0207bd48(data_021d13a8, 0x1e, m);
            hv = (unsigned short) func_0204bbbc(j);
            e = &data_021d13a8[k];
            if (func_0204e404(obj, &hv, data_021d13a8[k].a, e->b) != 0) {
                func_020800b8(self, e);
            }
            func_02081f94(e);
            n--;
            if (n <= 0) {
                return;
            }
        }
    }
}
