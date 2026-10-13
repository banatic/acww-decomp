/* func_020fa9f4 @ 0x020fa9f4, 0x178 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

// SPL manager setup: allocates the manager and fills the emitter and resource free lists.
// b2f is a bitfield so that it packs into the byte at 0x2F.
typedef void *(*Alloc)(unsigned int);

struct Mgr {
    Alloc alloc;
    unsigned int l1h, l1t;
    unsigned int l2h, l2t;
    unsigned int l3h, l3t;
    unsigned int unk_1C;
    unsigned int unk_20;
    unsigned short unk_24;
    unsigned short unk_26;
    unsigned short unk_28;
    unsigned short unk_2A;
    unsigned int q0 : 6;
    unsigned int q1 : 6;
    unsigned int q2 : 6;
    unsigned int q3 : 6;
    unsigned int b2f : 8;
    unsigned int unk_30;
    unsigned int unk_34;
    unsigned int unk_38;
};

extern void MI_CpuFill8(void *, int, unsigned int);
extern void func_020ff8ec(unsigned int *, void *);

struct Mgr *func_020fa9f4(Alloc alloc, int a, int b, int c, unsigned short d, unsigned short e)
{
    struct Mgr *m;
    int i;
    char *p;

    m = (struct Mgr *) alloc(0x3c);
    MI_CpuFill8(m, 0, 0x3c);
    m->unk_28 = (unsigned short) a;
    m->unk_2A = (unsigned short) b;
    m->q0 = d;
    m->q1 = e;
    m->q2 = m->q0;
    m->q3 = c;
    m->b2f = 0;
    m->alloc = alloc;
    m->l1t = 0;
    m->l2t = 0;
    m->l3t = 0;
    m->l1h = 0;
    m->l2h = 0;
    m->l3h = 0;
    m->unk_30 = 0;
    p = (char *) alloc(a * 0x84);
    MI_CpuFill8(p, 0, a * 0x84);
    for (i = 0; i < a; i++) {
        func_020ff8ec(&m->l2h, p);
        p += 0x84;
    }
    p = (char *) alloc(b * 0x44);
    MI_CpuFill8(p, 0, b * 0x44);
    for (i = 0; i < b; i++) {
        func_020ff8ec(&m->l3h, p);
        p += 0x44;
    }
    m->unk_1C = 0;
    m->unk_20 = 0;
    m->unk_26 = 0;
    m->unk_24 = m->unk_26;
    return m;
}
