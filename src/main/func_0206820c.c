/* func_0206820c @ 0x0206820c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x1E9C];
} UnkStruct_0206820c;
extern UnkStruct_0206820c *data_021cda88;
extern void func_0206812c(UnkStruct_0206820c *ptr);

void func_0206820c(void)
{
    int i;
    if (data_021cda88 == 0) {
        return;
    }
    i = 0;
    do {
        func_0206812c(data_021cda88 + i);
        i++;
    } while (i < 2);
}
