# project1.2 design

## Registers

| registers | usage                                       |
| --------- | ------------------------------------------- |
| x0        | (null)                                      |
| ra        | (return)                                    |
| sp        | stack                                       |
| gp        | (skip)                                      |
| tp        | (skip)                                      |
| t0        | iterater{traverse,main}                     |
| t1        | the address of instruction{traverse}        |
| t2        | iterater{print_binary}                      |
| s0        |                                             |
| s1        |                                             |
| a0        | (reserved)                                  |
| a1        | (reserved)                                  |
| a2        | (const)the number of codes                  |
| a3        | (const)the address of the first instruction |
| a4        | (const)the address of comp[]                |
| a5        | (para)16bit instr to be decompressed        |
| a6        | (para)instr to be printed                   |
| a7        |                                             |
| s2        | mask{classify,offset_check_32}              |
| s3        | shifter{classify}                           |
| s4        | mask{decompress}                            |
| s5        | offset{decompress,offset_check_32}          |
| s6        | new offset{offset_check_32}                 |
| s7        | iterater{offset_check_32}                   |
| s8        | temp{offset_check_32}                       |
| s9        |                                             |
| s10       | (const)the address of the last instr        |
| s11       |                                             |
| t3        | the 1th instr half{traverse}                |
| t4        | the 2nd instr half{traverse}                |
| t5        | temp{traverse,main}                         |
| t6        | temp{traverse}                              |

## Stack

| stack      |
| ---------- |
| bottom     |
| comp_arr[] |
| ra         |
| top        |