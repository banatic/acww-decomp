/* func_02054d60 @ 0x02054d60, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcc10(void *p1, void *p2);
extern void func_02054d80(void *p1, void *p2);

void func_02054d60(void *p1, void *p2)
{
    if (func_01ffcc10(p1, p2) == 0) {
        func_02054d80(p1, p2);
    }
}
