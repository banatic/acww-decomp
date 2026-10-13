/* func_0202f2f4 @ 0x0202f2f4, 0xec bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    int a, b;
};

extern "C" {
extern int func_0202f660(void *, void *);
extern int func_0202f838(Pair *, void *);
extern int FX_Sqrt(int);
extern void func_0202f898(Pair *, void *, Pair *);
extern int func_0202f7f4(Pair *);
extern void func_0202f8fc(Pair *, int, int);
extern int FX_MulFunc(int, int);
}

struct UnkStruct_0202f2f4 {
    virtual int v0();
    Pair p1;
    Pair p2;
    Pair p3;
};

extern "C" int func_0202f2f4(UnkStruct_0202f2f4 *o, Pair *dst, void *q, int lim)
{
    Pair w;
    Pair v[2];
    Pair *e;
    Pair *s;
    Pair *d;
    int t, n;

    if (o->v0() == 0) {
        return 0;
    }
    t = func_0202f660(o, dst);
    if (t >= 0 && t < lim + 0x200 && func_0202f660(o, q) > 0) {
        if (t < lim) {
            if (func_0202f660(o, q) <= 0) {
                return 0;
            }
            s = &o->p1;
            v[0].a = s->a;
            v[0].b = s->b;
            s = &o->p2;
            d = &v[1];
            d->a = s->a;
            d->b = s->b;
            e = &v[0];
            goto cond;
            do {
                n = FX_Sqrt(func_0202f838(e, dst));
                if (n < lim) {
                    func_0202f898(&w, dst, e);
                    if (func_0202f7f4(&w) == 0) {
                        s = &o->p3;
                        func_0202f8fc(&w, s->a, s->b);
                    } else {
                        lim -= n;
                    }
                    w.a = FX_MulFunc(w.a, lim);
                    w.b = FX_MulFunc(w.b, lim);
                    dst->a += w.a;
                    dst->b += w.b;
                    return 1;
                }
                e++;
            cond:;
            } while (e < &v[2]);
        } else {
            return 1;
        }
    }
    return 0;
}
