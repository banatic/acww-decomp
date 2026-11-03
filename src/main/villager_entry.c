/* villager_entry: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207d2b4 @ 0x0207d2b4, 0x88 bytes, Thumb
 * func_0207d278 @ 0x0207d278, 0x3a bytes, Thumb
 * func_0207d1f8 @ 0x0207d1f8, 0x80 bytes, Thumb
 * func_0207d18c @ 0x0207d18c, 0x6a bytes, Thumb
 * func_0207d16c @ 0x0207d16c, 0x20 bytes, Thumb
 * func_0207d148 @ 0x0207d148, 0x22 bytes, Thumb
 * func_0207d128 @ 0x0207d128, 0x20 bytes, Thumb
 * func_0207d0f0 @ 0x0207d0f0, 0x36 bytes, Thumb
 */

typedef struct {
    char pad_00[0x1e];
    unsigned char unk_1E;
} UnkStruct_0207d2b4;

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
} UnkStruct_0207d0f0;

extern int func_02003704(void *);
extern void *func_0207f270(void *);
extern void *func_020984e8(void);
extern int func_02099870(void *);
extern int func_020951bc(void *);
extern int func_02099020(void *, int);
extern int func_020807a8(void *, int);
extern int func_02081d20(void *object);
extern int func_020644cc(int);
extern unsigned int func_0208150c(unsigned int);
extern int func_020794c4(void *);
extern void func_02079468(unsigned char *);

void func_0207d0f0(void *arg0, int arg1);

void func_0207d2b4(void *a, void *b)
{
    int forwarded_value;

    UnkStruct_0207d2b4 *ptr;
    int c, d, e, val;

    if (func_02003704((void *) func_0208150c((unsigned int) a)) == 0) {
        goto end;
    }
    ptr = (UnkStruct_0207d2b4 *) func_0207f270(a);
    ptr->unk_1E = 0;
    if (b == 0) {
        b = func_020984e8();
    }
    if (b == 0) {
        goto end;
    }
    if (func_020951bc((void *) func_02099870(b)) == 0) {
        goto end;
    }
    if (func_02099020(b, 1) != 0) {
        goto end;
    }
    c = (int) func_02099870(b);
    if ((forwarded_value = (int) func_020807a8(a, c)) == 0) {
        goto end;
    }
    d = (int) func_02081d20((void *) forwarded_value);
    e = (int) func_020644cc(10);
    val = (d + 0x100) >> 7;
    val *= e + 1;
    if (val < 0) {
        val = 0;
    } else if (val > 32) {
        val = 32;
    }
    ptr->unk_1E = (unsigned char) val;
end:
    return;
}

int func_0207d278(int arg0)
{
    void *p;
    if (func_02003704((void *) func_0208150c(arg0)) != 0 && (p = func_0207f270((void *) arg0)) != 0 &&
        (func_020794c4(p) == 0 || func_020794c4(p) == 1)) {
        return 1;
    }
    return 0;
}

void func_0207d1f8(void *a, void *b)
{
    int forwarded_value;

    int x;
    int r4;
    int t;
    x = (int) func_0208150c((unsigned int) a);
    if (func_02003704((void *) x) == 0) {
        return;
    }
    r4 = 0;
    if (b == 0) {
        b = func_020984e8();
    }
    if (b != 0) {
        if (func_020951bc((void *) (func_02099870(b))) != 0 && func_02099020(b, 1) == 0 && func_0207d278((int) a) != 0 &&
            (forwarded_value = (int) func_020807a8(a, func_02099870(b))) != 0) {
            t = func_02081d20((void *) forwarded_value);
            r4 = func_020644cc(3) * ((t + 0x100) >> 7);
        }
    }
    func_0207d0f0(a, r4);
}

int func_0207d18c(int a, int b)
{
    int flag2;
    int result;

    if (b == 0) {
        b = (int) func_020984e8();
    }
    result = 0;
    flag2 = result;
    if (b != 0) {
        if (func_020951bc((void *) func_02099870((void *) b)) != 0) {
            if (func_02099020((void *) b, 1) == 0) {
                if (func_02003704((void *) func_0208150c(a)) != 0) {
                    if (*(unsigned char *) ((unsigned char *) func_0207f270((void *) a) + 0x1e) == 0x20) {
                        flag2 = 1;
                    }
                }
            }
        }
    }
    if (flag2 != 0) {
        if (func_0207d278(a) != 0) {
            result = 1;
        }
    }
    return result;
}

void func_0207d16c(void *arg0)
{
    void *pvVar1;

    if (func_02003704((void *) func_0208150c((unsigned int) arg0)) != 0) {
        pvVar1 = func_0207f270(arg0);
        *(unsigned char *) ((int) pvVar1 + 0x1e) = 0;
    }
    return;
}

void func_0207d148(unsigned char *param)
{
    unsigned char *ptr;
    unsigned char val;

    if (func_02003704((void *) func_0208150c((unsigned int) param)) != 0) {
        ptr = (unsigned char *) func_0207f270((void *) param);
        val = ptr[0x1e];
        val = (unsigned char) (val >> 1);
        ptr[0x1e] = val;
    }
}

void func_0207d128(int arg0)
{
    int val;

    val = func_02003704((void *) func_0208150c(arg0));
    if (val != 0) {
        func_02079468((unsigned char *) (int) func_0207f270((void *) arg0));
    }
    return;
}

void func_0207d0f0(void *arg0, int arg1)
{
    if (func_02003704((void *) ((int) func_0208150c((unsigned int) arg0)))) {
        UnkStruct_0207d0f0 *p;
        int value;
        p = (UnkStruct_0207d0f0 *) func_0207f270(arg0);
        value = arg1 + p->unk_1E;
        if (value < 0) {
            value = 0;
        } else if (value > 0x20) {
            value = 0x20;
        }
        p->unk_1E = value;
    }
}
