/* func_02065450 @ 0x02065450, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int type;
    int pad_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int pad_14;
    int pad_18;
    int pad_1C;
    int pad_20;
    int unk_24;
} UnkStruct_02065450;

extern int data_021c67a4;
void func_020653d0(UnkStruct_02065450 *obj);
void func_02065334(UnkStruct_02065450 *obj);
int func_0203c590(int arg);
void func_020ea78c(void *ptr, int val);
void func_0206515c(int *dst, int *src);
void func_02065520(int *ptr);

void func_02065450(UnkStruct_02065450 *obj)
{
    int local[3];
    int r;

    switch (obj->type) {
        case 0:
            func_020653d0(obj);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            func_02065334(obj);
            break;
    }

    if (data_021c67a4) {
        r = func_0203c590(data_021c67a4);
        func_020ea78c(&obj->unk_08, r);
    }

    local[0] = obj->unk_08;
    local[1] = obj->unk_0C;
    local[2] = obj->unk_10;
    func_0206515c(local, &obj->unk_08);
    func_02065520(&obj->unk_24);
}
