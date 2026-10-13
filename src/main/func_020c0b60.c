/* func_020c0b60 @ 0x020c0b60, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020c0e44(void *param1);
extern void func_020c0be4(void *param1);

void func_020c0b60(void *param1)
{
    void *r4 = param1;
    int result;

    result = func_020c0e44((char *) param1 + 0x34);
    if (result != 0) {
        *(int *) ((char *) r4 + 0xc) = 0x12;
        *(int *) ((char *) r4 + 0x58) = 3;
        func_020c0be4(r4);
    } else {
        *(int *) ((char *) r4 + 4) = 3;
    }
}
