/* func_ov118_0229bb00 @ 0x0229bb00, 0x48 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern int func_ov118_0229a4b8(void *);
extern void func_ov118_0229adf0(void *, int);
extern void func_ov118_0229a874(void *);

void func_ov118_0229bb00(unsigned char *obj)
{
    int ret;

    if (func_0208e484(obj + 0x6c0) == 0) {
        return;
    }
    ret = func_ov118_0229a4b8(obj);
    if (ret == 1) {
        return;
    }
    if (ret == 2) {
        func_ov118_0229adf0(obj, 0);
        obj[0xa3] = 0xff;
        func_ov118_0229a874(obj);
    } else {
        func_ov118_0229a874(obj);
    }
}
