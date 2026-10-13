/* func_020561fc @ 0x020561fc, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Entry {
    void *result;
    void *name;
} Entry;

extern int data_021c8ca8;
extern int data_021c9b2c;
extern Entry data_021c8e8c[];

extern int func_020562cc(void *name);
extern void OS_Terminate(void);
extern void *func_02056268(void *self, int slot);

int func_020561fc(void *self, void *name)
{
    int slot;
    int r;

    slot = data_021c9b2c;

    if (name != (void *) 0x4e554c4c) {
        r = func_020562cc(name);
        if (r != 0) {
            return r;
        }
    }
    if (data_021c8ca8 >= 0x96) {
        OS_Terminate();
        return 0;
    }
    r = (int) func_02056268(self, slot);
    if (r == 0) {
        OS_Terminate();
        return 0;
    }
    data_021c8e8c[data_021c8ca8].result = (void *) r;
    data_021c8e8c[data_021c8ca8].name = name;
    data_021c8ca8 = data_021c8ca8 + 1;
    return r;
}
