#!/usr/bin/env python3
"""
Test suite for C vector/tuple mathematics library
Generates comprehensive tests and logs results to test_results.log
"""

import math
import sys
from dataclasses import dataclass
from typing import List, Tuple, Callable


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


class VectorMath:
    """Python implementation of the C vector math functions"""
    
    @staticmethod
    def point(x: float, y: float, z: float) -> TupleData:
        return TupleData(x, y, z, 1.0)
    
    @staticmethod
    def vector(x: float, y: float, z: float) -> TupleData:
        return TupleData(x, y, z, 0.0)
    
    @staticmethod
    def add_tuples(a: TupleData, b: TupleData) -> TupleData:
        return TupleData(a.x + b.x, a.y + b.y, a.z + b.z, a.pt + b.pt)
    
    @staticmethod
    def substr_tuples(a: TupleData, b: TupleData) -> TupleData:
        return TupleData(a.x - b.x, a.y - b.y, a.z - b.z, a.pt - b.pt)
    
    @staticmethod
    def neg_tuples(a: TupleData) -> TupleData:
        zero = VectorMath.vector(0, 0, 0)
        return VectorMath.substr_tuples(zero, a)
    
    @staticmethod
    def mult_vec_scalar(vec: TupleData, scalar: float) -> TupleData:
        return TupleData(vec.x * scalar, vec.y * scalar, 
                        vec.z * scalar, vec.pt * scalar)
    
    @staticmethod
    def vec_magnitude(vec: TupleData) -> float:
        sum_val = vec.x**2 + vec.y**2 + vec.z**2 + vec.pt**2
        return math.sqrt(sum_val)
    
    @staticmethod
    def vec_normalise(vec: TupleData) -> TupleData:
        mag = VectorMath.vec_magnitude(vec)
        if mag == 0:
            return vec
        return TupleData(vec.x / mag, vec.y / mag, 
                        vec.z / mag, vec.pt / mag)
    
    @staticmethod
    def dot(a: TupleData, b: TupleData) -> float:
        return a.x * b.x + a.y * b.y + a.z * b.z + a.pt * b.pt
    
    @staticmethod
    def cross_product(a: TupleData, b: TupleData) -> TupleData:
        return VectorMath.vector(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        )


