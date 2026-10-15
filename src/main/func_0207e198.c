/* func_0207e198 @ 0x0207e198, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099870(int);
extern int func_02094ffc(void *);
extern int func_02098880(void *ptr);
extern char data_021dc7bc;

int func_0207e198(int argument0)
{
    if (func_02094ffc((void *) func_02099870((int) argument0)) == 0 && func_02098880(&data_021dc7bc) >= 2) {
        return 1;
    }
    return 0;
}
