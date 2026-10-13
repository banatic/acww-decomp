/* func_0203cc38 @ 0x0203cc38, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203cc04(void);
extern int func_0203cc18(void);

int func_0203cc38(void)
{
    int a = func_0203cc04();
    int b = func_0203cc18();
    if (a == b) {
        return 1;
    } else {
        return 0;
    }
}
