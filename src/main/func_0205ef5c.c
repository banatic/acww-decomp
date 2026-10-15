/* func_0205ef5c @ 0x0205ef5c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0205ef5c {
    char pad_00[0x2c];
    void *ptr;
} UnkStruct_0205ef5c;

typedef struct UnkStruct_0205ef5c_2 {
    char pad_00[4];
    UnkStruct_0205ef5c *inner;
    char pad_08[0x24 - 8];
    void (*callback)(void *p);
    char pad_28[0x92 - 0x28];
    unsigned char unk_92;
} UnkStruct_0205ef5c_2;

extern char data_021ca16c[];
extern int func_0205f130(const char *str, unsigned char c);
extern void func_02054d60(int result, UnkStruct_0205ef5c_2 *p);
extern void func_0205ef28(void *p);

void func_0205ef5c(UnkStruct_0205ef5c_2 *p)
{
    if (p->inner->ptr != 0) {
        func_02054d60(func_0205f130(data_021ca16c, *((unsigned char *) p->inner->ptr)), p);
    }
    p->callback = func_0205ef28;
    p->unk_92 = 2;
}
