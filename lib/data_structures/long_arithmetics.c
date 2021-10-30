//
// Created by Mikhail Tsaritsyn on 27.10.2021.
//

#include "data_structures/long_arithmetics.h"


/**
 * Puts the given value to the eldest digits of the long number. If it exceeds the BASE, it will take as many digits as
 * needed.
 */
static void append_value_to_long_int(LongNum* lnum, long long value);


static LongNum* new_empty_long_num(size_t size);


static void remove_leading_zeros(LongNum* lnum);


/**
 * Compares the absolute values of the given long numbers with no respect to their signs.
 */
static int compare_long_absolutes(const LongNum *lnum1, const LongNum *lnum2);


/**
 * Computes the sum of two given numbers and the given overflow value. If this sum exceeds BASE, the modulo BASE is
 * taken and the value of the overflow is written back to the overflow variable.
 *
 * Both a and b are assumed to not exceed the BASE.
 *
 * @return (a + b + overflow) % BASE
 */
static int add_with_overflow(unsigned int a, unsigned int b, int* overflow);


/**
 * Subtracts the given numbers and the overflow value. If the result is negative, then the BASE is added to it and the
 * overflow becomes equal to -1. Otherwise the overflow becomes 0;
 *
 * Both a and b are assumed to not exceed the BASE.
 *
 * @return (a - b - overflow) % BASE
 */
static unsigned int sub_with_overflow(unsigned int a, unsigned int b, int* overflow);


/**
 * Sums the absolute values of the given long numbers and writes the result into the first one.
 */
static void add_long_int_absolutes(LongNum** lnum1, const LongNum* lnum2);


/**
 * Computes the difference between absolute values of two long numbers and writes the result into the first one.
 */
static void sub_long_int_absolutes(LongNum** lnum1, const LongNum* lnum2);


/**
 * Multiplicates the given numbers and adds the overflow value. If the result is more than BASE, then the module of it with
 * BASE is returned and the result divided by BASE is written into the overflow.
 *
 * Both a and b are assumed to not exceed the BASE.
 *
 * @return (a * b + overflow) % BASE
 */
static int mul_with_overflow(unsigned int a, unsigned int b, unsigned long* overflow);


/**
 * Computes the (nom / denom) and (nom % denom) for the case when nom > denom. Both of them are considered positive, no
 * matter what their signs really are.
 */
static Pair* div_mod_long_absolutes(const LongNum* nom, const LongNum* denom);


LongNum* new_long_zero() {
    LongNum* lnum = new_empty_long_num(1);
    append_to_array(lnum->digits, 0);
    lnum->sign = ZERO;
    return lnum;
}


LongNum* new_long_num(long long value) {
    LongNum* lnum = new_empty_long_num(NUM_DIGITS_IN_LONG_LONG);
    if (value < 0) {
        lnum->sign = MINUS;
        value = -value;
    }
    else
        lnum->sign = PLUS;

    append_value_to_long_int(lnum, value);
    return lnum;
}


LongNum* new_long_num_from_string(const char* literal) {
    if (!is_int_literal(literal)) return NULL;

    int sign = PLUS;
//    if the literal starts with a sign, we will not include this symbol in the processing
//    also determine the sign of the number
    if (*literal == '-') {
        literal++;
        sign = MINUS;
    }
    else if (*literal == '+') literal++;

//    remove leading zeros
    while (*literal == '0') literal++;
    if (*literal == '\0') return new_long_zero();

    size_t len = strlen(literal);

//    this little string will contain only one digit and will slide through the given one
    char *digit_literal = malloc(BASE_LENGTH + 1);

    char *cur_digit_begin = literal + len;

//    the BASE-ish digits are written in the backward order, while decimal digits are in the right order
//    to handle it, we go from the end of the string, processing next BASE_LENGTH digits and stepping BASE_DIGITS back
//    to the beginning of the string
    LongNum* lnum = new_empty_long_num(len / BASE_LENGTH + 1);
    while (cur_digit_begin > literal) {
        strncpy(digit_literal, MAX(cur_digit_begin - BASE_LENGTH, literal), BASE_LENGTH);
        digit_literal[MIN(BASE_LENGTH, cur_digit_begin - literal)] = '\0';
        append_to_array(lnum->digits, atoi(digit_literal));
        cur_digit_begin -= BASE_LENGTH;
    }
    lnum->sign = sign;

    free(digit_literal);
    return lnum;
}


