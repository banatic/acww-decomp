/* voice: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020f0ccc @ 0x020f0ccc, 0x70 bytes, ARM
 * func_020f0444 @ 0x020f0444, 0x888 bytes, ARM
 * func_020efc74 @ 0x020efc74, 0x7d0 bytes, ARM
 */

typedef struct KbdWork {
    unsigned char pad_00[0x44];
    int mode;
} KbdWork;

extern void OS_Terminate(void);
extern void func_020f1fb4(void *obj, int id);
extern int func_020f0d40(KbdWork *self, unsigned int v);
extern void func_020f1da4(KbdWork *self, int idx, int w, int x);
extern int data_021fd1bc;
extern unsigned char data_021fd1b0;
extern unsigned char data_021fd1ac;
extern unsigned short data_021fd1b4;
extern unsigned short data_021fd1b8;
extern unsigned char data_0213e85c[];
extern unsigned char data_021fd1a8;

int func_020f0ccc(KbdWork *self, unsigned short idx)
{
    switch (idx) {
        case 0:
            idx = 0;
            break;
        default:
            switch (self->mode) {
                case 0:
                case 4:
                    idx = idx + 0xce;
                    break;
                case 1:
                case 3:
                    idx = idx + 0x140;
                    break;
                case 2:
                    idx = idx + 0x1b2;
                    break;
            }
            break;
    }
    return idx;
}

