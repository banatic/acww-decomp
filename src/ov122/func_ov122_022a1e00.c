/* func_ov122_022a1e00 @ 0x022a1e00, 0x40 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee45c(void *);
extern void func_ov090_022993cc(int, int);
extern void func_ov122_0229f454(void *, int);
extern void func_ov122_0229efc8(void *, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov122_0229f2d0(void *);
extern void func_ov122_0229effc(void *);

void func_ov122_022a1e00(void *param)
{
    func_ov090_022993cc(func_020ee45c(param), 7);
    func_ov122_0229f454(param, 0);
    func_ov122_0229efc8(param, 4);
    *((unsigned char *) param + 0x8c) = 0xd;
    func_ov002_022080a0((void *) (param), 1);
    func_ov122_0229f2d0(param);
    func_ov122_0229effc(param);
}
