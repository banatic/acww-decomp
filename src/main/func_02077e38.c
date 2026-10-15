/* func_02077e38 @ 0x02077e38, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eb04c(void *friend_data);

int func_02077e38(void *friend_data)
{
    int result;
    if (func_020eb04c(friend_data) == 2) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
