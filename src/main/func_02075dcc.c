/* func_02075dcc @ 0x02075dcc, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02075dcc {
    char pad_00[0x68];
    void *unk_68;
};

extern struct UnkStruct_02075dcc *data_020ccf94;

unsigned char func_02096284(void *ptr);
int func_0209847c(void *);
int func_02075ff8(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

int func_02075dcc(unsigned int a, unsigned int b)
{
    return func_02075ff8(a, func_0209847c((void *) func_02096284(data_020ccf94->unk_68)), 0x249c, 4, b);
}
