/* func_ov096_022a0074 @ 0x022a0074, 0x20 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_022a018c(void);
extern void func_ov096_0229ddd8(void *);
extern void func_ov002_02208098(void *, int);

void func_ov096_022a0074(void *p)
{
    if (func_ov096_022a018c()) {
        func_ov096_0229ddd8(p);
        func_ov002_02208098(p, 0x24);
    }
}
