/* func_0201b044 @ 0x0201b044, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201afd4(void *param1, void *param2);
extern int func_020eaa6c(void *param1, void *param2);

void func_0201b044(void *param1, void *param2)
{
    int result;
    void *ptr1;
    void *ptr2;

    ptr1 = param1;
    ptr2 = param2;

    result = func_020eaa6c((char *) ptr1 + 0x38, (char *) ptr1 + 0x44);
    if (result != 0) {
        func_0201afd4(ptr1, ptr2);
    }

    *(int *) ((char *) ptr1 + 0x38) = *(int *) ptr2;
    *(int *) ((char *) ptr1 + 0x3c) = *(int *) ((char *) ptr2 + 4);
    *(int *) ((char *) ptr1 + 0x40) = *(int *) ((char *) ptr2 + 8);
}
