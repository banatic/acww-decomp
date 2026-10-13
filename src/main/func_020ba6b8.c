/* func_020ba6b8 @ 0x020ba6b8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020becbc(void *addr, int value);
extern void func_020be388(void *addr);
extern void func_020bde5c(void *addr);

typedef struct {
    char pad_00[8];
    unsigned char b;
    char pad_09[3];
} UnkStruct_020ba6b8;

extern unsigned char data_021fa678[];
extern char data_021fba00[];
extern char data_021f8b48[];

void func_020ba6b8(void)
{
    UnkStruct_020ba6b8 *p = (UnkStruct_020ba6b8 *) data_021fa678;
    int i = 0;
    unsigned char val = (unsigned char) i;
    do {
        p->b = val;
        p++;
        i++;
    } while (i < 5);
    func_020becbc(data_021fba00, -1);
    func_020be388(data_021f8b48);
    func_020bde5c(data_021f8b48);
}
