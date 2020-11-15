#undef __STRICT_ANSI__
#include <stdio.h>
#include <math.h>

#define MAX 32
typedef enum bool {
  false, true
} bool;

void poly_print(double const p[], int const m);

double poly_evaluate(double const p[], int const m, double const x);

int poly_add(double const p[], int const m, double const q[], int const n, double r[]);

int poly_sub(double const p[], int const m, double const q[], int const n, double r[]);

int poly_mult(double const p[], int const m, double const q[], int const n, double r[]);

int poly_mult_fast(double const p[], int const m, double const q[], int const n, double r[]);

static int poly_mult_fast_recursive(double const p[], double const q[], int const m, double r[]);

static void pretty_print_pow(double const multiplicant, int const exponent);

static int poly_find_first_non_zero(double const p[], int const m);

static bool is_poly_degree_valid(int const m);

static bool is_pow_two(int const m);

static void test_cases_poly_print();
static void test_cases_poly_evaluate();
static void test_cases_poly_add();
static void test_cases_poly_mult();
static void test_cases_poly_mult_fast();

int main(void) {
  test_cases_poly_print();
  test_cases_poly_evaluate();
  test_cases_poly_add();
  test_cases_poly_mult();
  test_cases_poly_mult_fast();
  return 0;
}

void poly_print(double const p[], int const m) {
  if (!is_poly_degree_valid(m)) {
    return;
  }
  // Since a polynom can have a degree of zero the actual size of the array is degree + 1
  const int length_of_p = m + 1;
  printf("P(x)=");
  // Skip the leading zeros
  int starting = poly_find_first_non_zero(p, length_of_p);
  if (starting == -1) {
    printf("0\n");
    return;
  }
  bool already_printed = false;
  for (int i = starting; i < length_of_p; i++) {
    if (p[i] != 0) {
      if (i > 0 && p[i] > 0 && already_printed) {
        printf("+");
      }
      already_printed = true;
      pretty_print_pow(p[i], i);
    }
  }
  printf("\n");
}

double poly_evaluate(double const p[], int const m, double const x) {
  if(!is_poly_degree_valid(m)) {
    return 0;
  }
  const int length_of_p = m + 1;
  double sum = p[0];
  for (int i = 1; i < length_of_p; i++) {
    sum += p[i] * pow(x, i);
  }
  return sum;
}

int poly_add(double const p[], int const m, double const q[], int const n, double r[]) {
  if (!(is_poly_degree_valid(m) && is_poly_degree_valid(n))) {
    return 0;
  }

  int max = m > n ? m : n;
  double cur_m, cur_n;
  for (int i = 0; i <= max; i++) {
    cur_m = i <= m ? p[i] : 0;
    cur_n = i <= n ? q[i] : 0;
    r[i] = cur_m + cur_n;
  }
  return max;
}

int poly_sub(double const p[], int const m, double const q[], int const n, double r[]) {
  if (!(is_poly_degree_valid(m) && is_poly_degree_valid(n))) {
    return 0;
  }

  int max = m > n ? m : n;
  double cur_m, cur_n;
  for (int i = 0; i <= max; i++) {
    cur_m = i <= m ? p[i] : 0;
    cur_n = i <= n ? q[i] : 0;
    r[i] = cur_m - cur_n;
  }
  return max;
}

int poly_mult(double const p[], int const m, double const q[], int const n, double r[]) {
  if (!(is_poly_degree_valid(m) && is_poly_degree_valid(n) && is_poly_degree_valid(m + n))) {
    return 0;
  }
  const int length_of_p = m + 1;
  const int length_of_q = n + 1;
  // Initialize r with zeros
  for (int i = 0; i < length_of_p + length_of_q; i++) {
    r[i] = 0;
  }
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      r[i + j] += p[i] * q[j];
    }
  }
  return m + n;
}

int poly_mult_fast(double const p[], int const m, double const q[], int const n, double r[]) {
  if (m != n) {
    printf("m and n need to be equal!\n");
    return 0;
  }
  if (!(is_poly_degree_valid(m) && is_poly_degree_valid(n) 
        && is_poly_degree_valid(m + n))) {
    return 0;
  }
  if (!is_pow_two(m + 1)) {
    printf("m + 1 is not a power of two!\n");
    return 0;
  }
  for (int i = 0; i <= m + n; i++) {
    r[i] = 0;
  }
  return poly_mult_fast_recursive(p, q, m, r);
}

