/* func_ov118_0229ba34 @ 0x0229ba34, 0x2c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e930(void *);
extern void func_ov118_0229a874(void *);
extern void func_ov118_0229a440(void *, int);

void func_ov118_0229ba34(void *p)
{
    if (func_0208e930((void *) ((char *) p + 0x678))) {
        func_ov118_0229a874(p);
        func_ov118_0229a440(p, 0x1000);
    }
}
