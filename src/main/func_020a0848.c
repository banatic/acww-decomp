/* func_020a0848 @ 0x020a0848, 0x2b0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xef];
    unsigned char localReady[4];
    unsigned char pad_F3[1];
    unsigned char participantReady[4];
} UnkStruct_020a0848;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_020a0848_2;

extern int func_02073fdc(int firstBase);
extern void func_02074078(void);
extern int func_020ec260(void);
extern int func_02075aa4(int firstBase, int secondBase);
extern int func_02073044(void);
extern int func_020ebf70(void);
extern void func_020750fc(void);
extern void func_020750f4(void);
extern void func_0207428c(void);
extern int func_0209ffb0(UnkStruct_020a0848 *s);
extern int func_02075848(void);
// Its own body ignores self, but the ROM caller preserves this input in r0.
extern void func_020a261c(UnkStruct_020a0848 *self);
extern void func_020a25e8(UnkStruct_020a0848 *s);
extern UnkStruct_020a0848_2 *func_020682e0(int firstBase);
extern void func_02116a1c(int firstBase);

int func_020a0848(UnkStruct_020a0848 *self, unsigned char *state, int firstBase, int secondBase, int participantMask,
                  unsigned char postMessage)
{
    unsigned char currentState;
    int allReady;
    int missingMask;
    int lost;
    int i;

    currentState = *state;
    if (currentState == firstBase) {
        if (func_02073fdc(participantMask) != 0) {
            func_02074078();
            return 0x20;
        }
        if (func_020ec260() == 0) {
            if (func_02075aa4(2, participantMask) != 0) {
                *state = firstBase + 1;
            }
        } else {
            if (func_02075aa4(2, 1) != 0) {
                *state = firstBase + 1;
            }
        }
    } else if (currentState == firstBase + 1) {
        if (func_02073fdc(participantMask) != 0) {
            func_02074078();
            return 0x20;
        }
        if ((func_02073044(), func_020ebf70()) != 0) {
            *state = firstBase + 2;
        }
    } else if (currentState == firstBase + 2) {
        if (func_020ec260() == 0) {
            allReady = 1;
            missingMask = 0;
            func_020750fc();
            for (i = 3; i >= 0; i--) {
                if (i != 0) {
                    int bit = 1 << i;
                    if ((participantMask & bit) != 0) {
                        if (self->participantReady[i] == 0) {
                            allReady = 0;
                            missingMask |= bit;
                            missingMask = (unsigned short) missingMask;
                        }
                    }
                }
            }
            lost = func_02073fdc(missingMask);
            func_020750f4();
            if (lost != 0) {
                func_02074078();
                return 0x20;
            }
            if (allReady != 0) {
                func_0207428c();
                func_0209ffb0(self);
                *state = firstBase + 3;
            }
        } else {
            if (func_02073fdc(participantMask) != 0) {
                func_02074078();
                return 0x20;
            }
            if (self->localReady[0] != 0) {
                if (func_02075848() != 0) {
                    *state = firstBase + 3;
                }
            }
        }
    } else if (currentState == firstBase + 3) {
        if (func_020ec260() == 0) {
            *state = firstBase + 4;
        } else {
            if (func_02073fdc(participantMask) != 0) {
                func_02074078();
                return 0x20;
            }
            if ((func_02073044(), func_020ebf70()) != 0) {
                func_0207428c();
                func_0209ffb0(self);
                *state = firstBase + 4;
            }
        }
    } else if (currentState == firstBase + 4) {
        if (postMessage != 0) {
            func_020a261c(self);
        }
        *state = firstBase + 5;
    }

    // The first chain may advance state into the second chain this frame.
    currentState = *state;
    if (currentState == secondBase) {
        if (func_02073fdc(participantMask) != 0) {
            func_02074078();
            return 0x20;
        }
        if (func_020ec260() == 0) {
            if (func_02075aa4(2, participantMask) == 0) {
                goto end;
            }
            *state = secondBase + 1;
            goto end;
        }
        if (func_02075848() == 0) {
            goto end;
        }
        *state = secondBase + 1;
        goto end;
    }
    if (currentState == secondBase + 1) {
        if (func_02073fdc(participantMask) != 0) {
            func_02074078();
            return 0x20;
        }
        if ((func_02073044(), func_020ebf70()) == 0) {
            goto end;
        }
        *state = secondBase + 2;
        goto end;
    }
    if (currentState == secondBase + 2) {
        if (func_020ec260() == 0) {
            allReady = 1;
            missingMask = 0;
            func_020750fc();
            for (i = 3; i >= 0; i--) {
                if (i != 0) {
                    int bit = 1 << i;
                    if ((participantMask & bit) != 0) {
                        if (self->participantReady[i] == 0) {
                            allReady = 0;
                            missingMask |= bit;
                            missingMask = (unsigned short) missingMask;
                        }
                    }
                }
            }
            lost = func_02073fdc(missingMask);
            func_020750f4();
            if (lost != 0) {
                func_02074078();
                return 0x20;
            }
            if (allReady == 0) {
                goto end;
            }
            func_0207428c();
            func_0209ffb0(self);
            *state = secondBase + 3;
            goto end;
        }
        func_0207428c();
        func_0209ffb0(self);
        *state = secondBase + 3;
        goto end;
    }
    if (currentState == secondBase + 3) {
        if (postMessage != 0) {
            func_020a25e8(self);
        }
        *state = secondBase + 4;
        goto end;
    }
    if (currentState == secondBase + 4) {
        if (func_020682e0(0)->unk_04 == 0) {
            func_02116a1c(0);
        }
    }
end:
    return 0x20;
}
