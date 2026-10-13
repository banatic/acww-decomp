/* func_02041bb8 @ 0x02041bb8, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02038a44(void);
extern void func_02041b90(void);

struct FuncTableEntry {
    void (*func)(void);
    char pad[12];
};

extern struct FuncTableEntry data_020ca520[];
extern struct FuncTableEntry data_020ca518[];

struct GlobalVars {
    unsigned char state;
    unsigned char index;
    char pad[6];
    unsigned int unk_08;
};

extern struct GlobalVars data_021c75b8;

void func_02041bb8(void)
{
    unsigned char index;
    unsigned char state;

    if (func_02038a44() != 0) {
        return;
    }

    index = data_021c75b8.index;
    state = data_021c75b8.state;

    if (state == 2 || state == 0) {
        return;
    }

    if (data_020ca520[index].func != 0) {
        data_020ca520[index].func();
    }

    if (data_021c75b8.state == 1) {
        if (data_021c75b8.unk_08 != 0) {
            return;
        }
        data_021c75b8.state = 2;
        if (data_020ca518[index].func != 0) {
            data_020ca518[index].func();
        }
        return;
    } else if (data_021c75b8.state == 3) {
        if (data_021c75b8.unk_08 != 0) {
            return;
        }
        data_021c75b8.state = 0;
        if (data_020ca518[index].func != 0) {
            data_020ca518[index].func();
        }
        func_02041b90();
        return;
    } else {
        return;
    }
}
