/* collision_triangle_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202ff00 @ 0x0202ff00, 0x14 bytes, Thumb
 * func_0202feec @ 0x0202feec, 0x14 bytes, Thumb
 * func_0202fee0 @ 0x0202fee0, 0xc bytes, Thumb
 * func_0202fed4 @ 0x0202fed4, 0xc bytes, Thumb
 * func_0202feb4 @ 0x0202feb4, 0x20 bytes, Thumb
 */

typedef struct {
    char *unk_00;
    char pad_04[0x24];
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
} UnkStruct_0202ff00;

struct UnkStruct_0202feec {
    unsigned char *unk_00;
    char pad_04[0x24];
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
};

typedef struct {
    void *unk_00;
} Object;

extern unsigned char data_020da18c[];
extern int func_0202fc18(void *a, int b, int c, int d, int e);

void func_0202ff00(UnkStruct_0202ff00 *arg0)
{
    arg0->unk_00 = ((char *) data_020da18c);
    arg0->unk_28 = 0;
    arg0->unk_2C = 0;
    arg0->unk_30 = 0;
    arg0->unk_34 = 0;
}

void func_0202feec(struct UnkStruct_0202feec *param)
{
    param->unk_00 = data_020da18c;
    param->unk_28 = 0;
    param->unk_2C = 0;
    param->unk_30 = 0;
    param->unk_34 = 0;
}

void func_0202fee0(void **out)
{
    *out = ((char *) data_020da18c);
}

void func_0202fed4(char **ptr)
{
    *ptr = ((char *) data_020da18c);
}

Object *func_0202feb4(Object *obj, int b, int c, int d, int e)
{
    obj->unk_00 = ((char *) data_020da18c);
    func_0202fc18(obj, b, c, d, e);
    return obj;
}
