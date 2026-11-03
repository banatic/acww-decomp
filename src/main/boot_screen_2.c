/* boot_screen_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b5a78 @ 0x020b5a78, 0x44 bytes, Thumb
 * func_020b5a34 @ 0x020b5a34, 0x44 bytes, Thumb
 * func_020b5a18 @ 0x020b5a18, 0x1c bytes, Thumb
 * func_020b5898 @ 0x020b5898, 0x180 bytes, Thumb
 */

#define gGlobalConst (*(int *) 0x0000088c)

struct UnkStruct_020b5a78 {
    void *p;
    unsigned char pad_04[15];
    unsigned char flags;
};

typedef struct {
    unsigned char pad_00[0x50];
    unsigned char unk_50;
    unsigned char pad_51[0xf];
    unsigned int unk_60;
    unsigned int unk_64;
    unsigned int unk_68;
} UnkStruct_020b5a34;

typedef struct {
    char pad_00[0x60];
    void *unk_60;
    void *unk_64;
    void *unk_68;
} UnkStruct_020b5a18;

struct UnkStruct_020b5898 {
    char pad_00[0x50];
    unsigned char state;
    unsigned char timer;
    char pad_52[0x54 - 0x51 - 1];
    unsigned int tick_lo;
    unsigned int tick_hi;
    unsigned char r0;
    unsigned char r1;
    char pad_5E[0x5f - 0x5d - 1];
    unsigned char sub;
    char pad_60[0x64 - 0x5f - 1];
    int unk_64;
    int unk_68;
};

extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *ptr);
extern int data_020da13c;
extern int data_020e3c94;
extern int data_020e5320;
extern unsigned int data_020dd828;
extern unsigned int data_021fbe94;
extern void func_0200471c(void);
extern unsigned int func_020e9948(unsigned int, unsigned int);
extern void func_020e993c(void *, void *);
extern int func_020a1a40(int, int);
extern unsigned long long OS_GetTick(void);
extern void func_020b5794(void *receiver);
extern void func_02001aac(int);
extern void func_0200467c(void *);
extern void func_020b5724(struct UnkStruct_020b5898 *);
extern void func_020b56a8(struct UnkStruct_020b5898 *);
extern void func_02001b54(int);
extern void func_02001b1c(int);
extern int func_020b5e10(void);
extern unsigned char func_020b6454(int, int);
extern void func_020b5e44(int, int);

void *func_020b5a78(void)
{
    volatile struct UnkStruct_020b5a78 *obj = (volatile struct UnkStruct_020b5a78 *) func_020edf70(0x6c);
    if (obj) {
        func_020ee660((void *) obj);
        obj->p = (void *) &data_020da13c;
        obj->p = (void *) &data_020e3c94;
        obj->flags |= 1;
        obj->flags |= 4;
        obj->p = (void *) &data_020e5320;
    }
    return (void *) obj;
}

int func_020b5a34(UnkStruct_020b5a34 *param)
{
    data_020dd828 = 3;
    func_0200471c();
    param->unk_50 = 0;
    param->unk_60 = data_021fbe94;
    param->unk_64 = func_020e9948(param->unk_60, 0x173fc);
    param->unk_68 = func_020e9948(param->unk_60, 0x173fc);
    return 1;
}

int func_020b5a18(UnkStruct_020b5a18 *obj)
{
    func_020e993c(obj->unk_60, obj->unk_64);
    func_020e993c(obj->unk_60, obj->unk_68);
    return 1;
}

int func_020b5898(struct UnkStruct_020b5898 *this)
{
    int r;

    switch (this->sub) {
        case 0:
            if (this->state == 1) {
                this->sub = 1;
            }
            break;
        case 1:
            r = func_020a1a40(0, this->unk_64);
            if (r != 3) {
                this->r0 = (unsigned char) r;
                this->sub = 2;
            }
            break;
        case 2:
            r = func_020a1a40(1, this->unk_68);
            if (r != 3) {
                this->r1 = (unsigned char) r;
                this->sub = 3;
            }
            break;
    }

    switch (this->state) {
        case 0:
            func_020b5794(this);
            func_02001aac(-16);
            this->state = 1;
            this->timer = 0x10;
            func_0200467c(&gGlobalConst);
            break;
        case 1:
            if (this->timer != 0) {
                this->timer--;
                func_02001aac(-(int) this->timer);
            } else {
                this->state = 2;
                *(unsigned long long *) &this->tick_lo = OS_GetTick();
            }
            break;
        case 2: {
            unsigned long long now = OS_GetTick();
            if (this->sub < 5) {
                if (this->sub < 3) {
                    break;
                }
                func_020b5724(this);
                func_020b56a8(this);
                this->sub = 5;
            }
            {
                unsigned long long saved = *(unsigned long long *) &this->tick_lo;
                if (now - saved < 523656) {
                    break;
                }
            }
            this->state = 3;
            this->timer = 0x10;
            break;
        }
        case 3:
            if (this->timer != 0) {
                this->timer--;
                func_02001aac((int) this->timer - 0x10);
            } else {
                func_02001b54(0);
                func_02001b1c(0);
                this->state = 4;
                func_020b6454(func_020b5e10(), 0x2c);
                func_020b5e44(3, 2);
            }
            break;
    }

    return 1;
}
