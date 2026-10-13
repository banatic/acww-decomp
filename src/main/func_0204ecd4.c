/* func_0204ecd4 @ 0x0204ecd4, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e993c(void *param1, void *param2);
extern void func_02030bac(void *param1);

void func_0204ecd4(void *param1, void *param2)
{
    void *ptr;
    void *temp;

    ptr = *(void **) param1;
    if (ptr != 0) {
        func_020e993c(param2, ptr);
        *(void **) param1 = 0;
    }
    temp = *(void **) ((char *) param1 + 0x1c);
    func_02030bac(temp);
}
