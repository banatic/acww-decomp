/* func_02021f1c @ 0x02021f1c, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098eb8(int);
extern void func_0202d694(unsigned short *);
extern int func_0202da38(void *, char *, char *, int, int, int, int, int, int);
extern unsigned int func_0208150c(void *);
extern int func_020036e8(unsigned char *);
extern void func_02015de4(void *, unsigned short *, int, int);

struct Data_020c8c78 {
    int a;
    unsigned char b;
};
extern struct Data_020c8c78 data_020c8c78;

struct S_02021f1c {
    char pad_00[0x100];
    void *ptr;
    char data[0x20];
    unsigned short val;
};

int func_02021f1c(struct S_02021f1c *arg)
{
    int result;
    int ret;
    unsigned short local_val;

    ret = func_020984e8();
    result = 0;
    if (ret != 0) {
        if (func_02098eb8(func_02099734(ret)) != -1) {
            func_0202d694(&local_val);
            arg->val = local_val;
            if (arg->val != 0xfff1) {
                func_02015de4(arg, &arg->val, result, 7);
                func_0202da38(arg, arg->data, &arg->data[30], 30,
                              func_020036e8((unsigned char *) func_0208150c(*(void **) ((char *) arg->ptr + 0x830))),
                              data_020c8c78.a, data_020c8c78.b, result, result);
                result = 1;
            }
        }
    }
    return result;
}
