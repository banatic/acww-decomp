/* func_ov098_022a29d0 @ 0x022a29d0, 0x3c bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov098_022a28ec(void *p);
extern void func_ov003_02219840(void);
extern int func_ov096_0229cbbc(void *p);
extern void func_ov003_0222c3a8(void *ptr, int x);
extern void func_ov096_0229f57c(void *p, unsigned char b);
extern void func_ov002_02208098(void *p, int x);

void func_ov098_022a29d0(void *p)
{
    int x;

    func_ov098_022a28ec(p);
    func_ov003_02219840();
    x = func_ov096_0229cbbc(p);
    func_ov003_0222c3a8((char *) p + 0x2e14, x);
    func_ov096_0229f57c(p, *((unsigned char *) ((char *) p + 0xb6)));
    func_ov002_02208098(p, 0x33);
}
