/* villager_move_record_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209a7e8 @ 0x0209a7e8, 0x2c bytes, Thumb
 * func_0209a77c @ 0x0209a77c, 0x6c bytes, Thumb
 * func_0209a778 @ 0x0209a778, 0x2 bytes, Thumb
 * func_0209a774 @ 0x0209a774, 0x4 bytes, Thumb
 */

typedef struct {
    char pad_00[0xc];
    char unk_0C[0x10];
    char arr[5][30];
    unsigned char b2;
    unsigned char b3;
    unsigned char b4;
    unsigned char b5;
    unsigned char b6;
    unsigned char b7;
    unsigned char b8;
    unsigned char b9;
    unsigned char ba;
} UnkStruct_0209a77c;

extern __arm void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern int func_02003750(void *);
extern void func_0209bd7c(void *);
extern int func_0209526c(void *);
extern void func_0209bd5c(UnkStruct_0209a77c *p);
extern void func_02003738(char *p);
extern void func_02095238(char *p);

void *func_0209a7e8(void *arg)
{
    __cxa_vec_cleanup((void *) ((char *) arg + 0x1c), 5, 0x1e, (((void (*)(void *)) func_0209526c)));
    func_02003750((char *) arg + 0xc);
    func_0209bd7c(arg);
    return arg;
}

void func_0209a77c(UnkStruct_0209a77c *p)
{
    int i;
    func_0209bd5c(p);
    func_02003738(p->unk_0C);
    for (i = 0; i < 5; i++) {
        func_02095238(p->arr[i]);
    }
    p->b2 = 1;
    p->b3 = 1;
    p->b4 = 0;
    p->b5 = 0;
    p->b6 = 1;
    p->b7 = 1;
    p->b8 = 0;
    p->b9 = 0;
    p->ba = 5;
}

void *func_0209a778(void *record)
{
    return record;
}

int func_0209a774(int p0)
{
    return ((int) (p0) + (12));
}
