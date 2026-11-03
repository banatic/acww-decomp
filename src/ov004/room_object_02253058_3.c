/* room_object_02253058_3: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02217cb4 @ 0x02217cb4, 0x4 bytes, Thumb
 * func_ov004_02217c70 @ 0x02217c70, 0x44 bytes, Thumb
 * func_ov004_02217c6c @ 0x02217c6c, 0x4 bytes, Thumb
 * func_ov004_02217c58 @ 0x02217c58, 0x14 bytes, Thumb
 */

typedef void (*Fn)(void *self, int a, int b);

extern void func_0203ee08(void *self, void *p);
extern int func_0203e020(void *self);
extern int func_020b5e10(void);
extern int func_020b6434(int a, int b, int c, int d);
extern void func_020a1948(void);

int func_ov004_02217cb4(void *callbackObject)
{
    return 1;
}

void func_ov004_02217c70(char *self)
{
    void *p = *(void **) (self + 0x12c);
    char *q;

    if (p != 0 && *(int *) ((char *) p + 4) == 0) {
        q = self;
        if (self != 0) {
            q = q + 0xec;
        }
        func_0203ee08(self, q);
        func_0203e020(self);
        func_020b6434(func_020b5e10(), 0x2e, 2, 0);
        func_020a1948();
    }
}

int func_ov004_02217c6c(void *callbackObject)
{
    return 1;
}

void func_ov004_02217c58(void *self)
{
    (*(Fn **) self)[28](self, 8, 0xff);
}
