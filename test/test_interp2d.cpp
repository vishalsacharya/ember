#include "../src/quasi2d.h"

#include "gtest/gtest.h"


/* Data generated in Python:
    from scipy import interpolate
    x = np.array([0, 0.2, 0.8, 1.0])
    y = np.array([-2.0,-1.0,0.0,1.0,2.0])
    X, Y = np.meshgrid(x, y)
    D = (Y*Y + 3 * X) * (2 - X)
*/

class TestBilinearInterpolator : public testing::Test
{
public:
    TestBilinearInterpolator()
    {
        dmatrix data(5,4);

        data << 8.0, 8.28, 7.68, 7.0,
                2.0, 2.88, 4.08, 4.0,
                0.0, 1.08, 2.88, 3.0,
                2.0, 2.88, 4.08, 4.0,
                8.0, 8.28, 7.68, 7.0;
        dvector x(4);
        x[0] = 0.0;
        x[1] = 0.2;
        x[2] = 0.8;
        x[3] = 1.0;

        dvector y(5);
        y[0] = -2.0;
        y[1] = -1.0;
        y[2] = 0.0;
        y[3] = 1.0;
        y[4] = 2.0;

        interp.setup(data, x, y);
    }

    BilinearInterpolator interp;
};

TEST_F(TestBilinearInterpolator, AtGridPointsPlus)
{
    double eps = 1e-12;
    double tol = 1e-10;
    EXPECT_NEAR(0.00, interp.get(0.0 + eps, 0.0 + eps), tol);
    EXPECT_NEAR(2.88, interp.get(0.2 + eps, 1.0 + eps), tol);
    EXPECT_NEAR(7.68, interp.get(0.8 + eps, -2.0 + eps), tol);
    EXPECT_NEAR(2.88, interp.get(0.8 + eps, 0.0 + eps), tol);
    EXPECT_NEAR(7.00, interp.get(1.0 + eps, 2.0 + eps), tol);
}

TEST_F(TestBilinearInterpolator, AtGridPointsMinus)
{
    double eps = 1e-12;
    double tol = 1e-10;
    EXPECT_NEAR(0.00, interp.get(0.0 - eps, 0.0 - eps), tol);
    EXPECT_NEAR(2.88, interp.get(0.2 - eps, 1.0 - eps), tol);
    EXPECT_NEAR(7.68, interp.get(0.8 - eps, -2.0 - eps), tol);
    EXPECT_NEAR(2.88, interp.get(0.8 - eps, 0.0 - eps), tol);
    EXPECT_NEAR(7.00, interp.get(1.0 - eps, 2.0 - eps), tol);
}

TEST_F(TestBilinearInterpolator, IntermediatePointsX)
{
    EXPECT_FLOAT_EQ(3.28, interp.get(0.4, -1.0));
    EXPECT_FLOAT_EQ(3.28, interp.get(0.4, 1.0));
    EXPECT_FLOAT_EQ(3.98, interp.get(0.75, -1.0));
    EXPECT_FLOAT_EQ(3.98, interp.get(0.75, 1.0));
    EXPECT_FLOAT_EQ(0.054, interp.get(0.01, 0.0));
    EXPECT_FLOAT_EQ(0.27, interp.get(0.05, 0.0));
    EXPECT_FLOAT_EQ(1.026, interp.get(0.19, 0.0));
}

TEST_F(TestBilinearInterpolator, IntermediatePointsY)
{
    EXPECT_FLOAT_EQ(5.0, interp.get(0.0, -1.5));
    EXPECT_FLOAT_EQ(3.5, interp.get(0.0, -1.25));
    EXPECT_FLOAT_EQ(1.0, interp.get(0.0, -0.5));
    EXPECT_FLOAT_EQ(1.0, interp.get(0.0, 0.5));
    EXPECT_FLOAT_EQ(4.44, interp.get(0.8, 1.1));
    EXPECT_FLOAT_EQ(7.32, interp.get(0.8, 1.9));
}

TEST_F(TestBilinearInterpolator, IntermediatePointsXY)
{
    EXPECT_FLOAT_EQ(5.29, interp.get(0.1, -1.5));
    EXPECT_FLOAT_EQ(2.73, interp.get(0.5, 0.5));
    EXPECT_FLOAT_EQ(5.69, interp.get(0.9, 1.5));
}

TEST_F(TestBilinearInterpolator, Extrapolation)
{
    EXPECT_FLOAT_EQ(-1.08, interp.get(-0.2, 0.0));
    EXPECT_FLOAT_EQ(0.24, interp.get(-0.4, 1.0));
    EXPECT_FLOAT_EQ(3.92, interp.get(1.2, -1.0));
    EXPECT_FLOAT_EQ(14.0, interp.get(0.0, 3.0));
    EXPECT_FLOAT_EQ(14.0, interp.get(0.0, -3.0));
}