void delete_long_num(LongNum* lnum) {
    if (lnum == NULL) return;

    delete_array(lnum->digits);
    free(lnum);
}


void reset_long_num(LongNum **dst, LongNum *src) {
    if (dst == NULL) {
        printf("No long number provided for reset\n");
        return;
    }

    if (src == NULL) {
        printf("Trying to reset a long number with NULL\n");
        return;
    }

    delete_long_num(*dst);
    *dst = src;
}


LongNum* copy_long_num(const LongNum* lnum) {
    if (lnum == NULL) return NULL;

    LongNum* copy = new_empty_long_num(lnum->digits->length);
    size_t i;
    for (i = 0; i < lnum->digits->length; i++)
        copy->digits->elements[i] = lnum->digits->elements[i];
    copy->digits->length = lnum->digits->length;
    copy->sign = lnum->sign;
    return copy;
}


void print_long_num(const LongNum* lnum) {
    if (lnum == NULL) {
        printf("NULL\n");
        return;
    }

    if (lnum->sign == MINUS) printf("-");
    else if (lnum->sign == ZERO) printf("0x");
    printf("%d", lnum->digits->elements[lnum->digits->length - 1]);

    size_t i;
//    the second condition will catch overflow when subtract from unsigned 0
    for (i = lnum->digits->length - 2; i >= 0 && i < lnum->digits->length; i--)
        printf("_%0*d", BASE_LENGTH, lnum->digits->elements[i]);
}


LongNum* add_long_num(const LongNum* lnum1, const LongNum* lnum2) {
    if (lnum1 == NULL || lnum2 == NULL) return NULL;

    if (is_long_zero(lnum1)) return copy_long_num(lnum2);

//    the only reason to do this is not to repeat the code for add_to_long_num()
    LongNum* result = copy_long_num(lnum1);
    add_to_long_num(&result, lnum2);
    return result;
}


LongNum* sub_long_num(const LongNum* lnum1, const LongNum* lnum2) {
    if (lnum1 == NULL || lnum2 == NULL) return NULL;

    if (is_long_zero(lnum1)) {
        LongNum* result = copy_long_num(lnum2);
        result->sign *= -1;
        return result;
    }

//    the only reason to do this is not to repeat the code for sub_from_long_num()
    LongNum* result = copy_long_num(lnum1);
    sub_from_long_num(&result, lnum2);
    return result;
}


LongNum* mul_long_num_and_positive_int(const LongNum* lnum, unsigned int digit) {
    if (lnum == NULL) return NULL;

    if (is_long_zero(lnum) || digit == 0) return new_long_zero();

    LongNum* result = new_empty_long_num(lnum->digits->length);
    result->sign = lnum->sign;

    size_t i;
    unsigned long overflow = 0;
    for (i = 0; i < lnum->digits->length; i++)
        append_to_array(result->digits, mul_with_overflow(lnum->digits->elements[i], digit, &overflow));

    append_value_to_long_int(result, overflow);
    return result;
}


LongNum* mul_long_num(const LongNum* lnum1, const LongNum* lnum2) {
    if (lnum1 == NULL || lnum2 == NULL) return NULL;

    if (is_long_zero(lnum1) || is_long_zero(lnum2)) return new_long_zero();

    LongNum* result;

    if (is_long_one(lnum1)) {
        result = copy_long_num(lnum2);
        result->sign = lnum1->sign * lnum2->sign;
        return result;
    }

    if (is_long_one(lnum2)) {
        result = copy_long_num(lnum1);
        result->sign = lnum1->sign * lnum2->sign;
        return result;
    }

    const LongNum* longest = (lnum1->digits->length > lnum2->digits->length) ? lnum1 : lnum2;
    const LongNum* shortest = (lnum1->digits->length > lnum2->digits->length) ? lnum2 : lnum1;

//    if one of the numbers consisit of only one digit, the multiplication can be simplified
    if (shortest->digits->length == 1) {
        result = mul_long_num_and_positive_int(longest, shortest->digits->elements[0]);
        result->sign *= shortest->sign;
        return result;
    }

    result = new_long_zero();

//    here we go over all the digits of the shortest number
//    we multiply the longest number with the current digit of the shortest
//    then we shift this intermediate result to the left and add it to the overall result
    size_t i;
    LongNum* temp;
    for (i = 0; i < shortest->digits->length; i++) {
        temp = mul_long_num_and_positive_int(longest, shortest->digits->elements[i]);
        long_shift_left(&temp, i);
        add_to_long_num(&result, temp);
        delete_long_num(temp);
    }

    result->sign = lnum1->sign * lnum2->sign;
    return result;
}


