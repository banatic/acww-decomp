/* villager_talk_replies_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02020744 @ 0x02020744, 0x20 bytes, Thumb
 * func_02020728 @ 0x02020728, 0x1c bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02020744;

typedef struct {
    int a;
    int b;
} UnkStruct_02020728;

typedef struct UnkStruct_02020728_2 UnkStruct_02020728_2;

extern int func_02015590(void *param, int arg);
extern void func_0202dbf0(void *param, UnkStruct_02020744 s);
extern UnkStruct_02020744 data_020d9218;
extern int func_02014ba0(UnkStruct_02020728_2 *p);
extern void func_0202dbdc(UnkStruct_02020728_2 *p, UnkStruct_02020728 v);
extern UnkStruct_02020728 data_020d8f60;

void func_02020744(void *param, void *out)
{
    func_02015590(param, 3);
    func_0202dbf0(param, data_020d9218);
}

void func_02020728(UnkStruct_02020728_2 *p)
{
    func_02014ba0(p);
    func_0202dbdc(p, data_020d8f60);
}
