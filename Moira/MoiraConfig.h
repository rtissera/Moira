// -----------------------------------------------------------------------------
// This file is part of Moira - A Motorola 68k emulator
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Published under the terms of the MIT License
// -----------------------------------------------------------------------------

#pragma once

/* Set to true to enable precise timing mode (68000 and 68010 only).
 *
 * When disabled, Moira calls the 'sync' function at the end of each instruction,
 * passing the number of elapsed cycles as an argument. In precise timing mode,
 * 'sync' is called before each memory access, allowing the client to emulate
 * the surrounding hardware up to the point where the memory access occurs.
 *
 * Precise timing mode is available only for 68000 and 68010 emulation. For
 * other supported models, this setting has no effect.
 *
 * Enable to improve accuracy, disable it to enhance performance.
 */
#define MOIRA_PRECISE_TIMING false

/* Set to true to implement the CPU interface as virtual functions.
 *
 * To interact with the environment (e.g., for reading data from memory),
 * the CPU calls an appropriate function that must be implemented by the client.
 * When this option is enabled, all API functions are declared virtual, following
 * the standard object-oriented programming (OOP) paradigm. However, virtual
 * functions introduce a performance penalty. Setting this option to false allows
 * the client API to be statically linked, improving performance.
 *
 * Enable to adhere to the standard OOP paradigm, disable to gain speed.
 */
#define MOIRA_VIRTUAL_API true

/* Set to true to enable address error checking.
 *
 * The 68000 and 68010 trigger an address error violation if a word or longword
 * is accessed at an odd memory address.
 *
 * Enable to improve accuracy, disable to gain speed.
 */
#define MOIRA_EMULATE_ADDRESS_ERROR false

/* Set to true to emulate function code pins FC0 - FC2.
 *
 * Whenever memory is accessed, the function code pins enable external hardware
 * to inspect the access type. If used, these pins are usually connected to an
 * external memory management unit (MMU).
 *
 * Enable to improve accuracy, disable to gain speed.
 */
#define MOIRA_EMULATE_FC true

/* Set to true to enable the disassembler.
 *
 * The disassembler requires a jump table which consumes about 1MB of memory.
 *
 * Disable to save space.
 */
#define MOIRA_ENABLE_DASM true

/* Set to true to build the InstrInfo lookup table.
 *
 * The instruction info table stores information about the instruction
 * (Instr I), the addressing mode (Mode M), and the size attribute (Size S) for
 * all 65536 opcode words. The table is meant to provide data for, e.g.,
 * external debuggers. It is not needed by Moira itself and therefore disabled
 * by default.
 *
 * Disable to save space.
 */
#define MOIRA_BUILD_INSTR_INFO_TABLE true

/* Set to true to compile only the 68000 instruction handlers.
 *
 * The handler templates are instantiated for three cores (68000, 68010,
 * 68020+), and the 68010 and 68020 cores make up about two thirds of the
 * code. With this option, the jump table is always built for the 68000,
 * whatever model is selected. Meant for 68000-only machines.
 *
 * Enable to save space.
 */
#define MOIRA_68000_ONLY false

/* Set to false to leave out the 68010 instruction handlers.
 *
 * The 68010 core is about a third of the handler code. A host that never
 * selects a 68010 model (for example, one that runs 68000 and 68020 CPUs)
 * does not need it. With this option off, a 68010 model gets the 68000
 * jump table.
 *
 * Disable to save space.
 */
#define MOIRA_WITH_68010 true

/* Enables Musashi compatibility mode.
 *
 * When set to true, Moira runs in a special mode designed for compatibility
 * with the Musashi emulator. This mode is primarily used by the test runner
 * application to compare Moira's behavior against Musashi.
 *
 * Set to false for improved accuracy.
 */
#define MOIRA_MIMIC_MUSASHI true

/* The following macro appears at the beginning of each instruction handler.
 * Moira will call 'willExecute(...)' for all listed instructions.
 */
#define MOIRA_WILL_EXECUTE    I == Instr::STOP || I == Instr::TAS || I == Instr::BKPT

/* The following macro appear at the end of each instruction handler.
 * Moira will call 'didExecute(...)' for all listed instructions.
 */
#define MOIRA_DID_EXECUTE     I == Instr::RESET

/* Controls assertion checking.
 *
 * Comment out to enable assertions (recommended for debugging).
 * Uncomment to disable assertions (recommended for release builds).
 */
// #define NDEBUG
#include <cassert>
