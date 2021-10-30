//
// Created by Mikhail Tsaritsyn on 30.10.2021.
//

#include "data_structures/decimal.h"


static void normalize_decimal(Decimal *decimal);


static int compare_decimal_absolutes(const Decimal* decimal1, const Decimal*  decimal2);


Decimal* new_decimal(LongNum* nom, LongNum* denom) {
    if (nom == NULL || denom == NULL) return NULL;

    if (is_long_zero(denom)) {
        printf("Cannot create a decimal with zero denominator. Use new_decimal_inf() instead.");
        return NULL;
    }

    Decimal *decimal = malloc(sizeof(Decimal));

    decimal->nom = nom;
    decimal->denom = denom;

    normalize_decimal(decimal);
    return decimal;
}


Decimal* new_decimal_from_copies(const LongNum *nom, const LongNum *denom) {
    if (nom == NULL || denom == NULL) return NULL;

    if (is_long_zero(denom)) {
        printf("Cannot create a decimal with zero denominator. Use new_decimal_inf() instead.");
        return NULL;
    }

    Decimal *decimal = malloc(sizeof(Decimal));

    decimal->nom = copy_long_num(nom);
    decimal->denom = (is_long_zero(nom)) ? new_long_num(1) : copy_long_num(denom);

    normalize_decimal(decimal);
    return decimal;
}


Decimal* new_decimal_from_strings(const char* nom_literal, const char* denom_literal) {
    if (nom_literal == NULL || denom_literal == NULL) return NULL;
    return new_decimal(new_long_num_from_string(nom_literal), new_long_num_from_string(denom_literal));
}


Decimal* copy_decimal(const Decimal *decimal) {
    Decimal *copy = malloc(sizeof(Decimal));
    copy->nom = copy_long_num(decimal->nom);
    copy->denom = copy_long_num(decimal->denom);
    return copy;
}


void delete_decimal(Decimal* decimal) {
    if (decimal == NULL) return;

    delete_long_num(decimal->nom);
    delete_long_num(decimal->denom);
    free(decimal);
}


void print_decimal(const Decimal* decimal) {
    if (decimal == NULL) {
        printf("NULL");
        return;
    }

    if (is_decimal_inf(decimal)) {
        printf("%cInf", (decimal->nom->sign == MINUS) ? '-' : '+');
        return;
    }

    printf("Decimal(");
    print_long_num(decimal->nom);
    printf(", ");
    print_long_num(decimal->denom);
    printf(")");
}


Decimal* new_decimal_inf(int sign) {
    LongNum *nom = (sign < 0) ? new_long_num(-1) : new_long_num(1);
    Decimal *decimal = malloc(sizeof(Decimal));
    decimal->nom = nom;
    decimal->denom = new_long_zero();
    return decimal;
}


Decimal* new_decimal_zero(void) {
    return new_decimal(new_long_zero(), new_long_num(1));
}


Decimal* new_decimal_nan(void) {
    return new_decimal(new_long_zero(), new_long_zero());
}


int is_decimal_inf(const Decimal *decimal) {
    if (decimal == NULL) return 0;
    return is_long_zero(decimal->denom);
}


int is_decimal_zero(const Decimal *decimal) {
    if (decimal == NULL) return 0;
    return is_long_zero(decimal->nom);
}


int is_decimal_nan(const Decimal *decimal) {
    return is_long_zero(decimal->nom) && is_long_zero(decimal->denom);
}


int compare_decimal(const Decimal *decimal1, const Decimal *decimal2) {
    if (decimal1 == NULL && decimal2 == NULL) {
        printf("Comparison of two NULL decimals.\n");
        return 0;
    }
    else if (decimal1 == NULL && decimal2 != NULL) return -1;
    else if (decimal1 != NULL && decimal2 == NULL) return 1;

//    NaN is considered to be equal to anything
    if (is_decimal_nan(decimal1) || is_decimal_nan(decimal2)) {
        printf("Warning: comparison with Nan.\n");
        return 0;
    }

    if (is_decimal_inf(decimal1)) return decimal1->nom->sign;
    if (is_decimal_inf(decimal2)) return -decimal2->nom->sign;

    if (is_decimal_zero(decimal1)) return -decimal2->nom->sign;
    if (is_decimal_zero(decimal2)) return decimal1->nom->sign;

    if (decimal1->nom->sign == decimal2->nom->sign) {
        return decimal1->nom->sign * compare_decimal_absolutes(decimal1, decimal2);
    }
    else return decimal1->nom->sign;
}


