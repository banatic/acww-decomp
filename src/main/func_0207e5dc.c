/* func_0207e5dc @ 0x0207e5dc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207e5d4(void);
extern unsigned int func_0203cc18(void);
extern int func_0203cc04(void);

int func_0207e5dc(void)
{
    if (func_0207e5d4() == 0) {
        int tmp = (unsigned int) func_0203cc18() >> 1;
        if (func_0203cc04() < tmp) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}
