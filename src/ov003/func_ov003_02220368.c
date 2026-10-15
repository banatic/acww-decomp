/* func_ov003_02220368 @ 0x02220368, 0x1a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02220294(int argument0);
extern int func_ov009_02262ff8(void *object);

int func_ov003_02220368(int argument0)
{
    int object = func_ov003_02220294(argument0);
    return object ? func_ov009_02262ff8((void *) object) : 0;
}
