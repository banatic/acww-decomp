/* func_0204d698 @ 0x0204d698, 0x6e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204d8b0(void *ctx, void *p2, void *p3);
extern int func_0204d924(void *ctx, void *p2);
extern int func_0204d828(void *ctx, void *p, void *p2, void *p3, int n);
extern void *func_020e9968(void *heap, int n, int align);
extern void func_020e993c(void *heap, void *p);

void *func_0204d698(void *ctx, int *out, void *p2, void *p3, void *heap)
{
    int n;
    void *p;

    n = func_0204d8b0(ctx, p2, p3);
    if (n > 0 && (n & 3) == 0 && func_0204d924(ctx, p2) != 0) {
        p = func_020e9968(heap, n, 4);
        if (p != 0) {
            if (func_0204d828(ctx, p, p2, p3, n) != 0) {
                *out = n >> 2;
                return p;
            }
            func_020e993c(heap, p);
        }
    }
    return 0;
}
