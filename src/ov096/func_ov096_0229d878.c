/* func_ov096_0229d878 @ 0x0229d878, 0x42 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229d8ec(void *a);
extern void *func_ov096_0229c4dc(void *a);
extern void func_020665b8(void *p);
extern void func_0206fcb0(void *p);
extern void func_ov096_0229f5ac(void *a, unsigned char b);
extern void func_ov096_022a18dc(void *a, int x);
extern void func_ov096_022a1540(void *a);

typedef struct {
    char pad_00[0xb8];
    unsigned char b8;
} UnkStruct_0229d878;

void func_ov096_0229d878(UnkStruct_0229d878 *a)
{
    if (func_ov096_0229d8ec(a)) {
        void *p;
        p = func_ov096_0229c4dc(a);
        func_020665b8(p);
        func_0206fcb0(p);
        func_ov096_0229f5ac(a, a->b8);
        func_ov096_022a18dc(a, 8);
        func_ov096_022a1540(a);
    }
}
