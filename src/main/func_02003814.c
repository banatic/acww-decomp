/* func_02003814 @ 0x02003814, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern signed char data_020c7588[];
extern void func_0200396c(void *self, int value);
extern int func_02003938(void *self);
extern void func_0208a0c8(void *ptr);

typedef struct {
    unsigned char pad_00[0x20];
    int value20;
    unsigned int value24;
    unsigned char pad_28[0x32 - 0x28];
    unsigned char flag32;
    unsigned char flag33;
    unsigned char pad_34[0x3c - 0x34];
    int value3c;
} UnkStruct_02003814;

void func_02003814(UnkStruct_02003814 *self)
{
    if (self->flag33 != 0) {
        func_0200396c(self, 0);
    }

    if (self->flag32 != 0) {
        if (func_02003938(self) != 0) {
            unsigned int v = 4;
            self->value24 = v;
            self->value20 = data_020c7588[v];
        } else {
            unsigned int v = 0;
            self->value24 = v;
            self->value20 = data_020c7588[v];
        }
    } else {
        if (func_02003938(self) != 0) {
            if (self->value24 < 4) {
                self->value24 = self->value24 + 1;
                self->value20 = data_020c7588[self->value24];
                if (self->value24 == 4) {
                    func_0200396c(self, 0);
                }
            }
        } else {
            if (self->value24 != 0) {
                if (self->value24 == 4) {
                    func_0200396c(self, 1);
                }
                self->value24 = self->value24 - 1;
                self->value20 = data_020c7588[self->value24];
            }
        }
    }

    if (self->value3c > 0) {
        self->value3c = self->value3c - 1;
    }

    self = (UnkStruct_02003814 *) ((char *) self + 0xc);
    func_0208a0c8(self);
}
