/* mabel_talk_4: 5 functions, module ov049
 * mwccarm 1.2/base -O4,s
 * func_ov049_02261ba4 @ 0x02261ba4, 0x22 bytes, Thumb
 * func_ov049_02261b80 @ 0x02261b80, 0x22 bytes, Thumb
 * func_ov049_02261b6c @ 0x02261b6c, 0x14 bytes, Thumb
 * func_ov049_02261b48 @ 0x02261b48, 0x22 bytes, Thumb
 * func_ov049_02261b34 @ 0x02261b34, 0x14 bytes, Thumb
 */

extern void func_020157c8(int, int, int);
extern int func_02015828(int, int);
extern void func_ov049_022610c4(int, int);
extern void func_0201b420(void *a, int b);
extern void func_0201b3a4(int a, int b);

void func_ov049_02261ba4(int r0)
{
    int r4 = r0;
    func_020157c8(r4, 4, 0);
    func_02015828(r4, 2);
    func_ov049_022610c4(r4, 1);
}

void func_ov049_02261b80(int r0)
{
    int r4 = r0;
    func_020157c8(r4, 0xb, 0);
    func_02015828(r4, 2);
    func_ov049_022610c4(r4, 2);
}

void func_ov049_02261b6c(void *p)
{
    func_0201b420(*(void **) ((char *) p + 0xB0), 0x15e);
}

void func_ov049_02261b48(void *p)
{
    func_020157c8((int) p, 0x1e, 0);
    func_02015828((int) p, 2);
    func_ov049_022610c4((int) p, 6);
}

void func_ov049_02261b34(void *self)
{
    func_0201b3a4(*(int *) ((char *) self + 0xb0), *(int *) ((char *) self + 0xbc));
}
