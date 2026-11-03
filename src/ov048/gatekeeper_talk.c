/* gatekeeper_talk: 12 functions, module ov048
 * mwccarm 1.2/base -O4,s
 * func_ov048_02260d28 @ 0x02260d28, 0x100 bytes, Thumb
 * func_ov048_02260cd0 @ 0x02260cd0, 0x58 bytes, Thumb
 * func_ov048_02260c88 @ 0x02260c88, 0x48 bytes, Thumb
 * func_ov048_02260b64 @ 0x02260b64, 0x124 bytes, Thumb
 * func_ov048_02260b4c @ 0x02260b4c, 0x18 bytes, Thumb
 * func_ov048_02260ae8 @ 0x02260ae8, 0x64 bytes, Thumb
 * func_ov048_02260a60 @ 0x02260a60, 0x88 bytes, Thumb
 * func_ov048_02260a24 @ 0x02260a24, 0x3c bytes, Thumb
 * func_ov048_022609fc @ 0x022609fc, 0x28 bytes, Thumb
 * func_ov048_022609d0 @ 0x022609d0, 0x2a bytes, Thumb
 * func_ov048_022609a4 @ 0x022609a4, 0x2a bytes, Thumb
 * func_ov048_0226077c @ 0x0226077c, 0x228 bytes, Thumb
 */

typedef struct {
    char pad_00[0x18];
    unsigned char unk_18;
} LocalBuf;

typedef struct {
    unsigned char pad_00[0x812];
    unsigned char flag812;
} UnkStruct_02260c88;

typedef struct {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x74];
    void *unk_B8;
} ObjStruct;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_0226077c;

typedef struct {
    char x[0x40];
} UnkStruct_0226077c_2;

extern int func_ov048_02260f64(void *self, int x);
extern int func_ov048_02260f00(void *self);
extern int func_02074308(void);
extern int func_020ec148(void);
extern void func_020730c8(void);
extern void **func_020eb92c(void);
extern int func_020eb998(void *p);
extern void *func_020eb9c4(void *p);
extern void MI_CpuCopy8(void *a, void *buf, int b);
extern int func_020eb8d8(void *p);
extern void func_ov048_022616b8(void *self, int a);
extern int func_ov048_02260f30(void *p);
extern unsigned int func_02073044(void);
extern int func_020ec920(void);
extern int func_020ec1e8(void);
extern int func_020ec260(void);
extern void func_02074294(void *);
extern void func_02074120(void);
extern int func_0207417c(int arg);
extern int func_0208602c(void);
extern int func_020860c4(int);
extern int func_02087f30(void *);
extern int func_020984e8(void);
extern unsigned int func_02099688(unsigned int);
extern int func_0208829c(void *);
extern void func_02088284(void *);
extern int func_02074150(void);
extern void func_02088290(void *);
extern int func_020a6f44(void);
extern int func_02075dcc(void *addr, int arg2);
extern int data_020ccf94;
extern void func_020732b4(int arg1, int arg2);
extern void func_020a6f10(int arg);
extern void func_020a6ef0(int arg);
extern void func_020a13c4(unsigned long value);
extern void func_ov048_02262378(ObjStruct *obj);
extern void func_ov048_022635f4(void *ptr, int arg2);
extern int func_020eba18(void);
extern void func_ov048_02260e28(void *receiver, int code, int flag);
extern void func_0206844c(void *obj, char *cmd, void *data);
extern void *data_ov048_02263d20;
extern void *func_02073144(void *);
extern void func_020a0194(void);
extern void *func_02099664(void *);
extern void *func_02077bcc(void *record);
extern long long func_020eb694(int);
extern void func_ov048_02262588(void *p, unsigned long long value);
extern int func_020a0174(void);
extern int func_02073918(int, int);
extern int func_02073d90(int);
extern int func_020e8b0c(int, int, int);
extern void *func_020b5630(UnkStruct_0226077c_2 *);
extern int func_020b45d0(UnkStruct_0226077c_2 *, int, int, int, int, int);
extern void func_02068404(int, int, UnkStruct_0226077c_2 *);
extern void *func_020b5618(UnkStruct_0226077c_2 *);

unsigned char func_ov048_022609a4(void *receiver);

