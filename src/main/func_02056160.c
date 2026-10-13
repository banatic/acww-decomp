/* func_02056160 @ 0x02056160, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Entry {
    void *result;
    void *name;
} Entry;

extern int data_021c8ca4;
extern int data_021c9b2c;
extern Entry data_021c8cac[];

extern int func_02056294(void *name);
extern void OS_Terminate(void);
extern void *func_020561cc(void *self, int slot);

int func_02056160(void *self, void *name)
{
    int slot;
    int r;

    slot = data_021c9b2c;

    if (name != (void *) 0x4e554c4c) {
        r = func_02056294(name);
        if (r != 0) {
            return r;
        }
    }
    if (data_021c8ca4 >= 0x3c) {
        OS_Terminate();
        return 0;
    }
    r = (int) func_020561cc(self, slot);
    if (r == 0) {
        OS_Terminate();
        return 0;
    }
    data_021c8cac[data_021c8ca4].result = (void *) r;
    data_021c8cac[data_021c8ca4].name = name;
    data_021c8ca4 = data_021c8ca4 + 1;
    return r;
}
