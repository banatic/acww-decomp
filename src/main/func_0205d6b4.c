/* func_0205d6b4 @ 0x0205d6b4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205d520(void *);
extern int __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_02034ce0(void *);
extern void func_020051b0(void *);

struct _S {
    unsigned char pad_00[0x28];
    unsigned short arr[10];
    unsigned char unk_3C[1];
};

struct _S *func_0205d6b4(struct _S *p)
{
    __cxa_vec_ctor((void *) (p->arr), 10, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);
    func_0205d520(&p->unk_3C[0]);
    {
        int i;
        for (i = 0; i < 10; i++) {
            p->arr[i] = 0xfff1;
        }
    }
    return p;
}
