/* talk_process: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a9c6c @ 0x020a9c6c, 0x18 bytes, Thumb
 * func_020a9c4c @ 0x020a9c4c, 0x20 bytes, Thumb
 * func_020a9c2c @ 0x020a9c2c, 0x20 bytes, Thumb
 * func_020a9c04 @ 0x020a9c04, 0x28 bytes, Thumb
 * func_020a9bd8 @ 0x020a9bd8, 0x2c bytes, Thumb
 * func_020a9bb8 @ 0x020a9bb8, 0x20 bytes, Thumb
 * func_020a9ba0 @ 0x020a9ba0, 0x18 bytes, Thumb
 * func_020a9b88 @ 0x020a9b88, 0x18 bytes, Thumb
 * func_020a9b7c @ 0x020a9b7c, 0xc bytes, Thumb
 * func_020a9b70 @ 0x020a9b70, 0xc bytes, Thumb
 */

typedef struct {
    volatile unsigned int vtbl;
} UnkStruct_020a9c4c;

extern int func_020edf70(int);
extern void *func_020ee660(void *);
extern unsigned char data_020da13c[];
extern unsigned char data_020e3e8c[];
extern void func_020ee62c(void *p);
extern void func_020edf54(void *);
extern void func_0208ff88(void);
extern void func_020a7e30(void);
extern void func_02003108(void);
extern void func_02011fa4(void);
extern void func_02011ebc(void);
extern void func_0206829c(void);
extern void func_020b8cb8(void);
extern void func_020b8ca8(void);
extern void func_0206826c(void);
extern void func_02011eb0(void);
extern void func_0208ff78(void);
extern void func_0208ff68(void);
extern void func_0206823c(void);
extern void func_020b8c98(void);
extern void func_020b8c88(void);
extern void func_0206820c(void);
extern void func_0208ff58(void);
extern void func_02001b44(int);
extern void func_02001b34(int);

UnkStruct_020a9c4c *func_020a9c4c(UnkStruct_020a9c4c *obj);
void func_020a9b7c(void);
void func_020a9b70(void);

void func_020a9c6c(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result != 0) {
        func_020a9c4c((UnkStruct_020a9c4c *) ((void *) result));
    }
}

UnkStruct_020a9c4c *func_020a9c4c(UnkStruct_020a9c4c *obj)
{
    func_020ee660(obj);
    obj->vtbl = (unsigned int) data_020da13c;
    obj->vtbl = (unsigned int) data_020e3e8c;
    return obj;
}

void *func_020a9c2c(void *p)
{
    volatile unsigned int *v = p;
    *v = (unsigned int) data_020e3e8c;
    *v = (unsigned int) data_020da13c;
    func_020ee62c(p);
    return p;
}

void *func_020a9c04(void *arg)
{
    *(unsigned int *) arg = (unsigned int) data_020e3e8c;
    *(unsigned int *) arg = (unsigned int) data_020da13c;
    func_020ee62c(arg);
    func_020edf54(arg);
    return arg;
}

int func_020a9bd8(void)
{
    func_0208ff88();
    func_020a7e30();
    func_02003108();
    func_02011fa4();
    func_02011ebc();
    func_0206829c();
    func_020b8cb8();
    func_020a9b7c();
    return 1;
}

int func_020a9bb8(void)
{
    func_020a9b70();
    func_020b8ca8();
    func_0206826c();
    func_02011eb0();
    func_0208ff78();
    return 1;
}

int func_020a9ba0(void)
{
    func_0208ff68();
    func_0206823c();
    func_020b8c98();
    return 1;
}

int func_020a9b88(void)
{
    func_020b8c88();
    func_0206820c();
    func_0208ff58();
    return 1;
}

void func_020a9b7c(void)
{
    func_02001b44(0x10);
}

void func_020a9b70(void)
{
    func_02001b34(0x10);
}
