#pragma once
#include "../lib/BigUInt.hpp"
#include <mpi.h>

void createType_BigUInt(MPI_Datatype& datatype) {
    struct BigUInt::BigUInt instance;
    MPI_Datatype type[2] = { MPI_UNSIGNED, MPI_UNSIGNED_LONG_LONG };
    int blocklen[2] = { BigUInt::number_of_reserved_digits, 1 };
    MPI_Aint disp[2]={ offsetof(BigUInt::BigUInt, digits), offsetof(BigUInt::BigUInt, number_of_digits) };
    
    MPI_Type_create_struct(2, blocklen, disp, type, &datatype);
    MPI_Type_commit(&datatype);
}