LongNum* div_long_num(const LongNum* nom, const LongNum* denom) {
    if (nom == NULL || denom == NULL) return NULL;

    if (is_long_zero(denom)) {
        printf("Error: zero division in long number integer division!\n");
        return NULL;
    }

//    zero divided by anything is still zero
    if (is_long_zero(nom)) return new_long_zero();

    LongNum* result = NULL;
//    anything divided by 1 is the same and by -1 just changes the sign
    if (is_long_one(denom)) {
        result = copy_long_num(nom);
        result->sign = nom->sign * denom->sign;
        return result;
    }

    int relation = compare_long_absolutes(nom, denom);
//    anything divided by something greater in absolute value is 0 (or -1 if they have different signs)
    if (relation < 0)
        return (nom->sign == denom->sign) ? new_long_zero() : new_long_num(-1);
//    and the division of numbers with equal absolute values is 1 or -1
    else if (relation == 0)
        return (nom->sign == denom->sign) ? new_long_num(1) : new_long_num(-1);

    Pair* div_mod = div_mod_long_absolutes(nom, denom);
    result = div_mod->first;
    delete_long_num(div_mod->second);
    free(div_mod);

    if (nom->sign != denom->sign) {
        result->sign = MINUS;
        sub_positive_int_from_long_num(&result, 1);
    }
    else result->sign = PLUS;
    return result;
}


LongNum* mod_long_num(const LongNum* nom, const LongNum* denom) {
    if (nom == NULL || denom == NULL) return NULL;

    if (is_long_zero(denom)) {
        printf("Error: zero division in long number modulo!\n");
        return NULL;
    }

    if (is_long_zero(nom) || is_long_one(denom)) return new_long_zero();

    int relation = compare_long_absolutes(nom, denom);
    if (relation == 0) return new_long_zero();
//    if the nominator's absolute value is less, then for equal signs modulo gives the nominator itself, and for
//    different signs it gives their sum
    else if (relation < 0)
        return (nom->sign == denom->sign) ? copy_long_num(nom) : add_long_num(nom, denom);
    else {
        Pair* div_mod = div_mod_long_absolutes(nom, denom);
        delete_long_num(div_mod->first);
        LongNum* result = div_mod->second;
        free(div_mod);

        if (!is_long_zero(result))
            if (nom->sign != denom->sign) {
                if (denom->sign == MINUS) add_to_long_num(&result, denom);
                else {
                    result->sign = MINUS;
                    add_to_long_num(&result, denom);
                }
            }
        return result;
    }
}


