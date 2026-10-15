/* func_ov003_0220e614 @ 0x0220e614, 0x124 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200fbc4(void *p, int a, int b, short c);
extern int func_02056f94(void *ptr);
extern int func_ov003_0220e5c4(void *p, int a, int b, int c);
extern unsigned int *func_0200f27c(void *p, int n);
extern void func_020109a0(void *p, int b, int c, unsigned short d);
extern int func_02034270(void *dst, void *src, int a, int b);
extern int func_02091254(int a, void *src, int b, int c);
extern int func_0200f328(void *p, int n);
extern int func_ov003_02221228(int a, void *src);
extern void func_0200f268(void *p, int n);
extern int func_0200fbe0(void *p);
extern void func_0205eae0(void *ptr, int a, int b, int c);
extern void func_0203423c(void *ptr);

void func_ov003_0220e614(char *p)
{
    char *base;
    int *q;
    int *r1;
    struct {
        int tmp[3];
        int pad[3];
        int src[3];
        char obj[0x40];
        int dst[3];
    } local;

    base = p + 0x7d4;

    if (*(int *) (p + 0x704) == 0x90) {
        {
            int t2 = *(int *) (base + 4);
            local.tmp[0] = *(int *) base;
            local.tmp[1] = 0;
            local.tmp[2] = t2;
        }
        func_0200fbc4(p, local.tmp[0], local.tmp[2], *(short *) (p + 0x8e));
        q = (int *) (p + 0x5c);
        {
            int qv0 = q[0];
            int qv2 = q[2];
            if (qv0 != local.tmp[0] || qv2 != local.tmp[2]) {
                return;
            }
        }
        *(char *) (p + 0x2e4) = 1;
    }

    if (func_02056f94(p + 0x2d0)) {
        if (*(int *) (p + 0x704) == 0x91) {
            func_ov003_0220e5c4(p, *(int *) (base + 8), 6, -1);
            func_0200f27c(p, 9);
        } else {
            func_020109a0(p, 0x91, 3, 0);
            r1 = (int *) (p + 0x5c);
            local.src[0] = *(int *) (p + 0x5c);
            local.src[1] = r1[1];
            local.src[2] = r1[2];
            func_02034270(local.obj, local.src, 0, 0);
            if (*(int *) (local.obj + 0x34) == 0x13) {
                func_02091254(0x8f, local.src, 0, 0);
            } else {
                func_02091254(0x8e, local.src, 0, 0);
            }
            func_0200f328(p, 0x7e8);
            func_0200f27c(p, 9);
            local.dst[0] = local.src[0];
            local.dst[1] = local.src[1];
            local.dst[2] = local.src[2];
            func_ov003_02221228(*(int *) (p + 0x800), local.dst);
            func_0200f268(p, 0x12);
            if (func_0200fbe0(p) == 4) {
                func_0205eae0(p + 0x5a0, 0x10, 3, 1);
            }
            func_0203423c(local.obj);
        }
    }
}
