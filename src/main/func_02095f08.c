/* func_02095f08 @ 0x02095f08, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02095ea4(int arg0, int arg1);
extern int func_02095e84(int arg0, int arg1);

int func_02095f08(int param)
{
    if (param) {
        return func_02095ea4(0xb, 4);
    } else {
        return func_02095e84(0xb, 4);
    }
}
