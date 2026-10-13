/* func_ov132_0229b868 @ 0x0229b868, 0x1e bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov132_0229b564(void *object);
extern void func_ov002_022080a0(void *object);

int func_ov132_0229b868(void *obj)
{
    func_ov132_0229b564(obj);
    ((char *) obj)[0x8c] = 0;
    func_ov002_022080a0(obj);
    return 1;
}
