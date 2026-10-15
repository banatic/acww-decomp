/* func_ov129_0229b9d8 @ 0x0229b9d8, 0x52 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov129_0229bc34(void *p, unsigned int entry);
extern void func_ov129_0229c610(void *p, int arg);

int func_ov129_0229b9d8(unsigned char *p)
{
    int result = 0;
    if (p[0xb0] == 0xff) {
        goto end;
    }
    result = func_ov129_0229bc34(p, p[0xb0]);
    if (result == 1) {
        goto body;
    }
    if (result == 3) {
        func_ov129_0229c610(p, 0x16);
    }
    goto end;
body:
    p[0xb1] = 1;
    p[0xb2] = p[0xb0];
    p[0xb3] = p[0xb0];
end:
    return result;
}
