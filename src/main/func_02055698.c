/* func_02055698 @ 0x02055698, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbe94;
extern int func_02064b2c(int, int, int, int);
extern void *func_02107828(int resource);
extern int func_021077e8(int);
extern int func_02056268(void *, int);
extern int func_020561fc(void *, int);
extern int func_02056064(int, int);
extern int NNS_G3dBindMdlTex(int, int);
extern int NNS_G3dBindMdlPltt(int, int);
extern void func_020e993c(int, int);
extern void func_02055f6c(void *);

int func_02055698(void *arg1, int arg2, int arg3, int arg4)
{
    int ret;
    int global_val;
    void *obj;
    int ext2;
    void *r7;
    unsigned short off;
    char *mid;
    int val;

    global_val = data_021fbe94;
    ret = func_02064b2c(arg2, global_val, -4, 0);
    if (ret == 0) {
        return 0;
    }

    obj = func_02107828(ret);
    off = *((unsigned short *) ((char *) obj + 0xe));
    mid = (char *) obj + off;
    val = *(int *) (mid + 0xc);
    r7 = (char *) obj + val;

    ext2 = func_021077e8(ret);

    if (arg3) {
        *(int *) ((char *) arg1 + 0x5c) = func_02056268(r7, arg3);
    } else {
        *(int *) ((char *) arg1 + 0x5c) = func_020561fc(r7, arg4);
    }

    if (ext2) {
        func_02056064(ext2, *(int *) ((char *) arg1 + 0x94));
        NNS_G3dBindMdlTex(*(int *) ((char *) arg1 + 0x5c), ext2);
        NNS_G3dBindMdlPltt(*(int *) ((char *) arg1 + 0x5c), ext2);
    }

    func_020e993c(global_val, ret);
    func_02055f6c(arg1);

    return 1;
}
