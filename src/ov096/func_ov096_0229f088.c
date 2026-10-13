/* func_ov096_0229f088 @ 0x0229f088, 0x54 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f830(void *, void *);
extern int func_ov096_0229f820(void *, void *);
extern int func_ov096_0229f800(void *, void *);
extern int func_ov096_0229f7ac(void *, void *);
extern void func_ov096_0229f054(void *, void *);
extern int func_02065f08(void);
extern int func_ov094_0229aa84(void *, int);

int func_ov096_0229f088(void *a, void *b)
{
    if (func_ov096_0229f830(a, b)) {
        return func_ov094_0229aa84((void *) ((char *) a + 0x358), func_ov096_0229f7ac(a, b));
    } else if (func_ov096_0229f820(a, b)) {
        func_ov096_0229f054(a, b);
        return func_02065f08();
    } else {
        func_ov096_0229f800(a, b);
        return 0;
    }
}
