/* func_0207fc34 @ 0x0207fc34, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0207fc34;
typedef int (UnkStruct_0207fc34::*PMF)(int);
extern "C" PMF func_0207fc7c(UnkStruct_0207fc34 *obj);
extern "C" int func_0207fc34(UnkStruct_0207fc34 *obj, int arg)
{
    PMF pmf = func_0207fc7c(obj);
    int result = 1;
    if (pmf != 0) {
        if ((obj->*pmf)(arg) == 0) {
            result = 0;
        }
    }
    return result;
}
