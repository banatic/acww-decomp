/* model_cache_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020561fc @ 0x020561fc, 0x6c bytes, Thumb
 * func_020561cc @ 0x020561cc, 0x30 bytes, Thumb
 * func_02056160 @ 0x02056160, 0x6c bytes, Thumb
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
extern int func_02057a4c(int *);
extern int func_020e9948(int a1, int a2);
extern void MI_CpuCopy8(int a1, int a2, int a3);
extern int data_021c8ca4;
extern Entry data_021c8cac[];
extern int func_02056294(void *name);

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

int func_020561cc(int a1, int a2)
{
    int v1;
    int v2;

    v1 = func_02057a4c((int *) a1);
    v2 = func_020e9948(a2, v1);
    if (v2 == 0) {
        return 0;
    }
    MI_CpuCopy8(a1, v2, v1);
    return v2;
}

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
    r = (int) func_020561cc((int) self, slot);
    if (r == 0) {
        OS_Terminate();
        return 0;
    }
    data_021c8cac[data_021c8ca4].result = (void *) r;
    data_021c8cac[data_021c8ca4].name = name;
    data_021c8ca4 = data_021c8ca4 + 1;
    return r;
}
