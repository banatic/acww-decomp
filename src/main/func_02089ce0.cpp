/* func_02089ce0 @ 0x02089ce0, 0x290 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Vec {
    int x, y, z;
};
struct Node;

extern "C" {
extern void func_020eaca0(Vec *, const Vec *, const Vec *);
extern int func_020ea9c8(const Vec *);
extern int func_02089f70(Node *, Node *);
extern int FX_Div(int, int);
extern int FX_MulFunc(int, int);
}

struct Node {
    virtual const Vec *v0();
    virtual int v1();
    virtual void v2(unsigned char, unsigned char, int);
    int unk_04;
    int unk_08;
    unsigned char unk_0C, unk_0D, unk_0E, unk_0F;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    char pad_20[8];
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    Node *next;
    unsigned char unk_3C;
};

extern Node *data_021d3120;

extern "C" void func_02089ce0(void)
{
    Node *p;
    Node *b;
    const Vec *pos;
    Vec res;
    int len, d, ov;
    int gf, bf;
    int k2, k1, tot, m1, m2, h;

    for (p = data_021d3120; p != 0; p = p->next) {
        if ((p->unk_1C & 1) != 0) {
            p->unk_30 = (int) 0xfffff000;
        }
    }

    while (data_021d3120 != 0) {
        pos = data_021d3120->v0();
        for (b = data_021d3120->next; b != 0; b = b->next) {
            if (func_02089f70(data_021d3120, b) == 0) {
                continue;
            }
            func_020eaca0(&res, b->v0(), pos);
            if (res.y < 0) {
                d = b->unk_08 + res.y;
            } else {
                d = data_021d3120->unk_08 - res.y;
            }
            if (d <= 0) {
                continue;
            }
            len = func_020ea9c8(&res);
            if (len == 0) {
                res.x = 0x1000;
                len = 0x1000;
            }
            ov = (data_021d3120->unk_04 + b->unk_04) - len;
            if (ov <= 0) {
                continue;
            }
            b->unk_3C = 1;
            data_021d3120->unk_3C = b->unk_3C;
            if ((data_021d3120->unk_1C & 1) != 0) {
                if (ov >= data_021d3120->unk_30) {
                    data_021d3120->unk_30 = ov;
                    data_021d3120->unk_28 = b->unk_1C;
                    data_021d3120->unk_2C = b->v1();
                    data_021d3120->unk_0E = b->unk_0C;
                    data_021d3120->unk_0F = b->unk_0D;
                }
            } else {
                data_021d3120->unk_28 = b->unk_1C;
                data_021d3120->unk_2C = b->v1();
                data_021d3120->unk_0E = b->unk_0C;
                data_021d3120->unk_0F = b->unk_0D;
            }
            if ((b->unk_1C & 1) != 0) {
                if (ov >= b->unk_30) {
                    b->unk_28 = data_021d3120->unk_1C;
                    b->unk_2C = data_021d3120->v1();
                    b->unk_0E = data_021d3120->unk_0C;
                    b->unk_0F = data_021d3120->unk_0D;
                }
            } else {
                b->unk_28 = data_021d3120->unk_1C;
                b->unk_2C = data_021d3120->v1();
                b->unk_0E = data_021d3120->unk_0C;
                b->unk_0F = data_021d3120->unk_0D;
            }
            data_021d3120->v2(b->unk_0C, b->unk_0D, b->unk_1C);
            b->v2(data_021d3120->unk_0C, data_021d3120->unk_0D, data_021d3120->unk_1C);
            gf = data_021d3120->unk_1C;
            if ((gf & 1) != 0) {
                continue;
            }
            bf = b->unk_1C;
            if ((bf & 1) != 0) {
                continue;
            }
            if ((gf & 2) != 0 && (bf & 2) != 0) {
                continue;
            }
            if ((gf & 2) != 0) {
                b->unk_14 = 0;
                ov = FX_Div(ov, len);
                b->unk_10 = b->unk_10 + FX_MulFunc(res.x, ov);
                b->unk_18 = b->unk_18 + FX_MulFunc(res.z, ov);
            } else if ((bf & 2) != 0) {
                data_021d3120->unk_14 = 0;
                ov = FX_Div(ov, len);
                data_021d3120->unk_10 = data_021d3120->unk_10 - FX_MulFunc(res.x, ov);
                data_021d3120->unk_18 = data_021d3120->unk_18 - FX_MulFunc(res.z, ov);
            } else {
                m1 = data_021d3120->unk_34;
                m2 = b->unk_34;
                h = FX_Div(ov, len) >> 1;
                tot = m1 + m2;
                k1 = FX_MulFunc(h, FX_Div(m2, tot));
                k2 = FX_MulFunc(h, FX_Div(m1, tot));
                b->unk_14 = 0;
                data_021d3120->unk_14 = 0;
                data_021d3120->unk_10 = data_021d3120->unk_10 - FX_MulFunc(res.x, k1);
                data_021d3120->unk_18 = data_021d3120->unk_18 - FX_MulFunc(res.z, k1);
                b->unk_10 = b->unk_10 + FX_MulFunc(res.x, k2);
                b->unk_18 = b->unk_18 + FX_MulFunc(res.z, k2);
            }
        }
        data_021d3120 = data_021d3120->next;
    }
}
