/* func_02068e44 @ 0x02068e44, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9898(void *ptr);

void func_02068e44(void *param)
{
    void *ptr;
    void *ptr2;
    void *ptr3;

    ptr = *(void **) param;
    if (ptr != 0) {
        func_020e9898(ptr);
        *(void **) param = 0;
    }

    ptr2 = *(void **) ((char *) param + 4);
    if (ptr2 != 0) {
        func_020e9898(ptr2);
        *(void **) ((char *) param + 4) = 0;
    }

    ptr3 = *(void **) ((char *) param + 8);
    if (ptr3 != 0) {
        func_020e9898(ptr3);
        *(void **) ((char *) param + 8) = 0;
    }
}
