/* func_02016384 @ 0x02016384, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02016618(void *self, void *arg);
extern int func_0201a7b4(void *ptr);
extern int func_0201a7bc(void *ptr);
extern int func_02054230(void *ptr);
extern int func_0201a798(void);
extern unsigned int func_0201643c(void *self, int c);
extern unsigned int func_02016430(void *self, int c);
extern void func_02016530(void *self, void *arg, unsigned int a, unsigned int b);
extern void func_02016520(void *self, void *arg);
extern void func_02016448(void *self, void *arg);

typedef struct {
    u8 pad_00[0xc];
    int c;     // 0xc
    u8 flag10; // 0x10
    u8 pad_11[0x7];
    u8 flag18; // 0x18
} UnkStruct_02016384;

void func_02016384(UnkStruct_02016384 *self, void *arg)
{
    if (func_02016618(self, arg) == 0) {
        goto out;
    }

    if (func_0201a7b4((char *) arg + 0x418) >= 2) {
        goto L_206;
    }

    if (func_0201a7bc((char *) arg + 0x418) == 0) {
        goto L_3e6;
    }

    if (self->flag10 != 0) {
        if (func_02054230((char *) arg + 0xec) == 0) {
            goto out;
        }
    }

    self->c = func_0201a798();
    {
        unsigned int v1 = func_0201643c(self, self->c);
        unsigned int v2 = func_02016430(self, self->c);
        func_02016530(self, arg, v1, v2);
    }
    self->flag10 = 1;
    goto out;

L_3e6:
    if (self->flag10 == 1) {
        if (func_02054230((char *) arg + 0xec) != 0) {
            func_02016520(self, arg);
            self->flag10 = 0;
        }
    }
    goto out;

L_206:
    if (self->flag10 == 1) {
        func_02016520(self, arg);
        self->flag10 = 0;
    }

out:
    if (self->flag18 == 0) {
        func_02016448(self, arg);
    }
}
