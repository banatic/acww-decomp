/* villager_entry_2: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207d634 @ 0x0207d634, 0x90 bytes, Thumb
 * func_0207d608 @ 0x0207d608, 0x2c bytes, Thumb
 * func_0207d5dc @ 0x0207d5dc, 0x2c bytes, Thumb
 * func_0207d5bc @ 0x0207d5bc, 0x1e bytes, Thumb
 * func_0207d578 @ 0x0207d578, 0x42 bytes, Thumb
 * func_0207d540 @ 0x0207d540, 0x36 bytes, Thumb
 * func_0207d4bc @ 0x0207d4bc, 0x84 bytes, Thumb
 */

typedef struct {
    char pad_00[0x78c];
    unsigned short arr[10];
    char pad_7A0[0x30];
    unsigned short bitfield;
} UnkStruct_0207d634;

struct UnkStruct_0207d608 {
    char pad_00[0x7d0];
    unsigned short unk_7D0;
};

extern int func_0204bcdc(unsigned short *p);
extern int func_020644cc(int x);
extern int func_0207cc54(int mask, int count, int max);
extern int func_0207ffa0(void *p, int shift);
extern void func_020819d0(void *);
extern int func_0208150c(int a);
extern int func_02003704(int x);
extern void func_0209e474(void *p);
extern int func_020036e8(int x);
extern int func_020821d4(int x, void *p);
extern int func_020951bc(int);
extern int func_020807a8(int, int);
extern void func_020818c0(unsigned short *);
extern short data_021dc7aa;
extern void *func_020984e8(void);
extern void *func_02099870(void *a);
extern int func_02094ffc(void *m);
extern void *func_02099158(void *a);
extern int func_02081d20(void *e);
extern int func_02099d08(void *a, int b, int c, int d);

void func_0207d634(UnkStruct_0207d634 *self)
{
    unsigned short *p = self->arr;
    unsigned short mask = 0;
    int count = 0;
    int i;
    int n;

    self->bitfield = mask;
    for (i = 0; i < 10; i++) {
        if (func_0204bcdc(p) != 0) {
            mask |= (1 << i);
            count++;
        }
        p++;
    }

    n = count;
    if (count > 5) {
        n = 5;
    }
    if (n > 3) {
        n = func_020644cc(n - 2) + 3;
    }

    if (count > 0) {
        while (n > 0) {
            int res = func_0207cc54(mask, count, 10);
            if (res != -1) {
                self->bitfield |= (1 << res);
                mask &= ~(1 << res);
                count--;
            }
            n--;
        }
    }
}

int func_0207d608(void *p, int shift)
{
    if (func_0207ffa0(p, shift) && (((struct UnkStruct_0207d608 *) p)->unk_7D0 >> shift) & 1) {
        return 1;
    } else {
        return 0;
    }
}

void func_0207d5dc(int param1, int param2)
{
    int r5;
    int r4;
    int r0;
    unsigned short *r0_ptr;
    unsigned short r2;
    int r1;

    r5 = param1;
    r4 = param2;
    r0 = func_0207ffa0((void *) param1, param2);
    if (r0 != 0) {
        r0_ptr = (unsigned short *) (r5 + 0x7d0);
        r2 = *r0_ptr;
        r1 = 1 << r4;
        r2 &= ~r1;
        *r0_ptr = r2;
    }
}

void func_0207d5bc(void *arg0)
{
    void *p;
    int i;

    p = arg0;
    for (i = 0; i < 8; i++) {
        func_020819d0(p);
        p = (char *) p + 0x80;
    }
}

int func_0207d578(int a, void *b)
{
    int work[2];

    if (func_02003704(func_0208150c(a)) == 0) {
        goto fail;
    }

    work[0] = 0;
    work[1] = 0;

    if (b == 0) {
        func_0209e474(work);
        b = work;
    }

    return func_020821d4(func_020036e8(func_0208150c(a)), b);

fail:
    return 0;
}

void func_0207d540(int r0, int r1)
{
    unsigned short *condition_value0;
    int r5 = r0;
    int r4 = r1;
    int temp;

    temp = func_02003704((int) ((void *) (unsigned int) func_0208150c(r0)));
    if (temp != 0) {
        if (func_020951bc(r4) != 0) {
            if ((condition_value0 = (unsigned short *) (func_020807a8(r5, r4))) != 0) {
                func_020818c0(condition_value0);
            }
        }
    }
}

int func_0207d4bc(void *p0, void *p1)
{
    int t;
    void *a;
    void *m;
    void *e;
    int h;

    a = p1;
    if (func_02003704(func_0208150c((int) p0)) == 0) {
        goto zero;
    }
    t = (int) &data_021dc7aa;
    if (a == 0) {
        a = func_020984e8();
    }
    if (a == 0) {
        goto zero;
    }
    if (t == 0) {
        goto zero;
    }
    m = func_02099870(a);
    if (func_020951bc((int) m) == 0) {
        goto zero;
    }
    if (func_02094ffc(m) != 1) {
        goto zero;
    }
    e = (void *) func_020807a8((int) p0, (int) m);
    if (e == 0) {
        goto zero;
    }
    a = func_02099158(a);
    h = func_0208150c((int) p0);
    return func_02099d08(a, h, func_02081d20(e), t);
zero:
    return 0;
}
