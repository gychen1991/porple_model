constant_struct,global_check, texture1D_32, texture2D_32, sur2D_struct, split
texture1D/2D_32: regard 32 as a sector, query for whole warp
split: decide 2D or 1D format for each array without considering the latency. After that, then use branch and bound algorithm  to decide which view to be used for each reference(consider latency and bandwidth).
split_bb: strictly brand and bound
