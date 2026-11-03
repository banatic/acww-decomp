/* shop_list_a_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020aea5c @ 0x020aea5c, 0x28 bytes, Thumb
 * func_020aea40 @ 0x020aea40, 0x1c bytes, Thumb
 * func_020aea28 @ 0x020aea28, 0x18 bytes, Thumb
 * func_020aea20 @ 0x020aea20, 0x8 bytes, Thumb
 * func_020aea1c @ 0x020aea1c, 0x2 bytes, Thumb
 * func_020ae9c0 @ 0x020ae9c0, 0x5c bytes, Thumb
 */

struct UnkStruct_020aea28 {
    unsigned char data[0x10];
};

extern void func_020051b0(void *);
extern void func_02034ce0(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020b00c8(void *, const void *, int);
extern void func_0209e474(void *);
extern void func_0209e140(void *, int);
extern int func_02073d90(int);
extern int func_020ae92c(void *, void *);
extern void func_020ae96c(void *, int, int, int);
extern void func_020ae900(void *, void *);
extern int data_020ccf94;

int func_020aea5c(int param)
{
    __cxa_vec_ctor((void *) (param), 6, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);
    return param;
}

int func_020aea40(int arg)
{
    __cxa_vec_cleanup((void *) (arg), 6, 2, (void (*)(void *)) func_020051b0);
    return arg;
}

void func_020aea28(struct UnkStruct_020aea28 *p)
{
    func_020b00c8(p, (char *) p + 0x10, 6);
    p->data[0xF] = 1;
}

void func_020aea20(void *argument0)
{
    func_020aea28((struct UnkStruct_020aea28 *) ((void *) argument0));
}

void func_020aea1c(void *object) {}

void func_020ae9c0(void *param)
{
    unsigned int local[2];

    local[0] = 0;
    local[1] = 0;

    func_0209e474(local);
    if (((unsigned char *) local)[2] < 6) {
        func_0209e140(local, 1);
    }
    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    if (func_020ae92c(param, local) == 0) {
        return;
    }
    func_020ae96c(param, ((unsigned char *) local)[5], ((unsigned char *) local)[4], ((unsigned char *) local)[3]);
    func_020ae900(param, local);
}
