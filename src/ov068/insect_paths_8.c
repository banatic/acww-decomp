/* insect_paths_8: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02271cec @ 0x02271cec, 0xe8 bytes, Thumb
 * func_ov068_02271c58 @ 0x02271c58, 0x94 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x5c];
    struct {
        unsigned int x, y, z;
    } vec;
    unsigned char pad_68[0x30];
    unsigned int s;
} UnkStruct_02271cec;

extern UnkStruct_02271cec *func_020961a8(int);
extern int func_020826cc(void);
extern UnkStruct_02271cec *func_02082664(int);
extern int func_020ea990(unsigned int *dst, void *addr);

void func_ov068_02271c58(unsigned char *p, unsigned char *out, int r2, int r3);

void func_ov068_02271cec(void *ctx, unsigned char *out, unsigned int *dest)
{
    int min = 0x0fffffff;
    unsigned int zero;
    unsigned char flag = 1;
    UnkStruct_02271cec *obj;
    unsigned char i;
    int score;
    unsigned int v[3];
    unsigned char *addr;

    obj = func_020961a8(4);
    addr = (unsigned char *) ctx + 0x204;
    if (obj) {
        unsigned int *p = &obj->vec.x;
        dest[0] = *p;
        dest[1] = p[1];
        dest[2] = p[2];
        min = func_020ea990(dest, addr);
        func_ov068_02271c58((unsigned char *) ctx, &flag, obj->s, min);
        *out = (*out & flag) ? 1 : 0;
    }

    zero = 0;
    i = 0;
    while (i < func_020826cc()) {
        UnkStruct_02271cec *q = func_02082664(i);
        if (q) {
            unsigned int *p = &q->vec.x;
            v[0] = *p;
            v[1] = p[1];
            v[2] = p[2];
            score = func_020ea990(v, addr);
            func_ov068_02271c58((unsigned char *) ctx, &flag, q->s, score);
            *out = (*out & flag) ? 1 : zero;
            if (min > score) {
                min = score;
                dest[0] = v[0];
                dest[1] = v[1];
                dest[2] = v[2];
            }
        }
        i = (unsigned char) (i + 1);
    }
}

void func_ov068_02271c58(unsigned char *p, unsigned char *out, int r2, int r3)
{
    short v = *(unsigned char *) (p + 0x254);
    int t = *(int *) (p + 0x224);
    *out = 0;
    if (r3 < 0x2000) {
        v += 25;
    } else {
        if (r3 > t || r2 == 0) {
            *out = 1;
        } else {
            if (r2 <= 1000) {
                v += 1;
            } else if (r2 <= 1100) {
                v += 3;
            } else if (r2 <= 1168) {
                v += 5;
            } else if (r2 == 1169) {
                v += 8;
            } else {
                v += 15;
            }
        }
    }
    if (v > 254) {
        v = 254;
    }
    *(unsigned char *) (p + 0x254) = (unsigned char) v;
}
