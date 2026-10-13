/* func_02011bb0 @ 0x02011bb0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9898(void);

void func_02011bb0(void *arg0)
{
    void *r4 = arg0;
    if (*(unsigned int *) ((char *) r4 + 0x48) != 0) {
        func_020e9898();
        *(unsigned int *) ((char *) r4 + 0x48) = 0;
    }
}
