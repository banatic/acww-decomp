/* spawner_11: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02084d08 @ 0x02084d08, 0x2c bytes, Thumb
 * func_02084cd0 @ 0x02084cd0, 0x38 bytes, Thumb
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02084cd0;

extern unsigned char data_020e1ca8[];
extern void func_02084dc8(unsigned char *data, void *p0, void *p2, unsigned int p1, void *p3);
extern int func_02084af0(void);
extern int func_02073dd4(void *ptr, int val);
extern UnkStruct_02084cd0 *data_020ccf94;

int func_02084d08(void *p0, unsigned int p1, void *p2, void *p3)
{
    if (data_020e1ca8[0xF] < p1) {
        func_02084dc8(data_020e1ca8, p0, p2, p1, p3);
        return 1;
    }
    return 0;
}

int func_02084cd0(int a, int b, int c)
{
    if (func_02084af0() == 0) {
        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
            return func_02084d08((void *) a, 1, (void *) b, (void *) c);
        }
    }
    return 0;
}
