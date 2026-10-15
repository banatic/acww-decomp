/* func_ov096_022a0074 @ 0x022a0074, 0x20 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_022a018c(int argument0);
extern void func_ov096_0229ddd8(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov096_022a0074(void *p)
{
    if (func_ov096_022a018c((int) p)) {
        func_ov096_0229ddd8(p);
        func_ov002_02208098((void *) (p), 0x24);
    }
}
