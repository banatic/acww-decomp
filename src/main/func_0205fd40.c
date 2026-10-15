/* func_0205fd40 @ 0x0205fd40, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Vec3;
struct UnkStruct_0205fd40;
struct UnkStruct_0205fd40_2;

extern void *data_020ccf94;
extern int func_02073918(void *, unsigned int);
extern void func_0206026c(struct UnkStruct_0205fd40_2 *, int);
extern int func_02034270(void *, void *, int, int);
extern int func_020912d4(int, struct Vec3 *, int, int);
extern void func_02091278(int, struct Vec3 *, int, int);
extern void func_0203423c(void *);

struct Vec3 {
    int x;
    int y;
    int z;
};

struct UnkStruct_0205fd40 {
    unsigned char pad_00[0x30];
    unsigned int flag;
    unsigned int pad_34;
    unsigned int pad_38;
    int value;
    struct Vec3 vec;
};

struct UnkStruct_0205fd40_2 {
    unsigned int pad_00[2];
    int x;
    int y;
    int z;
    unsigned int pad_14[6];
    unsigned int unk_2C;
    unsigned int pad_30;
    int unk_34;
    unsigned int pad_38;
    unsigned int unk_3C;
};

void func_0205fd40(struct UnkStruct_0205fd40_2 *self)
{
    struct UnkStruct_0205fd40 data, data2;

    if (self->unk_2C == 0) {
        if (func_02073918(data_020ccf94, self->unk_3C) != 0) {
            func_0206026c(self, 4);
            return;
        }

        func_02034270(&data, &self->x, 1, 1);

        if (data.flag != 0) {
            data.vec.x = self->x;
            data.vec.y = self->y;
            data.vec.z = self->z;
            data.vec.y = data.value;

            if (self->unk_34 == -1) {
                self->unk_34 = func_020912d4(0x11, &data.vec, 0, 0);
            } else {
                func_02091278(self->unk_34, &data.vec, 0, 0);
            }
        }

        func_0203423c(&data);
    } else {
        func_02034270(&data2, &self->x, 1, 1);

        if (data2.flag != 0) {
            if (self->y < (data2.value + 1229)) {
                self->y = self->y + 410;
            } else {
                self->y = data2.value + 1229;
            }

            data2.vec.x = self->x;
            data2.vec.y = self->y;
            data2.vec.z = self->z;
            data2.vec.y = data2.value;

            if (self->unk_34 == -1) {
                self->unk_34 = func_020912d4(0x11, &data2.vec, 0, 0);
            } else {
                func_02091278(self->unk_34, &data2.vec, 0, 0);
            }
        }

        func_0203423c(&data2);
    }
}
