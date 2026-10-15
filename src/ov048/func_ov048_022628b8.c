/* func_ov048_022628b8 @ 0x022628b8, 0x9c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022628b8_3;

extern void *func_020682e0(int);
extern int func_0208602c(void);
extern void *func_020860cc(int);
extern struct UnkStruct_022628b8 *func_020961a8(int);
extern void func_0204f818(int *a, int *b, int *vec);
extern void func_02087e88(void *obj, int);
extern void func_02087e80(void *obj, int);
extern int func_020b5e10(void);
extern int func_020b5f84(int, int, int *, int, int, int, int);
extern void func_0203acd8(void);
extern void func_020a18d0(void);
extern int func_020b6434(int, int, int, int);
extern void func_ov048_022635f4(struct UnkStruct_022628b8_3 *self, int);

struct UnkStruct_022628b8_2 {
    int pad_00;
    int type;
};

struct UnkStruct_022628b8 {
    char pad_00[0x5c];
    int vec[3];
    char pad_68[0x8e - 0x68];
    short s;
};

struct UnkStruct_022628b8_3 {
    char pad_00[0x8e];
    short s;
};

int func_ov048_022628b8(struct UnkStruct_022628b8_3 *self)
{
    struct UnkStruct_022628b8_2 *t = func_020682e0(0);
    if (t->type == 5) {
        void *obj;
        struct UnkStruct_022628b8 *p;
        int vec[3];
        int a, b;
        int short_val;

        obj = func_020860cc((int) func_0208602c());

        p = func_020961a8(4);
        {
            int *vp = p->vec;
            vec[0] = vp[0];
            vec[1] = vp[1];
            vec[2] = vp[2];
        }
        short_val = p->s;

        a = 0;
        b = 0;
        func_0204f818(&a, &b, vec);

        func_02087e88(obj, 2);
        func_02087e80(obj, self->s);

        func_020b5f84(func_020b5e10(), 0xc, vec, 0x00800000, short_val, a, b);

        func_0203acd8();
        func_020a18d0();
        func_020b6434(func_020b5e10(), 0x2e, 2, 3);

        func_ov048_022635f4(self, 3);
    }
    return 1;
}
