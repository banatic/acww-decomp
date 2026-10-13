/* func_020621d4 @ 0x020621d4, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021cb5c0;
extern unsigned short data_021cb5b0;
extern int func_0206266c(unsigned short *p);

void func_020621d4(unsigned short *out, int n)
{
    if (data_021cb5c0 != 0) {
        int i = 0;
        unsigned short cur = data_021cb5b0;
        while (cur < 0x156e) {
            unsigned short tmp = cur;
            if (func_0206266c(&tmp) != 0) {
                if (i == n) {
                    *out = tmp;
                    return;
                }
                i++;
            }
            cur = (unsigned short) (cur + 1);
        }
    }
    *out = data_021cb5b0;
}
