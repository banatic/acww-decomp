/* func_020b45d0 @ 0x020b45d0, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *s, int c, unsigned int n);

extern void func_020b48ec(void *dst, unsigned int size, int a, int b);
extern void func_020b48b4(void *dst, unsigned int size, int a);
extern void func_020b488c(void *dst, unsigned int size, int a);
extern void func_020b4864(void *dst, unsigned int size, int a);
extern void func_020b47fc(void *dst, unsigned int size, int a);
extern void func_020b47d0(void *dst, unsigned int size);
extern void func_020b4758(void *dst, unsigned int dst_size, const void *src, unsigned int src_size);
extern int func_020a8be4(int a0, void *ptr);
extern int func_020b46a4(int a0, int a1, int a2);

int func_020b45d0(int a0, int a1, int a2, int a3, int a4, unsigned char a5)
{
    unsigned char A[0x1c];
    unsigned char B[0x1e];
    void *p;
    int ret;

    MI_CpuFill8(A, 0, sizeof(A));
    func_020b48ec(A, sizeof(A), a1, a2);

    if (a3 == 2) {
        goto do_23;
    }
    if (a3 == 3) {
        goto do_23;
    }
    goto skip_23;
do_23:
    func_020b48b4(A, sizeof(A), a2);
skip_23:

    if (a3 == 4) {
        goto do_45;
    }
    if (a3 == 5) {
        goto do_45;
    }
    goto skip_45;
do_45:
    func_020b488c(A, sizeof(A), a2);
skip_45:

    if (a3 == 6) {
        goto do_67;
    }
    if (a3 == 7) {
        goto do_67;
    }
    goto skip_67;
do_67:
    func_020b4864(A, sizeof(A), a2);
skip_67:

{
    unsigned int ok = 0;
    unsigned int idx = (unsigned int) (a3 - 1);
    if (idx <= 6) {
        if ((1u << idx) & 0x55) {
            ok = 1;
        }
    }
    if (ok) {
        func_020b47fc(A, sizeof(A), 3);
    }
}

    func_020b47d0(A, sizeof(A));

    p = A;
    if (a5 == 0) {
        MI_CpuFill8(B, 0, sizeof(B));
        func_020b4758(B, sizeof(B), A, sizeof(A));
        p = B;
    }

    ret = func_020a8be4(a0, p);

    if (a4 != 0) {
        ret &= func_020b46a4(a0, a1, a4);
        ret = ret ? 1 : 0;
    }

    return ret;
}