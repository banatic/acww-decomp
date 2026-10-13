/* func_02032e80 @ 0x02032e80, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int count;
    char pad_04[0x20];
} UnkStruct_02032e80;
extern void func_020330bc(void *entry, int p2, int p3, int p4, int a, int b);

int func_02032e80(UnkStruct_02032e80 *self, int p2, int p3, int p4, int a, int b)
{
    if (self->count >= 0x10) {
        goto fail;
    }
    func_020330bc((char *) self + 4 + *(volatile unsigned int *) &self->count * 0x24, p2, p3, p4, a, b);
    self->count++;
    return 1;
fail:
    return 0;
}
