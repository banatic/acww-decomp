/* func_0204c308 @ 0x0204c308, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c358(int param);
extern int func_0204c330(int param);
extern int func_02061624(unsigned char param);

unsigned short func_0204c308(int param)
{
    if (func_0204c358(param) != 0) {
        return (unsigned short) func_02061624((unsigned char) func_0204c330(param));
    } else {
        return 0;
    }
}
