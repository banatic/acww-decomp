/* func_ov003_02220384 @ 0x02220384, 0x1a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02220294(int argument0);
extern int func_ov009_0226305c(void *object);

int func_ov003_02220384(int argument0)
{
    int object = func_ov003_02220294(argument0);
    if (object) {
        return func_ov009_0226305c((void *) object);
    } else {
        return 0;
    }
}
