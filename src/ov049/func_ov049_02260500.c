/* func_ov049_02260500 @ 0x02260500, 0x20 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov049_02260520(void *unused0);
extern int func_0203e0a8(void *p, int v);

int func_ov049_02260500(void *p)
{
    int r;
    if (func_ov049_02260520(p)) {
        func_0203e0a8(p, 0);
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
