/* func_02020728 @ 0x02020728, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} UnkStruct_02020728;
typedef struct UnkStruct_02020728_2 UnkStruct_02020728_2;
extern void func_02014ba0(UnkStruct_02020728_2 *p);
extern void func_0202dbdc(UnkStruct_02020728_2 *p, UnkStruct_02020728 v);
extern UnkStruct_02020728 data_020d8f60;
void func_02020728(UnkStruct_02020728_2 *p)
{
    func_02014ba0(p);
    func_0202dbdc(p, data_020d8f60);
}
