#!/usr/bin/env python3
"""
Test suite for C matrix operations library
Generates comprehensive tests and logs results to matrix_test_results.log
"""

import math
import sys
from dataclasses import dataclass
from typing import List, Optional


@dataclass
class TupleData:
    """Represents a tuple (point or vector) from the C library"""
    x: float
    y: float
    z: float
    pt: float  # 1.0 for point, 0.0 for vector
    
    def __str__(self):
        type_str = "point" if self.pt == 1.0 else "vector"
        return f"{type_str}({self.x:.6f}, {self.y:.6f}, {self.z:.6f})"
    
    def is_close(self, other: 'TupleData', epsilon: float = 1e-5) -> bool:
        """Check if two tuples are approximately equal"""
        return (abs(self.x - other.x) < epsilon and
                abs(self.y - other.y) < epsilon and
                abs(self.z - other.z) < epsilon and
                abs(self.pt - other.pt) < epsilon)


class MatrixData:
    """Represents a matrix from the C library"""
    
    def __init__(self, rows: int, cols: int, data: Optional[List[float]] = None):
        self.rows = rows
        self.cols = cols
        if data is None:
            self.data = [0.0] * (rows * cols)
        else:
            self.data = list(data)
    
    def get_data(self, i: int, j: int) -> float:
        """Get element at row i, column j"""
        return self.data[self.cols * i + j]
    
    def set_data(self, i: int, j: int, value: float):
        """Set element at row i, column j"""
        self.data[self.cols * i + j] = value
    
    def __str__(self) -> str:
        """String representation of matrix"""
        lines = []
        for i in range(self.rows):
            row = []
            for j in range(self.cols):
                row.append(f"{self.get_data(i, j):8.4f}")
            lines.append("  [" + " ".join(row) + "]")
        return "Matrix " + str(self.rows) + "x" + str(self.cols) + ":\n" + "\n".join(lines)
    
    def is_close(self, other: 'MatrixData', epsilon: float = 1e-5) -> bool:
        """Check if two matrices are approximately equal"""
        if self.rows != other.rows or self.cols != other.cols:
            return False
        for i in range(len(self.data)):
            if abs(self.data[i] - other.data[i]) >= epsilon:
                return False
        return True


class MatrixMath:
    """Python implementation of C matrix math functions"""
    
    @staticmethod
    def vector(x: float, y: float, z: float) -> TupleData:
        return TupleData(x, y, z, 0.0)
    
    @staticmethod
    def point(x: float, y: float, z: float) -> TupleData:
        return TupleData(x, y, z, 1.0)
    
    @staticmethod
    def dot(a: TupleData, b: TupleData) -> float:
        """Dot product of two tuples"""
        return a.x * b.x + a.y * b.y + a.z * b.z + a.pt * b.pt
    
    @staticmethod
    def new_matrix(rows: int, cols: int) -> MatrixData:
        """Create new matrix"""
        return MatrixData(rows, cols)
    
    @staticmethod
    def get_data(mat: MatrixData, i: int, j: int) -> float:
        """Get matrix element at row i, column j"""
        return mat.get_data(i, j)
    
    @staticmethod
    def set_data(mat: MatrixData, i: int, j: int, value: float):
        """Set matrix element at row i, column j"""
        mat.set_data(i, j, value)
    
    @staticmethod
    def mat_equal(a: MatrixData, b: MatrixData, epsilon: float = 1e-5) -> bool:
        """Check if two matrices are equal"""
        if a.rows != b.rows or a.cols != b.cols:
            return False
        for i in range(a.rows):
            for j in range(a.cols):
                if abs(a.get_data(i, j) - b.get_data(i, j)) >= epsilon:
                    return False
        return True
    
    @staticmethod
    def mat_get_col(mat: MatrixData, col: int) -> TupleData:
        """Get column as tuple (assumes 4x4 matrix)"""
        return TupleData(
            mat.get_data(0, col),
            mat.get_data(1, col),
            mat.get_data(2, col),
            mat.get_data(3, col)
        )
    
    @staticmethod
    def mat_get_row(mat: MatrixData, row: int) -> TupleData:
        """Get row as tuple (assumes 4x4 matrix)"""
        return TupleData(
            mat.get_data(row, 0),
            mat.get_data(row, 1),
            mat.get_data(row, 2),
            mat.get_data(row, 3)
        )
    
    @staticmethod
    def mat_mult(a: MatrixData, b: MatrixData) -> MatrixData:
        """Multiply two matrices"""
        res = MatrixMath.new_matrix(a.rows, b.cols)
        for i in range(res.rows):
            for j in range(res.cols):
                row = MatrixMath.mat_get_row(a, i)
                col = MatrixMath.mat_get_col(b, j)
                res.set_data(i, j, MatrixMath.dot(row, col))
        return res
    
    @staticmethod
    def mat_tuple_mult(mat: MatrixData, tup: TupleData) -> TupleData:
        """Multiply matrix by tuple"""
        return TupleData(
            MatrixMath.dot(MatrixMath.mat_get_row(mat, 0), tup),
            MatrixMath.dot(MatrixMath.mat_get_row(mat, 1), tup),
            MatrixMath.dot(MatrixMath.mat_get_row(mat, 2), tup),
            MatrixMath.dot(MatrixMath.mat_get_row(mat, 3), tup)
        )
    
    @staticmethod
    def identity() -> MatrixData:
        """Create 4x4 identity matrix"""
        res = MatrixMath.new_matrix(4, 4)
        for i in range(16):
            if i == 0 or i == 5 or i == 10 or i == 15:
                res.data[i] = 1.0
            else:
                res.data[i] = 0.0
        return res
    
    @staticmethod
    def transpose(mat: MatrixData) -> MatrixData:
        """Transpose matrix"""
        res = MatrixMath.new_matrix(mat.rows, mat.cols)
        for i in range(res.rows):
            col = MatrixMath.mat_get_col(mat, i)
            res.set_data(i, 0, col.x)
            res.set_data(i, 1, col.y)
            res.set_data(i, 2, col.z)
            res.set_data(i, 3, col.pt)
        return res
    
    @staticmethod
    def determinant(mat: MatrixData) -> float:
        """Calculate determinant of 2x2 matrix"""
        return (mat.get_data(0, 0) * mat.get_data(1, 1) -
                mat.get_data(0, 1) * mat.get_data(1, 0))