Pair* divmod_long_num(const LongNum* nom, const LongNum* denom) {
    if (nom == NULL || denom == NULL) return NULL;

    if (is_long_zero(denom)) {
        printf("Error: zero division in long number division and modulo!\n");
        return NULL;
    }

    if (is_long_zero(nom)) return new_pair(new_long_zero(), new_long_zero());

    if (is_long_one(denom)) {
        LongNum* div_result = copy_long_num(nom);
        div_result->sign = nom->sign * denom->sign;
        return new_pair(div_result, new_long_zero());
    }

    int relation = compare_long_absolutes(nom, denom);
    if (relation < 0) {
        LongNum* div_result = (nom->sign == denom->sign) ? new_long_zero() : new_long_num(-1);
        LongNum* mod_result = (nom->sign == denom->sign) ? copy_long_num(nom) : add_long_num(nom, denom);
        return new_pair(div_result, mod_result);
    }
    else if (relation == 0) {
        LongNum* div_result = (nom->sign == denom->sign) ? new_long_num(1) : new_long_num(-1);
        return new_pair(div_result, new_long_zero());
    }

    Pair* div_mod = div_mod_long_absolutes(nom, denom);

//    process a special case for division result
    if (nom->sign != denom->sign) {
        ((LongNum*)div_mod->first)->sign = MINUS;
        sub_positive_int_from_long_num((LongNum **) &div_mod->first, 1);
    }

//    process a special case for modulo result
    if (!is_long_zero(((LongNum*)div_mod->second)))
        if (nom->sign != denom->sign) {
            if (denom->sign == MINUS) add_to_long_num((LongNum **) &div_mod->second, denom);
            else {
                ((LongNum*)div_mod->second)->sign = MINUS;
                add_to_long_num((LongNum **) &div_mod->second, denom);
            }
        }

    return div_mod;
}


void add_to_long_num(LongNum **lnum1, const LongNum* lnum2) {
    if (lnum1 == NULL || *lnum1 == NULL || lnum2 == NULL) {
        printf("A NULL passed to long number addition\n");
        return;
    }

    if (is_long_zero(*lnum1)) {
        delete_long_num(*lnum1);
        *lnum1 = copy_long_num(lnum2);
        return;
    }

    if (is_long_zero(lnum2)) return;

    if ((*lnum1)->sign == lnum2->sign)
        add_long_int_absolutes(lnum1, lnum2);
    else {
        int former_sign = (*lnum1)->sign;
        sub_long_int_absolutes(lnum1, lnum2);
        (*lnum1)->sign *= former_sign;
    }
}


void add_positive_int_to_long_num(LongNum** lnum, unsigned int num) {
    if (lnum == NULL || *lnum == NULL) {
        printf("A NULL passed to long number addition\n");
        return;
    }

    if (num == 0) return;

    if (is_long_zero(*lnum)) {
        delete_long_num(*lnum);
        *lnum = new_long_num(num);
        return;
    }

    if ((*lnum)->sign == PLUS) {
        size_t i;
        int overflow = 0;
        (*lnum)->digits->elements[0] = add_with_overflow((*lnum)->digits->elements[0], num, &overflow);
        for (i = 1; i < (*lnum)->digits->length; i++)
            (*lnum)->digits->elements[i] = add_with_overflow((*lnum)->digits->elements[i], 0, &overflow);
        append_value_to_long_int(*lnum, overflow);
    }
    else {
        if ((*lnum)->digits->length == 1) {
            if ((*lnum)->digits->elements[0] > num)
                (*lnum)->digits->elements[0] -= num;
            else if ((*lnum)->digits->elements[0] < num) {
                (*lnum)->digits->elements[0] = num - (*lnum)->digits->elements[0];
                (*lnum)->sign = PLUS;
            }
            else {
                delete_long_num(*lnum);
                *lnum = new_long_zero();
            }
            return;
        }

        size_t i;
        int overflow = 0;
        (*lnum)->digits->elements[0] = sub_with_overflow((*lnum)->digits->elements[0], num, &overflow);
        for (i = 1; i < (*lnum)->digits->length; i++)
            (*lnum)->digits->elements[i] = sub_with_overflow((*lnum)->digits->elements[i], 0, &overflow);
        remove_leading_zeros(*lnum);
    }
}


void sub_from_long_num(LongNum **lnum1, const LongNum* lnum2) {
    if (lnum1 == NULL || *lnum1 == NULL || lnum2 == NULL) {
        printf("A NULL passed to long number subtraction\n");
        return;
    }

    if (is_long_zero(*lnum1)) {
        delete_long_num(*lnum1);
        *lnum1 = copy_long_num(lnum2);
        (*lnum1)->sign = -lnum2->sign;
        return;
    }

    if (is_long_zero(lnum2)) return;

//    it is basically the same as for the sum, but the branches are swapped
    if ((*lnum1)->sign == -lnum2->sign)
        add_long_int_absolutes(lnum1, lnum2);
    else {
        int former_sign = (*lnum1)->sign;
        sub_long_int_absolutes(lnum1, lnum2);
        (*lnum1)->sign *= former_sign;
    }
}


