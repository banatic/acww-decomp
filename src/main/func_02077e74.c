/* func_02077e74 @ 0x02077e74, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a, b, c;
} Triple;

extern unsigned int func_020eb058(void *p1, Triple *p2);
extern void func_02077ebc(void *buffer);

unsigned int func_02077e74(void *p1, Triple *p2)
{
    Triple local;
    unsigned int ret;

    local = *p2;
    ret = func_020eb058(p1, &local);
    func_02077ebc(&local);

    return ret;
}
