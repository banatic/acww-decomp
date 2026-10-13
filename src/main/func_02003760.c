/* func_02003760 @ 0x02003760, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020642fc(void *a, void *b);
extern void func_020037ac(void *a, void *b);

void *func_02003760(void *a, void *b)
{
    func_020642fc(a, b);
    func_020037ac(a, b);
    return a;
}