void sub_positive_int_from_long_num(LongNum** lnum, unsigned int num) {
    if (lnum == NULL || *lnum == NULL) {
        printf("A NULL passed to long number subtraction\n");
        return;
    }

    if (num == 0) return;

    if (is_long_zero(*lnum)) {
        delete_long_num(*lnum);
        *lnum = new_long_num(-num);
        return;
    }

    if ((*lnum)->sign == MINUS) {
        size_t i;
        int overflow = 0;
        (*lnum)->digits->elements[0] = add_with_overflow((*lnum)->digits->elements[0], num, &overflow);
        for (i = 1; i < (*lnum)->digits->length; i++)
            (*lnum)->digits->elements[i] = add_with_overflow((*lnum)->digits->elements[i], 0, &overflow);
        append_value_to_long_int(*lnum, overflow);
    }
    else {
        if ((*lnum)->digits->length == 1) {
            if ((*lnum)->digits->elements[0] > num)
                (*lnum)->digits->elements[0] -= num;
            else if ((*lnum)->digits->elements[0] < num) {
                (*lnum)->digits->elements[0] = num - (*lnum)->digits->elements[0];
                (*lnum)->sign = MINUS;
            }
            else {
                delete_long_num(*lnum);
                *lnum = new_long_zero();
            }
            return;
        }

        size_t i;
        int overflow = 0;
        (*lnum)->digits->elements[0] = sub_with_overflow((*lnum)->digits->elements[0], num, &overflow);
        for (i = 1; i < (*lnum)->digits->length; i++)
            (*lnum)->digits->elements[i] = sub_with_overflow((*lnum)->digits->elements[i], 0, &overflow);
        remove_leading_zeros(*lnum);
    }
}


void long_shift_left(LongNum **lnum, size_t shift) {
    if (lnum == NULL || *lnum == NULL) {
        printf("A NULL passed to long number shift\n");
        return;
    }

    if (shift == 0) return;

    resize_array((*lnum)->digits, (*lnum)->digits->length + shift);
    (*lnum)->digits->length += shift;
    size_t i;
    for (i = (*lnum)->digits->length - 1; i >= shift; i--)
        (*lnum)->digits->elements[i] = (*lnum)->digits->elements[i - shift];
    for (i = shift - 1; i >= 0 && i < shift; i--)
        (*lnum)->digits->elements[i] = 0;
}


int compare_long_num(const LongNum* lnum1, const LongNum* lnum2) {
    if (lnum1 == NULL && lnum2 == NULL) {
        printf("Comparison of two NULL long numbers.\n");
        return 0;
    }
    else if (lnum1 == NULL && lnum2 != NULL) return -1;
    else if (lnum1 != NULL && lnum2 == NULL) return 1;

    if (lnum1->sign == ZERO) assert(is_long_zero(lnum1));
    if (lnum2->sign == ZERO) assert(is_long_zero(lnum2));

    if (lnum1->sign * lnum2->sign == MINUS) return (lnum1->sign == PLUS) ? 1 : -1;
    else return lnum1->sign * compare_long_absolutes(lnum1, lnum2);
}


int is_long_zero(const LongNum* lnum) {
    if (lnum == NULL) return 0;

    size_t i;
    for (i = 0; i < lnum->digits->length; i++)
        if (lnum->digits->elements[i] != 0) return 0;
    return 1;
}


int is_long_one(const LongNum* lnum) {
    if (lnum == NULL) return 0;

    size_t i;
//    check that all the digits except for the first one are zeros
    for (i = 1; i < lnum->digits->length; i++)
        if (lnum->digits->elements[i] != 0) return 0;
    return lnum->digits->elements[0] == 1;
}


//*********************************************************//
// Internal helper functions that are not part of the API. //
//*********************************************************//


static void append_value_to_long_int(LongNum* lnum, long long value) {
    if (lnum == NULL) {
        printf("Trying to append value to NULL\n");
        return;
    }

    while (value > 0) {
        append_to_array(lnum->digits, value % BASE);
        value = value / BASE;
    }
}


