/* func_020f0444 @ 0x020f0444, 0x888 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

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
