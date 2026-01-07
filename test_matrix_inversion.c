/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_matrix_inversion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 by mkeerewe                  #+#    #+#             */
/*   Updated: 2026/01/07 by mkeerewe                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	print_matrix(t_mat mat, const char *name)
{
	int	i;
	int	j;

	printf("\n%s:\n", name);
	i = 0;
	while (i < mat.rows)
	{
		j = 0;
		while (j < mat.cols)
		{
			printf("%10.5f ", get_data(mat, i, j));
			j++;
		}
		printf("\n");
		i++;
	}
}

void	test_determinant_2x2(void)
{
	t_mat	mat;
	double	det;

	printf("\n=== TEST: 2x2 Determinant ===\n");
	mat = new_matrix(2, 2);
	set_data(mat, 0, 0, 1.0);
	set_data(mat, 0, 1, 5.0);
	set_data(mat, 1, 0, -3.0);
	set_data(mat, 1, 1, 2.0);
	
	det = determinant(mat);
	printf("Expected: 17.0\n");
	printf("Got:      %.5f\n", det);
	printf("Result:   %s\n", equal(det, 17.0) ? "PASS" : "FAIL");
	
	destroy_matrix(mat);
}

void	test_submatrix_3x3(void)
{
	t_mat	mat;
	t_mat	sub;

	printf("\n=== TEST: Submatrix 3x3 ===\n");
	mat = new_matrix(3, 3);
	set_data(mat, 0, 0, 1.0);
	set_data(mat, 0, 1, 5.0);
	set_data(mat, 0, 2, 0.0);
	set_data(mat, 1, 0, -3.0);
	set_data(mat, 1, 1, 2.0);
	set_data(mat, 1, 2, 7.0);
	set_data(mat, 2, 0, 0.0);
	set_data(mat, 2, 1, 6.0);
	set_data(mat, 2, 2, -3.0);
	
	sub = submatrix(mat, 0, 2);
	print_matrix(mat, "Original 3x3");
	print_matrix(sub, "Submatrix (row 0, col 2 removed)");
	
	printf("Expected [0,0]: -3.0, Got: %.5f\n", get_data(sub, 0, 0));
	printf("Expected [1,1]: 6.0,  Got: %.5f\n", get_data(sub, 1, 1));
	
	destroy_matrix(mat);
	destroy_matrix(sub);
}

void	test_minor_and_cofactor(void)
{
	t_mat	mat;
	double	min;
	double	cof;

	printf("\n=== TEST: Minor and Cofactor ===\n");
	mat = new_matrix(3, 3);
	set_data(mat, 0, 0, 3.0);
	set_data(mat, 0, 1, 5.0);
	set_data(mat, 0, 2, 0.0);
	set_data(mat, 1, 0, 2.0);
	set_data(mat, 1, 1, -1.0);
	set_data(mat, 1, 2, -7.0);
	set_data(mat, 2, 0, 6.0);
	set_data(mat, 2, 1, -1.0);
	set_data(mat, 2, 2, 5.0);
	
	min = minor(mat, 1, 0);
	printf("Minor(1,0) - Expected: 25.0, Got: %.5f %s\n", 
		min, equal(min, 25.0) ? "PASS" : "FAIL");
	
	cof = cofactor(mat, 0, 0);
	printf("Cofactor(0,0) - Expected: -12.0, Got: %.5f %s\n", 
		cof, equal(cof, -12.0) ? "PASS" : "FAIL");
	
	cof = cofactor(mat, 1, 0);
	printf("Cofactor(1,0) - Expected: -25.0, Got: %.5f %s\n", 
		cof, equal(cof, -25.0) ? "PASS" : "FAIL");
	
	destroy_matrix(mat);
}

void	test_determinant_3x3(void)
{
	t_mat	mat;
	double	det;

	printf("\n=== TEST: 3x3 Determinant ===\n");
	mat = new_matrix(3, 3);
	set_data(mat, 0, 0, 1.0);
	set_data(mat, 0, 1, 2.0);
	set_data(mat, 0, 2, 6.0);
	set_data(mat, 1, 0, -5.0);
	set_data(mat, 1, 1, 8.0);
	set_data(mat, 1, 2, -4.0);
	set_data(mat, 2, 0, 2.0);
	set_data(mat, 2, 1, 6.0);
	set_data(mat, 2, 2, 4.0);
	
	det = determinant(mat);
	printf("Expected: -196.0\n");
	printf("Got:      %.5f\n", det);
	printf("Result:   %s\n", equal(det, -196.0) ? "PASS" : "FAIL");
	
	destroy_matrix(mat);
}

void	test_determinant_4x4(void)
{
	t_mat	mat;
	double	det;

	printf("\n=== TEST: 4x4 Determinant ===\n");
	mat = new_matrix(4, 4);
	set_data(mat, 0, 0, -2.0);
	set_data(mat, 0, 1, -8.0);
	set_data(mat, 0, 2, 3.0);
	set_data(mat, 0, 3, 5.0);
	set_data(mat, 1, 0, -3.0);
	set_data(mat, 1, 1, 1.0);
	set_data(mat, 1, 2, 7.0);
	set_data(mat, 1, 3, 3.0);
	set_data(mat, 2, 0, 1.0);
	set_data(mat, 2, 1, 2.0);
	set_data(mat, 2, 2, -9.0);
	set_data(mat, 2, 3, 6.0);
	set_data(mat, 3, 0, -6.0);
	set_data(mat, 3, 1, 7.0);
	set_data(mat, 3, 2, 7.0);
	set_data(mat, 3, 3, -9.0);
	
	det = determinant(mat);
	printf("Expected: -4071.0\n");
	printf("Got:      %.5f\n", det);
	printf("Result:   %s\n", equal(det, -4071.0) ? "PASS" : "FAIL");
	
	destroy_matrix(mat);
}

void	test_inverse_4x4(void)
{
	t_mat	mat;
	t_mat	inv;

	printf("\n=== TEST: 4x4 Matrix Inversion ===\n");
	mat = new_matrix(4, 4);
	set_data(mat, 0, 0, 8.0);
	set_data(mat, 0, 1, -5.0);
	set_data(mat, 0, 2, 9.0);
	set_data(mat, 0, 3, 2.0);
	set_data(mat, 1, 0, 7.0);
	set_data(mat, 1, 1, 5.0);
	set_data(mat, 1, 2, 6.0);
	set_data(mat, 1, 3, 1.0);
	set_data(mat, 2, 0, -6.0);
	set_data(mat, 2, 1, 0.0);
	set_data(mat, 2, 2, 9.0);
	set_data(mat, 2, 3, 6.0);
	set_data(mat, 3, 0, -3.0);
	set_data(mat, 3, 1, 0.0);
	set_data(mat, 3, 2, -9.0);
	set_data(mat, 3, 3, -4.0);
	
	inv = inverse(mat);
	if (inv.data == NULL)
	{
		printf("ERROR: Inverse returned NULL\n");
		destroy_matrix(mat);
		return;
	}
	
	print_matrix(mat, "Original Matrix A");
	print_matrix(inv, "Computed Inverse A^-1");
	
	printf("\n--- Expected Inverse Matrix ---\n");
	printf("| -0.15385 | -0.15385 | -0.28205 | -0.53846 |\n");
	printf("| -0.07692 |  0.12308 |  0.02564 |  0.03077 |\n");
	printf("|  0.35897 |  0.35897 |  0.43590 |  0.92308 |\n");
	printf("| -0.69231 | -0.69231 | -0.76923 | -1.92308 |\n");
	
	
	destroy_matrix(mat);
	destroy_matrix(inv);
}

void	test_inverse_multiply_identity(void)
{
	t_mat	mat;
	t_mat	inv;
	t_mat	product;
	t_mat	ident;

	printf("\n=== TEST: A * A^-1 = Identity ===\n");
	mat = new_matrix(4, 4);
	set_data(mat, 0, 0, 3.0);
	set_data(mat, 0, 1, -9.0);
	set_data(mat, 0, 2, 7.0);
	set_data(mat, 0, 3, 3.0);
	set_data(mat, 1, 0, 3.0);
	set_data(mat, 1, 1, -8.0);
	set_data(mat, 1, 2, 2.0);
	set_data(mat, 1, 3, -9.0);
	set_data(mat, 2, 0, -4.0);
	set_data(mat, 2, 1, 4.0);
	set_data(mat, 2, 2, 4.0);
	set_data(mat, 2, 3, 1.0);
	set_data(mat, 3, 0, -6.0);
	set_data(mat, 3, 1, 5.0);
	set_data(mat, 3, 2, -1.0);
	set_data(mat, 3, 3, 1.0);
	
	inv = inverse(mat);
	if (inv.data == NULL)
	{
		printf("ERROR: Inverse returned NULL\n");
		destroy_matrix(mat);
		return;
	}
	
	product = mat_mult(mat, inv);
	ident = identity();
	
	print_matrix(product, "A * A^-1");
	printf("\nShould equal identity matrix\n");
	printf("Result: %s\n", mat_equal(product, ident) ? "PASS" : "FAIL");
	
	destroy_matrix(mat);
	destroy_matrix(inv);
	destroy_matrix(product);
	destroy_matrix(ident);
}

void	test_multiply_by_inverse(void)
{
	t_mat	a;
	t_mat	b;
	t_mat	c;
	t_mat	b_inv;
	t_mat	result;

	printf("\n=== TEST: C = A * B, then C * B^-1 = A ===\n");
	
	a = new_matrix(4, 4);
	set_data(a, 0, 0, 3.0);
	set_data(a, 0, 1, -9.0);
	set_data(a, 0, 2, 7.0);
	set_data(a, 0, 3, 3.0);
	set_data(a, 1, 0, 3.0);
	set_data(a, 1, 1, -8.0);
	set_data(a, 1, 2, 2.0);
	set_data(a, 1, 3, -9.0);
	set_data(a, 2, 0, -4.0);
	set_data(a, 2, 1, 4.0);
	set_data(a, 2, 2, 4.0);
	set_data(a, 2, 3, 1.0);
	set_data(a, 3, 0, -6.0);
	set_data(a, 3, 1, 5.0);
	set_data(a, 3, 2, -1.0);
	set_data(a, 3, 3, 1.0);
	
	b = new_matrix(4, 4);
	set_data(b, 0, 0, 8.0);
	set_data(b, 0, 1, 2.0);
	set_data(b, 0, 2, 2.0);
	set_data(b, 0, 3, 2.0);
	set_data(b, 1, 0, 3.0);
	set_data(b, 1, 1, -1.0);
	set_data(b, 1, 2, 7.0);
	set_data(b, 1, 3, 0.0);
	set_data(b, 2, 0, 7.0);
	set_data(b, 2, 1, 0.0);
	set_data(b, 2, 2, 5.0);
	set_data(b, 2, 3, 4.0);
	set_data(b, 3, 0, 6.0);
	set_data(b, 3, 1, -2.0);
	set_data(b, 3, 2, 0.0);
	set_data(b, 3, 3, 5.0);
	
	c = mat_mult(a, b);
	b_inv = inverse(b);
	result = mat_mult(c, b_inv);
	
	print_matrix(a, "Original A");
	print_matrix(result, "C * B^-1 (should equal A)");
	
	printf("\nResult: %s\n", mat_equal(a, result) ? "PASS" : "FAIL");
	
	destroy_matrix(a);
	destroy_matrix(b);
	destroy_matrix(c);
	destroy_matrix(b_inv);
	destroy_matrix(result);
}

void	test_singular_matrix(void)
{
	t_mat	mat;
	t_mat	inv;

	printf("\n=== TEST: Singular Matrix (should fail) ===\n");
	mat = new_matrix(4, 4);
	set_data(mat, 0, 0, 1.0);
	set_data(mat, 0, 1, 2.0);
	set_data(mat, 0, 2, 3.0);
	set_data(mat, 0, 3, 4.0);
	set_data(mat, 1, 0, 2.0);
	set_data(mat, 1, 1, 4.0);
	set_data(mat, 1, 2, 6.0);
	set_data(mat, 1, 3, 8.0);
	set_data(mat, 2, 0, 3.0);
	set_data(mat, 2, 1, 6.0);
	set_data(mat, 2, 2, 9.0);
	set_data(mat, 2, 3, 12.0);
	set_data(mat, 3, 0, 4.0);
	set_data(mat, 3, 1, 8.0);
	set_data(mat, 3, 2, 12.0);
	set_data(mat, 3, 3, 16.0);
	
	printf("Determinant: %.5f (should be 0)\n", determinant(mat));
	inv = inverse(mat);
	
	printf("Result: %s\n", inv.data == NULL ? "PASS (correctly returned NULL)" : "FAIL");
	
	destroy_matrix(mat);
}

int	main(void)
{
	printf("========================================\n");
	printf("  MATRIX INVERSION TEST SUITE\n");
	printf("========================================\n");
	
	test_determinant_2x2();
	test_submatrix_3x3();
	test_minor_and_cofactor();
	test_determinant_3x3();
	test_determinant_4x4();
	test_inverse_4x4();
	test_inverse_multiply_identity();
	test_multiply_by_inverse();
	test_singular_matrix();
	
	printf("\n========================================\n");
	printf("  TEST SUITE COMPLETE\n");
	printf("========================================\n");
	
	return (0);
}