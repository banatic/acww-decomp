/* museum_room_setup_2: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02245458 @ 0x02245458, 0x4 bytes, Thumb
 * func_ov004_02245454 @ 0x02245454, 0x4 bytes, Thumb
 * func_ov004_022453c0 @ 0x022453c0, 0x94 bytes, Thumb
 * func_ov004_022453a8 @ 0x022453a8, 0x18 bytes, Thumb
 * func_ov004_02245390 @ 0x02245390, 0x18 bytes, Thumb
 * func_ov004_02245378 @ 0x02245378, 0x18 bytes, Thumb
 * func_ov004_02245358 @ 0x02245358, 0x20 bytes, Thumb
 */

typedef struct Elem {
    char pad_00[0x1c];
} Elem;

typedef struct Row {
    unsigned char id;
    char pad_01[3];
    Elem *arr;
    unsigned int n;
} Row;

struct _Obj {
    void *vtbl;
};

extern Row data_ov004_0224b868[];
extern int func_020b65c4(void);
extern int func_ov004_02245544(Elem *e);
extern unsigned int *func_ov004_02245554(Elem *e);
extern int func_ov004_0224554c(Elem *e);
extern int func_ov004_02245548(Elem *e);
extern short func_ov004_0224553c(Elem *e);
extern int func_ov004_02245538(Elem *e);
extern int func_ov004_02245534(Elem *e);
extern void func_ov004_0221b224(int a, void *position, int c, int d, short e, int f, int g);
extern int func_020edf70(int);
extern void *func_ov004_022454fc(void *arg);
extern int data_ov004_02256780;
extern void *func_ov004_02245474(void *);
extern void func_020edf54(void *);

void *func_ov004_02245390(void *arg);

int func_ov004_02245458(void)
{
    return 1;
}

int func_ov004_02245454(void)
{
    return 1;
}

void func_ov004_022453c0(void)
{
    // DECLS
    unsigned int j;
    Elem *e;
    Row *r;
    unsigned int n;
    unsigned int i;
    int k;
    // ENDDECLS

    k = func_020b65c4();
    for (i = 0; i < 7; i++) {
        r = &data_ov004_0224b868[i];
        if (k == data_ov004_0224b868[i].id) {
            for (j = 0, n = r->n; j < n; j++) {
                e = &r->arr[j];
                func_ov004_0221b224(func_ov004_02245544(e), func_ov004_02245554(e), func_ov004_0224554c(e),
                                    func_ov004_02245548(e), func_ov004_0224553c(e), func_ov004_02245538(e),
                                    func_ov004_02245534(e));
            }
            break;
        }
    }
}

void func_ov004_022453a8(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result == 0) {
        return;
    }
    func_ov004_02245390((void *) result);
}

void *func_ov004_02245390(void *arg)
{
    func_ov004_022454fc(arg);
    *(void **) arg = &data_ov004_02256780;
    return arg;
}

void *func_ov004_02245378(void *arg)
{
    *((void **) arg) = &data_ov004_02256780;
    func_ov004_02245474(arg);
    return arg;
}

void *func_ov004_02245358(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02256780);
    func_ov004_02245474(obj);
    func_020edf54(obj);
    return obj;
}
