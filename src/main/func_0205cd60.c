/* func_0205cd60 @ 0x0205cd60, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int arr0[25];
    unsigned short arr1[25];
    unsigned short arr2[25];
} my_struct;

extern int data_021c9af8;
extern void func_020e9b9c(void *);

void func_0205cd60(my_struct *p)
{
    void *condition_value0;
    int i;
    for (i = 0; i < 25; i++) {
        p->arr0[i] = 0;
        p->arr1[i] = 0x144;
        p->arr2[i] = 0;
    }
    if ((condition_value0 = (void *) (data_021c9af8))) {
        func_020e9b9c(condition_value0);
    }
}
