/* func_02077b9c @ 0x02077b9c, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void FS_EndOverlay(void *ptr);

void func_02077b9c(void *arg)
{
    void *ptr;
    int val;

    ptr = (void *) ((char *) arg + 8);
    FS_EndOverlay(ptr);
    val = -1;
    *(int *) arg = val;
}
