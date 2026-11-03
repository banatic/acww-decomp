/* talk_tags_14: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206ac60 @ 0x0206ac60, 0x2 bytes, Thumb
 * func_0206ac48 @ 0x0206ac48, 0x16 bytes, Thumb
 * func_0206ac30 @ 0x0206ac30, 0x16 bytes, Thumb
 * func_0206ac18 @ 0x0206ac18, 0x16 bytes, Thumb
 * func_0206ac00 @ 0x0206ac00, 0x16 bytes, Thumb
 * func_0206abe8 @ 0x0206abe8, 0x16 bytes, Thumb
 * func_0206abbc @ 0x0206abbc, 0x2c bytes, Thumb
 * func_0206aba8 @ 0x0206aba8, 0x14 bytes, Thumb
 * func_0206ab84 @ 0x0206ab84, 0x24 bytes, Thumb
 * func_0206ab60 @ 0x0206ab60, 0x24 bytes, Thumb
 * func_0206ab48 @ 0x0206ab48, 0x16 bytes, Thumb
 * func_0206ab30 @ 0x0206ab30, 0x16 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x24];
    unsigned char *data;
    unsigned char pad_28[0x10];
    unsigned char something[0x16];
    unsigned char flag;
} UnkStruct_0206ab84;

extern int func_02050c40(void);
extern void func_020a9334(void *object, void *next);
extern int func_02050c38(void);
extern int func_02050c30(void);
extern int func_02050c48(void);
extern int func_02050c50(void);
extern void func_020a861c(void *param1, void *param2);
extern void func_020a8750(void *ptr);

void func_0206ac60(void) {}

void func_0206ac48(int object)
{
    int next = func_02050c40();
    func_020a9334((void *) object, (void *) next);
}

void func_0206ac30(int object)
{
    int next = func_02050c38();
    func_020a9334((void *) object, (void *) next);
}

void func_0206ac18(int arg)
{
    int ret = func_02050c30();
    func_020a9334((void *) arg, (void *) ret);
}

void func_0206ac00(int object)
{
    int next = func_02050c48();
    func_020a9334((void *) object, (void *) next);
}

void func_0206abe8(int object)
{
    int next = func_02050c50();
    func_020a9334((void *) object, (void *) next);
}

void func_0206abbc(void *param0)
{
    unsigned short temp;
    void *sp;
    void *r4 = param0;

    func_020a861c((void *) ((unsigned int) param0 + 0x38), &sp);
    temp = *(unsigned short *) &sp;
    *(unsigned int *) ((unsigned int) r4 + 0x58) = (unsigned int) temp << 12;
    *(unsigned char *) (*(unsigned int *) ((unsigned int) r4 + 0x24) + 0x1a4a) = 1;
}

void func_0206aba8(void *arg)
{
    void *ptr = (char *) arg + 0x38;
    func_020a8750(ptr);
    *(unsigned int *) ((char *) arg + 0x30) = 4;
}

void func_0206ab84(UnkStruct_0206ab84 *x)
{
    func_020a8750(x->something);
    x->flag = 1;
    x->data[0x1a49] = 1;
}

void func_0206ab60(void *param)
{
    unsigned char *p;
    unsigned char *q;
    int offset;

    func_020a8750((char *) param + 0x38);
    p = (unsigned char *) param + 0x4e;
    *p = 0;
    q = *(unsigned char **) ((char *) param + 0x24);
    offset = 0x1a49;
    q[offset] = 0;
}

void func_0206ab48(void *arg0)
{
    void *r4 = arg0;
    func_020a8750((char *) arg0 + 0x38);
    *(unsigned char *) ((char *) r4 + 0x4f) = 1;
}

void func_0206ab30(void *arg)
{
    void *r4;
    r4 = arg;
    func_020a8750((char *) r4 + 0x38);
    *(char *) ((char *) r4 + 0x4f) = 0;
}
