/* soft_keyboard_keys: 8 functions, module ov095
 * mwccarm 1.2/base -O4,s
 * func_ov095_0229c974 @ 0x0229c974, 0xf0 bytes, Thumb
 * func_ov095_0229c930 @ 0x0229c930, 0x44 bytes, Thumb
 * func_ov095_0229c8f0 @ 0x0229c8f0, 0x40 bytes, Thumb
 * func_ov095_0229c8e4 @ 0x0229c8e4, 0xc bytes, Thumb
 * func_ov095_0229c7c8 @ 0x0229c7c8, 0x11c bytes, Thumb
 * func_ov095_0229c750 @ 0x0229c750, 0x76 bytes, Thumb
 * func_ov095_0229c654 @ 0x0229c654, 0xfa bytes, Thumb
 * func_ov095_0229c5fc @ 0x0229c5fc, 0x58 bytes, Thumb
 */

typedef struct UnkStruct_0229c974 {
    int unk_00;
    unsigned int lo : 12;
    unsigned int pal : 4;
    unsigned int hi : 16;
} UnkStruct_0229c974;

typedef struct {
    unsigned char pad_00[22];
    unsigned char mode;
} UnkStruct_0229c8f0;

extern UnkStruct_0229c974 *func_ov095_0229b16c(void *a);
extern void func_ov095_0229cb5c(UnkStruct_0229c8f0 *self, int b, int c);
extern void func_ov095_0229ca64(UnkStruct_0229c8f0 *self, int b, int c);
extern void func_ov095_022999a8(UnkStruct_0229c8f0 *self, int val);
extern int _s32_div_f(int a, int b);
extern int func_ov095_022999b0(unsigned int a, unsigned int b);

int func_ov095_0229c930(unsigned char *p, int cmd, int sub);

void func_ov095_0229c974(void *a, int id, int val)
{
    UnkStruct_0229c974 *p;
    int idx;
    int i;

    if (func_ov095_0229c930((unsigned char *) a, id, val) != 0) {
        return;
    }
    if (id < 0xc9 || id > 0xf6) {
        return;
    }
    p = func_ov095_0229b16c(a);
    idx = -1;
    if (id <= 0xd2) {
        idx = id - 0xc9;
    } else if (id <= 0xdc) {
        idx = id - 0xc9;
    } else if (id == 0xdd) {
        p[0x14].pal = val;
        p[0x15].pal = val;
        return;
    } else if (id <= 0xe6) {
        idx = id - 0xc8;
    } else if (id == 0xe7) {
        for (i = 0x1f; i <= 0x21; i++) {
            p[i].pal = val;
        }
        return;
    } else if (id <= 0xf1) {
        idx = id - 0xc6;
    } else if (id == 0xf4) {
        for (i = 0x2e; i <= 0x31; i++) {
            p[i].pal = val;
        }
        return;
    } else if (id <= 0xf3) {
        idx = id - 0xc6;
    } else if (id <= 0xf6) {
        idx = id - 0xc3;
    }
    if (idx < 0) {
        return;
    }
    p[idx].pal = val;
}

int func_ov095_0229c930(unsigned char *p, int cmd, int sub)
{
    unsigned char val;
    switch (cmd) {
        case 0x109:
        case 0x10a:
            switch (sub) {
                case 0xC:
                    val = 0xC;
                    break;
                case 0xE:
                    val = 0xE;
                    break;
                case 0xD:
                    val = 0xD;
                    break;
            }
            if (cmd == 0x109) {
                p[0x19] = val;
            } else {
                p[0x1A] = val;
            }
            break;
        default:
            break;
    }
    return 0;
}

/* Jump-table switch on p->mode: cases 1/2/4 call 3-arg handlers, 0/3 fall
   through, then a common func_ov095_022999a8(self, 1). */

void func_ov095_0229c8f0(UnkStruct_0229c8f0 *self, int b, int c)
{
    switch (self->mode) {
        case 0:
        case 3:
            break;
        case 1:
            func_ov095_0229cb5c(self, b, c);
            break;
        case 2:
            func_ov095_0229ca64(self, b, c);
            break;
        case 4:
            func_ov095_0229c974((void *) self, b, c);
            break;
    }
    func_ov095_022999a8(self, 1);
}

void func_ov095_0229c8e4(int a, int b)
{
    func_ov095_0229c8f0((UnkStruct_0229c8f0 *) a, b, 13);
}

