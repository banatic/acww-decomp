/* func_020a0f3c @ 0x020a0f3c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a0f3c_2;
struct UnkStruct_020a0f3c {
    char pad_00[0x64];
    int unk_64;
};
extern struct UnkStruct_020a0f3c *data_020ccf94;
extern int func_02073dd4(struct UnkStruct_020a0f3c *g, int i);
extern void func_020a2444(struct UnkStruct_020a0f3c_2 *o, int a, int b);

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
    g = data_020ccf94;
    for (; i >= 0; i--) {
        if (func_02073dd4(g, i)) {
            list[n] = i;
            n++;
        }
    }
    for (i = 3; i >= 0; i--) {
        func_020a2444(self, i, 4);
    }
    for (i = 0; i < n; i++) {
        j = i + 1;
        if (j >= n) {
            j = 0;
        }
        a = *(volatile int *) &list[i];
        func_020a2444(self, a, list[j]);
    }
}
