/* func_0206829c @ 0x0206829c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    char pad_04[0x1e9c - 4];
} UnkStruct_0206829c;

extern void *func_02138e38(int, int, int, void (*)(void *), void (*)(void *));
extern void *func_020684b0(void *object);
extern void *func_02068644(void *object);
extern UnkStruct_0206829c *data_021cda88;

void func_0206829c(void)
{
    int i;
    data_021cda88 = (UnkStruct_0206829c *) func_02138e38(2, 0x1e9c, 8, (((void (*)(void *)) func_02068644)),
                                                         (((void (*)(void *)) func_020684b0)));
    for (i = 0; i < 2; i++) {
        data_021cda88[i].unk_00 = i;
    }
}