int func_ov095_0229c7c8(int a, unsigned int b, unsigned int c)
{
    if (c < 0x60) {
        return -1;
    }
    if (c >= 0xb0) {
        return -1;
    }
    if (c < 0x70) {
        if (b < 4) {
            return -1;
        }
        if (b >= 0xf4) {
            return -1;
        }
        return (int) (b - 4) / 20 + 0x3b;
    }
    if (c < 0x80) {
        if (b < 0xc) {
            return -1;
        }
        if (b >= 0xfc) {
            return -1;
        }
        if (b >= 0xd4) {
            return 0x51;
        }
        return (int) (b - 0xc) / 20 + 0x47;
    }
    if (c < 0x90) {
        if (b < 4) {
            return -1;
        }
        if (b < 0x18) {
            return 0x52;
        }
        if (b >= 0xfc) {
            return -1;
        }
        if (b >= 0xcc) {
            return 0x5c;
        }
        return (int) (b - 0x18) / 20 + 0x53;
    }
    if (c < 0xa0) {
        if (b < 4) {
            return -1;
        }
        if (b < 0x20) {
            return 0x5d;
        }
        if (b >= 0xe8) {
            return -1;
        }
        return (int) (b - 0x20) / 20 + 0x5e;
    }
    if (c < 0xb0) {
        if (b < 0x18) {
            return -1;
        }
        if (b >= 0x40 && b < 0xcc) {
            return 0x6b;
        }
        if (b < 0x54) {
            return (int) (b - 0x18) / 20 + 0x68;
        }
        if (b >= 0xf4) {
            return -1;
        }
        return (int) (b - 0xa4) / 20 + 0x6c;
    }
    return -1;
}

int func_ov095_0229c750(int unused, unsigned int y, unsigned int z)
{
    if (z < 0x68) {
        return -1;
    }
    if (z >= 0xa8) {
        return -1;
    }

    if (z >= 0x98) {
        if (y < 0x50) {
            goto fail3;
        }
        if (y >= 0xb0) {
            goto fail3;
        }
        return 0x91;
    fail3:
        return -1;
    }

    if (y < 8) {
        return -1;
    }
    if (y >= 0xf8) {
        return -1;
    }
    if (y < 0xd0) {
        int q = _s32_div_f(y - 8, 0x14);
        return q + (((int) z - 0x68) >> 4) * 10 + 0x70;
    }

    if (z >= 0x78) {
        return 0x90;
    }
    if (y < 0xe4) {
        return 0x8e;
    }
    return 0x8f;
}

int func_ov095_0229c654(int a1, unsigned short a2, unsigned short a3)
{
    if (a3 < 0x60) {
        return -1;
    }
    if (a3 >= 0xb0) {
        return -1;
    }
    if (a3 < 0x70) {
        if (a2 < 4) {
            return -1;
        }
        if (a2 < 0xcc) {
            return _s32_div_f(a2 - 4, 0x14) + 0xc9;
        }
        return -1;
    }
    if (a3 < 0x80) {
        if (a2 < 0xc) {
            return -1;
        }
        if (a2 < 0xd4) {
            return _s32_div_f(a2 - 0xc, 0x14) + 0xd3;
        }
        if (a2 < 0xfc) {
            return 0xdd;
        }
        return -1;
    }
    if (a3 < 0x90) {
        if (a2 < 0x18) {
            return -1;
        }
        if (a2 < 0xcc) {
            return _s32_div_f(a2 - 0x18, 0x14) + 0xde;
        }
        if (a2 < 0xfc) {
            return 0xe7;
        }
        return -1;
    }
    if (a3 < 0xa0) {
        if (a2 < 0x20) {
            return -1;
        }
        if (a2 < 0xe8) {
            return _s32_div_f(a2 - 0x20, 0x14) + 0xe8;
        }
        return -1;
    }
    if (a2 < 0x28) {
        return -1;
    }
    if (a2 < 0x3c) {
        return 0xf2;
    }
    if (a2 < 0x50) {
        return 0xf3;
    }
    if (a2 < 0xa8) {
        return 0xf4;
    }
    if (a2 < 0xbc) {
        return 0xf5;
    }
    if (a2 < 0xd0) {
        return 0xf6;
    }
    return -1;
}

int func_ov095_0229c5fc(unsigned int a, unsigned int b, unsigned int c)
{
    if (func_ov095_022999b0(a, 4) != 0) {
        if (c < 0x50 || c > 0x58) {
            goto fail;
        }
        if (b < 0x30) {
            return 0x109;
        }
        if (b > 0xd0) {
            return 0x10a;
        }
    } else {
        if (c < 0x48 || c > 0x50) {
            goto fail;
        }
        if (b < 0x30) {
            return 0x109;
        }
        if (b > 0xd0) {
            return 0x10a;
        }
    }
fail:
    return -1;
}
