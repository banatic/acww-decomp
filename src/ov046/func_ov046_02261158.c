/* func_ov046_02261158 @ 0x02261158, 0x110 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a12e8(void *, void *);
extern int func_0202ea80(int, int);
extern int func_02073d90(void *);
extern void *func_0209d358(int, int);
extern int func_020b1558(void);
extern void *data_020ccf94;
extern char data_ov046_0226242c[];
extern char data_ov046_02261fe8[];
extern unsigned char data_ov046_02261c88[];
extern void *data_ov046_02261c84[];

struct Param0 {
    unsigned char pad_00[0xb0];
    int state;
    unsigned char *data;
};

struct UnkStruct_02261158 {
    void *ptr;
    unsigned char byte;
};

void func_ov046_02261158(struct Param0 *p, struct UnkStruct_02261158 *out)
{
    int state;

    if (func_020a12e8(p, out) != 0) {
        out->ptr = (void *) data_ov046_0226242c;
        out->byte = 0x14;
        return;
    }

    state = p->state;
    if (state == 5) {
        if (func_0202ea80(2, 1) == 0) {
            if (p->data[0x73e] == 0) {
                p->state = 1;
            } else {
                p->state = 0;
            }
        } else {
            if (p->data[0x73e] == 0) {
                p->state = 3;
            } else {
                p->state = 2;
            }
        }
    }

    state = p->state;
    if (state == 4 && p->data[0x73e] == 0) {
        if (func_02073d90(data_020ccf94) != 0 || (*(signed short *) func_0209d358(0, 0x4a)) != 0) {
            if (func_020b1558() < 0x10) {
                out->byte = 0x13;
            } else {
                out->byte = 0x10;
            }
        } else {
            if (func_020b1558() < 0x10) {
                out->byte = 0x14;
            } else {
                out->byte = 1;
            }
        }
        out->ptr = (void *) data_ov046_02261fe8;
        return;
    }

    if (state >= 0 && state < 5) {
        out->byte = data_ov046_02261c88[state * 8];
        out->ptr = data_ov046_02261c84[p->state * 2];
    }
}
