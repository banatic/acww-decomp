/* func_020b5898 @ 0x020b5898, 0x180 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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

extern int func_020a1a40(int, int);
extern unsigned long long OS_GetTick(void);
extern void func_020b5794(void);
extern void func_02001aac(int);
#define gGlobalConst (*(int *) 0x0000088c)
extern void RtcSendPxiCommand(void *);
extern void func_020b5724(struct UnkStruct_020b5898 *);
extern void func_020b56a8(struct UnkStruct_020b5898 *);
extern void func_02001b54(int);
extern void func_02001b1c(int);
extern int func_020b5e10(void);
extern unsigned char func_020b6454(int, int);
extern void func_020b5e44(int, int);

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
            asm { add r0, this, #0 }
            func_020b5794();
            func_02001aac(-16);
            this->state = 1;
            this->timer = 0x10;
            RtcSendPxiCommand(&gGlobalConst);
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
