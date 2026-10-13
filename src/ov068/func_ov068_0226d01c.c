/* func_ov068_0226d01c @ 0x0226d01c, 0x64 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the same-arm if keeps param[0xa08] loaded before local.b[1]; the plain compare loads the local first */

extern void func_0209e474(unsigned char *p);
extern int func_0203dff0(int c);
extern int func_ov068_0226d20c(unsigned char *p);
extern int func_0201cddc(unsigned char *p);
extern void func_ov068_0226d080(unsigned char *p, unsigned char *l);
extern void func_ov068_0226d14c(unsigned char *p, unsigned char *l);
void func_ov068_0226d01c(unsigned char *param)
{
    union {
        unsigned char b[8];
        unsigned int w[2];
    } local;
    int ret;
    unsigned char b;
    if (ret) {
        local.w[0] = 0;
        local.w[1] = 0;
        func_0209e474(local.b);
        b = param[0xa08];
    } else {
        local.w[0] = 0;
        local.w[1] = 0;
        func_0209e474(local.b);
        b = param[0xa08];
    }
    if (b != local.b[1]) {
        if (func_0203dff0(local.b[1]) == 0) {
            if (func_ov068_0226d20c(param) != 0) {
                ret = func_0201cddc(param);
                if (ret != 3) {
                    if (ret == 4) {
                        func_ov068_0226d14c(param, local.b);
                    }
                } else {
                    func_ov068_0226d080(param, local.b);
                }
            }
        }
        param[0xa08] = local.b[1];
    }
}
