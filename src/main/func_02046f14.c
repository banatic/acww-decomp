/* func_02046f14 @ 0x02046f14, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int count;
} Param1;

typedef struct {
    unsigned char data[0x90];
} UnkStruct_02046f14;

extern UnkStruct_02046f14 data_021c7a08[];
extern void func_0209def4(void *ptr);
extern void *func_02047114(void *ptr);
extern void func_02048cb8(void *a, void *b, int c, int d, void *e, void (*f)(void), int g);

extern unsigned char data_021c779c[];

extern void func_02048e34(void);

void func_02046f14(void *param0, Param1 *param1)
{
    int i, j;
    unsigned char used;
    int local0 = 0;
    int limit;

    limit = param1->count - 2;

    for (i = 0; i < limit; i++) {
        used = *((unsigned char *) &data_021c7a08[i] + 0x88);
        j = 2 - used;
        while (j > 0) {
            func_02048cb8(param0, param1, i + 1, 4, func_02047114(param0), (void (*)(void))(unsigned int) func_02048e34,
                          local0);
            j--;
        }
    }
    func_0209def4((void *) data_021c779c);
}
