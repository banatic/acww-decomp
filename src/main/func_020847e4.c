/* func_020847e4 @ 0x020847e4, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099640(int object);
extern int func_0209ad9c(int, int);
extern void *func_0209b4d4(int);
extern int func_0209bd44(void *);
extern int func_0209bba8(unsigned char *);
extern int func_02084ad0(void);

int func_020847e4(void)
{
    int forwarded_value;

    int r4;
    if ((forwarded_value = (int) func_020984e8()) != 0) {
        r4 = func_0209ad9c(func_02099640((int) forwarded_value), 0);
    } else {
        r4 = 0;
    }
    if (r4 == 0) {
        goto fail;
    }
    if (func_0209bd44((void *) func_0209b4d4(r4)) == 0) {
        goto fail;
    }
    if (func_0209bba8((unsigned char *) func_0209b4d4(r4)) != 1) {
        goto fail;
    }
    if (func_02084ad0() != 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}