static LongNum* new_empty_long_num(size_t size) {
    LongNum* lnum = malloc(sizeof(LongNum));
    lnum->digits = new_empty_array_u_int(size);
    lnum->sign = PLUS;
    return lnum;
}


static void remove_leading_zeros(LongNum* lnum) {
    if (lnum == NULL) return;

    size_t i = lnum->digits->length;
//    we must leave at least one digit, so we restrict i to be > 1
    while (i > 1 && lnum->digits->elements[i-1] == 0)
        i--;
    resize_array(lnum->digits, i);
    if (i == 0)
        lnum->sign = ZERO;
}


static int compare_long_absolutes(const LongNum *lnum1, const LongNum *lnum2) {
    size_t i;
    size_t len1, len2;
//    determine the lengths of the arrays without leading zeros
    for (len1 = lnum1->digits->length; len1 > 0 && lnum1->digits->elements[len1-1] == 0; len1--);
    for (len2 = lnum2->digits->length; len2 > 0 && lnum2->digits->elements[len2-1] == 0; len2--);

//    if any number is longer than the other one, and the exceeding length does not consist of zeros only, we consider
//    the longer one to be greater
    if (len1 > len2) return 1;
    else if (len1 < len2) return -1;
    else {
        for (i = len1 - 1; i >= 0 && i < len1; i--) {
            int element_relation = compare_numerical(lnum1->digits->elements[i], lnum2->digits->elements[i]);
            if (element_relation != 0) return element_relation;
        }
    }
    return 0;
}


static int add_with_overflow(unsigned int a, unsigned int b, int* overflow) {
    if (overflow == NULL) {
        printf("No overflow value provided for addition\n");
        return 0;
    }

    unsigned long long sum = (unsigned long long)a + b + *overflow;
    *overflow = sum / BASE;
    return sum % BASE;
}


static unsigned int sub_with_overflow(unsigned int a, unsigned int b, int* overflow) {
    if (overflow == NULL) {
        printf("No overflow value provided for subtraction\n");
        return 0;
    }

    long result = (long)a - b - *overflow;
    if (result < 0) {
        result += BASE;
        *overflow = 1;
    }
    else
        *overflow = 0;
    return result;
}


static void add_long_int_absolutes(LongNum** lnum1, const LongNum* lnum2) {
    size_t i;
    int overflow = 0;
//    if lnum1 is the longest, we must assign its leading digits instead of appending to it
    if ((*lnum1)->digits->length > lnum2->digits->length) {
        for (i = 0; i < lnum2->digits->length; i++)
            (*lnum1)->digits->elements[i] = add_with_overflow((*lnum1)->digits->elements[i], lnum2->digits->elements[i], &overflow);
        for (; i < (*lnum1)->digits->length; i++)
            (*lnum1)->digits->elements[i] = add_with_overflow((*lnum1)->digits->elements[i], 0, &overflow);
    }
    else {
        for (i = 0; i < (*lnum1)->digits->length; i++)
            (*lnum1)->digits->elements[i] = add_with_overflow((*lnum1)->digits->elements[i], lnum2->digits->elements[i], &overflow);
        for (; i < lnum2->digits->length; i++)
        append_to_array((*lnum1)->digits, add_with_overflow(lnum2->digits->elements[i], 0, &overflow));
    }

    append_value_to_long_int(*lnum1, overflow);
}


static void sub_long_int_absolutes(LongNum** lnum1, const LongNum* lnum2) {
    int relation = compare_long_absolutes(*lnum1, lnum2);
    if (relation == 0) {
        reset_long_num(lnum1, new_long_zero());
        return;
    }

//    we will always subtract the smallest from the largest
    const LongNum* small = (relation < 0) ? *lnum1 : lnum2;
    const LongNum* large = (relation < 0) ? lnum2 : *lnum1;

    size_t i;
    int overflow = 0;
//    sum the digits of the numbers until reach the end of the shortest one
    for (i = 0; i < small->digits->length; i++)
        (*lnum1)->digits->elements[i] = sub_with_overflow(large->digits->elements[i], small->digits->elements[i],
                                                          &overflow);

//    for the remaining of the longest one we assume the digits of the second number as to be 0
    resize_array((*lnum1)->digits, large->digits->length);
    (*lnum1)->digits->length = large->digits->length;
    for (; i < large->digits->length; i++)
        (*lnum1)->digits->elements[i] = sub_with_overflow(large->digits->elements[i], 0, &overflow);

    remove_leading_zeros(*lnum1);
    (*lnum1)->sign = (relation < 0) ? MINUS : PLUS;
}


