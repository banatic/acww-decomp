/* func_ov050_02262ad8 @ 0x02262ad8, 0x30 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov050_02263408(void *a, int b);
extern void func_0209ab94(int b);

typedef struct {
    char pad_00[0xb4];
    char *arr;
    char pad_B8[0xd0 - 0xb4 - 4];
    int val;
} UnkStruct_02262ad8;

void func_ov050_02262ad8(UnkStruct_02262ad8 *a, int b)
{
    func_ov050_02263408(a, b);
    func_0209ab94(b);
    a->arr[0x73e] = 0;
    a->val = 0xa;
}
