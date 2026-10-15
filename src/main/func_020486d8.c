/* func_020486d8 @ 0x020486d8, 0x100 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;
typedef struct {
    int unk_00;
    Pair pos;
} UnkStruct_020486d8;
extern int func_020644cc(int n);
extern unsigned short *func_0204f5e0(UnkStruct_020486d8 *e, int a, int b, int c, int d, int f);
extern void func_0204f800(int *o1, int *o2, int a, int b, int c, int d);
extern int func_02049944(UnkStruct_020486d8 *e, Pair *p1, Pair *p2, void *cb);
extern int func_02049bc4(void *, void *, void *, void *);
void func_020486d8(int unused, UnkStruct_020486d8 *ent, int nx, int ny)
{
    void *ptr;
    int y;
    int x0 = 0;
    int zn = 0;
    int zj = 0;
    int z6 = 0;
    int zflag = 0;
    int o1;
    int o2;
    Pair v1;
    Pair v2;
    Pair arr[256];
    int n;
    int i;
    int j;
    int k;
    int x;
    int flag;
    int a1;
    int b1;
    Pair *p;
    unsigned short *r;
    Pair *q;
    Pair *e;
    for (y = 0; y < ny; y++) {
        for (x = x0; x < nx; x++) {
            if (func_020644cc(100) < 20) {
                p = arr;
                do {
                    p->a = zn;
                    p->b = zn;
                    p++;
                } while (p != (arr + 256));
                n = zn;
                i = n;
                do {
                    j = zj;
                    do {
                        r = func_0204f5e0(ent, x + 1, (y + 1) ^ 0, j, i, z6);
                        if (r != 0) {
                            flag = zflag;
                            if ((*r) <= 0x19) {
                                flag = 1;
                            }
                            if (flag != 0) {
                                func_0204f800(&o1, &o2, x + 1, y + 1, j, i);
                                e = &arr[n];
                                arr[n].a = o1;
                                e->b = o2;
                                n++;
                            }
                        }
                        j++;
                    } while (j < 16);
                    i++;
                } while (i < 16);
                if (n > 0) {
                    k = func_020644cc(n);
                    ptr = (void *) func_02049bc4;
                    q = &ent->pos;
                    a1 = q->a << 4;
                    b1 = q->b << 4;
                    e = &arr[k];
                    v2.a = arr[k].a;
                    v2.b = e->b;
                    v1.a = a1;
                    v1.b = b1;
                    func_02049944(ent, &v1, &v2, ptr);
                }
            }
        }
    }
}
