/* func_020eef80 @ 0x020eef80, 0x54 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void OS_Terminate(void);
extern unsigned long func_020efc18(const unsigned long *p);
extern void func_020ef284(int node);
extern void *func_020efc2c(void *list, void *object);

void func_020eef80(void *list)
{
    void *node;
    if (list == 0) {
        OS_Terminate();
    }
    node = (void *) func_020efc18((const unsigned long *) list);
    if (node == 0) {
        return;
    }
    do {
        func_020ef284((int) node);
        node = func_020efc2c(list, node);
    } while (node != 0);
}
