/* func_0207fc34 @ 0x0207fc34, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0207fc34;

typedef int (UnkStruct_0207fc34::*PMF)(unsigned short *);
extern "C" PMF func_0207fc7c(UnkStruct_0207fc34 *obj, unsigned int category);

extern "C" int func_0207fc34(UnkStruct_0207fc34 *obj, unsigned short *item, unsigned int category)
{
    PMF pmf = func_0207fc7c(obj, category);
    int result = 1;
    if (pmf != 0) {
        if ((obj->*pmf)(item) == 0) {
            result = 0;
        }
    }
    return result;
}
