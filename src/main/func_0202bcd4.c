/* func_0202bcd4 @ 0x0202bcd4, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02080a2c(void *ptr);
extern char func_02082264(void);
extern void func_02015dd4(void *a, int b, char *c, void *d, char *e);
extern void func_0202bd40(void *a, int b, void *c);
extern void func_0202bd7c(void *a, int b, unsigned char c);
extern int data_020d9f48;
extern unsigned char data_020c8938[];

typedef struct UnkStruct_0202bcd4 UnkStruct_0202bcd4;
typedef struct UnkStruct_0202bcd4_2 {
    char pad_00[0x100];
    UnkStruct_0202bcd4 *unk_100;
} UnkStruct_0202bcd4_2;
struct UnkStruct_0202bcd4 {
    char pad_00[0x830];
    void *unk_830;
};

void func_0202bcd4(UnkStruct_0202bcd4_2 *self)
{
    void *ptr;
    char buf[2];
    int i;

    ptr = self->unk_100->unk_830;
    if (ptr != 0) {
        func_02080a2c(ptr);
        buf[0] = func_02082264();
        buf[1] = 0;
        func_02015dd4(self, 0, buf, &data_020d9f48, buf + 1);
        func_0202bd40(self, 6, ptr);
    }
    for (i = 0; i < 4; i++) {
        func_0202bd7c(self, i + 7, data_020c8938[i]);
    }
}
