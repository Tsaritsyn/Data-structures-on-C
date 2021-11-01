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

    if (is_decimal_nan(decimal)) {
        printf("Nan");
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
    add_to_long_num(new_nom, temp);
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
    sub_from_long_num(new_nom, temp);
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


void print_decimal_as_float(const Decimal *decimal, size_t max_precision, int consider_period) {
    if (decimal == NULL) {
        printf("NULL");
        return;
    }

    if (is_decimal_inf(decimal)) {
        printf("%cInf", (decimal->nom->sign == MINUS) ? '-' : '+');
        return;
    }

    if (is_decimal_nan(decimal)) {
        printf("Nan");
        return;
    }

    if (is_decimal_zero(decimal)) {
        printf("0.");
        return;
    }

//    if the denominator is 1, then it is in fact an integer number equal to its nominator
    if (is_long_one(decimal->denom)) {
        print_long_num(decimal->nom);
        printf(".");
        return;
    }

    Pair* div_mod = NULL;
    if (decimal->nom->sign == PLUS)
        div_mod = divmod_long_num(decimal->nom, decimal->denom);
    else {
        LongNum *nom_abs = copy_long_num(decimal->nom);
        nom_abs->sign = PLUS;
        div_mod = divmod_long_num(nom_abs, decimal->denom);
        delete_long_num(nom_abs);
    }

    LongNum *before_dot = div_mod->first;
    if (decimal->nom->sign == MINUS) printf("-");
    print_long_num(before_dot);
    printf(".");

//    to represent the fractional part we have to do essentially the same thing as for long number division
//    although, now we will always take zero as the next nominator digit

    string* after_dot = new_empty_string(10);

    LongNum* cur_mod = copy_long_num(div_mod->second);
    int is_periodic = 0;
    string* one_digit_literal = new_empty_string(BASE_LENGTH + 1);
    one_digit_literal->length = BASE_LENGTH;
    while (1) {
        long_shift_left(cur_mod, 1);
        cur_mod->digits->elements[0] = 0;

        int relation = compare_long_num(cur_mod, decimal->denom);
        unsigned int mult = 0;
//        if the window is less than denom, set 0 to the current digit's div_result and continue extracting nom's digits
        if (relation < 0) {}
//        if at some point we get a zero division remainder, than the fraction can be represented in decimal notation
//        precisely
        else if (relation == 0) break;
//        otherwise, determine the maximum multiplier that being multiplied with the denom gives value less than the
//        window, but being increased by 1 gives value greater than the window
//        effectively, here we reassign the window to itself modulo denom
        else {
            unsigned int left = 0, right = BASE - 1;
            mult = right;
            LongNum* multiplied_denom = NULL;
//            we determine the multiplier via the binary search
            while (1) {
                delete_long_num(multiplied_denom);
                multiplied_denom = mul_long_num_and_positive_int(decimal->denom, mult);
                multiplied_denom->sign = PLUS;
                int temp_relation = compare_long_num(multiplied_denom, cur_mod);

                if (temp_relation == 0) break;
                else if (temp_relation < 0) {
                    if (right - left == 1) break;
                    else left = mult;
                }
                else right = mult;
                mult = (left + right) / 2;
            }

//            this multiplier will be the current digit of the div_result
//            append_to_array(after_dot, mult);
            multiplied_denom->sign = PLUS;
            sub_from_long_num(cur_mod, multiplied_denom);
            delete_long_num(multiplied_denom);
        }

        sprintf(one_digit_literal->c_string, "%0*u", BASE_LENGTH, mult);
        string_concat_to(after_dot, one_digit_literal);
        if (after_dot->length > max_precision) break;

        if (consider_period) {
//        search if this digit has already appeared, which will mean that the fraction is periodic
            array_u_long *pos = find_substrings(after_dot, one_digit_literal);
            size_t num_found = pos->length;
            delete_array(pos);
            if (num_found > 1) {
                is_periodic = 1;
                break;
            }
        }
    }

//    remove trailing zeros
    while (after_dot->c_string[after_dot->length - 1] == '0')
        after_dot->c_string[--after_dot->length] = '\0';
    print_string(after_dot);
    if (is_periodic) printf("...");

    delete_long_num(cur_mod);
    delete_string(one_digit_literal);
    delete_string(after_dot);
    delete_pair(div_mod, (void (*)(void *)) &delete_long_num, (void (*)(void *)) &delete_long_num);
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

    int resulting_sign = decimal->nom->sign * decimal->denom->sign;
    decimal->nom->sign = PLUS;
    decimal->denom->sign = PLUS;

    LongNum *gcd = gcd_long_num(decimal->nom, decimal->denom);
    if (!is_long_one(gcd)) {
        reset_long_num(&decimal->nom, div_long_num(decimal->nom, gcd));
        reset_long_num(&decimal->denom, div_long_num(decimal->denom, gcd));
    }
    delete_long_num(gcd);

    decimal->nom->sign = (resulting_sign == MINUS) ? MINUS : PLUS;

//    print_decimal(decimal);
//    printf("\n");
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
