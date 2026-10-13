/* func_02060b48 @ 0x02060b48, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021ebcd4;
extern void *func_02060f04(void *ptr, void *key);
extern void func_0206117c(void *node, void *param);

int func_02060b48(void *key, void *param)
{
    void *res;
    res = func_02060f04(&data_021ebcd4, key);
    if (res != 0) {
        func_0206117c(res, param);
        return 1;
    }
    return 0;
}
