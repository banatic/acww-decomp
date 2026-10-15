/* func_02011bb0 @ 0x02011bb0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9898(int);

void func_02011bb0(void *arg0)
{
    int condition_value0;
    void *r4 = arg0;
    if ((condition_value0 = (int) (*(unsigned int *) ((char *) r4 + 0x48))) != 0) {
        func_020e9898(condition_value0);
        *(unsigned int *) ((char *) r4 + 0x48) = 0;
    }
}