static int poly_mult_fast_recursive(double const p[], double const q[], int const m, double r[]) {
  if (m == 0) {
    r[0] = p[0] * q[0];
    return m;
  }
  int half_m = m / 2;
  double p_r[MAX] = {0};
  double p_l[MAX] = {0};
  double q_r[MAX] = {0};
  double q_l[MAX] = {0};

  for (int i = 0; i <= half_m; i++) {
    p_l[i] = p[i];
    q_l[i] = q[i];

    p_r[i] = p[half_m + i + 1];
    q_r[i] = q[half_m + i + 1];
  }
  double h_r[MAX] = {0};
  double h_l[MAX] = {0};
  double h_m[MAX] = {0};
  double h_m_p[MAX] = {0};
  double h_m_q[MAX] = {0};

  poly_mult_fast_recursive(p_l, q_l, half_m, h_l);
  poly_mult_fast_recursive(p_r, q_r, half_m, h_r);

  // Calculation for h_m
  poly_add(p_r, half_m, p_l, half_m, h_m_p);
  poly_add(q_r, half_m, q_l, half_m, h_m_q);

  poly_mult_fast_recursive(h_m_p, h_m_q, half_m, h_m);

  // Shift the result h_m - h_l - h_r with m/2 + 1
  double tmp1[MAX] = {0};
  double tmp2[MAX] = {0};
  double tmp3[MAX] = {0};

  poly_sub(h_m, m, h_l, m, tmp1);
  poly_sub(tmp1, m, h_r, m, tmp2);
  for(int i = half_m + 1; i >= 0; i--) {
    tmp2[half_m + i + 1] = tmp2[i];
    tmp2[i] = 0;
  }
  for(int i = 0; i <= m; i++) {
    h_r[m + i + 1] = h_r[i];
    h_r[i] = 0;
  }
  int new_m = (m + 1) * 2 - 1;
  poly_add(h_l, new_m, tmp2, new_m, tmp3);
  poly_add(tmp3, new_m, h_r, new_m, r);
  return new_m;
}

/**
 * Finds the first number which is not zero and returns its index.
 * Starts at the start_index.
 * If there are only zeros it returns -1.
 */
static int poly_find_first_non_zero(const double p[], int const m) {
  for (int i = 0; i < m; i++) {
    if (p[i] != 0) {
      return i;
    }
  }
  return -1;
}

/**
 * Pretty prints the multiplier with x and its exponent
 */
static void pretty_print_pow(double const multiplier, int const exponent) {
  bool printed_multi = true;
  if (multiplier == 0) {
    return;
  }
  // Check if multiplier is 1 or -1
  if (multiplier * multiplier == 1) {
    printed_multi = false;
    (void) (multiplier == 1 || printf("-"));
  } else {
    printf("%g", multiplier);
  }
  switch (exponent) {
    case 0:
      (void) (printed_multi || printf("1"));
      break;
    case 1:
      printf("x");
      break;
    default:
      printf("x^%d", exponent);
  }
}

/**
 * Checks if polynom degree is smaller than the MAX
 */
static bool is_poly_degree_valid(int const m) {
  if (m > MAX) {
    printf("Polynom degree of %d must be smaller than %d", m, MAX);
    return false;
  } else if (m < 0) {
    printf(" Polynom degree must be bigger or equal 0");
    return false;
  }
  return true;
}

static bool is_pow_two(int const m) {
  return (m & (m - 1)) == 0;
}

/*** TEST CASES ***/

/**
 * Test cases for the poly print function
 */
static void test_cases_poly_print() {
  printf("TEST CASES FOR POLY PRINT\n");
  /* Some simple Test Cases */
  double const p[] = {1, 1, 3, -4};
  double const q[] = {1, 2, -5, -3, 0, -2};
  /* Edge Cases */
  double const empty[] = {0, 0, 0, 0}; // Polynomfunction with only zeros
  double const half_empty_half_one[] = {0, 0, -1, 1}; // First half of the function are zeros
  double const other_half_empty_half_one[] = {-1, 1, 0, 0}; // Second half o the function are zeros
  double const middle_zero[] = {1, 0, 0, 1}; // There are zeros in the middle of the function
  double const one[] = {1, 1, 1, 1}; // Everything is positive
  double const neg_one[] = {-1, -1, -1, -1}; // Everything is negativ
  double const single[] = {10}; // Only one element
  printf("p\n");
  poly_print(p, 3);
  printf("q\n");
  poly_print(q, 5);
  printf("empty\n");
  poly_print(empty, 3);
  printf("half empty\n");
  poly_print(half_empty_half_one, 3);
  printf("other half empty half one\n");
  poly_print(other_half_empty_half_one, 3);
  printf("one\n");
  poly_print(one, 3);
  printf("neg one\n");
  poly_print(neg_one, 3);
  printf("middle zero\n");
  poly_print(middle_zero, 3);
  printf("single\n");
  poly_print(single, 0);
}

