#pragma once

/*
 * Through chain models we can add support for different chain formats
 * and future encoding/decoding will be done according to it's format.
 *
 * Chain Model specification will be stored in config file.
 * Also, there's should be a way to map instructions to their chain models.
 * Different instructions even from same ISA can have different chain models.
 * The default chain model for all instructions should be chain model called 'GENERIC'.
 *
 * Also, for future, support for custom chain model descritpion should be added.
 */

/*
 * GENERIC chain format description
 *          8 bit          8 bit       8 bit     8 bit      8 bit    8 bit     8 bit 
 * | chain_model_word | opcode_word | ext_bit | ext_word | cc_bit | cc_word | imv_bit | ....
 *
 *                    8 bit         8 bit          8 bit        16 bit
 * imv_bit = 1: ...| reg_idx_word | reg_idx_word | reg_idx_word | padding |
 *
 *                    8 bit                      32 bit
 * imv_bit = 0: ...| reg_idx_word |               imv                     |
 */

enum class ChainModel
{
  GENERIC = 0,
};
