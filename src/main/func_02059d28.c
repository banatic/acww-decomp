/* func_02059d28 @ 0x02059d28, 0xe8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cec0(const void *table, int mask);
extern int func_020808ec(unsigned int object);

extern unsigned char data_021e5a2c[];

int func_02059d28(void *param)
{
    int forwarded_value;

    volatile unsigned short id_store;
    unsigned short full;
    unsigned short raw;
    int ret = 3;

    id_store = 0xfff1;
    id_store = (unsigned short) (*(unsigned int *) ((unsigned char *) param + 8));

    full = id_store;
    raw = id_store;

    switch ((raw & 0xf000) >> 12) {
        case 0xe: {
            int idx = ((forwarded_value = (int) func_0207cec0((const void *) data_021e5a2c, raw & 0x0fff)),
                       func_020808ec((unsigned int) forwarded_value));
            switch (idx) {
                case 0:
                case 5:
                case 6:
                case 10:
                case 12:
                case 15:
                case 16:
                case 21:
                case 25:
                case 31:
                case 32:
                    ret = 4;
                    break;
                case 1:
                case 2:
                case 4:
                case 7:
                case 9:
                case 13:
                case 14:
                case 17:
                case 19:
                case 20:
                case 22:
                case 23:
                case 26:
                case 27:
                case 29:
                    ret = 5;
                    break;
            }
        } break;
        case 0xd:
            switch (full) {
                case 0xd00c:
                    ret = 0;
                    break;
                case 0xd013:
                    ret = 1;
                    break;
                case 0xd012:
                case 0xd025:
                    ret = 2;
                    break;
            }
            break;
    }
    return ret;
}