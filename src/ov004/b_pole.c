/* b_pole: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222f458 @ 0x0222f458, 0x1c bytes, Thumb
 * func_ov004_0222f440 @ 0x0222f440, 0x18 bytes, Thumb
 * func_ov004_0222f428 @ 0x0222f428, 0x18 bytes, Thumb
 * func_ov004_0222f408 @ 0x0222f408, 0x20 bytes, Thumb
 * func_ov004_0222f3a0 @ 0x0222f3a0, 0x68 bytes, Thumb
 * func_ov004_0222f38c @ 0x0222f38c, 0x12 bytes, Thumb
 * func_ov004_0222f378 @ 0x0222f378, 0x14 bytes, Thumb
 * func_ov004_0222f368 @ 0x0222f368, 0x10 bytes, Thumb
 */

struct _Obj {
    void *vtbl;
};

extern int func_020edf70(unsigned int size);
extern void *func_ov004_0222c87c(void *arg);
extern int data_ov004_02255290;
extern void *func_ov004_0222c7a0(void *);
extern void func_020edf54(void *);
extern void func_02055050(void *);
extern void func_02055060(void *, int, int, int, int, int);
extern int func_02055140(void *, int);
extern int func_ov004_0222c3c4(void *, int);
extern int func_ov004_0222c5c8(void *, void *);
extern void *data_021c9b24;
extern void *data_ov004_022552f8;
extern void func_02055124(void *);
extern void func_0205510c(void *, int);
extern void func_ov004_0222c598(char *parameter0);

void *func_ov004_0222f440(void *arg);

void func_ov004_0222f458(void)
{
    void *conditionInput0;

    if ((conditionInput0 = (void *) (func_020edf70(0x290)))) {
        func_ov004_0222f440((void *) conditionInput0);
    }
}

void *func_ov004_0222f440(void *arg)
{
    func_ov004_0222c87c(arg);
    *(void **) arg = &data_ov004_02255290;
    return arg;
}

void *func_ov004_0222f428(void *arg)
{
    *((void **) arg) = &data_ov004_02255290;
    func_ov004_0222c7a0(arg);
    return arg;
}

void *func_ov004_0222f408(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02255290);
    func_ov004_0222c7a0(obj);
    func_020edf54(obj);
    return obj;
}

int func_ov004_0222f3a0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c5c8(self, &data_ov004_022552f8);
    if (func_ov004_0222c3c4(self + 0x1a4, 0x0) != 0x0 &&
        func_02055140(self + 0xec, *(int *) ((char *) &data_021c9b24)) != 0x0) {
        func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0x0), 0x0, 0x1000, 0x0, 0x0);
        func_02055050(self + 0xec);
    }
    return 0x1;
}

int func_ov004_0222f38c(char *self)
{
    // DECLS
    // ENDDECLS
    func_02055124(self + 0xec);
    return 0x1;
}

int func_ov004_0222f378(char *self)
{
    // DECLS
    // ENDDECLS
    func_0205510c(self + 0xec, 0x0);
    return 0x1;
}

int func_ov004_0222f368(char *arg0)
{
    func_ov004_0222c598((char *) arg0);
    return 1;
}
