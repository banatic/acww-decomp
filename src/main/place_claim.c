/* place_claim: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02051eb8 @ 0x02051eb8, 0x94 bytes, Thumb
 * func_02051eac @ 0x02051eac, 0xc bytes, Thumb
 * func_02051ea4 @ 0x02051ea4, 0x8 bytes, Thumb
 * func_02051e9c @ 0x02051e9c, 0x8 bytes, Thumb
 * func_02051e38 @ 0x02051e38, 0x64 bytes, Thumb
 * func_02051e30 @ 0x02051e30, 0x8 bytes, Thumb
 * func_02051e28 @ 0x02051e28, 0x8 bytes, Thumb
 * func_02051e20 @ 0x02051e20, 0x8 bytes, Thumb
 * func_02051e18 @ 0x02051e18, 0x8 bytes, Thumb
 * func_02051e0c @ 0x02051e0c, 0xc bytes, Thumb
 * func_02051e04 @ 0x02051e04, 0x8 bytes, Thumb
 * func_02051dfc @ 0x02051dfc, 0x8 bytes, Thumb
 */

typedef struct {
    int unk_00;
    int pad_04;
    int unk_08;
} UnkStruct_02051eb8;

typedef struct {
    int pad_00;
} UnkStruct_02051eb8_2;

extern int data_021c8750;
extern UnkStruct_02051eb8_2 *data_020ccf94;
extern int data_021c87fc;
int func_02073d90(UnkStruct_02051eb8_2 *p);
int func_02073918(UnkStruct_02051eb8_2 *p, int zero);
int func_020b65c4(void);
int func_02053380(int *addr, int zero, int v, UnkStruct_02051eb8 *param);
void func_02073820(UnkStruct_02051eb8_2 *p);
void func_020737f0(UnkStruct_02051eb8_2 *p, char *buf, int len);
void func_02073770(UnkStruct_02051eb8_2 *p, int a, int b);
extern int func_0205340c(void *addr, int param);

void func_02051eb8(UnkStruct_02051eb8 *param)
{
    char buf[3];
    UnkStruct_02051eb8_2 *p;
    int v;

    data_021c8750 = 0;
    p = data_020ccf94;

    if (func_02073d90(p) == 0) {
        goto else_part;
    }
    if (func_02073918(p, 0) == 0) {
        goto then_part;
    }

else_part:
    v = func_020b65c4();
    if (func_02053380(&data_021c87fc, 0, v, param) != 0) {
        data_021c8750 = 1;
    } else {
        data_021c8750 = 2;
    }
    goto end_part;

then_part:
    buf[0] = (char) (param->unk_00 >> 9);
    buf[1] = (char) (param->unk_08 >> 9);
    buf[2] = (char) func_020b65c4();
    p = data_020ccf94;
    func_02073820(p);
    func_020737f0(p, buf, 3);
    func_02073770(p, 30, 0);

end_part:
    return;
}

unsigned int func_02051eac(void)
{
    return (*(unsigned int *) &data_021c8750);
}

void func_02051ea4(void *argument0)
{
    func_02051eb8((UnkStruct_02051eb8 *) ((void *) argument0));
}

unsigned int func_02051e9c(void)
{
    return func_02051eac();
}

void func_02051e38(int param)
{
    void *ptr;
    void *ptr2;

    data_021c8750 = 0;
    ptr = (*(void * *) &data_020ccf94);
    if (func_02073d90((UnkStruct_02051eb8_2 *) ptr) == 0) {
        goto else_branch;
    }
    if (func_02073918((UnkStruct_02051eb8_2 *) ptr, 0) != 0) {
        goto else_branch;
    }
    if (func_02073918((UnkStruct_02051eb8_2 *) ptr, 4) == 0) {
        goto then_branch;
    }
else_branch:
    func_0205340c(&data_021c87fc, param);
    goto end;
then_branch:
    ptr2 = (*(void * *) &data_020ccf94);
    func_02073820((UnkStruct_02051eb8_2 *) ptr2);
    func_02073770((UnkStruct_02051eb8_2 *) ptr2, 0x21, 0);
end:;
}

void func_02051e30(void *argument0)
{
    func_02051eb8((UnkStruct_02051eb8 *) ((void *) argument0));
}

unsigned int func_02051e28(void)
{
    return func_02051eac();
}

void func_02051e20(void *argument0)
{
    func_02051eb8((UnkStruct_02051eb8 *) ((void *) argument0));
}

unsigned int func_02051e18(void)
{
    return func_02051eac();
}

void func_02051e0c(void)
{
    func_02051e38(0);
}

void func_02051e04(void *argument0)
{
    func_02051eb8((UnkStruct_02051eb8 *) ((void *) argument0));
}

unsigned int func_02051dfc(void)
{
    return func_02051eac();
}