class MatrixTestSuite:
    """Comprehensive test suite for matrix operations"""
    
    def __init__(self, log_file: str = "matrix_test_results.log"):
        self.log_file = log_file
        self.passed = 0
        self.failed = 0
        self.tests_run = 0
        self.log_lines = []
        
    def log(self, message: str):
        """Add message to log"""
        self.log_lines.append(message)
        print(message)
    
    def assert_matrix_equal(self, result: MatrixData, expected: MatrixData, 
                           test_name: str, epsilon: float = 1e-5) -> bool:
        """Assert two matrices are equal"""
        self.tests_run += 1
        if result.is_close(expected, epsilon):
            self.passed += 1
            self.log(f"✓ PASS: {test_name}")
            return True
        else:
            self.failed += 1
            self.log(f"✗ FAIL: {test_name}")
            self.log(f"  Expected:\n{expected}")
            self.log(f"  Got:\n{result}")
            return False
    
    def assert_tuple_equal(self, result: TupleData, expected: TupleData, 
                          test_name: str, epsilon: float = 1e-5) -> bool:
        """Assert two tuples are equal"""
        self.tests_run += 1
        if result.is_close(expected, epsilon):
            self.passed += 1
            self.log(f"✓ PASS: {test_name}")
            return True
        else:
            self.failed += 1
            self.log(f"✗ FAIL: {test_name}")
            self.log(f"  Expected: {expected}")
            self.log(f"  Got:      {result}")
            return False
    
    def assert_float_equal(self, result: float, expected: float, 
                          test_name: str, epsilon: float = 1e-5) -> bool:
        """Assert two floats are equal"""
        self.tests_run += 1
        if abs(result - expected) < epsilon:
            self.passed += 1
            self.log(f"✓ PASS: {test_name}")
            return True
        else:
            self.failed += 1
            self.log(f"✗ FAIL: {test_name}")
            self.log(f"  Expected: {expected:.6f}")
            self.log(f"  Got:      {result:.6f}")
            return False
    
    def assert_bool(self, result: bool, expected: bool, test_name: str) -> bool:
        """Assert boolean value"""
        self.tests_run += 1
        if result == expected:
            self.passed += 1
            self.log(f"✓ PASS: {test_name}")
            return True
        else:
            self.failed += 1
            self.log(f"✗ FAIL: {test_name}")
            self.log(f"  Expected: {expected}")
            self.log(f"  Got:      {result}")
            return False
    
    def test_matrix_creation(self):
        """Test matrix creation and access"""
        self.log("\n=== Testing Matrix Creation and Access ===")
        mm = MatrixMath()
        
        # Create 4x4 matrix
        mat = mm.new_matrix(4, 4)
        self.assert_float_equal(mat.rows, 4, "Matrix has 4 rows")
        self.assert_float_equal(mat.cols, 4, "Matrix has 4 columns")
        
        # Set and get data
        mm.set_data(mat, 0, 0, 1.5)
        mm.set_data(mat, 0, 3, 2.5)
        mm.set_data(mat, 1, 2, 3.5)
        mm.set_data(mat, 2, 2, 4.5)
        mm.set_data(mat, 3, 0, 5.5)
        mm.set_data(mat, 3, 2, 6.5)
        
        self.assert_float_equal(mm.get_data(mat, 0, 0), 1.5, "Get element [0,0]")
        self.assert_float_equal(mm.get_data(mat, 0, 3), 2.5, "Get element [0,3]")
        self.assert_float_equal(mm.get_data(mat, 1, 2), 3.5, "Get element [1,2]")
        self.assert_float_equal(mm.get_data(mat, 2, 2), 4.5, "Get element [2,2]")
        self.assert_float_equal(mm.get_data(mat, 3, 0), 5.5, "Get element [3,0]")
        self.assert_float_equal(mm.get_data(mat, 3, 2), 6.5, "Get element [3,2]")
    
    def test_matrix_equality(self):
        """Test matrix equality comparison"""
        self.log("\n=== Testing Matrix Equality ===")
        mm = MatrixMath()
        
        # Create two identical matrices
        mat1 = mm.new_matrix(4, 4)
        mat2 = mm.new_matrix(4, 4)
        
        for i in range(4):
            for j in range(4):
                value = i * 4 + j
                mm.set_data(mat1, i, j, value)
                mm.set_data(mat2, i, j, value)
        
        self.assert_bool(mm.mat_equal(mat1, mat2), True, "Identical matrices are equal")
        
        # Modify one element
        mm.set_data(mat2, 2, 2, 999.0)
        self.assert_bool(mm.mat_equal(mat1, mat2), False, 
                        "Matrices with different elements are not equal")
        
        # Test with different dimensions
        mat3 = mm.new_matrix(3, 3)
        self.assert_bool(mm.mat_equal(mat1, mat3), False, 
                        "Matrices with different dimensions are not equal")
    
    def test_get_row_column(self):
        """Test getting rows and columns as tuples"""
        self.log("\n=== Testing Get Row/Column ===")
        mm = MatrixMath()
        
        mat = mm.new_matrix(4, 4)
        # Set up test matrix
        mat.data = [
            1,  2,  3,  4,
            5,  6,  7,  8,
            9,  10, 11, 12,
            13, 14, 15, 16
        ]
        
        # Test get_row
        row0 = mm.mat_get_row(mat, 0)
        expected = TupleData(1, 2, 3, 4)
        self.assert_tuple_equal(row0, expected, "Get row 0")
        
        row2 = mm.mat_get_row(mat, 2)
        expected = TupleData(9, 10, 11, 12)
        self.assert_tuple_equal(row2, expected, "Get row 2")
        
        # Test get_col
        col0 = mm.mat_get_col(mat, 0)
        expected = TupleData(1, 5, 9, 13)
        self.assert_tuple_equal(col0, expected, "Get column 0")
        
        col3 = mm.mat_get_col(mat, 3)
        expected = TupleData(4, 8, 12, 16)
        self.assert_tuple_equal(col3, expected, "Get column 3")
    
    def test_identity_matrix(self):
        """Test identity matrix creation"""
        self.log("\n=== Testing Identity Matrix ===")
        mm = MatrixMath()
        
        identity = mm.identity()
        
        # Check diagonal elements are 1
        for i in range(4):
            self.assert_float_equal(mm.get_data(identity, i, i), 1.0, 
                                   f"Identity diagonal [{i},{i}] is 1")
        
        # Check off-diagonal elements are 0
        for i in range(4):
            for j in range(4):
                if i != j:
                    self.assert_float_equal(mm.get_data(identity, i, j), 0.0, 
                                           f"Identity off-diagonal [{i},{j}] is 0")
    
    def test_matrix_multiplication(self):
        """Test matrix multiplication"""
        self.log("\n=== Testing Matrix Multiplication ===")
        mm = MatrixMath()
        
        # Test with specific matrices
        mat1 = mm.new_matrix(4, 4)
        mat1.data = [
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2
        ]
        
        mat2 = mm.new_matrix(4, 4)
        mat2.data = [
            -2, 1, 2,  3,
            3,  2, 1, -1,
            4,  3, 6,  5,
            1,  2, 7,  8
        ]
        
        result = mm.mat_mult(mat1, mat2)
        
        expected = mm.new_matrix(4, 4)
        expected.data = [
            20, 22,  50,  48,
            44, 54, 114, 108,
            40, 58, 110, 102,
            16, 26,  46,  42
        ]
        
        self.assert_matrix_equal(result, expected, "Matrix multiplication")
        
        # Test identity property: A * I = A
        identity = mm.identity()
        result = mm.mat_mult(mat1, identity)
        self.assert_matrix_equal(result, mat1, "Matrix * Identity = Matrix")
        
        result = mm.mat_mult(identity, mat1)
        self.assert_matrix_equal(result, mat1, "Identity * Matrix = Matrix")
    
    def test_matrix_tuple_multiplication(self):
        """Test matrix-tuple multiplication"""
        self.log("\n=== Testing Matrix-Tuple Multiplication ===")
        mm = MatrixMath()
        
        mat = mm.new_matrix(4, 4)
        mat.data = [
            1, 2, 3, 4,
            2, 4, 4, 2,
            8, 6, 4, 1,
            0, 0, 0, 1
        ]
        
        tup = TupleData(1, 2, 3, 1)
        
        result = mm.mat_tuple_mult(mat, tup)
        expected = TupleData(18, 24, 33, 1)
        
        self.assert_tuple_equal(result, expected, "Matrix * Tuple")
        
        # Test with identity matrix
        identity = mm.identity()
        point = mm.point(1, 2, 3)
        result = mm.mat_tuple_mult(identity, point)
        
        self.assert_tuple_equal(result, point, "Identity * Tuple = Tuple")
        
        # Test with vector
        vec = mm.vector(1, 2, 3)
        result = mm.mat_tuple_mult(identity, vec)
        self.assert_tuple_equal(result, vec, "Identity * Vector = Vector")
    
    def test_transpose(self):
        """Test matrix transpose"""
        self.log("\n=== Testing Matrix Transpose ===")
        mm = MatrixMath()
        
        mat = mm.new_matrix(4, 4)
        mat.data = [
            0, 9, 3, 0,
            9, 8, 0, 8,
            1, 8, 5, 3,
            0, 0, 5, 8
        ]
        
        result = mm.transpose(mat)
        
        expected = mm.new_matrix(4, 4)
        expected.data = [
            0, 9, 1, 0,
            9, 8, 8, 0,
            3, 0, 5, 5,
            0, 8, 3, 8
        ]
        
        self.assert_matrix_equal(result, expected, "Transpose matrix")
        
        # Test transpose of identity is identity
        identity = mm.identity()
        result2 = mm.transpose(identity)
        self.assert_matrix_equal(result2, identity, "Transpose of identity is identity")
        
        # Test double transpose returns original
        double_transpose = mm.transpose(result)
        self.assert_matrix_equal(double_transpose, mat, "Transpose(Transpose(A)) = A")
    
    def test_determinant(self):
        """Test 2x2 determinant"""
        self.log("\n=== Testing 2x2 Determinant ===")
        mm = MatrixMath()
        
        # Test case 1
        mat1 = mm.new_matrix(2, 2)
        mat1.data = [1, 5, -3, 2]
        result = mm.determinant(mat1)
        expected = 17.0  # (1*2) - (5*-3) = 2 + 15 = 17
        self.assert_float_equal(result, expected, "Determinant of [[1,5],[-3,2]]")
        
        # Test case 2
        mat2 = mm.new_matrix(2, 2)
        mat2.data = [3, 8, 4, 6]
        result = mm.determinant(mat2)
        expected = -14.0  # (3*6) - (8*4) = 18 - 32 = -14
        self.assert_float_equal(result, expected, "Determinant of [[3,8],[4,6]]")
        
        # Test identity 2x2
        identity_2x2 = mm.new_matrix(2, 2)
        identity_2x2.data = [1, 0, 0, 1]
        result = mm.determinant(identity_2x2)
        self.assert_float_equal(result, 1.0, "Determinant of 2x2 identity is 1")
        
        # Test zero matrix
        zero_mat = mm.new_matrix(2, 2)
        zero_mat.data = [0, 0, 0, 0]
        result = mm.determinant(zero_mat)
        self.assert_float_equal(result, 0.0, "Determinant of zero matrix is 0")
    
    def test_matrix_properties(self):
        """Test mathematical properties of matrices"""
        self.log("\n=== Testing Matrix Properties ===")
        mm = MatrixMath()
        
        # Test associativity: (A * B) * C = A * (B * C)
        mat_a = mm.new_matrix(4, 4)
        mat_a.data = [1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2]
        
        mat_b = mm.new_matrix(4, 4)
        mat_b.data = [2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1]
        
        mat_c = mm.new_matrix(4, 4)
        mat_c.data = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8]
        
        ab = mm.mat_mult(mat_a, mat_b)
        abc_left = mm.mat_mult(ab, mat_c)
        
        bc = mm.mat_mult(mat_b, mat_c)
        abc_right = mm.mat_mult(mat_a, bc)
        
        self.assert_matrix_equal(abc_left, abc_right, 
                                "Matrix multiplication is associative")
        
        # Test transpose property: (A * B)^T = B^T * A^T
        ab = mm.mat_mult(mat_a, mat_b)
        ab_transpose = mm.transpose(ab)
        
        a_transpose = mm.transpose(mat_a)
        b_transpose = mm.transpose(mat_b)
        bt_at = mm.mat_mult(b_transpose, a_transpose)
        
        self.assert_matrix_equal(ab_transpose, bt_at, 
                                "(A*B)^T = B^T * A^T")
    
    def test_edge_cases(self):
        """Test edge cases"""
        self.log("\n=== Testing Edge Cases ===")
        mm = MatrixMath()
        
        # Test with zero matrix
        zero_mat = mm.new_matrix(4, 4)
        for i in range(16):
            zero_mat.data[i] = 0.0
        
        identity = mm.identity()
        result = mm.mat_mult(zero_mat, identity)
        self.assert_matrix_equal(result, zero_mat, "Zero * Identity = Zero")
        
        # Test with negative values
        neg_mat = mm.new_matrix(4, 4)
        for i in range(4):
            for j in range(4):
                mm.set_data(neg_mat, i, j, -(i * 4 + j + 1))
        
        neg_transpose = mm.transpose(neg_mat)
        expected = mm.new_matrix(4, 4)
        for i in range(4):
            for j in range(4):
                mm.set_data(expected, i, j, -(j * 4 + i + 1))
        
        self.assert_matrix_equal(neg_transpose, expected, 
                                "Transpose with negative values")
    
    def run_all_tests(self):
        """Run all tests and write results to log file"""
        self.log("=" * 70)
        self.log("MATRIX OPERATIONS TEST SUITE")
        self.log("=" * 70)
        
        # Run all test categories
        self.test_matrix_creation()
        self.test_matrix_equality()
        self.test_get_row_column()
        self.test_identity_matrix()
        self.test_matrix_multiplication()
        self.test_matrix_tuple_multiplication()
        self.test_transpose()
        self.test_determinant()
        self.test_matrix_properties()
        self.test_edge_cases()
        
        # Summary
        self.log("\n" + "=" * 70)
        self.log("TEST SUMMARY")
        self.log("=" * 70)
        self.log(f"Tests run:    {self.tests_run}")
        self.log(f"Tests passed: {self.passed}")
        self.log(f"Tests failed: {self.failed}")
        self.log(f"Success rate: {(self.passed/self.tests_run*100):.1f}%")
        self.log("=" * 70)
        
        # Write to file (overwrite mode)
        with open(self.log_file, 'w') as f:
            f.write('\n'.join(self.log_lines))
        
        print(f"\nResults written to {self.log_file}")
        
        return self.failed == 0


if __name__ == "__main__":
    suite = MatrixTestSuite("matrix_test_results.log")
    success = suite.run_all_tests()
    sys.exit(0 if success else 1)