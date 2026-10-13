/* func_02064ef8 @ 0x02064ef8, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Position;

typedef struct {
    int type;
    int unk_04[2];
    int unk_0C;
    unsigned char pad_10[0x24];
    unsigned short dir;
    unsigned char pad_36[2];
    int sub38;
} UnkStruct_02064ef8;

extern void func_02065020(UnkStruct_02064ef8 *);
extern void func_02064fb4(UnkStruct_02064ef8 *);
extern void func_02064f84(UnkStruct_02064ef8 *);
extern int func_020bbf00(int);
extern void func_02065110(UnkStruct_02064ef8 *, Position *);
extern void func_0206515c(Position *, void *);

void func_02064ef8(UnkStruct_02064ef8 *self)
{
    volatile unsigned short buf[2];
    Position local;
    Position copy;

    switch (self->type) {
        case 3:
            func_02065020(self);
            local.x = 0;
            local.y = -0x1000;
            local.z = 0;
            break;
        case 4:
            func_02064fb4(self);
            local.x = 0;
            local.y = -0x1000;
            local.z = 0;
            break;
        case 5:
            func_02064f84(self);
            local.x = 0;
            local.y = -0x1000;
            local.z = 0;
            break;
        default:
            buf[0] = (unsigned short) func_020bbf00(self->unk_0C);
            buf[1] = buf[0];
            self->dir = buf[1];
            local.x = 0;
            local.y = 0;
            local.z = -0x1000;
            break;
    }

    func_02065110(self, &local);
    copy.x = local.x;
    copy.y = local.y;
    copy.z = local.z;
    func_0206515c(&copy, &self->sub38);
}
