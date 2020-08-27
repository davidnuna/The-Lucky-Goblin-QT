#include "validation.h"

void VALIDATOR::ValidateDate(MYDATE DateToValidate)
{
    if (DateToValidate.GetDay() < 1 || DateToValidate.GetDay() > 31)
        throw VALIDATION_ERROR("Invalid day! Must be between 1 and 31!\n\n");

    if (DateToValidate.GetMonth() < 1 || DateToValidate.GetMonth() > 12)
        throw VALIDATION_ERROR("Invalid month!Must be between 1 and 12!\n\n");

    if (DateToValidate.GetYear() < 1 || DateToValidate.GetYear() > 2020)
        throw VALIDATION_ERROR("Invalid year! Must be between 1 and 2020!\n\n");
}