/* field_actor_64: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02213988 @ 0x02213988, 0xf8 bytes, Thumb
 * func_ov003_02213944 @ 0x02213944, 0x44 bytes, Thumb
 * func_ov003_02213914 @ 0x02213914, 0x30 bytes, Thumb
 */

typedef struct {
    int unk_00;
    unsigned short unk_04;
    unsigned char unk_06, unk_07, unk_08, unk_09, unk_0A;
} UnkStruct_02213988_2;

typedef struct {
    unsigned char unk_00, unk_01, unk_02;
} UnkStruct_02213988_3;

typedef struct {
    char pad_00[0xc];
    UnkStruct_02213988_3 s;
} UnkStruct_02213988;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x5a0 - 0x60];
    int unk_5A0;
    char pad_5A4[0x704 - 0x5a4];
    int unk_704;
    char pad_708[0x7d4 - 0x708];
    UnkStruct_02213988_2 q;
    char pad_7E0[0x800 - 0x7e0];
    int unk_800;
    char pad_804[0x81c - 0x804];
    int unk_81C;
    char pad_820[0x8f0 - 0x820];
    int unk_8F0;
} UnkStruct_02213988_4;

typedef struct {
    char pad_00[0x45c];
    unsigned short unk_45C;
    unsigned short unk_45E;
    char pad_460[0x374];
    int unk_7D4;
} UnkStruct_02213914;

extern void func_020109a0(void *self, int b, int c, unsigned short d);
extern void func_0205eae0(void *p, int a, int b, int c);
extern unsigned char func_0203cc1c(void);
extern void func_020109fc(void *self, int a, int b, int c);
extern int func_02073908(int a, int b);
extern void func_02035684(int a, int b, int c);
extern int func_0208b500(void);
extern void func_0208d07c(void *argument0);
extern void func_02079774(void *p);
extern void func_ov003_02213ac4(void *p, unsigned char s, int a, int b, int c, int d);
extern int data_020ccf94;
extern void func_ov003_02213a90(void *p, unsigned char *a, unsigned char *b, unsigned char *c, unsigned char *d,
                                unsigned char *e);
extern void *func_ov003_02213ae4(void *p, unsigned char a, unsigned char b, unsigned char c, int d, int e);
extern void func_0209129c(int value);

void func_ov003_02213988(UnkStruct_02213988_4 *self, UnkStruct_02213988 *a, int previous)
{
    UnkStruct_02213988_3 *p;
    UnkStruct_02213988_2 *q;
    int k, d, m;

    p = &a->s;
    k = p->unk_00;
    d = p->unk_01;
    m = p->unk_02;
    if (m == 0) {
        func_020109a0(self, 0x5c, 3, 0);
        func_0205eae0(&self->unk_5A0, 5, 3, 1);
    }
    q = &self->q;
    q->unk_07 = k;
    q->unk_08 = d;
    q->unk_06 = m;
    q->unk_04 = 0x39;
    q->unk_0A = func_0203cc1c();
    if (m != 0) {
        if (m == 3) {
            q->unk_09 = 3;
            q->unk_04 = 0x3b;
            self->unk_81C = 8;
        } else {
            if (self->unk_704 == 0x6c) {
                q->unk_06 = 2;
                func_020109fc(self, 0, 3, 3);
            }
            q->unk_09 = 7;
        }
    } else {
        if (func_02073908(data_020ccf94, self->unk_800) != 0) {
            func_02035684(0x12, 0, 0);

            func_0208d07c((void *) func_0208b500());
            func_02079774(&self->unk_5C);
        }
        q->unk_09 = 0;
    }
    q->unk_00 = -1;
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_ov003_02213ac4(&self->unk_8F0, q->unk_09, k, d, m, 0);
    }
}

void func_ov003_02213944(void *p1, int p2)
{
    unsigned char buf[5];
    func_ov003_02213a90((char *) p1 + 0x8f0, &buf[0], &buf[1], &buf[2], &buf[3], &buf[4]);
    func_ov003_02213ae4(p1, buf[3], buf[1], buf[2], 6, p2);
}

void func_ov003_02213914(UnkStruct_02213914 *obj)
{
    if (obj->unk_7D4 != -1) {
        func_0209129c(obj->unk_7D4);
    }
    obj->unk_45C = 0;
    obj->unk_45E = 0;
}
