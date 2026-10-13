/* func_ov095_0229bd40 @ 0x0229bd40, 0x94 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229bd40 {
    unsigned char pad_00[0x10];
    unsigned short unk_10;
    unsigned short unk_12;
};

extern int func_ov095_0229b784(void *a, int b);
extern int func_ov095_0229bdd4(void *a, void *b, int c, int d, int e, int f);
extern int func_ov095_0229b9e0(void *a, int b);
extern void func_ov095_0229b400(void *a, int b, int c);
extern void func_ov095_0229b3ec(void *a);
extern void func_ov095_022999c0(void *a, int b);

int func_ov095_0229bd40(struct UnkStruct_0229bd40 *a0, unsigned short *a1, int a2, unsigned char *a3, int a4, int a5, int a6)
{
    int ret = func_ov095_0229b784(a0, a2);
    int tmp = *a3;
    if (ret == 0 || ret == 2) {
        if (func_ov095_0229bdd4(a0, a1, a0->unk_12, tmp, a4, -1) != 0) {
            (*a3)++;
        } else {
            return 0;
        }
    }
    if (ret == 1 || ret == 2) {
        a1[tmp - 1] = a0->unk_10;
    }
    if (a5 == 0) {
        if (func_ov095_0229b9e0(a0, a2) != 0) {
            func_ov095_0229b400(a0, a2, ret);
        } else {
            func_ov095_0229b3ec(a0);
        }
        if (a6 != 0) {
            func_ov095_022999c0(a0, a2);
        }
    }
    return 1;
}
