/* gatekeeper_talk_2: 23 functions, module ov048
 * mwccarm 1.2/base -O4,s
 * func_ov048_022616b8 @ 0x022616b8, 0x6 bytes, Thumb
 * func_ov048_0226166c @ 0x0226166c, 0x4c bytes, Thumb
 * func_ov048_02261640 @ 0x02261640, 0x2c bytes, Thumb
 * func_ov048_02261608 @ 0x02261608, 0x38 bytes, Thumb
 * func_ov048_022615dc @ 0x022615dc, 0x2c bytes, Thumb
 * func_ov048_022615a4 @ 0x022615a4, 0x38 bytes, Thumb
 * func_ov048_02261578 @ 0x02261578, 0x2c bytes, Thumb
 * func_ov048_02261540 @ 0x02261540, 0x38 bytes, Thumb
 * func_ov048_02261514 @ 0x02261514, 0x2c bytes, Thumb
 * func_ov048_022614dc @ 0x022614dc, 0x38 bytes, Thumb
 * func_ov048_022614ac @ 0x022614ac, 0x30 bytes, Thumb
 * func_ov048_02261380 @ 0x02261380, 0x12c bytes, Thumb
 * func_ov048_0226125c @ 0x0226125c, 0x124 bytes, Thumb
 * func_ov048_022611f0 @ 0x022611f0, 0x6c bytes, Thumb
 * func_ov048_022611a0 @ 0x022611a0, 0x50 bytes, Thumb
 * func_ov048_02261120 @ 0x02261120, 0x80 bytes, Thumb
 * func_ov048_022610f8 @ 0x022610f8, 0x28 bytes, Thumb
 * func_ov048_0226107c @ 0x0226107c, 0x7c bytes, Thumb
 * func_ov048_02260f64 @ 0x02260f64, 0x118 bytes, Thumb
 * func_ov048_02260f30 @ 0x02260f30, 0x34 bytes, Thumb
 * func_ov048_02260f00 @ 0x02260f00, 0x30 bytes, Thumb
 * func_ov048_02260ea8 @ 0x02260ea8, 0x58 bytes, Thumb
 * func_ov048_02260e78 @ 0x02260e78, 0x30 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[180];
    unsigned long unk_B4;
} UnkStruct_022616b8;

typedef struct {
    char pad_00[0xb4];
    int unk_B4;
    char pad_B8[0x813 - 0xb4 - 4];
    unsigned char flag;
} UnkStruct_0226166c;

struct UnkStruct_02261608 {
    char pad_00[0xb4];
    int unk_B4;
};

typedef struct {
    char pad_00[0xB4];
    int count;
} UnkStruct_02261514;

struct FieldStruct {
    char pad_00[0xb4];
    int unk_B4;
};

struct UnkStruct_022611f0;

struct UnkStruct_022611f0 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x3ec - 0x44];
    int unk_3EC;
};

struct UnkStruct_022611a0 {
    char pad_00[0x40];
    void *unk_40;
};

typedef struct UnkStruct_02261120 {
    char pad_00[0x40];
    void *unk_40;
} UnkStruct_02261120;

typedef struct {
    char pad_00[0x40];
    void *ptr;
    char pad_44[0x6a];
    unsigned char unk_AE;
    char pad_AF[0x762];
    unsigned char unk_811;
} UnkStruct_0226107c;

extern unsigned int func_02073044(void);
extern int func_020ec920(void);
extern void func_02073100(void);
extern int func_020eb844(void);
extern int func_0209fea4(void);
extern void func_020eb9fc(void);
extern int func_0209fdf8(void);
extern int func_0209fe40(void);
extern int func_0209fdd4(void);
extern int func_0209ff54(void);
extern int func_0209fdac(void);
extern int func_0209ff0c(void);
extern int func_0209fe1c(void);
extern int func_020eba08(void);
extern int func_020e8b0c(int, const char *, const char *);
extern void *data_020ccf94;
extern void *data_ov048_02263d20;
extern void *func_02073138(void *a);
extern void *func_020984e8(void);
extern void *func_02073144(void *a);
extern int func_020eb8a0(int a);
extern void func_ov048_02260e28(void *receiver, int code, int flag);
extern int func_020eb704(int a);
extern int func_020eb6b8(void *a);
extern void *func_02099664(void *a);
extern void *func_02077bc8(void *a);
extern void *func_02077d68(void *object);
extern void func_020eb6a0(void *a, void *b);
extern void *func_02077bcc(void *record);
extern void MI_CpuCopy8(void *dst, void *src, int size);
extern int func_020a15ac(void);
extern int func_ov048_02260a60(void *self);
extern void func_ov048_02262378(void *self);
extern int func_02074308(void);
extern int func_020ec148(void);
extern void func_020730c8(void);
extern void *func_020eb92c(void);
extern void *func_020641c8(void *);
extern void *func_02064170(void *);
extern void *func_02094fd4(void *);
extern void *func_02094f7c(void *);
extern int func_020eb998(void *);
extern void *func_020eb9c4(void *);
extern void func_020a8874(void *, void *, int);
extern int func_020a8a70(void *, void *, int, int);
extern void func_02068404(void *, int, void *);
extern void *func_02094f64(void *);
extern void *func_02094fbc(void *);
extern void *func_02064158(void *);
extern void *func_020641b0(void *);
extern int func_0206fc6c(void);
extern int func_0206fc8c(void);
extern int func_020eb868(int x);
extern void func_0206844c(void *ctx, char *msg, int val);
extern int func_ov048_02262658(void *receiver);
extern void func_02068440(void *ptr);
extern int func_020ec49c(void);
extern int func_0209985c(int object);
extern void func_0209fd54(void);
extern void func_0209fcd8(void);
extern void func_0209fc60(void);
extern void func_020a01f8(void);
extern int func_020a1518(void);
extern int func_ov048_02260474(unsigned int);
extern void func_020a1900(void);
extern void func_020c189c(void);
extern int func_020a17ec(void);
extern int func_020a1810(void);
extern void func_020c1874(void);
extern unsigned char data_ov048_02264704[];
extern int func_020eba18(void);
extern int func_020ec1e8(void);
extern void *func_020b5630(void *);
extern void *func_020b5618(void *);
extern int func_020b45d0(void *, int, int, int, int, int);
extern unsigned char func_ov048_022609d0(void *receiver);
extern int func_020e8840(int arg);
extern int func_ov048_0226077c(void *, int);

int func_ov048_022614ac(void);
int func_ov048_02260ea8(void *self);
int func_ov048_02260e78(void *this);

void func_ov048_022616b8(UnkStruct_022616b8 *p, unsigned long v)
{
    p->unk_B4 = v;
}

void func_ov048_0226166c(UnkStruct_0226166c *p)
{
    func_02073044();
    func_020ec920();
    if (func_ov048_02260ea8((void *) p) != 0) {
        return;
    }
    func_02073100();
    if (func_020eb844() == 0) {
        return;
    }
    if (p->flag == 0) {
        func_ov048_022616b8((UnkStruct_022616b8 *) p, 0x13);
    } else {
        func_ov048_022616b8((UnkStruct_022616b8 *) p, p->unk_B4 + 1);
    }
}

void func_ov048_02261640(int a)
{
    int *p;
    int v;

    if (func_0209fea4() != 0) {
        p = (int *) (a + 0xb4);
        v = *p + 1;
        func_ov048_022616b8((UnkStruct_022616b8 *) a, v);
    } else {
        p = (int *) (a + 0xb4);
        v = *p + 2;
        func_ov048_022616b8((UnkStruct_022616b8 *) a, v);
    }
}

void func_ov048_02261608(struct UnkStruct_02261608 *obj)
{
    int ret = func_ov048_022614ac();
    if (ret) {
        func_020eb9fc();
        func_ov048_022616b8((UnkStruct_022616b8 *) obj, obj->unk_B4 + 1);
    } else if (func_0209fdf8()) {
        func_ov048_022616b8((UnkStruct_022616b8 *) obj, obj->unk_B4 + 1);
    }
}

void func_ov048_022615dc(int param)
{
    int *p;
    int val;

    if (func_0209fe40() != 0) {
        p = (int *) (param + 0xb4);
        val = *p + 1;
        func_ov048_022616b8((UnkStruct_022616b8 *) param, val);
    } else {
        p = (int *) (param + 0xb4);
        val = *p + 2;
        func_ov048_022616b8((UnkStruct_022616b8 *) param, val);
    }
}

void func_ov048_022615a4(void *r0)
{
    void *r4 = r0;
    if (func_ov048_022614ac()) {
        func_020eb9fc();
        func_ov048_022616b8((UnkStruct_022616b8 *) r4, *(int *) ((char *) r4 + 0xb4) + 1);
    } else if (func_0209fdd4()) {
        func_ov048_022616b8((UnkStruct_022616b8 *) r4, *(int *) ((char *) r4 + 0xb4) + 1);
    }
}

void func_ov048_02261578(int arg0)
{
    int r4;
    int r1;

    r4 = arg0;
    if (func_0209ff54() != 0) {
        r1 = *(int *) (r4 + 0xb4);
        func_ov048_022616b8((UnkStruct_022616b8 *) r4, r1 + 1);
    } else {
        r1 = *(int *) (r4 + 0xb4);
        func_ov048_022616b8((UnkStruct_022616b8 *) r4, r1 + 2);
    }
}

void func_ov048_02261540(void *p)
{
    if (func_ov048_022614ac()) {
        func_020eb9fc();
        func_ov048_022616b8((UnkStruct_022616b8 *) p, (*(int *) ((char *) p + 0xb4) + 1));
    } else {
        if (func_0209fdac()) {
            func_ov048_022616b8((UnkStruct_022616b8 *) p, (*(int *) ((char *) p + 0xb4) + 1));
        }
    }
}

void func_ov048_02261514(UnkStruct_02261514 *p)
{
    if (func_0209ff0c()) {
        func_ov048_022616b8((UnkStruct_022616b8 *) p, p->count + 1);
    } else {
        func_ov048_022616b8((UnkStruct_022616b8 *) p, p->count + 2);
    }
}

void func_ov048_022614dc(void *arg)
{
    if (func_ov048_022614ac() != 0) {
        func_020eb9fc();
        func_ov048_022616b8((UnkStruct_022616b8 *) arg, ((struct FieldStruct *) arg)->unk_B4 + 1);
    } else if (func_0209fe1c() != 0) {
        func_ov048_022616b8((UnkStruct_022616b8 *) arg, ((struct FieldStruct *) arg)->unk_B4 + 1);
    }
}

int func_ov048_022614ac(void)
{
    int x = func_020eba08();
    if (x < 0) {
        x = -x;
    }
    return func_020e8b0c(x, (const char *) 0x00017ed0, (const char *) 0x000182b7) != 0;
}

void func_ov048_02261380(void *self)
{
    void *r7 = data_020ccf94;
    void *r4;
    void *r6;
    u8 b;

    r4 = func_02073138(r7);
    r6 = func_020984e8();

    if (*(u8 *) ((char *) self + 0x1e) == 0x62) {
        int r4_val;
        int ret;
        u8 byte;

        r6 = func_02073144(r7);
        r4_val = *(int *) ((char *) self + 0x3ec);
        func_02073100();
        ret = func_020eb8a0(r4_val);
        byte = *(u8 *) ((char *) r6 + ret * 0x23 + 0x1a0);
        if (byte != 6 || ret == ~0) {
            func_ov048_02260e28(self, 0x78, 1);
        } else {
            r4_val = *(int *) ((char *) self + 0x3ec);
            func_02073100();
            func_020eb704(r4_val);
            *(u16 *) (*(char **) ((char *) self + 0xb8) + 0xe6e) = 0x960;
            func_ov048_022616b8((UnkStruct_022616b8 *) self, 5);
        }
        return;
    }

    {
        int val;
        if (func_020eb6b8((char *) r4 + 0x20) != 0) {
            void *a1 = func_02099664(r6);
            void *a2 = func_02077bc8(a1);
            void *a3 = func_02077d68(a2);
            void *b2;

            func_020eb6a0((char *) r4 + 0x20, a3);
            b2 = func_02077bcc(func_02099664(r6));
            r4 = (char *) r4 + 0x20;
            MI_CpuCopy8(r4, b2, 0x40);
            if (func_020a15ac() == 0) {
                val = 0x75;
            } else {
                val = 2;
            }
        } else {
            val = func_ov048_02260a60(self);
        }
        b = val;
    }

    func_0206844c(*(void **) ((char *) self + 0x40), (char *) (&b), (int) data_ov048_02263d20);

    if (*(u8 *) ((char *) self + 0x813) == 0 || *(u8 *) ((char *) self + 0x810) != 0) {
        func_ov048_022616b8((UnkStruct_022616b8 *) self, 0x14);
    } else {
        func_ov048_02262378(self);
        func_ov048_022616b8((UnkStruct_022616b8 *) self, 0);
    }
}

void func_ov048_0226125c(void *param)
{
    int n;
    void **arr;
    int val;
    unsigned char buf[0x1c];
    unsigned char buf1[0x20];
    unsigned char buf2[0x1c];
    unsigned char buf3[0x20];
    unsigned char buf4[0x20];
    void *elem;
    void *target;
    unsigned char i;

    if (func_ov048_02260e78(param) != 0) {
        return;
    }

    func_02074308();
    n = func_020ec148();
    if (n <= 0) {
        return;
    }

    func_020730c8();
    arr = func_020eb92c();

    func_020641c8(buf1);
    func_02064170(buf2);
    func_02094fd4(buf3);
    func_02094f7c(buf4);

    target = *(void **) ((char *) param + 0x40);

    for (i = 0; i < n; i++) {
        elem = arr[i];

        if (elem == 0) {
            continue;
        }

        func_020730c8();
        val = func_020eb998(elem);
        if (val != 0x1a) {
            continue;
        }

        func_020730c8();
        MI_CpuCopy8(func_020eb9c4(elem), &buf[2], val);
        if (buf[0x1a] != 0) {
            continue;
        }

        MI_CpuCopy8(elem, (char *) param + 0x30c, 0xe0);

        func_020a8874(buf2, &buf[2], 6);
        func_020a8a70(buf1, buf2, 0, 0);
        func_020a8874(buf4, &buf[0xe], 6);
        func_020a8a70(buf3, buf4, 0, 0);

        func_02068404(target, 3, buf1);
        func_02068404(target, 4, buf3);

        buf[0] = 0x57;
        func_0206844c(target, (char *) buf, (int) data_ov048_02263d20);

        func_ov048_02262378(param);
        func_ov048_022616b8((UnkStruct_022616b8 *) param, 0);

        break;
    }

    func_02094f64(buf4);
    func_02094fbc(buf3);
    func_02064158(buf2);
    func_020641b0(buf1);
}

void func_ov048_022611f0(struct UnkStruct_022611f0 *self)
{
    char msg[2];

    if (func_0206fc6c()) {
        int x = func_0206fc8c();
        func_02073100();
        self->unk_3EC = func_020eb868(x);
        msg[0] = 'b';
        func_0206844c(self->unk_40, &msg[0], (*(int *) &data_ov048_02263d20));
        func_ov048_022616b8((UnkStruct_022616b8 *) self, 0);
    } else {
        func_ov048_022616b8((UnkStruct_022616b8 *) self, 20);
        msg[1] = 'a';
        func_0206844c(self->unk_40, &msg[1], (*(int *) &data_ov048_02263d20));
    }
}

void func_ov048_022611a0(struct UnkStruct_022611a0 *self)
{
    char buf[8];
    if (func_0206fc6c()) {
        buf[0] = 0x59;
        func_0206844c(self->unk_40, buf, (*(int *) &data_ov048_02263d20));
    } else {
        buf[1] = 0x58;
        func_0206844c(self->unk_40, buf + 1, (*(int *) &data_ov048_02263d20));
        func_ov048_02262658(self);
    }
    func_ov048_022616b8((UnkStruct_022616b8 *) self, 0);
}

void func_ov048_02261120(UnkStruct_02261120 *p)
{
    char local;
    void *ptr40;
    int ret;

    ptr40 = p->unk_40;
    if (ptr40) {
        func_02068440(ptr40);
    }
    func_02073100();
    if (func_020ec49c() == 0) {
        return;
    }
    if (ptr40) {
        func_ov048_02262378((void *) p);
    }
    ret = (int) func_020984e8();
    if (ret == 0) {
        goto common_exit;
    }
    ret = func_0209985c(ret);
    if (ret < 0 || ret >= 4) {
        goto common_exit;
    }
    func_0209fd54();
    func_0209fcd8();
    func_0209fc60();
    func_ov048_02262658(p);
    func_020a01f8();
    if (func_020a1518() == 0) {
        goto common_exit;
    }
    local = 2;
    func_0206844c(p->unk_40, &local, (*(unsigned int *) &data_ov048_02263d20));
common_exit:
    func_ov048_022616b8((UnkStruct_022616b8 *) p, 0);
}

void func_ov048_022610f8(void *this)
{
    if (func_ov048_02260474(*(unsigned int *) ((char *) this + 0xb8)) != 0) {
        func_020a1900();
        func_ov048_022616b8((UnkStruct_022616b8 *) this, 0x16);
    } else {
        func_020c189c();
    }
}

void func_ov048_0226107c(UnkStruct_0226107c *this)
{
    char buf[2];
    void *r4 = this->ptr;
    if (func_020a17ec() != 0) {
        func_ov048_02262378(this);
        buf[0] = 10;
        func_0206844c(r4, buf, (int) ((void *) data_ov048_02264704));
        func_ov048_022616b8((UnkStruct_022616b8 *) this, 0);
    } else {
        if (func_020a1810() != 0) {
            this->unk_811 = 1;
            func_ov048_02262378(this);
            buf[1] = this->unk_AE;
            func_0206844c(r4, &buf[1], (int) data_ov048_02263d20);
            func_020c1874();
            func_ov048_022616b8((UnkStruct_022616b8 *) this, 0);
        }
    }
}

int func_ov048_02260f64(void *self, int flag)
{
    char obj1[64];
    char obj2[64];
    int id;

    id = func_020eba18();
    if (id != 0 || flag != 0) {
        if (flag != 0) {
            func_ov048_02260e28(self, func_ov048_022609d0(self), 0);
        } else {
            if (func_020ec1e8() == 3 || func_020ec1e8() == 4) {
                int v = func_020eba08();
                int q;
                if (v < 0) {
                    v = -v;
                }
                q = v / 1000;
                func_020b5630(obj1);
                func_020b5630(obj2);
                func_020b45d0(obj1, q, 2, 6, 0, 0);
                func_020b45d0(obj2, v - q * 1000, 3, 6, 0, 0);
                func_02068404(*(void **) ((char *) self + 0x40), 6, obj1);
                func_02068404(*(void **) ((char *) self + 0x40), 7, obj2);
                if (id == 0x400b) {
                    func_ov048_02260e28(self, 0x7d, 0);
                } else if (id == 0x400a) {
                    func_ov048_02260e28(self, 0x78, 0);
                } else if (v == 0x13a1a) {
                    func_ov048_02260e28(self, 0x7a, 0);
                } else {
                    func_ov048_02260e28(self, 0x7e, 0);
                }
                func_020b5618(obj2);
                func_020b5618(obj1);
            } else {
                func_ov048_02260e28(self, func_ov048_022609d0(self), 0);
            }
        }
        return 1;
    }
    return 0;
}

int func_ov048_02260f30(void *this)
{
    int result;
    int offset = 0x0e6e;

    if (func_020e8840(*(int *) ((char *) this + 0xb8) + offset) == 0) {
        result = func_ov048_022609d0(this);
        func_ov048_02260e28(this, result, 0);
        return 1;
    }
    return 0;
}

int func_ov048_02260f00(void *this)
{
    int result;
    int v1;

    v1 = *(int *) ((char *) this + 0xb8);
    result = func_020e8840(v1 + 0xe6e);
    if (result == 0) {
        func_ov048_02260e28(this, 0x65, 0);
        return 1;
    }
    return 0;
}

int func_ov048_02260ea8(void *self)
{
    if (func_020e8840(*(unsigned int *) ((char *) self + 0xb8) + 0xe6e) == 0) {
        func_ov048_02260e28(self, 0x7a, 1);
        return 1;
    } else {
        if (func_020eba18() != 0) {
            int v = func_020eba08();
            if (v < 0) {
                v = -v;
            }
            v = func_ov048_0226077c(self, v);
            func_ov048_02260e28(self, v, 1);
            return 1;
        } else {
            return 0;
        }
    }
}

int func_ov048_02260e78(void *this)
{
    int result;
    int offset = 0x0e6e;
    int value = *(int *) ((char *) this + 0xb8);
    if (func_020e8840(value + offset) == 0) {
        func_ov048_02260e28(this, 0x56, 0);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