void func_ov048_02260d28(void *self)
{
    int n;
    void **tbl;
    unsigned char i;
    int flag_init;
    void *entry;
    int value;
    LocalBuf lbuf;
    int flag;

    if (func_ov048_02260f64(self, 0)) {
        return;
    }
    if (func_ov048_02260f00(self)) {
        return;
    }

    func_02074308();
    n = func_020ec148();
    if (n <= 0) {
        return;
    }

    func_020730c8();
    tbl = func_020eb92c();
    flag_init = 0;

    for (i = 0; i < n; i++) {
        entry = tbl[i];
        if (entry == 0) {
            continue;
        }

        func_020730c8();
        value = func_020eb998(entry);
        if (value != 0x1a) {
            continue;
        }

        func_020730c8();
        MI_CpuCopy8(func_020eb9c4(entry), &lbuf, value);
        if (lbuf.unk_18 != 0) {
            continue;
        }

        flag = (*((unsigned char *) entry + 2) == *((unsigned char *) self + 0x30e) &&
                *((unsigned char *) entry + 3) == *((unsigned char *) self + 0x30f) &&
                *((unsigned char *) entry + 4) == *((unsigned char *) self + 0x310) &&
                *((unsigned char *) entry + 5) == *((unsigned char *) self + 0x311) &&
                *((unsigned char *) entry + 6) == *((unsigned char *) self + 0x312) &&
                *((unsigned char *) entry + 7) == *((unsigned char *) self + 0x313))
                   ? 1
                   : flag_init;

        if (flag == 0) {
            continue;
        }

        func_020730c8();
        func_020eb8d8(entry);
        *(short *) ((char *) (*(void **) ((char *) self + 0xb8)) + 0xe6e) = 0xc8;
        func_ov048_022616b8(self, 5);
    }
}

void func_ov048_02260cd0(void *param1)
{
    if (func_ov048_02260f64(param1, 0) != 0) {
        return;
    }
    if (func_ov048_02260f30(param1) != 0) {
        return;
    }
    func_02073044();
    if (func_020ec920() == 0) {
        return;
    }
    if (func_020ec1e8() == 3) {
        goto skip;
    }
    func_020ec1e8();
skip:
    *(unsigned short *) (*(unsigned char **) ((unsigned char *) param1 + 0xb8) + 0xe6e) = 0xc8;
    func_ov048_022616b8(param1, 6);
    func_02074294((void *) func_020ec260());
}

void func_ov048_02260c88(UnkStruct_02260c88 *self)
{
    int flag;

    func_02073044();
    if (func_020ec920() == 0) {
        flag = 1;
    } else {
        flag = 0;
    }

    if (func_ov048_02260f64((void *) self, flag)) {
        func_02074120();
    } else {
        if (func_0207417c(0)) {
            self->flag812 = 0;
            func_ov048_022616b8((void *) self, 7);
        }
    }
}

void func_ov048_02260b64(ObjStruct *obj)
{
    int flag, val, r, r2;

    func_02073044();
    flag = !func_020ec920();
    if (func_ov048_02260f64((void *) obj, flag) != 0) {
        func_02074120();
        if (func_02087f30((void *) func_020860c4((int) func_0208602c())) != 0) {
            if (func_0208829c((void *) func_02099688((unsigned int) func_020984e8())) != 0) {
                func_02088284((void *) func_02099688((unsigned int) func_020984e8()));
            }
        }
        return;
    }

    val = func_02074150();
    if (val == 5) {
        if (func_02087f30((void *) func_020860c4((int) func_0208602c())) != 0) {
            if (func_0208829c((void *) func_02099688((unsigned int) func_020984e8())) == 0) {
                func_02088290((void *) func_02099688((unsigned int) func_020984e8()));
            }
        }
        r = func_020a6f44();
        if (func_02075dcc((char *) obj + 0x812, r) != 0) {
            func_020732b4(data_020ccf94, 0);
            func_020a6f10(0);
            func_020a6ef0(0);
            func_020a13c4((unsigned long) func_020ec260());
            func_02074120();
            *(int *) ((char *) obj->unk_40 + 0x14) = 0;
            func_ov048_02262378(obj);
            func_ov048_022616b8((void *) obj, 0);
            func_ov048_022635f4(obj->unk_B8, 0xC);
        }
        return;
    }

    if (val != 6) {
        if (func_020eba18() != 0x800c) {
            return;
        }
    }
    func_02074120();
    if (func_020eba18() == 0x800c) {
        func_ov048_02260e28(obj, 0x79, 1);
    } else {
        r2 = func_ov048_022609a4(obj);
        func_ov048_02260e28(obj, r2, 0);
    }
}

void func_ov048_02260b4c(int arg0)
{
    func_0207417c(1);
    func_ov048_022616b8((void *) arg0, 9);
}

void func_ov048_02260ae8(void *self)
{
    char *obj;
    int ret;
    char local;

    obj = *(char **) ((char *) self + 0x40);
    ret = func_02074150();
    if ((unsigned) (ret - 5) > 1) {
        return;
    }
    func_ov048_02262378((ObjStruct *) self);
    func_ov048_022616b8(self, 0);
    if (ret == 5) {
        *(unsigned int *) (obj + 0x14) = 0;
        func_ov048_022635f4(*(void **) ((char *) self + 0xb8), 13);
        func_020a6f10(1);
        func_020a6ef0(1);
    } else {
        local = 12;
        func_0206844c(obj, &local, data_ov048_02263d20);
    }
    func_02074120();
}

