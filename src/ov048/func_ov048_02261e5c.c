/* func_ov048_02261e5c @ 0x02261e5c, 0x1c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov048_02261d08(void *arg0);

void func_ov048_02261e5c(char *r0, int r1)
{
    if (r1 == 0) {
        r0[0x813] = 0;
        func_ov048_02261d08((void *) r0);
    }
}
