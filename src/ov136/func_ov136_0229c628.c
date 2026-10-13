/* func_ov136_0229c628 @ 0x0229c628, 0x28 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a164(void *p);
extern void func_ov002_02208098(void *p, int n);

void func_ov136_0229c628(void *obj)
{
    func_ov002_0220a164((char *) obj + 0x94);
    ((unsigned char *) obj)[0x2b76] = ((unsigned char *) obj)[0x8d];
    func_ov002_02208098(obj, 12);
}
