/* func_02063084 @ 0x02063084, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef int (*Handler)(int);
struct HandlerEntry {
    char pad_00[0x10];
    Handler func;
};
extern struct HandlerEntry data_020ccab0[];

int func_02063084(int param)
{
    unsigned int i;
    for (i = 0; i < 9; i++) {
        if (data_020ccab0[i].func(param) != 0) {
            return i;
        }
    }
    return 9;
}
