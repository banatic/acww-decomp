/* exchange_blocks: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a0fac @ 0x020a0fac, 0x8c bytes, Thumb
 * func_020a0f3c @ 0x020a0f3c, 0x70 bytes, Thumb
 */

struct UnkStruct_020a0f3c_2;

struct UnkStruct_020a0f3c {
    char pad_00[0x64];
    int unk_64;
};

extern int func_020a6ed0(void);
extern int func_02073dd4(int *p, int v);
extern void func_020a2444(void *p, int a, int b);
extern int func_020644cc(int n);
extern int *data_020ccf94;

void func_020a0fac(void *p)
{
    int x;
    int count;
    int i;
    int *ptr;
    int arr[4];
    int v;

    x = func_020a6ed0();
    count = 0;
    i = 3;
    ptr = data_020ccf94;
    while (i >= 0) {
        if (i != x && func_02073dd4(ptr, i)) {
            arr[count] = i;
            count++;
        }
        i--;
    }

    i = 3;
    while (i >= 0) {
        if (func_02073dd4(ptr, i)) {
            func_020a2444(p, i, i);
        } else {
            func_020a2444(p, i, 4);
        }
        i--;
    }

    v = arr[func_020644cc(count)];
    func_020a2444(p, v, x);
    func_020a2444(p, x, v);
}

void func_020a0f3c(struct UnkStruct_020a0f3c_2 *self)
{
    int list[5];
    struct UnkStruct_020a0f3c *g;
    int n;
    int i;
    int j;
    int a;

    n = 0;
    i = 3;
    g = (*(struct UnkStruct_020a0f3c * *) &data_020ccf94);
    for (; i >= 0; i--) {
        if (func_02073dd4((int *) g, i)) {
            list[n] = i;
            n++;
        }
    }
    for (i = 3; i >= 0; i--) {
        func_020a2444((void *) self, i, 4);
    }
    for (i = 0; i < n; i++) {
        j = i + 1;
        if (j >= n) {
            j = 0;
        }
        a = *(volatile int *) &list[i];
        func_020a2444((void *) self, a, list[j]);
    }
}