Decimal* add_decimal(const Decimal *decimal1, const Decimal *decimal2) {
    if (decimal1 == NULL || decimal2 == NULL) return NULL;

    if (is_decimal_nan(decimal1) || is_decimal_nan(decimal2)) {
        printf("Warning: addition with NaN\n");
        return new_decimal_nan();
    }

    if (is_decimal_zero(decimal1)) return copy_decimal(decimal2);
    if (is_decimal_zero(decimal2)) return copy_decimal(decimal1);

    //    addition of two infinities of the same signs gives the infinity of the same sign,
//    and of different signs gives the Nan
    if (is_decimal_inf(decimal1) && is_decimal_inf(decimal2))
        return (decimal1->nom->sign == decimal2->nom->sign) ? new_decimal_inf(decimal1->nom->sign) : new_decimal_nan();
    else if (is_decimal_inf(decimal1)) return new_decimal_inf(decimal1->nom->sign);
    else if (is_decimal_inf(decimal2)) return new_decimal_inf(decimal2->nom->sign);

    if (compare_decimal_absolutes(decimal1, decimal2) == 0 && decimal1->nom->sign == -decimal2->nom->sign)
        return new_decimal_zero();

    Pair *gcd_lcm = gcd_lcm_long_num(decimal1->denom, decimal2->denom);
//    new denominator is the LCM of the two denominators
    LongNum *new_denom = gcd_lcm->second;
    LongNum *mult1 = div_long_num(decimal1->denom, gcd_lcm->first);
    LongNum *mult2 = div_long_num(decimal2->denom, gcd_lcm->first);
//    we cannot delete the pair itself, because its second element will be used in the result;
    delete_long_num(gcd_lcm->first);
    free(gcd_lcm);

    LongNum *new_nom = mul_long_num(decimal1->nom, mult2);
    delete_long_num(mult2);
    LongNum *temp = mul_long_num(decimal2->nom, mult1);
    delete_long_num(mult1);
    add_to_long_num(&new_nom, temp);
    delete_long_num(temp);

    return new_decimal(new_nom, new_denom);
}


Decimal* sub_decimal(const Decimal *decimal1, const Decimal *decimal2) {
    if (decimal1 == NULL || decimal2 == NULL) return NULL;

    if (is_decimal_nan(decimal1) || is_decimal_nan(decimal2)) {
        printf("Warning: subtraction with NaN\n");
        return new_decimal_nan();
    }

    if (is_decimal_zero(decimal1)) {
        Decimal *result = copy_decimal(decimal2);
        result->nom->sign = -decimal2->nom->sign;
        return result;
    }
    if (is_decimal_zero(decimal2)) return copy_decimal(decimal1);

//    subtraction of two infinities of different signs gives the infinity of the same sign as the first one,
//    and of the same signs gives the Nan
    if (is_decimal_inf(decimal1) && is_decimal_inf(decimal2))
        return (decimal1->nom->sign == -decimal2->nom->sign) ? new_decimal_inf(decimal1->nom->sign) : new_decimal_nan();
    else if (is_decimal_inf(decimal1)) return new_decimal_inf(decimal1->nom->sign);
    else if (is_decimal_inf(decimal2)) return new_decimal_inf(decimal2->nom->sign);

    if (compare_decimal_absolutes(decimal1, decimal2) == 0 && decimal1->nom->sign == decimal2->nom->sign)
        return new_decimal_zero();

    Pair *gcd_lcm = gcd_lcm_long_num(decimal1->denom, decimal2->denom);
//    new denominator is the LCM of the two denominators
    LongNum *new_denom = gcd_lcm->second;
    LongNum *mult1 = div_long_num(decimal1->denom, gcd_lcm->first);
    LongNum *mult2 = div_long_num(decimal2->denom, gcd_lcm->first);
//    we cannot delete the pair itself, because its second element will be used in the result;
    delete_long_num(gcd_lcm->first);
    free(gcd_lcm);

    LongNum *new_nom = mul_long_num(decimal1->nom, mult2);
    delete_long_num(mult2);
    LongNum *temp = mul_long_num(decimal2->nom, mult1);
    delete_long_num(mult1);
    sub_from_long_num(&new_nom, temp);
    delete_long_num(temp);

    return new_decimal(new_nom, new_denom);
}


