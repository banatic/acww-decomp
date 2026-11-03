/* talk_page_3: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206c800 @ 0x0206c800, 0x50 bytes, Thumb
 * func_0206c7f4 @ 0x0206c7f4, 0xc bytes, Thumb
 * func_0206c7e8 @ 0x0206c7e8, 0xc bytes, Thumb
 * func_0206c7dc @ 0x0206c7dc, 0xc bytes, Thumb
 * func_0206c7d0 @ 0x0206c7d0, 0xc bytes, Thumb
 * func_0206c7c4 @ 0x0206c7c4, 0xc bytes, Thumb
 * func_0206c7b8 @ 0x0206c7b8, 0xc bytes, Thumb
 * func_0206c7ac @ 0x0206c7ac, 0xc bytes, Thumb
 * func_0206c7a0 @ 0x0206c7a0, 0xc bytes, Thumb
 * func_0206c794 @ 0x0206c794, 0xc bytes, Thumb
 * func_0206c788 @ 0x0206c788, 0xc bytes, Thumb
 * func_0206c77c @ 0x0206c77c, 0xc bytes, Thumb
 * func_0206c770 @ 0x0206c770, 0xc bytes, Thumb
 * func_0206c764 @ 0x0206c764, 0xc bytes, Thumb
 * func_0206c758 @ 0x0206c758, 0xc bytes, Thumb
 * func_0206c74c @ 0x0206c74c, 0xc bytes, Thumb
 */

typedef struct UnkStruct_0206c800 {
    char pad_00[0x2c];
    void *data;
} UnkStruct_0206c800;

typedef struct Caller {
    char pad_00[0xc];
    int (*func)(void *);
} Caller;

extern int func_0206786c(void *p);
extern void func_020a9334(void *obj, int v);
extern void func_020a7994(void *p, int v);
extern void func_0206d484(int, int);
extern void func_0206d428(void *self, int index);

void func_0206c800(UnkStruct_0206c800 *obj)
{
    func_0206786c(obj->data);
    {
        void *p = (char *) obj->data + 0x1d2c;
        Caller *q = *(Caller **) p;
        int ret = q->func(p);
        func_020a9334(obj, ret);
    }
    {
        void *p = (char *) obj->data + 0x1d2c;
        Caller *q = *(Caller **) p;
        int ret = q->func(p);
        func_020a7994((char *) obj->data + 0x1a58, ret);
    }
    *(int *) ((char *) obj->data + 0x1a60) = 0;
}

void func_0206c7f4(int p0)
{
    func_0206d484(p0, 0);
}

void func_0206c7e8(int a)
{
    func_0206d484(a, 1);
}

void func_0206c7dc(int a)
{
    func_0206d484(a, 2);
}

void func_0206c7d0(int a)
{
    func_0206d484(a, 3);
}

void func_0206c7c4(void *a)
{
    func_0206d484((int) a, 4);
}

void func_0206c7b8(void *a)
{
    func_0206d484((int) a, 5);
}

void func_0206c7ac(int a)
{
    func_0206d484(a, 6);
}

void func_0206c7a0(void *a)
{
    func_0206d484((int) a, 7);
}

void func_0206c794(int a)
{
    func_0206d484(a, 8);
}

void func_0206c788(void *a)
{
    func_0206d484((int) a, 9);
}

void func_0206c77c(void *a)
{
    func_0206d484((int) a, 0xa);
}

void func_0206c770(void *arg0)
{
    func_0206d428(arg0, 0);
}

void func_0206c764(void *a)
{
    func_0206d428(a, 1);
}

void func_0206c758(void *a)
{
    func_0206d428(a, 2);
}

void func_0206c74c(void *a)
{
    func_0206d428(a, 3);
}