int func_ov048_02260a60(void *obj)
{
    char *base;
    int n, i, ret;
    long long v;

    base = func_02073144((*(void * *) &data_020ccf94));
    n = 0;
    for (i = 0; i < 0x20; i++) {
        if (*(unsigned char *) (base + i * 0x23 + 0x1a0) == 6) {
            n++;
        }
    }
    ret = 0;
    switch (*(unsigned char *) ((char *) obj + 0x813)) {
        case 0:
            func_020a0194();
            ret = 0x26;
            v = func_020eb694((int) func_02077bcc(func_02099664((void *) func_020984e8())));
            func_ov048_02262588(obj, (unsigned long long) v);
            func_020a0174();
            break;
        case 1:
            if (n != 0) {
                ret = 0x6b;
            } else {
                ret = 0x46;
            }
            break;
        case 2:
            ret = 0x5d;
            break;
    }
    return ret;
}

int func_ov048_02260a24(void *receiver)
{
    int r4;

    r4 = data_020ccf94;
    if (func_02073918(r4, 0) != 0) {
        if (func_02073d90(r4) != 0) {
            return 0x17;
        } else {
            if (func_020ec1e8() == 3) {
                return 0x3a;
            } else {
                return 0x38;
            }
        }
    } else {
        return 0x3d;
    }
}

unsigned char func_ov048_022609fc(void *receiver)
{
    int val;
    if (func_02073918(data_020ccf94, 0) != 0) {
        val = 0x21;
    } else {
        val = 0x22;
    }
    return (unsigned char) val;
}

unsigned char func_ov048_022609d0(void *receiver)
{
    int flag = 1;
    if (func_020ec1e8() != 3 && func_020ec1e8() != 4) {
        flag = 0;
    }
    return (unsigned char) (flag ? 0x82 : 0x65);
}

unsigned char func_ov048_022609a4(void *receiver)
{
    int flag = 1;
    if (func_020ec1e8() != 3 && func_020ec1e8() != 4) {
        flag = 0;
    }
    {
        int val = flag ? 0x80 : 0x63;
        return ((unsigned) val << 24) >> 24;
    }
}

int func_ov048_0226077c(UnkStruct_0226077c *p, int id)
{
    UnkStruct_0226077c_2 a;
    UnkStruct_0226077c_2 b;
    int code;
    int q;

    code = 0x84;
    if (id == 0x4e85 || id == 0x5bcf || func_020e8b0c(id, 0x59d8, 0x5dbf) != 0) {
        code = 0x83;
    } else if (func_020e8b0c(id, 0x4e86, 0x4e8b) != 0 || id == 0x4e8d || func_020e8b0c(id, 0x4e8f, 0x5207) != 0 ||
               func_020e8b0c(id, 0xcb24, 0xcb82) != 0 || func_020e8b0c(id, 0xcc4c, 0xccaf) != 0 ||
               func_020e8b0c(id, 0xcf08, 0xcf6b) != 0 || func_020e8b0c(id, 0xcf6c, 0xcfcf) != 0 ||
               func_020e8b0c(id, 0xcfd0, 0xd033) != 0) {
        code = 0x84;
    } else if (id == 0x4e8c) {
        code = 0x85;
    } else if (id == 0x4e8e) {
        code = 0x86;
    } else if (id == 0xc3b3) {
        code = 0x87;
    } else if (func_020e8b0c(id, 0xc79b, 0xc79e) != 0 || func_020e8b0c(id, 0xc7a0, 0xc7fe) != 0 ||
               func_020e8b0c(id, 0xc864, 0xc8c6) != 0) {
        code = 0x88;
    } else if (id == 0xc79f) {
        code = 0x89;
    } else if (func_020e8b0c(id, 0xc800, 0xc863) != 0) {
        code = 0x8a;
    } else if (func_020e8b0c(id, 0xcb20, 0xcb23) != 0 || func_020e8b0c(id, 0xcb84, 0xcb87) != 0 ||
               func_020e8b0c(id, 0xcbe8, 0xcbeb) != 0) {
        code = 0x8b;
    }

    q = id / 1000;
    func_020b5630(&a);
    func_020b5630(&b);
    func_020b45d0(&a, q, 2, 6, 0, 0);
    func_020b45d0(&b, id - q * 1000, 3, 6, 0, 0);
    func_02068404(p->unk_40, 6, &a);
    func_02068404(p->unk_40, 7, &b);
    func_020b5618(&b);
    func_020b5618(&a);
    return code;
}