static void test_cases_poly_evaluate() {
  printf("TEST CASES FOR POLY EVALUATE\n");
  /* Simple Test Cases */
  double const f[] = {4, 3, -2, 1};
  double const p[] = {1, 1, 3, -4};
  double const q[] = {1, 0, 0, -4};
  /* Edge Cases */
  double const single[] = {10};
  double const null[] = {0 , 0, 0, 0};

  printf("f(pi)=-56.1703=%g\n", poly_evaluate(f, 3, -M_PI));

  printf("p(1)=1=%g\n", poly_evaluate(p, 3, 1));
  printf("p(5)=-419=%g\n", poly_evaluate(p, 3, 5));
  printf("p(10)=-3689=%g\n", poly_evaluate(p, 3, 10));

  printf("q(1)=-3=%g\n", poly_evaluate(q, 3, 1));  
  printf("q(0)=1=%g\n", poly_evaluate(q, 3, 0));

  printf("single(1)=10=%g\n", poly_evaluate(single, 0, 1));
  printf("single(10)=10=%g\n", poly_evaluate(single, 0, 10));

  printf("null(1)=0=%g\n", poly_evaluate(null, 3, 1));
  printf("null(10)=0=%g\n", poly_evaluate(null, 3, 10));
}

static void test_cases_poly_add() {
  printf("TEST CASES FOR POLY ADD\n");
  /* Simple Test Cases */
  double const f[] = {4, 3, -2, 1};
  double const p[] = {1, 1, 3, -4};
  double const q[] = {1, 0, -4};
  double const null[] = {0, 0, 0, 0};
  /* Result Arrays */
  double pq[MAX];
  double fp[MAX];
  double fnull[MAX];

  // Add not same sized polys
  poly_add(p, 3, q, 2, pq);
  printf("2+x-x^2-4x^3=");
  poly_print(pq, 3);

  // Add same sized polys
  poly_add(f, 3, p, 3, fp);
  printf("5+4x+x^2-3x^3=");
  poly_print(fp, 3);

  // Add to nothing
  poly_add(f, 3, null, 3, fnull);
  printf("4+3x-2x^2+x^4=");
  poly_print(fnull, 3);
}

static void test_cases_poly_mult() {
  printf("TEST CASES FOR POLY MULT\n");
  double const f[] = {1, 1, 3, -4};
  double const p[] = {1, 2, -5, -3};
  double const half_empty_half_one[] = {0, 0, -1, 1};
  double const other_half_empty_half_one[] = {-1, 1, 0, 0};
  double const one[1] = {1};
  double const null[1] = {0};
  /* Result Arrays */
  double fp[MAX];
  double fone[MAX];
  double fnull[MAX];
  double halfs[MAX];

  // Simple multiplication
  printf("1+3x-6x^3-26x^4+11x^5+12x^6=");
  poly_mult(f, 3, p, 3, fp);
  poly_print(fp, 7);

  // Mult with one
  printf("1+x+3x^2-4x^3=");
  poly_mult(f, 3, one, 0, fone);
  poly_print(fone, 3);

  // Mult with zero
  printf("0=");
  poly_mult(f, 3, null, 0, fnull);
  poly_print(fnull, 3);

  // Mult half empty polys
  printf("x^2-2x^3+x^4=");
  poly_mult(half_empty_half_one, 3, other_half_empty_half_one, 3, halfs);
  poly_print(halfs, 7);
}

static void test_cases_poly_mult_fast() {
  printf("TEST CASES FOR POLY MULT FAST\n");
  double const f[] = {1, 1, 3, -4};
  double const p[] = {1, 2, -5, -3};
  double const half_empty_half_one[] = {0, 0, -1, 1};
  double const other_half_empty_half_one[] = {-1, 1, 0, 0};
  double const one[] = {1, 1, 1, 1};
  double const null[] = {0, 0, 0, 0};
  /* Result Arrays */
  double fp[MAX];
  double fone[MAX];
  double fnull[MAX];
  double halfs[MAX];

  // Simple multiplication
  printf("1+3x-6x^3-26x^4+11x^5+12x^6=");
  poly_mult_fast(f, 3, p, 3, fp);
  poly_print(fp, 7);

  // Mult with one
  printf("1+2x+5x^2+x^3-x^5-4x^6=");
  poly_mult_fast(f, 3, one, 3, fone);
  poly_print(fone, 7);

  // Mult with zero
  printf("0=");
  poly_mult_fast(f, 3, null, 3, fnull);
  poly_print(fnull, 7);

  // Mult half empty polys
  printf("x^2-2x^3+x^4=");
  poly_mult_fast(half_empty_half_one, 3, other_half_empty_half_one, 3, halfs);
  poly_print(halfs, 7);
}
