/* func_ov048_0226369c @ 0x0226369c, 0x2c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void);
extern int func_020b65c4(void);
extern int func_0203e328(void);

int func_ov048_0226369c(void)
{
    if (func_0202ec14() == 0) {
        return 0;
    }
    if (func_020b65c4() == 0xd || func_020b65c4() == 0xe) {
        func_0203e328();
    }
    return 1;
}
