/* func_02076b10 @ 0x02076b10, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;

extern void *func_0204e414(void);
extern void func_020736bc(void *g, void *dst, int n);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_02045d80(int *pos, int k);
extern int func_02045aa4(int *pos, int a);
extern unsigned char *func_02045bac(int idx);
extern void func_0204510c(void *sub, int flag, int a);

struct UnkStruct_02076b10_3 {
    unsigned char c_lo2 : 2;
    unsigned char c_hi6 : 6;
    unsigned char d_lo7 : 7;
    unsigned char d_b7 : 1;
    unsigned short he;
    unsigned short h10;
    unsigned short h12;
};

struct UnkStruct_02076b10 {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned short unk_08;
    unsigned short unk_0A;
    struct UnkStruct_02076b10_3 sub;
    int pos[2];
    int pos2[2];
};

struct UnkStruct_02076b10_2 {
    unsigned char a_lo3 : 3;
    unsigned char a_hi5 : 5;
    unsigned char b_lo7 : 7;
    unsigned char b_b7 : 1;
    unsigned char c_b0 : 1;
    unsigned char c_hi7 : 7;
};

void func_02076b10(int a0, int a1, int a2, int a3)
{
    void *ctx;
    struct UnkStruct_02076b10 s;
    unsigned short *o;
    struct UnkStruct_02076b10_2 *p;
    int flag;
    int x;
    int z;
    int cx;
    int cz;
    int x2;
    int z2;
    int idx;

    ctx = func_0204e414();
    if (ctx == 0) {
        return;
    }
    func_020736bc(data_020ccf94, &s.sub, 8);
    flag = 0;
    s.unk_08 = s.sub.he;
    s.unk_02 = s.unk_08;
    s.unk_00 = s.unk_08;
    x = s.unk_00 >> 8;
    z = s.unk_02 & 0xff;
    cx = x >> 4;
    cz = z >> 4;
    o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), s.sub.d_b7);
    if (o == 0) {
        goto end;
    }
    if (*o != s.sub.h10) {
        goto end;
    }
    s.unk_0A = s.sub.he;
    s.unk_06 = s.unk_0A;
    s.unk_04 = s.unk_0A;
    x2 = s.unk_04 >> 8;
    s.pos[0] = x2;
    z2 = s.unk_06 & 0xff;
    s.pos[1] = z2;
    idx = func_02045d80(s.pos, s.sub.d_b7);
    if (idx < 0) {
        s.pos2[0] = x2;
        s.pos2[1] = z2;
        if (func_02045aa4(s.pos2, a3) == 0) {
            goto end;
        }
        flag = 1;
        goto end;
    }
    p = (struct UnkStruct_02076b10_2 *) func_02045bac(idx);
    if (p->a_lo3 != s.sub.c_lo2) {
        goto end;
    }
    if (p->b_b7 == 0) {
        goto end;
    }
    if (p->c_b0 != 0) {
        goto end;
    }
    flag = 1;
end:
    func_0204510c(&s.sub, flag, a3);
}
