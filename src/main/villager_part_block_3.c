/* villager_part_block_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209b5b8 @ 0x0209b5b8, 0x30 bytes, Thumb
 * func_0209b594 @ 0x0209b594, 0x24 bytes, Thumb
 * func_0209b56c @ 0x0209b56c, 0x28 bytes, Thumb
 */

typedef struct {
    char pad_00[12];
    char arr[2][16];
    char flag;
} UnkStruct0209b56c;

extern void func_0209bd80(void *);
extern int func_02003750(void *);
extern int func_02003780(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_0209bd7c(void *ptr);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_0209bd5c(UnkStruct0209b56c *arg);
extern void func_02003738(char *p);

void *func_0209b5b8(void *param)
{
    func_0209bd80(param);
    __cxa_vec_ctor((void *) ((char *) param + 12), 2, 16, (((void (*)(void *)) func_02003780)),
                   (((void (*)(void *)) func_02003750)));
    return param;
}

unsigned char *func_0209b594(unsigned char *ptr)
{
    __cxa_vec_cleanup((void *) (ptr + 12), 2, 16, (((void (*)(void *)) func_02003750)));
    func_0209bd7c(ptr);
    return ptr;
}

void func_0209b56c(UnkStruct0209b56c *arg)
{
    int i;
    func_0209bd5c(arg);
    for (i = 0; i < 2; i++) {
        func_02003738(arg->arr[i]);
    }
    arg->flag = 0;
}
