/* message_decoder_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b4e88 @ 0x020b4e88, 0x16 bytes, Thumb
 * func_020b4e70 @ 0x020b4e70, 0x16 bytes, Thumb
 * func_020b4e58 @ 0x020b4e58, 0x16 bytes, Thumb
 * func_020b4e38 @ 0x020b4e38, 0x1e bytes, Thumb
 */

extern int func_02050c30(void);
extern int func_02050c18(void);
extern void func_020a9334(void *object, void *next);
extern int func_02050c10(void);
extern void func_020b5074(void *p);
extern void func_020b50e0(void *p);

void func_020b4e88(void *p)
{
    func_020a9334(p, (void *) (func_02050c30()));
}

void func_020b4e70(int object)
{
    int next = func_02050c18();
    func_020a9334((void *) object, (void *) next);
}

void func_020b4e58(int object)
{
    int next = func_02050c10();
    func_020a9334((void *) object, (void *) next);
}

void func_020b4e38(unsigned char *p0)
{
    if (p0[0x46] != 0) {
        func_020b5074(p0);
    } else {
        func_020b50e0(p0);
    }
}
