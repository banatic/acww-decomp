/* func_ov122_022a0038 @ 0x022a0038, 0x1c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov122_0229f2f4(void *);
extern void func_ov002_02207fc0(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

unsigned char *func_ov122_022a0038(void *param)
{
    func_ov002_02207fc0(param);
    func_ov122_0229f2f4(param);
    return func_ov002_02208098((void *) (param), 6);
}