static int mul_with_overflow(unsigned int a, unsigned int b, unsigned long* overflow) {
    if (a > BASE || b > BASE) {
        printf("Operands must not exceed the BASE = %d\n", BASE);
        return 0;
    }

    u_int64_t result = (a == 0 || b == 0) ? *overflow : (u_int64_t)a * b + *overflow;
    *overflow = result / BASE;
    return result % BASE;
}


/**
 * Computes the result of the integer division of the two given long numbers along with the modulo value.
 *
 * @return pair containing the pointer to the division result in the first field, and the pointer to the modulo in the
 *  second one
 */
static Pair* div_mod_long_absolutes(const LongNum* nom, const LongNum* denom) {
    size_t denom_len = denom->digits->length;
    size_t nom_len = nom->digits->length;
    size_t len_result = nom->digits->length - denom_len;
    size_t i;

//    the last digits of nom are in the beginning here, which allows us to extract them simpler, without extra care with indices
    LongNum* nom_reverted = copy_long_num(nom);
    revert_array(nom_reverted->digits);

//    extracting the last digits of the nominator into a sliding window
    LongNum* mod_result = new_empty_long_num(denom_len);
    mod_result->sign = PLUS;
    for (i = 0; i < denom_len - 1; i++)
    append_to_array(mod_result->digits, nom_reverted->digits->elements[i]);
    revert_array(mod_result->digits);

    LongNum* div_result = new_empty_long_num(len_result);
    div_result->sign = PLUS;

    for (i = denom_len - 1; i < nom_len; i++) {
//        append the current nominator digit to the end of the sliding window
        long_shift_left(&mod_result, 1);
        mod_result->digits->elements[0] = nom_reverted->digits->elements[i];

        int relation = compare_long_absolutes(mod_result, denom);
//        if the window is less than denom, set 0 to the current digit's div_result and continue extracting nom's digits
        if (relation < 0) append_to_array(div_result->digits, 0);
//        if the window is exactly equal to the denom, nullify it and set current div_result's digit to 1
        else if (relation == 0) {
            append_to_array(div_result->digits, 1);
            reset_long_num(&mod_result, new_long_zero());
        }
//        otherwise, determine the maximum multiplier that being multiplied with the denom gives value less than the
//        window, but being increased by 1 gives value greater than the window
//        effectively, here we reassign the window to itself modulo denom
        else {
            unsigned int left = 0, right = BASE - 1, mult = right;
            LongNum* multiplied_denom = NULL;
//            we determine the multiplier via the binary search
            while (1) {
                delete_long_num(multiplied_denom);
                multiplied_denom = mul_long_num_and_positive_int(denom, mult);
                multiplied_denom->sign = PLUS;
                int temp_relation = compare_long_absolutes(multiplied_denom, mod_result);

                if (temp_relation == 0) break;
                else if (temp_relation < 0) {
                    if (right - left == 1) break;
                    else left = mult;
                }
                else right = mult;
                mult = (left + right) / 2;
            }

//            this multiplier will be the current digit of the div_result
            append_to_array(div_result->digits, mult);
            multiplied_denom->sign = PLUS;
            sub_from_long_num(&mod_result, multiplied_denom);
            delete_long_num(multiplied_denom);
        }
    }

    delete_long_num(nom_reverted);
//    since the digits in the div_result come in the backwards order, we need to revert it
    revert_array(div_result->digits);
    remove_leading_zeros(div_result);

    if (compare_long_absolutes(mod_result, denom) == 0) reset_long_num(&mod_result, new_long_zero());
    else remove_leading_zeros(mod_result);

    return new_pair(div_result, mod_result);
}
