/* func_02010030 @ 0x02010030, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_ov004_02225ef8(int a);
extern int func_ov003_0220c57c(int a);
int func_02010030(int a)
{
    unsigned int ok;
    if (data_020e54a8 == 1) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok > 0) {
        return func_ov004_02225ef8(a);
    } else {
        return func_ov003_0220c57c(a);
    }
}
