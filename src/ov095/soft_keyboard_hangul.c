/* soft_keyboard_hangul: 4 functions, module ov095
 * mwccarm 1.2/base -O4,s
 * func_ov095_0229b704 @ 0x0229b704, 0x80 bytes, Thumb
 * func_ov095_0229b454 @ 0x0229b454, 0x2b0 bytes, Thumb
 * func_ov095_0229b400 @ 0x0229b400, 0x52 bytes, Thumb
 * func_ov095_0229b3ec @ 0x0229b3ec, 0x12 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned short arr[6];
    int count;
} UnkStruct_0229b400;

typedef struct {
    short arr[6];
    int unk_0C;
} UnkStruct_0229b3ec;

extern int func_ov095_0229b8d8(void *self, int x);
extern int func_ov095_0229b810(void *ctx, int c);
extern unsigned short data_ov095_0229d0f8[];
extern int func_ov095_0229ba0c(void *ctx, int c);
extern int func_ov095_0229ba28(void *ctx, int c);

int func_ov095_0229b454(void *ctx, u16 *src, u16 *dst);
void func_ov095_0229b3ec(UnkStruct_0229b3ec *p);

int func_ov095_0229b704(void *self, void *ptr)
{
    unsigned short buf[6];
    int v;
    int k;

    v = 0;
    do {
        buf[v] = 0;
        v++;
    } while (v < 4);

    if (func_ov095_0229b454(self, (u16 *) ptr, (u16 *) buf) == 0) {
        return 0;
    }

    v = func_ov095_0229b8d8(self, buf[0]);
    v = (unsigned short) (v + func_ov095_0229b8d8(self, buf[1]));
    if (buf[2] != 0) {
        v = (unsigned short) (v + func_ov095_0229b810(self, buf[2]));
    }

    for (k = 0; k < 0x933; k++) {
        if (v == data_ov095_0229d0f8[k]) {
            return v;
        }
    }
    return 0;
}

int func_ov095_0229b454(void *ctx, u16 *src, u16 *dst)
{
    int i;

    i = 0;
    if (func_ov095_0229ba0c(ctx, src[0]) == 0) {
        return 0;
    }
    dst[0] = src[0];
    if (func_ov095_0229ba28(ctx, src[1]) == 0) {
        return 0;
    }
    dst[1] = src[1];
    i = i + 2;
    if (src[i] == 0) {
        return 1;
    }
    if (func_ov095_0229ba28(ctx, src[i]) != 0) {
        if (dst[1] == 0x3157) {
            switch (src[i]) {
                case 0x314f:
                    dst[1] = 0x3158;
                    break;
                case 0x3150:
                    dst[1] = 0x3159;
                    break;
                case 0x3163:
                    dst[1] = 0x315a;
                    break;
                default:
                    return 0;
            }
        } else if (dst[1] == 0x315c) {
            switch (src[i]) {
                case 0x3153:
                    dst[1] = 0x315d;
                    break;
                case 0x3154:
                    dst[1] = 0x315e;
                    break;
                case 0x3163:
                    dst[1] = 0x315f;
                    break;
                default:
                    return 0;
            }
        } else if (dst[1] == 0x3161) {
            if (src[i] == 0x3163) {
                dst[1] = 0x3162;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
        i = i + 1;
    }
    if (src[i] == 0) {
        return 1;
    }
    if (func_ov095_0229ba0c(ctx, src[i]) == 0) {
        return 0;
    }
    if (func_ov095_0229b810(ctx, src[i]) == 0) {
        return 0;
    }
    dst[2] = src[i];
    if (src[i + 1] == 0) {
        return 1;
    }
    if (func_ov095_0229ba0c(ctx, src[i + 1]) == 0) {
        return 0;
    }
    switch (dst[2]) {
        case 0x3131:
            if (src[i + 1] == 0x3145) {
                dst[2] = 0x3133;
            } else {
                return 0;
            }
            break;
        case 0x3134:
            switch (src[i + 1]) {
                case 0x3148:
                    dst[2] = 0x3135;
                    break;
                case 0x314e:
                    dst[2] = 0x3136;
                    break;
                default:
                    return 0;
            }
            break;
        case 0x3139:
            switch (src[i + 1]) {
                case 0x3131:
                    dst[2] = 0x313a;
                    break;
                case 0x3141:
                    dst[2] = 0x313b;
                    break;
                case 0x3142:
                    dst[2] = 0x313c;
                    break;
                case 0x3145:
                    dst[2] = 0x313d;
                    break;
                case 0x314c:
                    dst[2] = 0x313e;
                    break;
                case 0x314d:
                    dst[2] = 0x313f;
                    break;
                case 0x314e:
                    dst[2] = 0x3140;
                    break;
                default:
                    return 0;
            }
            break;
        case 0x3142:
            if (src[i + 1] == 0x3145) {
                dst[2] = 0x3144;
            } else {
                return 0;
            }
            break;
        default:
            return 0;
    }
    if (src[i + 2] == 0) {
        return 1;
    }
    return 0;
}

void func_ov095_0229b400(UnkStruct_0229b400 *s, int val, int mode)
{
    switch (mode) {
        case 0:
            func_ov095_0229b3ec((UnkStruct_0229b3ec *) s);
            s->arr[s->count] = val;
            break;
        case 1:
            s->arr[s->count] = val;
            break;
        case 2: {
            unsigned short last;
            if (s->count > 0) {
                last = s->arr[s->count - 1];
                func_ov095_0229b3ec((UnkStruct_0229b3ec *) s);
            }
            s->arr[0] = last;
            s->arr[1] = val;
            s->count = 2;
            return;
        }
        default:
            break;
    }
    if (s->count < 6) {
        s->count++;
    }
}

void func_ov095_0229b3ec(UnkStruct_0229b3ec *p)
{
    int i;
    i = 0;
    do {
        p->arr[i] = 0;
        i++;
    } while (i < 6);
    p->unk_0C = 0;
}
