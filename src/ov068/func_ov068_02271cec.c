/* func_ov068_02271cec @ 0x02271cec, 0xe8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
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
extern void func_ov068_02271c58(void *ctx, unsigned char *flag, unsigned int s, int score);

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
        func_ov068_02271c58(ctx, &flag, obj->s, min);
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
            func_ov068_02271c58(ctx, &flag, q->s, score);
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
