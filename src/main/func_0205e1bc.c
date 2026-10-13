/* func_0205e1bc @ 0x0205e1bc, 0xb6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0205e1bc UnkStruct_0205e1bc;
struct UnkStruct_0205e1bc {
    unsigned char pad_00[0xd];
    unsigned char state;
};

extern UnkStruct_0205e1bc *func_0205e14c(UnkStruct_0205e1bc *p, int n);
extern UnkStruct_0205e1bc *func_0205e194(UnkStruct_0205e1bc *p, int n);
extern int func_0205e138(UnkStruct_0205e1bc *p, int n);
extern int func_021077e8(UnkStruct_0205e1bc *p);
extern void func_020b9eec(UnkStruct_0205e1bc *p, int val, int flag);

int func_0205e1bc(UnkStruct_0205e1bc *p)
{
    volatile int unused;
    int r6 = 0;
    int r4 = r6;
    UnkStruct_0205e1bc *a = func_0205e14c(p, r6);
    unsigned int flag1 = (a->state == 2) ? 1 : 0;
    if (flag1 != 0) {
        r6 = 1;
    } else {
        unsigned int flag2 = (a->state == 1) ? 1 : 0;
        if (flag2 == 0) {
            UnkStruct_0205e1bc *b0 = func_0205e194(p, 0);
            int e = func_021077e8(b0);
            func_020b9eec(a, e, 1);
        }
    }
    if (func_0205e138(p, 1) < 0x9e) {
        UnkStruct_0205e1bc *b1 = func_0205e194(p, 1);
        UnkStruct_0205e1bc *a2 = func_0205e14c(p, 1);
        unsigned int flag3 = (a2->state == 2) ? 1 : 0;
        if (flag3 != 0) {
            r4 = 1;
        } else {
            unsigned int flag4 = (a2->state == 1) ? 1 : 0;
            if (flag4 == 0) {
                int e2 = func_021077e8(b1);
                func_020b9eec(a2, e2, 1);
            }
        }
    } else {
        r4 = 1;
    }
    if (r6 != 0 && r4 != 0) {
        return 1;
    } else {
        return 0;
    }
}
