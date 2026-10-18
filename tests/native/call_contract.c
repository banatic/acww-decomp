/* Exercise the production trace writer, loader, typed comparator and call-in path. */
#include "../../runtime/native_run.c"

const NativeFunction native_functions[1], clean_functions[1];
const uint32_t native_function_count = 0, clean_function_count = 0;
const NativeBody native_bodies[1], clean_bodies[1];
const uint32_t native_body_count = 0, clean_body_count = 0;
const NativePrivate native_private[1];
const uint32_t native_private_count = 0;
const char *const native_module_names[1] = {"main"};
const uint32_t native_module_count = 1;

#define CHECK(x) do { if (!(x)) { fprintf(stderr, "Failed line %d: %s\n", __LINE__, #x); exit(2); } } while (0)

int main(int argc, char **argv)
{
    CHECK(argc == 3 && memory_init() == 0);
    const char *test = argv[1], *path = argv[2];
    if (strncmp(test, "policy-", 7) == 0) {
        strcpy(modules[0].name, "itcm");
        strcpy(modules[1].name, "main");
        strcpy(modules[2].name, "ov000");
        module_count = 3;
        if (strcmp(test, "policy-file") == 0) {
            CHECK(load_policy(path) == 0);
            CHECK(contract_at(0x01ffd44c)->argument_contract == 0x107);
            CHECK(contract_at(0x0202dbf0)->argument_contract == 0x103);
            CHECK(contract_at(0x02034e28)->argument_contract == 0x103);
            CHECK(contract_at(0x0207fc7c)->argument_contract == 0x103);
            unsigned contracts = 0;
            for (int i = 0; i < fn_count; i++) contracts += fns[i].argument_contract != 0;
            CHECK(contracts == 4);
            puts("Actual generated policy has all four audited contracts");
            return 0;
        }
        FILE *file = fopen(path, "w");
        CHECK(file != NULL);
        int words = strcmp(test, "policy-word-count") == 0 ? 6 : 7;
        unsigned contract = 0x107;
        if (strcmp(test, "policy-zero-words") == 0) contract = 0x100;
        if (strcmp(test, "policy-pointer-mask") == 0) contract = 0x8007;
        if (strcmp(test, "policy-too-many") == 0) contract = 0x111;
        fprintf(file, "01ffd44c %s c0 R func_01ffd44c 4 %d -1 -1 -1",
                strcmp(test, "policy-overlay") == 0 ? "ov000" : "itcm", words);
        if (strcmp(test, "policy-legacy") != 0) fprintf(file, " %x", contract);
        if (strcmp(test, "policy-invalid-number") == 0) fputs(" broken", file);
        fputc('\n', file);
        if (strcmp(test, "policy-duplicate") == 0) fputs("01ffd44c main c0 R duplicate 4 7 -1 -1 -1 0\n", file);
        fclose(file);
        int valid = strcmp(test, "policy-valid") == 0 || strcmp(test, "policy-legacy") == 0;
        CHECK(load_policy(path) == (valid ? 0 : -1));
        if (valid) CHECK(fn_count == 1 && fns[0].argument_contract ==
                          (strcmp(test, "policy-legacy") == 0 ? 0u : 0x107u));
        puts("Policy contract checked");
        return 0;
    }
    ArmCpu state;
    arm_init(&state);
    cpu = &state;
    NativeFunction metadata[4] = {{.info = 0x40}, {.info = 0x20}, {.info = 0x20}, {.info = 0x20}};
    Fn targets[4] = {
        {.address = 0x01ffd44c, .size = 0xc0, .status = 'R', .native = &metadata[0],
         .name = "func_01ffd44c", .params = 4, .arg_words = 7, .argument_contract = 0x107},
        {.address = 0x0202dbf1, .size = 0x14, .status = 'R', .native = &metadata[1],
         .name = "func_0202dbf0", .params = 2, .arg_words = 3, .argument_contract = 0x103},
        {.address = 0x02034e29, .size = 0x50, .status = 'R', .native = &metadata[2],
         .name = "func_02034e28", .params = 2, .arg_words = 3, .argument_contract = 0x103},
        {.address = 0x0207fc7d, .size = 0x4c, .status = 'R', .native = &metadata[3],
         .name = "func_0207fc7c", .params = 2, .arg_words = 3, .argument_contract = 0x103},
    };
    fns = targets;
    fn_count = 4;
    modules[0].resident = resident_ready = 1;
    entry_bits = calloc((ENTRY_END - ENTRY_BASE) / 16, 1);
    CHECK(entry_bits != NULL);
    for (int i = 0; i < fn_count; i++) {
        uint32_t bit = ((targets[i].address & ~1u) - ENTRY_BASE) >> 1;
        entry_bits[bit >> 3] |= (uint8_t) (1u << (bit & 7));
        CHECK(loaded_at(targets[i].address) == &targets[i]);
    }
    Fn *target = &targets[0];
    if (strncmp(test, "setter-", 7) == 0 || strcmp(test, "record-unexpected") == 0) target = &targets[1];
    if (strncmp(test, "array-", 6) == 0) target = &targets[2];
    if (strncmp(test, "return-", 7) == 0) target = &targets[3];
    if (strcmp(test, "record-padding") == 0) {
        target->arg_words = 6;
        target->argument_contract = 0x106;
    }
    if (strstr(test, "maximum") != NULL) {
        target->arg_words = ARG_WORDS;
        target->argument_contract = 0x100 | ARG_WORDS;
    }
    uint32_t address = target->address & ~1u;
    cpu->r[0] = 0x02200000;
    cpu->r[1] = 0x02012341;
    cpu->r[2] = 0;
    cpu->r[3] = 0x02012381;
    cpu->r[13] = 0x023f0000;
    cpu->steps = 100;
    uint32_t *stack = (uint32_t *) (uintptr_t) cpu->r[13];
    stack[0] = 0;
    stack[1] = 0x020123c1;
    stack[2] = 0;
    for (unsigned i = 3; i < STACK_WORDS; i++) stack[i] = 0x80000000u + i;
    uint32_t kind = strncmp(test, "call-in", 7) == 0 ? CROSS_CALL : CROSS_CALL_OUT;
    uint32_t original_hash = argument_hash(target);
    record_out = fopen(path, "wb");
    CHECK(record_out != NULL);
    write_record(0, kind, address, 100, kind == CROSS_CALL ? original_hash : cpu->r[13]);
    write_record(STREAM_IRQ, CROSS_CALL, 0x0202dbf0, 101, argument_hash(&targets[1]));
    write_record(0x02200080, CROSS_CALL, address, 102, original_hash);
    CHECK(fclose(record_out) == 0);
    record_out = NULL;
    unsigned extra_count = contract_words(target) > 4 ? (contract_words(target) - 4 + 2) / 3 : 0;
    CHECK(record_count == 3 + 2 * extra_count);

    if (strncmp(test, "record-", 7) == 0) {
        uint32_t raw[80];
        FILE *file = fopen(path, "rb");
        CHECK(file != NULL);
        size_t words = fread(raw, 4, 80, file);
        fclose(file);
        if (strcmp(test, "record-missing") == 0) {
            memmove(raw + 10, raw + 20, (words - 20) * 4); words -= 10;
        } else if (strcmp(test, "record-duplicate") == 0 || strcmp(test, "record-unexpected") == 0) {
            memmove(raw + 20, raw + 10, (words - 10) * 4); words += 10;
            if (!extra_count) raw[11] = CROSS_ARGUMENTS;
        } else if (strcmp(test, "record-stream") == 0) raw[10] = STREAM_IRQ;
        else if (strcmp(test, "record-parent") == 0) raw[13] = 4;
        else if (strcmp(test, "record-kind") == 0) raw[14] = CROSS_RETURN;
        else if (strcmp(test, "record-function") == 0) raw[12] = 0x02034e28;
        else if (strcmp(test, "record-offset") == 0) raw[15] = 7;
        else if (strcmp(test, "record-count") == 0) raw[16] = 2;
        else if (strcmp(test, "record-padding") == 0) raw[19] = 1;
        else if (strcmp(test, "record-reorder") == 0) {
            uint32_t swap[10]; memcpy(swap, raw + 10, 40);
            memcpy(raw + 10, raw + 20, 40); memcpy(raw + 20, swap, 40);
        } else CHECK(strcmp(test, "record-truncated") == 0);
        file = fopen(path, "wb");
        CHECK(file != NULL);
        CHECK(fwrite(raw, 1, words * 4 - (strcmp(test, "record-truncated") == 0), file) > 0);
        fclose(file);
        memset(streams, 0, sizeof(streams)); stream_count = 0;
        CHECK(load_replay(path) == -1);
        puts("Rejected malformed argument attachment");
        return 0;
    }
    memset(streams, 0, sizeof(streams)); stream_count = 0;
    CHECK(load_replay(path) == 0);
    CHECK(stream_count == 3 && stream_for(0)->next == 1);
    CHECK(stream_for(STREAM_IRQ)->next == 2 + extra_count);
    CHECK(stream_for(0x02200080)->next == 3 + extra_count);
    CHECK(records[0].next == 0); /* Neither extra words nor IRQ records enter this chain. */

    if (strcmp(test, "unavailable-owner") == 0) {
        modules[0].resident = 0;
        check_arguments(&records[0], address);
        CHECK(0);
    }
    if (strcmp(test, "detached-parent") == 0) {
        Record detached = records[0];
        check_arguments(&detached, address);
        CHECK(0);
    }

    if (strcmp(test, "negative") == 0) cpu->r[2] = 0xfffffff0u;
    else if (strcmp(test, "negative-high") == 0) cpu->r[2] = 0xfffe0000u;
    else if (strcmp(test, "high") == 0 || strcmp(test, "call-in-high") == 0) cpu->r[2] = 0x80000000u;
    else if (strcmp(test, "host-target") == 0) cpu->r[1] = 0x00401234u;
    else if (strcmp(test, "stack-b") == 0 || strcmp(test, "call-in-stack") == 0) stack[0] = 0xfffffff0u;
    else if (strcmp(test, "stack-target") == 0) stack[1] ^= 0x10;
    else if (strcmp(test, "stack-adjustment") == 0) stack[2] = 0x80000000u;
    else if (strcmp(test, "maximum-stack-tail") == 0) stack[STACK_WORDS - 1] ^= 1;
    else if (strcmp(test, "array-tail") == 0 || strcmp(test, "setter-tail") == 0 || strcmp(test, "return-category") == 0) cpu->r[2] = 16;
    else if (strcmp(test, "return-unused") == 0) cpu->r[1] ^= 1;
    else if (strcmp(test, "object-null") == 0) cpu->r[0] = 0;
    else if (strcmp(test, "object-different-ds") == 0) cpu->r[0] += 4;
    else if (strcmp(test, "object-inaccessible") == 0) cpu->r[0] = 0xdead0000u;
    else if (strcmp(test, "object-host") == 0) cpu->r[0] = (uint32_t) (uintptr_t) &metadata;
    else CHECK(strcmp(test, "valid") == 0 || strcmp(test, "call-in-valid") == 0 ||
               strcmp(test, "maximum") == 0 || strcmp(test, "call-in-maximum") == 0);
    if (strstr(test, "stack") || strstr(test, "tail")) CHECK(argument_hash(target) != original_hash);
    if (kind == CROSS_CALL) {
        replaying = 1;
        crossing(kind, address, argument_hash(target), 0);
        CHECK(stream_for(0)->next == 0 && stream_for(0)->seen == 1);
        CHECK(replay_events == 1 + extra_count);
    } else {
        check_arguments(&records[0], address);
    }
    puts("Audited arguments agree");
    return 0;
}
