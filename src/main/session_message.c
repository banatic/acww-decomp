/* session_message: 64 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207716c @ 0x0207716c, 0x20 bytes, Thumb
 * func_0207714c @ 0x0207714c, 0x20 bytes, Thumb
 * func_02077108 @ 0x02077108, 0x44 bytes, Thumb
 * func_020770e0 @ 0x020770e0, 0x28 bytes, Thumb
 * func_020770c0 @ 0x020770c0, 0x20 bytes, Thumb
 * func_020770a0 @ 0x020770a0, 0x20 bytes, Thumb
 * func_02077078 @ 0x02077078, 0x28 bytes, Thumb
 * func_02077050 @ 0x02077050, 0x28 bytes, Thumb
 * func_02077028 @ 0x02077028, 0x28 bytes, Thumb
 * func_02077008 @ 0x02077008, 0x20 bytes, Thumb
 * func_02076fe0 @ 0x02076fe0, 0x28 bytes, Thumb
 * func_02076fd4 @ 0x02076fd4, 0xc bytes, Thumb
 * func_02076fc8 @ 0x02076fc8, 0xc bytes, Thumb
 * func_02076fbc @ 0x02076fbc, 0xc bytes, Thumb
 * func_02076f9c @ 0x02076f9c, 0x20 bytes, Thumb
 * func_02076f74 @ 0x02076f74, 0x28 bytes, Thumb
 * func_02076f4c @ 0x02076f4c, 0x28 bytes, Thumb
 * func_02076f2c @ 0x02076f2c, 0x20 bytes, Thumb
 * func_02076f04 @ 0x02076f04, 0x28 bytes, Thumb
 * func_02076ef8 @ 0x02076ef8, 0xc bytes, Thumb
 * func_02076e58 @ 0x02076e58, 0xa0 bytes, Thumb
 * func_02076de4 @ 0x02076de4, 0x74 bytes, Thumb
 * func_02076dac @ 0x02076dac, 0x38 bytes, Thumb
 * func_02076d68 @ 0x02076d68, 0x44 bytes, Thumb
 * func_02076d40 @ 0x02076d40, 0x28 bytes, Thumb
 * func_02076c84 @ 0x02076c84, 0xbc bytes, Thumb
 * func_02076c3c @ 0x02076c3c, 0x48 bytes, Thumb
 * func_02076c14 @ 0x02076c14, 0x28 bytes, Thumb
 * func_02076bec @ 0x02076bec, 0x28 bytes, Thumb
 * func_02076b10 @ 0x02076b10, 0xdc bytes, Thumb
 * func_02076ae8 @ 0x02076ae8, 0x28 bytes, Thumb
 * func_02076ac0 @ 0x02076ac0, 0x28 bytes, Thumb
 * func_02076aa0 @ 0x02076aa0, 0x20 bytes, Thumb
 * func_02076a78 @ 0x02076a78, 0x28 bytes, Thumb
 * func_02076a18 @ 0x02076a18, 0x60 bytes, Thumb
 * func_020769b8 @ 0x020769b8, 0x60 bytes, Thumb
 * func_0207695c @ 0x0207695c, 0x5c bytes, Thumb
 * func_02076900 @ 0x02076900, 0x5c bytes, Thumb
 * func_0207689c @ 0x0207689c, 0x64 bytes, Thumb
 * func_020767ac @ 0x020767ac, 0xf0 bytes, Thumb
 * func_020766f8 @ 0x020766f8, 0xb4 bytes, Thumb
 * func_02076638 @ 0x02076638, 0xc0 bytes, Thumb
 * func_020765cc @ 0x020765cc, 0x6c bytes, Thumb
 * func_02076568 @ 0x02076568, 0x64 bytes, Thumb
 * func_02076540 @ 0x02076540, 0x28 bytes, Thumb
 * func_02076518 @ 0x02076518, 0x28 bytes, Thumb
 * func_020764f0 @ 0x020764f0, 0x26 bytes, Thumb
 * func_020764cc @ 0x020764cc, 0x24 bytes, Thumb
 * func_020764a4 @ 0x020764a4, 0x26 bytes, Thumb
 * func_02076480 @ 0x02076480, 0x24 bytes, Thumb
 * func_02076458 @ 0x02076458, 0x26 bytes, Thumb
 * func_02076434 @ 0x02076434, 0x24 bytes, Thumb
 * func_020763f4 @ 0x020763f4, 0x40 bytes, Thumb
 * func_0207639c @ 0x0207639c, 0x58 bytes, Thumb
 * func_02076374 @ 0x02076374, 0x28 bytes, Thumb
 * func_0207631c @ 0x0207631c, 0x58 bytes, Thumb
 * func_020762b8 @ 0x020762b8, 0x64 bytes, Thumb
 * func_020762ac @ 0x020762ac, 0xc bytes, Thumb
 * func_020762a0 @ 0x020762a0, 0xc bytes, Thumb
 * func_0207626c @ 0x0207626c, 0x34 bytes, Thumb
 * func_0207623c @ 0x0207623c, 0x30 bytes, Thumb
 * func_02076230 @ 0x02076230, 0xc bytes, Thumb
 * func_020761fc @ 0x020761fc, 0x34 bytes, Thumb
 * func_02076198 @ 0x02076198, 0x64 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02076de4 {
    unsigned char pad_00[0x64];
    int unk_64;
};

typedef struct UnkStruct_02076c84 {
    u16 unk_00;
    u16 unk_02;
} UnkStruct_02076c84;

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

typedef struct UnkStruct_02076900 UnkStruct_02076900;

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char buf[2];
    int word;
} UnkStruct_020767ac;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_020762b8;

extern void func_020348fc(int *);
extern int func_020714a0(int *);
extern unsigned int data_021fbe94;
extern unsigned int func_020e9958(unsigned int, unsigned int);
extern void func_02070760(unsigned int, unsigned int);
extern void func_020e993c(unsigned int, unsigned int);
extern void func_0203f4ec(char *, int);
extern void *data_020ccf94;
extern void func_02052b90(void *);
extern void func_02052b20(int *);
extern void func_020736bc(void *src, void *dest, int size);
extern void func_02052a3c(int a, void *b);
extern void func_02052ac8(int a, void *b);
extern void func_02052a64(int param1, unsigned int *param2);
extern void func_02052960(unsigned int *);
extern void func_020528fc(void *, int);
extern void func_020528e4(int arg);
extern void *func_020528d4(int arg);
extern void func_020b2734(int *a);
extern void func_020b260c(char *, unsigned int);
extern void func_020b25e0(int *, int);
extern int func_0209d3a8(int *arg);
extern void func_020ad7f4(int *data, int d);
extern int func_020ad7e4(int value);
extern unsigned char data_020e54a8;
extern void func_02073820(void *obj);
extern void func_020737f0(void *obj, void *data, int flag);
extern void func_02073770(void *obj, int a, int b);
extern unsigned char func_ov003_0222d7d0(unsigned char);
extern unsigned char data_ov003_0226053c;
void func_ov003_0222e750(int _x);
extern void func_ov003_0222e4c0(unsigned char);
extern void func_ov003_0222e6c4(int, int);
extern void func_ov003_0222e7f8(int);
extern void func_02050884(void *buf, int d);
extern void func_0209646c(int *v, UnkStruct_02076c84 *w, int *sel);
extern int func_020955e0(u16 *p, int sel, int a3);
extern int func_020984fc(int a3);
extern u16 *func_02099728(unsigned int);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_02062148(u16 *p);
extern void func_0209971c(int h, u16 *p);
extern int func_02095694(int n, int a3);
extern void func_02096440(char *, char *, char *);
extern void func_02099808(int, unsigned char);
extern void func_020997e0(int, unsigned char);
extern int func_02095578(unsigned char, int);
extern int func_02095558(int, int);
extern void *func_0204e414(void);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_02045d80(int *pos, int k);
extern int func_02045aa4(int *pos, int a);
extern unsigned char *func_02045bac(int idx);
extern void func_0204510c(void *sub, int flag, int a);
extern void func_02044e28(char *src, int param);
extern void func_0209d4c0(void *param1, void *param2);
extern void func_0209d498(unsigned int *);
extern void func_0209d484(void *src, int param);
extern char data_021dc7aa[];
extern void func_020789f4(int *, int *, int *);
extern int func_0207cec0(int *, int);
extern int func_02099870(int);
extern int func_02081e94(int, int, char *, int);
extern void func_02081e14(void *obj, int val, const char *str, int flag);
extern int data_021e5a2c[];
int func_020807c0(int, unsigned int);
void func_02081a80(int, unsigned char);
extern void func_02081d18(void *x, int v);
extern void func_02078794(unsigned int *out1, unsigned int *out2, unsigned short *in1, unsigned short *in2);
extern int func_02081edc(void *object);
extern void func_02081ac0(int handle, void *buf);
extern void func_020786d8(int *, unsigned char *, unsigned char *, unsigned char *);
extern void *func_0209b5e8(int);
extern void *func_0209b91c(void *);
extern int func_0209bd44(void *);
extern void func_0209bb90(void *, int);
extern void func_0209ba7c(void *);
extern void func_0209b920(void *);
extern void func_0209b8a4(void *, int);
extern void func_0209b890(void *, int);
void func_020785a4(int *p0, unsigned char *p1, unsigned short *p2, int *p3, unsigned char *p4, int *p5);
unsigned int func_0207f1c8(unsigned int object);
int func_0207f270(int v);
int func_020794d0(int);
void func_0209bd5c(void *);
void func_0209b9cc(int a, unsigned char b, unsigned short *c, int d, int e);
extern unsigned int func_02078448(int *out, volatile u16 *v, u8 *p);
extern int func_0209bc40(void *o);
extern u16 *func_0209b8c4(void *o);
extern void func_02080cd8(int a, volatile u16 *id);
void func_0207835c(unsigned int *key, unsigned short *arr, void *buf);
unsigned short *func_0207dfd4(void *handle, unsigned int index);
extern void func_020a6f74(unsigned int param0, unsigned char param1);
extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a1240(int x, int y, int z);
extern void func_020a1210(int);
extern void func_020a1248(int, int, int);
extern void func_02074d60(unsigned char);
extern void func_020a1208(int a, int b, int c);
extern void func_020a1264(int, int);
extern void func_020a7948(void *);
extern void func_020a7938(void *, void *);
extern void func_020a7408(void *, unsigned char);
extern void func_020a7944(void *);
extern void *func_020a7820(unsigned char *p);
extern void func_020a77dc(unsigned char *p1, int *p2, unsigned char *p3, unsigned char *p4, unsigned char *p5, int *p6);
extern void func_020a7394(int a, unsigned char b, unsigned char c, unsigned char d, int e);
extern int func_020a7810(unsigned char *p);
extern void func_020a7380(int, unsigned char);
extern int func_020a7880(char *);
extern void func_020a7830(char *, char *, char *, char *, int *);
extern void func_020a7360(int, unsigned char, unsigned char, unsigned char, int);
extern int func_020a7870(char *);
extern void func_020a76cc(void *);
extern void func_020a7684(void *, void *, void *, void *);
extern void func_020a76c8(void *);
extern void func_020a6f20(int, int);
extern void func_020a6f10(int);
extern void func_020a6f34(int);
extern void func_020a6e8c(int a, int b);
extern void func_020a6e7c(int a);
extern int func_02073424(void *);
extern void func_02073404(void *, void *);
extern void func_020a6db0(void);
extern void *func_020733c4(void *);
extern void func_020733a0(void *, void *);
extern void func_020a6e6c(int param);
extern int func_0205fa84(char *);
extern int func_02077898(void *p);
extern void func_02077a34(void *a, void *b, void *c);
extern void func_0205f9d4(signed char a, signed char b, unsigned char c, int d, int e);

void func_0207716c(int param, int sequence, unsigned char category, unsigned int player)
{
    int local;
    func_020736bc((void *) ((*(int *) &data_020ccf94)), (void *) (&local), param);
    func_020348fc(&local);
}

void func_0207714c(int a, int sequence, unsigned char category, unsigned int player)
{
    int local;
    func_020736bc((void *) ((*(int *) &data_020ccf94)), (void *) (&local), a);
    func_020714a0(&local);
}

void func_02077108(int length, int sequence, unsigned char category, unsigned int player)
{
    unsigned int w = data_021fbe94;
    unsigned int v = func_020e9958(w, length);
    func_020736bc((void *) ((*(unsigned int *) &data_020ccf94)), (void *) v, length);
    func_02070760(v, player);
    func_020e993c(w, v);
}

void func_020770e0(int length, int sequence, unsigned char category, unsigned int player)
{
    char buf[8];
    func_020736bc((void *) ((*(int *) &data_020ccf94)), (void *) buf, length);
    func_0203f4ec(buf, player);
}

void func_020770c0(void *param, int sequence, unsigned char category, unsigned int player)
{
    void *local;
    func_020736bc(data_020ccf94, &local, (int) param);
    func_02052b90(&local);
}

void func_020770a0(int arg, int sequence, unsigned char category, unsigned int player)
{
    int local;
    func_020736bc((void *) ((*(int *) &data_020ccf94)), (void *) (&local), arg);
    func_02052b20(&local);
}

void func_02077078(int a1, int a2, int a3, unsigned int player)
{
    int buf;
    func_020736bc(data_020ccf94, &buf, 4);
    func_02052a3c(a3, &buf);
}

void func_02077050(int param1, int param2, int param3, unsigned int player)
{
    char buffer[4];
    func_020736bc(data_020ccf94, buffer, 4);
    func_02052ac8(param3, buffer);
}

void func_02077028(int param1, int param2, int param3, unsigned int player)
{
    unsigned int local_4;
    unsigned int *ptr;
    int r4;

    r4 = param3;
    ptr = (unsigned int *) (*(unsigned int *) &data_020ccf94);
    func_020736bc((void *) ptr, (void *) (&local_4), 4);
    func_02052a64(r4, &local_4);
}

void func_02077008(unsigned int arg, int sequence, unsigned char category, unsigned int player)
{
    unsigned int local;
    func_020736bc((void *) ((*(unsigned int *) &data_020ccf94)), (void *) (&local), arg);
    func_02052960(&local);
}

void func_02076fe0(int a1, int a2, int a3, int a4)
{
    char buf[8];
    func_020736bc((void *) ((*(int *) &data_020ccf94)), buf, 3);
    func_020528fc(buf, a4);
}

void func_02076fd4(int length, int sequence, unsigned char category, unsigned int player)
{
    func_020528e4(1);
}

void func_02076fc8(int length, int sequence, unsigned char category, unsigned int player)
{
    func_020528e4(0);
}

void func_02076fbc(int a, int b, int c, int d)
{
    func_020528d4(d);
}

void func_02076f9c(int param, int sequence, unsigned char category, unsigned int player)
{
    int var;
    func_020736bc((void *) ((*(int *) &data_020ccf94)), (void *) (&var), param);
    func_020b2734(&var);
}

void func_02076f74(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
    char buf[8];
    func_020736bc((void *) ((*(unsigned int *) &data_020ccf94)), (void *) buf, a1);
    func_020b260c(buf, a4);
}

void func_02076f4c(int param0, int param1, int param2, int param3)
{
    int local[2];
    func_020736bc((void *) ((*(int *) &data_020ccf94)), (void *) local, param0);
    func_020b25e0(local, param3);
}

void func_02076f2c(int arg, int sequence, unsigned char category, unsigned int player)
{
    int local;
    func_020736bc(data_020ccf94, (void *) (&local), arg);
    func_0209d3a8(&local);
}

void func_02076f04(int length, int sequence, unsigned char category, unsigned int player)
{
    int buf;
    func_020736bc(data_020ccf94, (void *) (&buf), length);
    func_020ad7f4(&buf, player);
}

int func_02076ef8(int a, int b, int c, int d)
{

    return func_020ad7e4(d);
}

void func_02076e58(int a, int b, int c, int d)
{
    unsigned char data[2];
    void *obj;
    unsigned int cond;

    data[1] = 1;
    obj = data_020ccf94;
    func_020736bc(obj, data, a);

    cond = (data_020e54a8 == 0) ? 1 : 0;
    if (cond > 0) {
        data[1] = func_ov003_0222d7d0(data[0]);
    }

    func_02073820(obj);

    if (data[1] == 0) {
        data[0] &= 0xF;
        data[0] |= (d << 4);
        data[0] += 0x10;
        obj = data_020ccf94;
        func_020737f0(obj, data, 1);
        func_02073770(obj, 0x29, 7);
    } else {
        obj = data_020ccf94;
        func_020737f0(obj, data + 1, 1);
        func_02073770(obj, 0x29, d);
    }
}

void func_02076de4(int a, int sequence, unsigned char category, unsigned int player)
{
    struct UnkStruct_02076de4 *p;
    unsigned char local;
    unsigned int hi;
    unsigned int cond;

    cond = (data_020e54a8 == 0) ? 1 : 0;
    if (cond != 0) {
        p = (*(struct UnkStruct_02076de4 * *) &data_020ccf94);
        func_020736bc((void *) p, &local, a);

        hi = ((unsigned int) local << 20) >> 24;

        local = (local & 0xF) | 0x10;

        if (local == 1) {
            data_ov003_0226053c = 1;
        } else {
            if (hi - 1 == p->unk_64) {
                data_ov003_0226053c = 0;
                func_ov003_0222e750(local);
            } else {
                data_ov003_0226053c = 1;
            }
        }
    }
}

void func_02076dac(int arg0, int sequence, unsigned char category, unsigned int player)
{
    unsigned char local[4];
    unsigned int flag;

    func_020736bc((void *) ((*(int *) &data_020ccf94)), local, arg0);
    flag = (data_020e54a8 == 0) ? 1 : 0;
    if (flag > 0) {
        func_ov003_0222e4c0(local[0]);
    }
}

void func_02076d68(int param, int sequence, unsigned char category, unsigned int player)
{
    unsigned char local;
    int flag;

    func_020736bc((void *) ((*(int *) &data_020ccf94)), (void *) (&local), param);
    flag = data_020e54a8 ? 0 : 1;
    if (flag != 0) {
        if (local < 4) {
            func_ov003_0222e6c4(local, 0);
        } else {
            func_ov003_0222e7f8(local);
        }
    }
}

void func_02076d40(int a, int b, int c, int d)
{
    char buffer[8];
    func_020736bc(data_020ccf94, buffer, a);
    func_02050884(buffer, d);
}

void func_02076c84(int a0, int a1, int a2, int a3)
{
    UnkStruct_02076c84 w;
    int v;
    int sel;
    int h;
    u16 *q;
    int r;
    int n;
    unsigned int ok;

    func_020736bc(data_020ccf94, (void *) (&v), a0);
    func_0209646c(&v, &w, &sel);
    w.unk_02 = w.unk_00;
    switch (sel) {
        case 0:
        case 1:
        case 2:
            func_020955e0(&w.unk_02, sel, a3);
            break;
        case 3:
            h = func_020984fc(a3);
            q = func_02099728(h);
            if (func_0204bcdc(&w.unk_02) != 0) {
                r = func_0204bc64(&w.unk_02);
                ok = (r == func_0204bc64(q)) ? 1 : 0;
            } else {
                ok = (w.unk_02 == *q) ? 1 : 0;
            }
            if (ok == 0) {
                n = func_02062148(&w.unk_02);
                func_0209971c(h, &w.unk_02);
                func_02095694(n + 1, a3);
            }
            break;
    }
}

void func_02076c3c(int p1, int p2, int p3, int p4)
{
    char buf[3];
    int x;
    func_020736bc((void *) ((*(int *) &data_020ccf94)), (void *) buf, p1);
    func_02096440(buf, buf + 1, buf + 2);
    x = func_020984fc(p4);
    func_02099808(x, buf[1]);
    func_020997e0(x, buf[2]);
}

void func_02076c14(int length, int sequence, unsigned char category, unsigned int player)
{
    unsigned char buffer[8];
    func_020736bc((void *) ((*(unsigned int *) &data_020ccf94)), (void *) buffer, length);
    func_02095578(buffer[0], player);
}

void func_02076bec(int a, int b, int c, int d)
{
    unsigned char buf[8];
    func_020736bc((void *) ((*(int *) &data_020ccf94)), buf, a);
    func_02095558(buf[0], d);
}

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

void func_02076ae8(int a, int b, int c, unsigned int player)
{
    char buffer[16];
    func_020736bc(data_020ccf94, (void *) buffer, 14);
    func_02044e28(buffer, c);
}

void func_02076ac0(void *param1, void *param2, void *param3, void *param4)
{
    void *sp0;
    void *r4 = param4;
    func_020736bc(data_020ccf94, &sp0, 1);
    func_0209d4c0(&sp0, r4);
}

void func_02076aa0(int length, int sequence, unsigned char category, unsigned int player)
{
    unsigned int local;
    func_020736bc((void *) ((*(unsigned int *) &data_020ccf94)), (void *) (&local), 1);
    func_0209d498(&local);
}

void func_02076a78(int length, int sequence, unsigned char category, unsigned int player)
{
    char buf[8];
    func_020736bc(data_020ccf94, buf, 1);
    func_0209d484(buf, player);
}

void func_02076a18(int a, int b, int c, int d)
{
    int s0;
    int s1;
    int s2;
    int x;
    int r5;

    func_020736bc((void *) ((*(int *) &data_020ccf94)), (void *) (&s0), a);
    func_020789f4(&s1, &s2, &s0);
    x = func_0207cec0(((int *) data_021e5a2c), s1);
    if (x != 0) {
        r5 = func_020807c0(x, s2);
        if (r5 != 0) {
            int ret;
            ret = func_02099870((int) func_020984fc(d));
            func_02081e94(r5, ret, data_021dc7aa, 0);
        }
    }
}

void func_020769b8(int a, int b, int c, int d)
{
    int loc0, loc1, loc2;
    int cond;
    void *ptr;

    func_020736bc((void *) ((*(int * *) &data_020ccf94)), (void *) (&loc0), a);
    func_020789f4(&loc1, &loc2, &loc0);
    cond = func_0207cec0(((int *) data_021e5a2c), loc1);
    if (cond != 0) {
        ptr = (void *) func_020807c0(cond, loc2);
        if (ptr != 0) {
            func_02081e14(ptr, func_02099870(func_020984fc(d)), ((const char *) data_021dc7aa), 0);
        }
    }
}

void func_0207695c(int length, int sequence, unsigned char category, unsigned int player)
{
    unsigned int val = (*(unsigned int *) &data_020ccf94);
    struct {
        unsigned char b0;
        unsigned char b1;
        unsigned char pad[2];
        unsigned int word1;
        unsigned int word2;
    } buf;
    int ret;

    func_020736bc((void *) val, &buf, 1);
    func_020789f4((int *) (&buf.word1), (int *) (&buf.word2), (int *) (&buf));
    ret = func_0207cec0((int *) data_021e5a2c, buf.word1);
    if (ret != 0) {
        int res;
        res = func_020807c0(ret, buf.word2);
        if (res != 0) {
            func_020736bc((void *) val, &buf.b1, 1);
            func_02081a80(res, buf.b1);
        }
    }
}

void func_02076900(int length, int sequence, unsigned char category, unsigned int player)
{
    signed char buf[2];
    int ab[2];
    void *g = data_020ccf94;
    void *x;
    func_020736bc(g, (void *) (&buf[0]), 1);
    func_020789f4(&ab[0], &ab[1], (int *) buf);
    x = (void *) func_0207cec0((int *) (((UnkStruct_02076900 *) data_021e5a2c)), ab[0]);
    if (x != 0) {
        x = (void *) func_020807c0((int) x, ab[1]);
        if (x != 0) {
            func_020736bc(g, (void *) (&buf[1]), 1);
            func_02081d18(x, buf[1]);
        }
    }
}

void func_0207689c(int length, int sequence, unsigned char category, unsigned int player)
{
    struct {
        unsigned short a;
        unsigned short b;
        unsigned char pad[4];
        unsigned int c;
        unsigned int d;
    } local;
    int ret1, ret2;

    local.a = 0xfff1;
    func_020736bc(data_020ccf94, (void *) (&local.b), 3);
    func_02078794(&local.c, &local.d, &local.a, &local.b);

    ret1 = func_0207cec0((int *) ((void *) ((unsigned char *) data_021e5a2c)), local.c);
    if (ret1 != 0) {
        ret2 = func_020807c0(ret1, local.d);
        if (ret2 != 0) {
            if (func_02081edc((void *) ret2)) {
                func_02081ac0(ret2, &local);
            }
        }
    }
}

void func_020767ac(int length, int sequence, unsigned char category, unsigned int player)
{
    UnkStruct_020767ac local;
    void *r4;
    void *base;
    int result;

    local.unk_00 = 6;
    local.unk_01 = 0;

    func_020736bc(data_020ccf94, (void *) local.buf, 2);
    func_020786d8(&local.word, &local.unk_00, &local.unk_01, local.buf);

    base = (void *) ((unsigned char *) data_021e5a2c);
    result = func_0207cec0((int *) base, local.word);
    if (result == 0) {
        return;
    }

    r4 = func_0209b5e8((int) func_0207f1c8(result));

    switch (local.unk_00) {
        case 0:
            if (func_0209bd44(func_0209b91c(r4)) != 0) {
                func_0209bb90(func_0209b91c(r4), local.unk_01);
            }
            break;
        case 1:
            func_0209ba7c(r4);
            break;
        case 2:
            if (func_0209bd44(func_0209b91c(r4)) != 0) {
                func_0209b920(r4);
            }
            break;
        case 3:
            if (func_0209bd44(func_0209b91c(r4)) != 0) {
                func_0209b8a4(r4, local.unk_01);
            }
            break;
        case 4:
            if (func_0209bd44(func_0209b91c(r4)) != 0) {
                func_0209b890(r4, local.unk_01);
            }
            // fallthrough
        case 5:
            if (func_0209bd44(func_0209b91c(r4)) != 0) {
                *((unsigned char *) r4 + 0x2e) = local.unk_01;
            }
            break;
    }
}

void func_020766f8(int length, int sequence, unsigned char category, unsigned int player)
{
    int tested_value0;
    unsigned char b1, b2;
    unsigned short w;
    int x, y, v14;
    int r4, r5, r6, r7;
    unsigned int temp;

    b1 = 0x16;
    w = 0xfff1;
    v14 = 4;
    b2 = 0;

    func_020736bc(data_020ccf94, (void *) (&x), v14);

    func_020785a4(&y, &b1, &w, &v14, &b2, &x);

    r6 = func_0207cec0(((int *) data_021e5a2c), y);
    if (r6 == 0) {
        return;
    }

    r7 = (int) func_0209b5e8((int) func_0207f1c8((unsigned int) r6));

    r4 = 0;
    if (b2) {
        temp = 1;
    } else {
        temp = r4;
    }
    if (temp > 0) {
        r5 = 1;
    } else {
        r5 = 0;
    }

    func_0209bd5c((void *) func_020794d0((int) func_0207f270(r6)));

    if (v14 < 4) {
        if ((tested_value0 = (int) (func_020984fc((int) ((void *) v14)))) != 0) {
            r4 = func_02099870(tested_value0);
        }
    }

    func_0209b9cc(r7, b1, &w, r4, r5);
}

void func_02076638(int length, int sequence, unsigned char category, unsigned int player)
{
    int forwarded_value;

    struct {
        volatile u16 v;
        u8 b[4];
        u8 pad[2];
        int r;
    } q;
    void *o5;
    void *o4;
    unsigned int ok;
    unsigned int a, b;
    u16 *p;

    q.v = 0xfff1;
    func_020736bc(data_020ccf94, (void *) q.b, 4);
    func_02078448(&q.r, &q.v, q.b);
    if ((forwarded_value = (int) func_0207cec0(((int *) data_021e5a2c), q.r)) == 0) {
        return;
    }
    o5 = func_0209b5e8((int) func_0207f1c8((unsigned int) forwarded_value));
    o4 = func_0209b91c((void *) o5);
    if (func_0209bd44(o4) == 0) {
        return;
    }
    if (func_0209bc40(o4) == 0) {
        ok = 0;
        a = q.v;
        b = q.v;
        if (b >= 0x12b0 && a <= 0x12e7) {
            ok = 1;
        }
        if (ok != 0) {
            goto act;
        }
    }
    if (func_0209bc40(o4) != 1) {
        return;
    }
    ok = 0;
    a = q.v;
    b = q.v;
    if (b >= 0x12e8 && a <= 0x131f) {
        ok = 1;
    }
    if (ok == 0) {
        return;
    }
act:
    p = func_0209b8c4(o5);
    *p = q.v;
}

void func_020765cc(int length, int sequence, unsigned char category, unsigned int player)
{
    volatile u16 id;
    u8 buf[3];
    int out;
    int r;

    id = 0xfff1;
    func_020736bc(data_020ccf94, (void *) buf, 3);
    func_02078448(&out, &id, buf);
    r = func_0207cec0((int *) (((u8 *) data_021e5a2c)), out);
    if (r != 0) {
        unsigned int ok = 0;
        u16 hi = id;
        u16 lo = id;
        if (lo >= 0x11a8 && hi <= 0x12a7) {
            ok = 1;
        }
        if (ok > 0) {
            func_02080cd8(r, &id);
        }
    }
}

void func_02076568(int length, int sequence, unsigned char category, unsigned int player)
{
    unsigned int key;
    unsigned short arr[4];
    char buf[9];
    void *handle;
    int i;
    unsigned short *p;

    arr[0] = 0xFFF1;
    arr[1] = 0xFFF1;
    arr[2] = 0xFFF1;
    arr[3] = 0xFFF1;

    func_020736bc((void *) data_020ccf94, buf, 9);
    func_0207835c(&key, arr, buf);

    handle = (void *) func_0207cec0((int *) (((unsigned int *) data_021e5a2c)), key);
    if (handle) {
        for (i = 0; i < 4; i++) {
            p = func_0207dfd4(handle, i);
            if (p) {
                *p = arr[i];
            }
        }
    }
}

void func_02076540(unsigned int param0, unsigned int param1, unsigned int param2, unsigned int param3)
{
    unsigned int *ptr;
    unsigned char byte;
    unsigned int local;

    ptr = (unsigned int *) (*(unsigned int *) &data_020ccf94);
    func_020736bc((void *) ptr, (void *) ((unsigned char *) &byte), 1);
    func_020a6f74(param3, byte);
}

void func_02076518(int length, int sequence, unsigned char category, unsigned int player)
{
    unsigned char flag;
    int *ptr = (*(int * *) &data_020ccf94);
    func_020736bc((void *) ptr, (void *) (&flag), 1);
    func_020a6f74(ptr[25], flag);
}

void func_020764f0(int length, int sequence, unsigned char category, unsigned int player)
{
    int result = func_020b65c4();
    if (result != 46) {
        return;
    }
    result = func_020a132c();
    if (result != 0) {
        func_020a1240(func_020a132c(), player, 1);
    }
    return;
}

void func_020764cc(int length, int sequence, unsigned char category, unsigned int player)
{
    int temp;

    if (func_020b65c4() == 0x2e) {
        if (func_020a132c() != 0) {
            temp = func_020a132c();
            func_020a1210(1);
        }
    }
}

void func_020764a4(int a1, int a2, int a3, int a4)
{
    if (func_020b65c4() == 0x2E) {
        if (func_020a132c() != 0) {
            func_020a1248(func_020a132c(), a4, 1);
        }
    }
}

void func_02076480(int length, int sequence, unsigned char category, unsigned int player)
{
    unsigned char byte_var;
    func_020736bc((void *) ((*(unsigned int *) &data_020ccf94)), (void *) (&byte_var), 1);
    func_02074d60(byte_var);
}

void func_02076458(int a1, int a2, int a3, int a4)
{
    if (func_020b65c4() == 0x2e) {
        if (func_020a132c()) {
            func_020a1208(func_020a132c(), a4, 1);
        }
    }
}

void func_02076434(int length, int sequence, unsigned char category, unsigned int player)
{
    if (func_020b65c4() == 0x2e) {
        if (func_020a132c() != 0) {
            func_020a1264(func_020a132c(), 1);
        }
    }
}

void func_020763f4(int a, int b, int c, void *d)
{
    unsigned char local[8];

    func_020a7948(local);
    func_020736bc(data_020ccf94, local, 1);
    func_020a7938(local, local + 1);
    func_020a7408(d, local[1]);
    func_020a7944(local);
}

void func_0207639c(int length, int sequence, unsigned char category, unsigned int player)
{
    unsigned char arr[8];
    int x;
    int y;

    func_020a7820(arr + 3);
    func_020736bc(data_020ccf94, (void *) (arr + 3), 2);
    func_020a77dc(arr + 3, &x, arr, arr + 1, arr + 2, &y);
    func_020a7394(x, arr[0], arr[1], arr[2], y);
    func_020a7810(arr + 3);
}

void func_02076374(int a, int b, int c, int d)
{
    unsigned char local;

    func_020736bc((void *) ((*(unsigned int *) &data_020ccf94)), (void *) (&local), 1);
    func_020a7380(d, local);
}

void func_0207631c(int p0, int p1, int p2, int p3)
{
    char buf[8];
    int temp;
    func_020a7880(&buf[3]);
    func_020736bc(data_020ccf94, (void *) (&buf[3]), 2);
    func_020a7830(&buf[3], buf, &buf[1], &buf[2], &temp);
    func_020a7360(p3, buf[0], buf[1], buf[2], temp);
    func_020a7870(&buf[3]);
}

void func_020762b8(int a, int b, int c, int param)
{
    int local[5];
    UnkStruct_020762b8 *s;

    func_020a76cc(local);
    s = (*(UnkStruct_020762b8 * *) &data_020ccf94);
    func_020736bc(s, local, 1);
    func_020a7684(local, &local[1], &local[2], &local[3]);

    if (param == 0) {
        func_020a6f20(s->unk_64, local[1]);
    } else {
        func_020a6f20(param, local[1]);
    }

    if (local[2] < 4) {
        func_020a6f10(local[2]);
    }
    if (local[3] < 4) {
        func_020a6f34(local[3]);
    }

    func_020a76c8(local);
}

void func_020762ac(int length, int sequence, unsigned char category, unsigned int player)
{
    func_020a6e8c(player, 1);
}

void func_020762a0(int length, int sequence, unsigned char category, unsigned int player)
{
    func_020a6e7c(player);
}

void func_0207626c(void *param, int sequence, unsigned char category, unsigned int player)
{
    void *ptr = data_020ccf94;
    int ret = func_02073424(ptr);
    func_020736bc(ptr, (void *) ret, (int) param);
    func_02073404(ptr, param);
    func_020a6db0();
}

void func_0207623c(void *param, int sequence, unsigned char category, unsigned int player)
{
    void *p = data_020ccf94;
    void *res;

    res = func_020733c4(p);
    func_020736bc(p, res, (int) param);
    func_020733a0(p, param);
}

void func_02076230(int length, int sequence, unsigned char category, unsigned int player)
{
    func_020a6e6c(1);
}

void func_020761fc(unsigned int param, int sequence, unsigned char category, unsigned int player)
{
    char buffer[12];
    unsigned int i = 0;
    int data = (*(int *) &data_020ccf94);
    while (i < param) {
        func_020736bc((void *) data, (void *) buffer, 5);
        func_0205fa84(buffer);
        i += 5;
    }
}

void func_02076198(unsigned int count, int sequence, unsigned char category, unsigned int player)
{
    unsigned char data[7];
    unsigned int i = 0;
    void *g = data_020ccf94;
    int flag = i;
    int val;

    for (; i < count; i += 5) {
        func_020736bc(g, &data[2], 5);
        val = func_02077898(&data[2]);
        func_02077a34(&data[4], &data[0], &data[1]);
        func_0205f9d4((signed char) data[5], (signed char) data[6], data[0], val, (data[1] != 0) ? 1 : flag);
    }
}
