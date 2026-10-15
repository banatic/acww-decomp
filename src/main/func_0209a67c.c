/* func_0209a67c @ 0x0209a67c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a6ec(void *);
extern int func_020951bc(void *object);

int func_0209a67c(void *argument0)
{
    int forwarded_value;

    int result;

    if ((forwarded_value = (int) func_0209a6ec((void *) argument0)) != 0 && func_020951bc((void *) forwarded_value) != 0) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}
