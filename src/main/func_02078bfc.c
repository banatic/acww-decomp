/* func_02078bfc @ 0x02078bfc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c9ac0;
extern int func_020ea0e0(unsigned int, void *);

void func_02078bfc(int *arr)
{
    void *p = data_021c9ac0;
    int i;
    for (i = 0; i < 8; i++) {
        arr[i] = func_020ea0e0(0x7ac, p);
    }
}
