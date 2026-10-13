/* func_02072594 @ 0x02072594, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02072600(void *param1);
extern void func_020e9898(void *param1);

void func_02072594(void *param1)
{
    void *ptr;
    void *local;

    ptr = param1;
    if (*((unsigned int *) ptr) != 0) {
        func_020e9898(*((void **) ptr));
        *((unsigned int *) ptr) = 0;
    }
    func_02072600(ptr);
}
