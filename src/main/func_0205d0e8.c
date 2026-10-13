/* func_0205d0e8 @ 0x0205d0e8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055b40(void *);
extern void func_020e9b9c(int);
extern int data_021c9ae8;

struct UnkStruct_0205d0e8 {
    char pad_00[0x14];
};

struct UnkStruct_0205d0e8_2 {
    int arr[4];
    struct UnkStruct_0205d0e8 sub[4];
};

void func_0205d0e8(struct UnkStruct_0205d0e8_2 *p)
{
    int i;

    for (i = 0; i < 4; i++) {
        func_02055b40(&p->sub[i]);
    }

    for (i = 0; i < 4; i++) {
        p->arr[i] = 0;
    }

    if (data_021c9ae8) {
        func_020e9b9c(data_021c9ae8);
    }
}
