/* func_02029074 @ 0x02029074, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02137550(void *dst, unsigned int size);
extern unsigned int func_0208150c(unsigned int param);
extern void func_0207cb9c(void *ptr, unsigned int *buf, int num);
extern int data_021e5a2c;

typedef struct UnkStruct_02029074 UnkStruct_02029074;
typedef struct UnkStruct_02029074_2 UnkStruct_02029074_2;

struct UnkStruct_02029074 {
    char pad_00[0x830];
    unsigned int val;
};

struct UnkStruct_02029074_2 {
    char pad_00[0x100];
    UnkStruct_02029074 *ptr;
};

void func_02029074(UnkStruct_02029074_2 *arg0)
{
    unsigned int local;
    func_02137550(&local, 4);
    local = func_0208150c(arg0->ptr->val);
    func_0207cb9c(&data_021e5a2c, &local, 1);
}
