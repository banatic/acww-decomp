/* func_02028d04 @ 0x02028d04, 0x258 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02028d04 UnkStruct_02028d04;
struct UnkStruct_02028d04 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xbc];
    void *unk_100;
    char pad_104[0x20];
    unsigned short unk_124;
    char pad_126[0x3e];
    int unk_164;
};

typedef struct {
    unsigned char zb[0x28];
} UnkStruct_02028d04_2;

extern unsigned char data_020e54a8;
extern const int data_021c2c8c;
extern const int data_020c8928;
extern const int data_021c1d6c;
extern const int data_020c8924;
typedef struct {
    int unk_00, w1;
} Pair8;
extern const Pair8 data_020d8db8;

extern void func_0207f270(void *);
extern int func_020794d0(void);
extern void func_0207f1c8(void *);
extern int func_0209b5e8(void);
extern int func_0201cddc(void *);
extern int func_0209bc40(int);
extern void func_0202e118(unsigned short *, void *);
extern void func_020266d8(unsigned short *, UnkStruct_02028d04 *, int);
extern void func_02026584(unsigned short *, UnkStruct_02028d04 *, int);
extern void func_0201cfb4(UnkStruct_02028d04 *, UnkStruct_02028d04_2 *);
extern void func_0201cf74(UnkStruct_02028d04 *, UnkStruct_02028d04_2 *, int, const int *, const int *);
extern void func_0202d9d0(UnkStruct_02028d04 *, int);
extern void func_0201cec8(UnkStruct_02028d04 *, UnkStruct_02028d04_2 *);
extern void func_0202da74(UnkStruct_02028d04 *, Pair8);
extern void func_02068388(int, int);

int func_02028d04(UnkStruct_02028d04 *p, void *arg)
{
    unsigned short q[8];
    UnkStruct_02028d04_2 z;
    int changed;
    int r6;
    unsigned int ok2;
    unsigned short hv, lv;

    func_0207f270(arg);
    r6 = func_020794d0();
    q[0] = 0xfff1;
    changed = 0;
    func_0207f1c8(arg);
    p->unk_164 = func_0209b5e8();
    if (func_0201cddc(p->unk_100) != 0xb) {
        goto end;
    }
    switch (func_0209bc40(r6)) {
        case 0:
            if ((unsigned int) (data_020e54a8 == 0) + (unsigned int) changed) {
                func_0202e118(&q[1], p->unk_100);
                ok2 = 0;
                hv = *(volatile unsigned short *) &q[1];
                lv = *(volatile unsigned short *) &q[1];
                if (lv >= 0x1376 && hv <= 0x1376) {
                    ok2 = 1;
                }
                if (ok2 == 0) {
                    goto end;
                }
            }
            func_020266d8(&q[2], p, 0);
            q[0] = q[2];
            ok2 = 0;
            hv = *(volatile unsigned short *) &q[0];
            lv = *(volatile unsigned short *) &q[0];
            if (lv >= 0x12b0 && hv <= 0x12e7) {
                ok2 = 1;
            }
            if (ok2) {
                p->unk_124 = hv;
                changed = 1;
            }
            break;
        case 1:
            if ((unsigned int) (data_020e54a8 == 0) + (unsigned int) changed) {
                func_0202e118(&q[3], p->unk_100);
                ok2 = 0;
                hv = *(volatile unsigned short *) &q[3];
                lv = *(volatile unsigned short *) &q[3];
                if (lv >= 0x1374 && hv <= 0x1374) {
                    ok2 = 1;
                }
                if (ok2 == 0) {
                    goto end;
                }
            }
            func_02026584(&q[4], p, 0);
            q[0] = q[4];
            ok2 = 0;
            hv = *(volatile unsigned short *) &q[0];
            lv = *(volatile unsigned short *) &q[0];
            if (lv >= 0x12e8 && hv <= 0x131f) {
                ok2 = 1;
            }
            if (ok2) {
                p->unk_124 = hv;
                changed = 1;
            }
            break;
        case 2:
            if ((unsigned int) (data_020e54a8 == 0) + (unsigned int) changed) {
                func_0202e118(&q[5], p->unk_100);
                ok2 = 0;
                hv = *(volatile unsigned short *) &q[5];
                lv = *(volatile unsigned short *) &q[5];
                if (lv >= 0x1369 && hv <= 0x1369) {
                    ok2 = 1;
                }
                if (ok2 == 0) {
                    goto end;
                }
            }
            changed = 1;
            break;
        default:
            if ((unsigned int) (data_020e54a8 == 0) + (unsigned int) changed) {
                func_0202e118(&q[6], p->unk_100);
                if (q[6] != 0xfff1) {
                    func_0202e118(&q[7], p->unk_100);
                    ok2 = 0;
                    hv = *(volatile unsigned short *) &q[7];
                    lv = *(volatile unsigned short *) &q[7];
                    if (lv >= 0x1380 && hv <= 0x139f) {
                        ok2 = 1;
                    }
                    if (ok2 == 0) {
                        goto end;
                    }
                }
            }
            changed = 1;
            break;
    }
end:
    if (changed) {
        func_0201cfb4(p, &z);
        func_0201cf74(p, &z, 0, &data_020c8928, &data_021c2c8c);
        func_0202d9d0(p, r6);
        func_0201cf74(p, &z, 1, &data_020c8924, &data_021c1d6c);
        z.zb[0x20] = 2;
        z.zb[0x21] = (char) (z.zb[0x20] - 1);
        func_0201cec8(p, &z);
        func_0202da74(p, data_020d8db8);
        func_02068388(p->unk_40, 1);
        return 1;
    }
    return 0;
}
