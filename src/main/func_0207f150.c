/* func_0207f150 @ 0x0207f150, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207f120(void *param);
extern int func_0207f0f0(void *param);
extern int func_0207f0c0(void *param);

int func_0207f150(void *param)
{
    int result;

    if (func_0207f120(param) != 0) {
        result = 0;
    } else if (func_0207f0f0(param) != 0) {
        result = 1;
    } else if (func_0207f0c0(param) != 0) {
        result = 2;
    } else {
        result = 3;
    }
    return result;
}
