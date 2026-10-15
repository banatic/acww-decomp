/* func_0204cbc0 @ 0x0204cbc0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204cb90(int, int);
extern void *func_0204cc04(int);

void func_0204cbc0(int argument0, int argument1)
{
    int result;
    void *ptr;

    result = func_0204cb90((int) argument0, (int) argument1);
    if (result >= 0) {
        ptr = func_0204cc04(result);
        *(unsigned short *) ptr = 0x63;
        *(unsigned int *) ((char *) ptr + 4) = 1;
        *(unsigned int *) ((char *) ptr + 8) = 1;
    }
}
