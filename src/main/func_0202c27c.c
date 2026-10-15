/* func_0202c27c @ 0x0202c27c, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_0209975c(int);

struct Spad {
    char pad_00[0x1d];
    unsigned char b : 1;
};

int func_0202c27c(int a, struct Spad *p)
{
    int res;
    unsigned bit;
    res = func_020984e8();
    bit = p->b;
    if (bit != 0) {
        goto fail;
    }
    if (res == 0) {
        goto fail;
    }
    if (func_0209975c(res) == 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}