Decimal* mul_decimal(const Decimal *decimal1, const Decimal *decimal2) {
    if (decimal1 == NULL || decimal2 == NULL) return NULL;

    if (is_decimal_nan(decimal1) || is_decimal_nan(decimal2)) {
        printf("Warning: multiplication with NaN\n");
        return new_decimal_nan();
    }

    if (is_decimal_zero(decimal1))
        return (is_decimal_inf(decimal2)) ? new_decimal_nan() : new_decimal_zero();
    if (is_decimal_zero(decimal2))
        return (is_decimal_inf(decimal1)) ? new_decimal_nan() : new_decimal_zero();

    int resulting_sign = decimal1->nom->sign * decimal2->nom->sign;

    if (is_decimal_inf(decimal1) || is_decimal_inf(decimal2)) return new_decimal_inf(resulting_sign);

    return new_decimal(
            mul_long_num(decimal1->nom, decimal2->nom),
            mul_long_num(decimal1->denom, decimal2->denom)
    );
}


Decimal* div_decimal(const Decimal *nom, const Decimal *denom) {
    Decimal *reverted_denom = new_decimal(denom->denom, denom->nom);
    Decimal *result = mul_decimal(nom, reverted_denom);
    free(reverted_denom);
    return result;
}


//*********************************************************//
// Internal helper functions that are not part of the API. //
//*********************************************************//


static void normalize_decimal(Decimal *decimal) {
    if (decimal == NULL || is_decimal_inf(decimal) || is_decimal_nan(decimal)) return;

    if (is_long_zero(decimal->nom)) {
        reset_long_num(&decimal->denom, new_long_num(1));
        return;
    }

    LongNum *gcd = gcd_long_num(decimal->nom, decimal->denom);
    if (!is_long_one(gcd)) {
        reset_long_num(&decimal->nom, div_long_num(decimal->nom, gcd));
        reset_long_num(&decimal->denom, div_long_num(decimal->denom, gcd));
    }
    delete_long_num(gcd);

    if (decimal->nom->sign * decimal->denom->sign == MINUS) {
        decimal->nom->sign = MINUS;
        decimal->denom->sign = PLUS;
    }
    else {
        decimal->nom->sign = PLUS;
        decimal->denom->sign = PLUS;
    }
}


static int compare_decimal_absolutes(const Decimal* decimal1, const Decimal*  decimal2) {
    LongNum *gcd = gcd_long_num(decimal1->denom, decimal2->denom);

    LongNum *ratio1 = div_long_num(decimal1->denom, gcd);
    LongNum *ratio2 = div_long_num(decimal2->denom, gcd);

    LongNum *multiplied_nom1 = mul_long_num(decimal1->nom, ratio1);
    multiplied_nom1->sign = PLUS;
    LongNum *multiplied_nom2 = mul_long_num(decimal2->nom, ratio2);
    multiplied_nom2->sign = PLUS;

    int relation = compare_long_num(multiplied_nom1, multiplied_nom2);

    delete_long_num(gcd);
    delete_long_num(ratio1);
    delete_long_num(ratio2);
    delete_long_num(multiplied_nom1);
    delete_long_num(multiplied_nom2);
    return relation;
}