int func_020f0444(int arg0, int code)
{
    int s;
    int initial;
    int medial;

    if (code >= 0xAC00 && code <= 0xD7A3) {
        s = code - 0xAC00;
        medial = (s % 588) / 28;
        initial = s / 588;
        switch (initial) {
            case 0:
                switch (medial) {
                    case 0:
                    case 1:
                    case 2:
                    case 9:
                        code = 0x2e;
                        break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 11:
                    case 15:
                        code = 0x31;
                        break;
                    case 4:
                    case 6:
                    case 8:
                    case 12:
                    case 14:
                        code = 0x32;
                        break;
                    case 13:
                    case 17:
                    case 18:
                        code = 0x30;
                        break;
                    case 16:
                    case 19:
                    case 20:
                        code = 0x2f;
                        break;
                }
                break;
            case 1:
            case 15:
                switch (medial) {
                    case 0:
                    case 1:
                    case 2:
                    case 9:
                        code = 0x06;
                        break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 11:
                    case 15:
                        code = 0x09;
                        break;
                    case 4:
                    case 6:
                    case 8:
                    case 12:
                    case 14:
                        code = 0x0a;
                        break;
                    case 13:
                    case 17:
                    case 18:
                        code = 0x08;
                        break;
                    case 16:
                    case 19:
                    case 20:
                        code = 0x07;
                        break;
                }
                break;
            case 2:
                switch (medial) {
                    case 0:
                    case 1:
                    case 2:
                    case 9:
                        code = 0x15;
                        break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 11:
                    case 15:
                        code = 0x18;
                        break;
                    case 4:
                    case 6:
                    case 8:
                    case 12:
                    case 14:
                        code = 0x19;
                        break;
                    case 13:
                    case 17:
                    case 18:
                        code = 0x17;
                        break;
                    case 16:
                    case 19:
                    case 20:
                        code = 0x16;
                        break;
                }
                break;
            case 3:
                switch (medial) {
                    case 0:
                    case 1:
                    case 2:
                    case 9:
                        code = 0x38;
                        break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 11:
                    case 15:
                        code = 0x39;
                        break;
                    case 4:
                    case 6:
                    case 8:
                    case 12:
                    case 14:
                        code = 0x3a;
                        break;
                    case 13:
                    case 17:
                    case 18:
                        code = 0x35;
                        break;
                    case 16:
                    case 19:
                    case 20:
                        code = 0x34;
                        break;
                }
                break;
            case 4:
            case 14:
            case 16:
                switch (medial) {
                    case 0:
                    case 1:
                    case 2:
                    case 9:
                        code = 0x10;
                        break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 11:
                    case 15:
                        code = 0x13;
                        break;
                    case 4:
                    case 6:
                    case 8:
                    case 12:
                    case 14:
                        code = 0x14;
                        break;
                    case 13:
                    case 17:
                    case 18:
                        code = 0x12;
                        break;
                    case 16:
                    case 19:
                    case 20:
                        code = 0x11;
                        break;
                }
                break;
            case 5:
                switch (medial) {
                    case 0:
                    case 1:
                    case 2:
                    case 9:
                        code = 0x27;
                        break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 11:
                    case 15:
                        code = 0x2a;
                        break;
                    case 4:
                    case 6:
                    case 8:
                    case 12:
                    case 14:
                        code = 0x2b;
                        break;
                    case 13:
                    case 17:
                    case 18:
                        code = 0x29;
                        break;
                    case 16:
                    case 19:
                    case 20:
                        code = 0x28;
                        break;
                }
                break;
            case 6:
                switch (medial) {
                    case 0:
                    case 1:
                    case 2:
                    case 9:
                        code = 0x1f;
                        break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 11:
                    case 15:
                        code = 0x22;
                        break;
                    case 4:
                    case 6:
                    case 8:
                    case 12:
                    case 14:
                        code = 0x23;
                        break;
                    case 13:
                    case 17:
                    case 18:
                        code = 0x21;
                        break;
                    case 16:
                    case 19:
                    case 20:
                        code = 0x20;
                        break;
                }
                break;
            case 7:
                switch (medial) {
                    case 0:
                    case 1:
                    case 2:
                    case 9:
                        code = 0x3b;
                        break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 11:
                    case 15:
                        code = 0x3e;
                        break;
                    case 4:
                    case 6:
                    case 8:
                    case 12:
                    case 14:
                        code = 0x3f;
                        break;
                    case 13:
                    case 17:
                    case 18:
                        code = 0x3d;
                        break;
                    case 16:
                    case 19:
                    case 20:
                        code = 0x3c;
                        break;
                }
                break;
            case 8:
            case 17:
                switch (medial) {
                    case 0:
                    case 1:
                    case 2:
                    case 9:
                        code = 0x40;
                        break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 11:
                    case 15:
                        code = 0x43;
                        break;
                    case 4:
                    case 6:
                    case 8:
                    case 12:
                    case 14:
                        code = 0x44;
                        break;
                    case 13:
                    case 17:
                    case 18:
                        code = 0x42;
                        break;
                    case 16:
                    case 19:
                    case 20:
                        code = 0x41;
                        break;
                }
                break;
            case 9:
            case 10:
                switch (medial) {
                    case 0:
                    case 1:
                    case 2:
                    case 9:
                        code = 0x0b;
                        break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 11:
                    case 15:
                        code = 0x0e;
                        break;
                    case 4:
                    case 6:
                    case 8:
                    case 12:
                    case 14:
                        code = 0x0f;
                        break;
                    case 13:
                    case 17:
                    case 18:
                        code = 0x0d;
                        break;
                    case 16:
                    case 19:
                    case 20:
                        code = 0x0c;
                        break;
                }
                break;
            case 11:
                switch (medial) {
                    case 0:
                    case 1:
                        code = 0x01;
                        break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 11:
                    case 15:
                        code = 0x04;
                        break;
                    case 4:
                    case 6:
                    case 8:
                    case 14:
                        code = 0x05;
                        break;
                    case 13:
                    case 18:
                        code = 0x03;
                        break;
                    case 16:
                    case 19:
                    case 20:
                        code = 0x02;
                        break;
                    case 2:
                        code = 0x24;
                        break;
                    case 17:
                        code = 0x25;
                        break;
                    case 12:
                        code = 0x26;
                        break;
                    case 9:
                        code = 0x2c;
                        break;
                }
                break;
            case 12:
                switch (medial) {
                    case 0:
                    case 1:
                    case 2:
                    case 9:
                        code = 0x33;
                        break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 11:
                    case 15:
                        code = 0x36;
                        break;
                    case 4:
                    case 6:
                    case 8:
                    case 12:
                    case 14:
                        code = 0x37;
                        break;
                    case 13:
                    case 17:
                    case 18:
                        code = 0x35;
                        break;
                    case 16:
                    case 19:
                    case 20:
                        code = 0x34;
                        break;
                }
                break;
            case 13:
                switch (medial) {
                    case 0:
                    case 1:
                    case 2:
                    case 9:
                        code = 0x10;
                        break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 11:
                    case 15:
                        code = 0x13;
                        break;
                    case 4:
                    case 6:
                    case 8:
                    case 12:
                    case 14:
                        code = 0x14;
                        break;
                    case 13:
                    case 17:
                    case 18:
                        code = 0x12;
                        break;
                    case 16:
                    case 19:
                    case 20:
                        code = 0x11;
                        break;
                }
                break;
            case 18:
                switch (medial) {
                    case 0:
                    case 1:
                    case 2:
                    case 9:
                        code = 0x1a;
                        break;
                    case 3:
                    case 5:
                    case 7:
                    case 10:
                    case 11:
                    case 15:
                        code = 0x1d;
                        break;
                    case 4:
                    case 6:
                    case 8:
                    case 12:
                    case 14:
                        code = 0x1e;
                        break;
                    case 13:
                    case 17:
                    case 18:
                        code = 0x1c;
                        break;
                    case 16:
                    case 19:
                    case 20:
                        code = 0x1b;
                        break;
                }
                break;
        }
    } else {
        switch (code) {
            case 0x3147:
                code = 0;
                break;
            default:
                code = 0;
                break;
        }
    }
    return code;
}

