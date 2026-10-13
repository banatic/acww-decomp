/* func_0204cbc0 @ 0x0204cbc0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204cb90(void);
extern void *func_0204cc04(void);

void func_0204cbc0(void)
{
    int result;
    void *ptr;

    result = func_0204cb90();
    if (result >= 0) {
        ptr = func_0204cc04();
        *(unsigned short *) ptr = 0x63;
        *(unsigned int *) ((char *) ptr + 4) = 1;
        *(unsigned int *) ((char *) ptr + 8) = 1;
    }
}
