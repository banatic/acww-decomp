/* func_0208f748 @ 0x0208f748, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned long long OS_GetTick(void);
extern void func_02001ba4(int);
extern void func_0208f858(void *);

typedef struct {
    unsigned char pad_00[0x28];
    int counter;
    int state;
    unsigned long long threshold;
    unsigned char flag;
} UnkStruct_0208f748;

void func_0208f748(UnkStruct_0208f748 *self)
{
    unsigned long long t = OS_GetTick();
    if (t < self->threshold) {
        goto skip_switch;
    }
    if (self->state == 0) {
        t += 0x1991b;
        self->threshold = t;
        self->flag = 1;
        self->state = 1;
    } else if (self->state == 1) {
        t += 0x1991b;
        self->threshold = t;
        self->flag = 0;
        self->state = 2;
    } else if (self->state == 2) {
        t += 0x1991b;
        self->threshold = t;
        self->flag = 1;
        self->state = 3;
    } else if (self->state == 3) {
        t += 0x4cb51;
        self->threshold = t;
        self->flag = 0;
        self->state = 0;
    }
skip_switch:
    if (self->counter > 0) {
        self->counter--;
        if (self->counter <= 0) {
            func_02001ba4(4);
            func_0208f858(self);
        }
    }
}