class TestSuite:
    """Comprehensive test suite for vector operations"""
    
    def __init__(self, log_file: str = "test_results.log"):
        self.log_file = log_file
        self.passed = 0
        self.failed = 0
        self.tests_run = 0
        self.log_lines = []
        
    def log(self, message: str):
        """Add message to log"""
        self.log_lines.append(message)
        print(message)
    
    def assert_tuple_equal(self, result: TupleData, expected: TupleData, 
                          test_name: str, epsilon: float = 1e-5) -> bool:
        """Assert two tuples are equal within epsilon"""
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
        """Assert two floats are equal within epsilon"""
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
    
    def test_point_creation(self):
        """Test point creation"""
        self.log("\n=== Testing Point Creation ===")
        vm = VectorMath()
        
        p = vm.point(4.3, -4.2, 3.1)
        self.assert_float_equal(p.x, 4.3, "Point x coordinate")
        self.assert_float_equal(p.y, -4.2, "Point y coordinate")
        self.assert_float_equal(p.z, 3.1, "Point z coordinate")
        self.assert_float_equal(p.pt, 1.0, "Point pt flag is 1.0")
    
    def test_vector_creation(self):
        """Test vector creation"""
        self.log("\n=== Testing Vector Creation ===")
        vm = VectorMath()
        
        v = vm.vector(4.3, -4.2, 3.1)
        self.assert_float_equal(v.x, 4.3, "Vector x coordinate")
        self.assert_float_equal(v.y, -4.2, "Vector y coordinate")
        self.assert_float_equal(v.z, 3.1, "Vector z coordinate")
        self.assert_float_equal(v.pt, 0.0, "Vector pt flag is 0.0")
    
    def test_tuple_addition(self):
        """Test tuple addition"""
        self.log("\n=== Testing Tuple Addition ===")
        vm = VectorMath()
        
        # Point + Vector = Point
        p1 = vm.point(3, 2, 1)
        v1 = vm.vector(5, 6, 7)
        result = vm.add_tuples(p1, v1)
        expected = vm.point(8, 8, 8)
        self.assert_tuple_equal(result, expected, "Point + Vector")
        
        # Vector + Vector = Vector
        v2 = vm.vector(3, 2, 1)
        v3 = vm.vector(5, 6, 7)
        result = vm.add_tuples(v2, v3)
        expected = vm.vector(8, 8, 8)
        self.assert_tuple_equal(result, expected, "Vector + Vector")
        
        # Adding negative numbers
        p2 = vm.point(1.5, -2.3, 4.7)
        v4 = vm.vector(-1.0, 0.5, -3.2)
        result = vm.add_tuples(p2, v4)
        expected = vm.point(0.5, -1.8, 1.5)
        self.assert_tuple_equal(result, expected, "Point + Vector with negatives")
    
    def test_tuple_subtraction(self):
        """Test tuple subtraction"""
        self.log("\n=== Testing Tuple Subtraction ===")
        vm = VectorMath()
        
        # Point - Point = Vector
        p1 = vm.point(3, 2, 1)
        p2 = vm.point(5, 6, 7)
        result = vm.substr_tuples(p1, p2)
        expected = vm.vector(-2, -4, -6)
        self.assert_tuple_equal(result, expected, "Point - Point")
        
        # Point - Vector = Point
        p3 = vm.point(3, 2, 1)
        v1 = vm.vector(5, 6, 7)
        result = vm.substr_tuples(p3, v1)
        expected = vm.point(-2, -4, -6)
        self.assert_tuple_equal(result, expected, "Point - Vector")
        
        # Vector - Vector = Vector
        v2 = vm.vector(3, 2, 1)
        v3 = vm.vector(5, 6, 7)
        result = vm.substr_tuples(v2, v3)
        expected = vm.vector(-2, -4, -6)
        self.assert_tuple_equal(result, expected, "Vector - Vector")
    
    def test_tuple_negation(self):
        """Test tuple negation"""
        self.log("\n=== Testing Tuple Negation ===")
        vm = VectorMath()
        
        # Negate vector
        v1 = vm.vector(1, -2, 3)
        result = vm.neg_tuples(v1)
        expected = vm.vector(-1, 2, -3)
        self.assert_tuple_equal(result, expected, "Negate vector")
        
        # Negate point
        p1 = vm.point(1, -2, 3)
        result = vm.neg_tuples(p1)
        expected = TupleData(-1, 2, -3, -1.0)
        self.assert_tuple_equal(result, expected, "Negate point")
        
        # Negate zero vector
        v2 = vm.vector(0, 0, 0)
        result = vm.neg_tuples(v2)
        expected = vm.vector(0, 0, 0)
        self.assert_tuple_equal(result, expected, "Negate zero vector")
    
    def test_scalar_multiplication(self):
        """Test scalar multiplication"""
        self.log("\n=== Testing Scalar Multiplication ===")
        vm = VectorMath()
        
        # Multiply by positive scalar
        v1 = vm.vector(1, -2, 3)
        result = vm.mult_vec_scalar(v1, 3.5)
        expected = vm.vector(3.5, -7, 10.5)
        self.assert_tuple_equal(result, expected, "Vector * 3.5")
        
        # Multiply by fraction
        v2 = vm.vector(1, -2, 3)
        result = vm.mult_vec_scalar(v2, 0.5)
        expected = vm.vector(0.5, -1, 1.5)
        self.assert_tuple_equal(result, expected, "Vector * 0.5")
        
        # Multiply by zero
        v3 = vm.vector(1, -2, 3)
        result = vm.mult_vec_scalar(v3, 0)
        expected = vm.vector(0, 0, 0)
        self.assert_tuple_equal(result, expected, "Vector * 0")
        
        # Multiply by negative
        v4 = vm.vector(1, -2, 3)
        result = vm.mult_vec_scalar(v4, -1)
        expected = vm.vector(-1, 2, -3)
        self.assert_tuple_equal(result, expected, "Vector * -1")
    
    def test_magnitude(self):
        """Test vector magnitude"""
        self.log("\n=== Testing Vector Magnitude ===")
        vm = VectorMath()
        
        # Unit vectors
        v1 = vm.vector(1, 0, 0)
        self.assert_float_equal(vm.vec_magnitude(v1), 1.0, "Magnitude of (1,0,0)")
        
        v2 = vm.vector(0, 1, 0)
        self.assert_float_equal(vm.vec_magnitude(v2), 1.0, "Magnitude of (0,1,0)")
        
        v3 = vm.vector(0, 0, 1)
        self.assert_float_equal(vm.vec_magnitude(v3), 1.0, "Magnitude of (0,0,1)")
        
        # Non-unit vectors
        v4 = vm.vector(1, 2, 3)
        self.assert_float_equal(vm.vec_magnitude(v4), math.sqrt(14), 
                               "Magnitude of (1,2,3)")
        
        v5 = vm.vector(-1, -2, -3)
        self.assert_float_equal(vm.vec_magnitude(v5), math.sqrt(14), 
                               "Magnitude of (-1,-2,-3)")
        
        # Zero vector
        v6 = vm.vector(0, 0, 0)
        self.assert_float_equal(vm.vec_magnitude(v6), 0.0, "Magnitude of zero vector")
    
    def test_normalization(self):
        """Test vector normalization"""
        self.log("\n=== Testing Vector Normalization ===")
        vm = VectorMath()
        
        # Normalize (4, 0, 0) to (1, 0, 0)
        v1 = vm.vector(4, 0, 0)
        result = vm.vec_normalise(v1)
        expected = vm.vector(1, 0, 0)
        self.assert_tuple_equal(result, expected, "Normalize (4,0,0)")
        
        # Normalize (1, 2, 3)
        v2 = vm.vector(1, 2, 3)
        result = vm.vec_normalise(v2)
        mag = math.sqrt(14)
        expected = vm.vector(1/mag, 2/mag, 3/mag)
        self.assert_tuple_equal(result, expected, "Normalize (1,2,3)")
        
        # Magnitude of normalized vector should be 1
        v3 = vm.vector(1, 2, 3)
        normalized = vm.vec_normalise(v3)
        mag = vm.vec_magnitude(normalized)
        self.assert_float_equal(mag, 1.0, "Magnitude of normalized vector is 1")
        
        # Normalize already normalized vector
        v4 = vm.vector(1, 0, 0)
        result = vm.vec_normalise(v4)
        expected = vm.vector(1, 0, 0)
        self.assert_tuple_equal(result, expected, "Normalize unit vector")
    
    def test_dot_product(self):
        """Test dot product"""
        self.log("\n=== Testing Dot Product ===")
        vm = VectorMath()
        
        # Perpendicular vectors (dot product = 0)
        v1 = vm.vector(1, 0, 0)
        v2 = vm.vector(0, 1, 0)
        self.assert_float_equal(vm.dot(v1, v2), 0.0, 
                               "Dot product of perpendicular vectors")
        
        # Parallel vectors
        v3 = vm.vector(1, 2, 3)
        v4 = vm.vector(2, 4, 6)
        self.assert_float_equal(vm.dot(v3, v4), 28.0, 
                               "Dot product of parallel vectors")
        
        # General case
        v5 = vm.vector(1, 2, 3)
        v6 = vm.vector(2, 3, 4)
        self.assert_float_equal(vm.dot(v5, v6), 20.0, 
                               "Dot product of (1,2,3) and (2,3,4)")
        
        # Dot product with itself
        v7 = vm.vector(1, 2, 3)
        result = vm.dot(v7, v7)
        expected = vm.vec_magnitude(v7) ** 2
        self.assert_float_equal(result, expected, "Dot product with itself")
        
        # Dot product is commutative
        v8 = vm.vector(1, 2, 3)
        v9 = vm.vector(4, 5, 6)
        result1 = vm.dot(v8, v9)
        result2 = vm.dot(v9, v8)
        self.assert_float_equal(result1, result2, "Dot product is commutative")
    
    def test_cross_product(self):
        """Test cross product"""
        self.log("\n=== Testing Cross Product ===")
        vm = VectorMath()
        
        # Standard basis vectors
        v1 = vm.vector(1, 0, 0)
        v2 = vm.vector(0, 1, 0)
        result = vm.cross_product(v1, v2)
        expected = vm.vector(0, 0, 1)
        self.assert_tuple_equal(result, expected, "Cross (1,0,0) x (0,1,0)")
        
        # Reverse order should negate result
        result2 = vm.cross_product(v2, v1)
        expected2 = vm.vector(0, 0, -1)
        self.assert_tuple_equal(result2, expected2, "Cross (0,1,0) x (1,0,0)")
        
        # General case
        v3 = vm.vector(1, 2, 3)
        v4 = vm.vector(2, 3, 4)
        result = vm.cross_product(v3, v4)
        expected = vm.vector(-1, 2, -1)
        self.assert_tuple_equal(result, expected, "Cross (1,2,3) x (2,3,4)")
        
        # Cross product of parallel vectors is zero
        v5 = vm.vector(1, 2, 3)
        v6 = vm.vector(2, 4, 6)
        result = vm.cross_product(v5, v6)
        expected = vm.vector(0, 0, 0)
        self.assert_tuple_equal(result, expected, "Cross product of parallel vectors")
        
        # Cross product is perpendicular to both vectors
        v7 = vm.vector(1, 2, 3)
        v8 = vm.vector(2, 3, 4)
        cross = vm.cross_product(v7, v8)
        dot1 = vm.dot(cross, v7)
        dot2 = vm.dot(cross, v8)
        self.assert_float_equal(dot1, 0.0, "Cross product perpendicular to first vector")
        self.assert_float_equal(dot2, 0.0, "Cross product perpendicular to second vector")
    
    def test_edge_cases(self):
        """Test edge cases and special scenarios"""
        self.log("\n=== Testing Edge Cases ===")
        vm = VectorMath()
        
        # Very small numbers
        v1 = vm.vector(1e-10, 1e-10, 1e-10)
        v2 = vm.vector(1e-10, 1e-10, 1e-10)
        result = vm.add_tuples(v1, v2)
        expected = vm.vector(2e-10, 2e-10, 2e-10)
        self.assert_tuple_equal(result, expected, "Addition with very small numbers", 1e-15)
        
        # Very large numbers
        v3 = vm.vector(1e10, 1e10, 1e10)
        v4 = vm.vector(1e10, 1e10, 1e10)
        result = vm.add_tuples(v3, v4)
        expected = vm.vector(2e10, 2e10, 2e10)
        self.assert_tuple_equal(result, expected, "Addition with very large numbers", 1e5)
        
        # Mixed signs
        v5 = vm.vector(5, -3, 2)
        v6 = vm.vector(-2, 3, -1)
        result = vm.add_tuples(v5, v6)
        expected = vm.vector(3, 0, 1)
        self.assert_tuple_equal(result, expected, "Addition with mixed signs")
    
    def run_all_tests(self):
        """Run all tests and write results to log file"""
        self.log("=" * 70)
        self.log("VECTOR MATHEMATICS TEST SUITE")
        self.log("=" * 70)
        
        # Run all test categories
        self.test_point_creation()
        self.test_vector_creation()
        self.test_tuple_addition()
        self.test_tuple_subtraction()
        self.test_tuple_negation()
        self.test_scalar_multiplication()
        self.test_magnitude()
        self.test_normalization()
        self.test_dot_product()
        self.test_cross_product()
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
    suite = TestSuite("test_results.log")
    success = suite.run_all_tests()
    sys.exit(0 if success else 1)