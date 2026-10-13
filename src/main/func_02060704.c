/* func_02060704 @ 0x02060704, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int arr0[9];
    struct {
        char data[20];
    } sub[9];
    unsigned char pad_D8[0x678];
    int arr1[9];
} UnkStruct_02060704;

extern void func_02055b40(void *ptr);
extern void func_020e9b9c(void);
extern int data_021c9ac8;

void func_02060704(UnkStruct_02060704 *p)
{
    int i;

    for (i = 0; i < 9; i++) {
        func_02055b40(&p->sub[i]);
    }

    for (i = 0; i < 9; i++) {
        p->arr0[i] = 0;
        p->arr1[i] = 0;
    }

    if (data_021c9ac8) {
        func_020e9b9c();
    }
}
