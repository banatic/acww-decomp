/* func_ov140_0229b248 @ 0x0229b248, 0x1e bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov140_0229acc0(void *obj);
extern unsigned char *func_ov002_022080a0(void *, unsigned char);

int func_ov140_0229b248(void *obj)
{
    func_ov140_0229acc0(obj);
    ((unsigned char *) obj)[0x8c] = 0;
    func_ov002_022080a0(obj, 0);
    return 1;
}
