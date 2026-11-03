/* chat_scene_8: 3 functions, module ov111
 * mwccarm 1.2/base -O4,s
 * func_ov111_022a0de8 @ 0x022a0de8, 0x20 bytes, Thumb
 * func_ov111_022a0dcc @ 0x022a0dcc, 0x1a bytes, Thumb
 * func_ov111_022a0d9c @ 0x022a0d9c, 0x30 bytes, Thumb
 */

extern void func_ov111_0229ff88(void *p);
extern void func_ov002_02208090(void *p, int arg);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_020ee45c(void *argument0);
extern unsigned char func_ov090_0229936c(void *argument0);
extern void func_ov111_0229ff60(void *arg);
extern int func_ov111_0229efd8(void *, int);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *);
extern void func_ov111_0229fe0c(void *);

int func_ov111_022a0de8(void *p)
{
    func_ov111_0229ff88(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0((void *) (p), 1);
    return 1;
}

int func_ov111_022a0dcc(void *arg)
{

    func_ov090_0229936c((void *) func_020ee45c(arg));
    func_ov111_0229ff60(arg);
    return 1;
}

int func_ov111_022a0d9c(void *arg)
{
    if (func_ov111_0229efd8(arg, 4) != 0) {
        if (func_0206fe54() != 0) {
            func_ov002_02209eb8((char *) arg + 0x3d38);
        }
        func_ov111_0229fe0c(arg);
    }
    return 1;
}
