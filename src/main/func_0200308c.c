/* func_0200308c @ 0x0200308c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9898(int);

void func_0200308c(void *arg0)
{
    int condition_value0;
    if ((condition_value0 = (int) (*(unsigned int *) ((char *) arg0 + 0x4c))) != 0) {
        func_020e9898(condition_value0);
        *(unsigned int *) ((char *) arg0 + 0x4c) = 0;
    }
}
