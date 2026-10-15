/* func_ov003_0221a860 @ 0x0221a860, 0x26 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221a8ac(void *argument0);
extern int func_ov003_0221a888(int a);

int func_ov003_0221a860(int a)
{
    if (func_ov003_0221a8ac((void *) a)) {
        if (func_ov003_0221a888(a)) {
            return 0;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}
