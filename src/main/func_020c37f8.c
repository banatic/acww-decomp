/* func_020c37f8 @ 0x020c37f8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020c3690(void *ptr, int arg);
extern void *data_021fbca0;

void func_020c37f8(void)
{
    if (data_021fbca0) {
        func_020c3690(data_021fbca0, 4);
    }
}