void func_020efc74(KbdWork *self, int action, int layout, unsigned short cur, unsigned short prev)
{
    int steps;
    unsigned char y;
    int x;
    int idx;
    unsigned short jamo;

    if (self->mode == 5) {
        OS_Terminate();
    }

    switch (action) {
        case 0:
            if (cur == 0x30FB || prev == 0x30FB) {
                func_020f1fb4(&data_021fd1bc, 0x2c);
            } else {
                x = 0;
                steps = 0;
                y = 0x7f;
                switch (layout) {
                    case 0:
                        steps = 1;
                        switch (data_021fd1b0) {
                            case 0:
                                x = -0x40;
                                y = 0x50;
                                break;
                            case 1:
                                x = 0x80;
                                y = 0x6e;
                                break;
                            case 2:
                                x = 0x40;
                                y = 0x64;
                                break;
                            case 3:
                                x = 0x40;
                                y = 0x69;
                                break;
                        }
                        break;
                    case 1:
                        steps = 1;
                        switch (data_021fd1b0) {
                            case 0:
                            case 8:
                                x = 0xf0;
                                y = 0x7d;
                                break;
                            case 1:
                            case 9:
                                x = 0xb4;
                                y = 0x6e;
                                break;
                            case 2:
                            case 10:
                                x = 0x96;
                                y = 0x5a;
                                break;
                            case 4:
                            case 12:
                                x = 0xbe;
                                y = 0x7d;
                                break;
                            case 5:
                            case 13:
                                x = 0x78;
                                y = 0x6e;
                                break;
                            case 6:
                            case 14:
                                x = 0x5a;
                                y = 0x5a;
                                break;
                            case 3:
                            case 7:
                            case 11:
                            default:
                                x = -0x4d;
                                y = 0x69;
                                break;
                        }
                        break;
                    case 2:
                        steps = 2;
                        if (data_021fd1b0 == 0) {
                            if (data_021fd1ac == 0) {
                                data_021fd1ac = 1;
                            } else {
                                data_021fd1ac = 0;
                            }
                        }
                        if (data_021fd1ac == 0) {
                            x = -(data_021fd1b0 * 0x11);
                        } else {
                            x = 0x4d - data_021fd1b0 * 0x11;
                        }
                        if (data_021fd1ac == 0) {
                            y = (unsigned char) (0x64 - data_021fd1b0 * 3);
                        } else {
                            y = (unsigned char) (0x73 - data_021fd1b0 * 3);
                        }
                        break;
                    case 3:
                        steps = 1;
                        switch (data_021fd1b0) {
                            case 0:
                            case 8:
                                x = 0x5a;
                                y = 0x69;
                                break;
                            case 1:
                            case 9:
                                x = 0x1e;
                                y = 0x5a;
                                break;
                            case 2:
                            case 10:
                                y = 0x46;
                                break;
                            case 4:
                            case 12:
                                x = 0x28;
                                y = 0x69;
                                break;
                            case 5:
                            case 13:
                                x = -0x1e;
                                y = 0x5a;
                                break;
                            case 6:
                            case 14:
                                x = -0x3c;
                                y = 0x46;
                                break;
                            case 3:
                            case 7:
                            case 11:
                            default:
                                x = -0xe3;
                                y = 0x55;
                                break;
                        }
                        break;
                    case 4:
                        steps = 2;
                        switch (data_021fd1b0) {
                            case 0:
                                x = 0x80;
                                y = 0x4b;
                                break;
                            case 1:
                                x = 0x100;
                                y = 0x5f;
                                break;
                            case 2:
                                x = 0x1c0;
                                y = 0x7d;
                                break;
                            case 3:
                                x = 0x140;
                                y = 0x69;
                                break;
                            case 4:
                                x = 0xc0;
                                y = 0x55;
                                break;
                            case 5:
                                x = 0x80;
                                y = 0x4b;
                                break;
                            case 6:
                                x = 0x40;
                                y = 0x41;
                                break;
                            case 7:
                                x = 0x80;
                                y = 0x4b;
                                break;
                            case 8:
                                x = 0x1c0;
                                y = 0x7d;
                                break;
                            case 9:
                                x = 0x140;
                                y = 0x69;
                                break;
                            case 10:
                                x = 0xc0;
                                y = 0x55;
                                break;
                            case 11:
                                x = 0x40;
                                y = 0x41;
                                break;
                            case 12:
                                x = 0x80;
                                y = 0x4b;
                                break;
                            case 13:
                                x = 0x140;
                                y = 0x69;
                                break;
                            case 14:
                                x = 0x80;
                                y = 0x4b;
                                break;
                            case 15:
                                x = 0x140;
                                y = 0x69;
                                break;
                        }
                        break;
                }

                switch (prev) {
                    case 0xFF01:
                        x = 0x100;
                        y = 0x7f;
                        break;
                    case 0x0A:
                    case 0xFF0C:
                        x = -0x40;
                        y = 0x5a;
                        break;
                    case 0xFF1F:
                        x = 0x180;
                        y = 0x6e;
                        break;
                }

                idx = 0;
                switch (cur) {
                    default:
                        idx = func_020f0ccc(self, (unsigned short) func_020f0444((int) self, cur));
                        break;
                    case 0x20:
                    case 0x0A:
                    case 0xFF0C:
                        if (prev >= 0xAC00 && prev <= 0xD7A3) {
                            idx = func_020f0ccc(self, (unsigned short) func_020f0444((int) self, prev));
                        } else if (data_021fd1b4 >= 0xAC00 && data_021fd1b4 <= 0xD7A3) {
                            idx = func_020f0ccc(self, (unsigned short) func_020f0444((int) self, data_021fd1b4));
                        }
                        break;
                    case 0xFF1F:
                        x = 0x180;
                        y = 0x6e;
                        if (data_021fd1b4 >= 0xAC00 && data_021fd1b4 <= 0xD7A3) {
                            idx = func_020f0ccc(self, (unsigned short) func_020f0444((int) self, data_021fd1b4));
                        } else {
                            jamo = func_020f0444((int) self, data_021fd1b8);
                            idx = func_020f0ccc(self, data_0213e85c[jamo]);
                        }
                        break;
                    case 0xFF01:
                        x = 0x100;
                        y = 0x7f;
                        if (data_021fd1b4 >= 0xAC00 && data_021fd1b4 <= 0xD7A3) {
                            idx = func_020f0ccc(self, (unsigned short) func_020f0444((int) self, data_021fd1b4));
                        } else {
                            jamo = func_020f0444((int) self, data_021fd1b8);
                            idx = func_020f0ccc(self, data_0213e85c[jamo]);
                        }
                        break;
                    case 0x30FC:
                    case 0xFF5E:
                        if (data_021fd1b4 >= 0xAC00 && data_021fd1b4 <= 0xD7A3) {
                            idx = func_020f0ccc(self, (unsigned short) func_020f0444((int) self, data_021fd1b4));
                        } else {
                            jamo = func_020f0444((int) self, data_021fd1b8);
                            idx = func_020f0ccc(self, data_0213e85c[jamo]);
                        }
                        break;
                }

                func_020f1da4(self, idx, func_020f0d40(self, y), x - 0x40);

                data_021fd1b0 = data_021fd1b0 + 1;
                if (data_021fd1b0 > 0xf) {
                    data_021fd1b0 = 0;
                }
                if (cur == 0x30FB || cur == 0xFF1F || cur == 0xFF01 || cur == 0x0A || prev == 0x30FB || prev == 0xFF1F ||
                    prev == 0xFF01 || prev == 0x0A) {
                    data_021fd1b0 = 0;
                }
                if (cur == 0x20 || prev == 0x20) {
                    if (data_021fd1a8 == steps) {
                        data_021fd1a8 = 0;
                        data_021fd1b0 = 0;
                    } else {
                        data_021fd1a8 = data_021fd1a8 + 1;
                    }
                }
            }
            if (cur != 0x30FC && cur != 0xFF5E) {
                data_021fd1b8 = cur;
            }
            if (prev != 0x30FC && prev != 0xFF5E) {
                data_021fd1b4 = prev;
            }
            break;
        case 1:
            func_020f1fb4(&data_021fd1bc, 0x2c);
            break;
        case 2:
            break;
    }
}
