/* func_0206671c @ 0x0206671c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003780(void *);
extern void *func_0209529c(void *);
extern void func_02095208(void *, void *);
extern void *func_02095074(void *, void *);
extern void func_020037ac(void *, void *);
extern int func_02003618(void *, void *);
extern int func_0209526c(void *);
extern int func_02003750(void *);

struct Param {
    unsigned char pad_00[0x1e];
    unsigned char mode;
};

int func_0206671c(struct Param *p, void *q)
{
    unsigned char obj0[16];
    unsigned char obj1[36];

    func_02003780(&obj0);
    func_0209529c(&obj1);

    switch (p->mode) {
        case 1:
        case 2:
        case 6:
            func_02095208(&obj1, p);
            func_02095074(&obj1, q);
            break;
        case 3:
        case 5:
            func_020037ac(&obj0, p);
            func_02003618(&obj0, q);
            break;
    }

    func_0209526c(&obj1);
    return func_02003750(&obj0);
}
