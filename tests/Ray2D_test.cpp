#include "gtest/gtest.h"
#include "ray2d.h"
#include "box2d.h"
#include <sstream>
#include <unordered_set>

TEST(test_ray, test_construction)
{
  //Default creation
  Ray2D r1;
  EXPECT_EQ(r1.x0(), 0.0f);
  EXPECT_EQ(r1.y0(), 0.0f);
  EXPECT_EQ(r1.GetDirect(0), 0.0f);
  EXPECT_EQ(r1.GetDirect(1), 0.0f);


  //Create the ray with angle parametrization
  Ray2D r2(1.0f, 2.0f, pi()/2.0f);
  EXPECT_EQ(r2.x0(), 1.0f);
  EXPECT_EQ(r2.y0(), 2.0f);
  EXPECT_EQ(r2.GetDirect(0), 0.0f);
  EXPECT_EQ(r2.GetDirect(1), 1.0f);

  //Create the ray
  Ray2D r3(1.0f, 2.0f, 4.0f, 6.0f);
  EXPECT_EQ(r3.x0(), 1.0f);
  EXPECT_EQ(r3.y0(), 2.0f);
  EXPECT_EQ(r3.GetDirect(0), 0.6f);
  EXPECT_EQ(r3.GetDirect(1), 0.8f);

  Ray2D r4=r3;
  EXPECT_EQ(r4, r3);
}

TEST(test_ray, test_initializer_list)
{
  Ray2D r5={1.0f, 2.0f, 4.0f, 6.0f};
  EXPECT_EQ(r5.x0(), 1.0f);
  EXPECT_EQ(r5.y0(), 2.0f);
  EXPECT_EQ(r5.GetDirect(0), 0.6f);
  EXPECT_EQ(r5.GetDirect(1), 0.8f);

  Ray2D r6={1.0f, 2.0f, pi()/3.0f};
  EXPECT_EQ(r6.x0(), 1.0f);
  EXPECT_EQ(r6.y0(), 2.0f);
  EXPECT_EQ(r6.GetDirect(0), 0.5f);
  EXPECT_EQ(r6.GetDirect(1), 0.866f);

  Ray2D r7={1.0f, 2.0f};
  EXPECT_EQ(r7.x0(), 1.0f);
  EXPECT_EQ(r7.y0(), 2.0f);
  EXPECT_EQ(r7.GetDirect(0), 0.0f);
  EXPECT_EQ(r7.GetDirect(1), 0.0f);
}

TEST(test_ray, test_movement)
{
  Ray2D r8(1.0f, 2.0f, pi()/2.0f);
  Ray2D r9(std::move(r8));
  EXPECT_EQ(r9.x0(), 1.0f);
  EXPECT_EQ(r9.y0(), 2.0f);
  EXPECT_EQ(r9.GetDirect(0), 0.0f);
  EXPECT_EQ(r9.GetDirect(1), 1.0f);

  Ray2D r10(1.0f, 2.0f, 4.0f, 6.0f);
  Ray2D r11 = std::move(r10);
  EXPECT_EQ(r10.x0(), 0.0f);
  EXPECT_EQ(r10.y0(), 0.0f);
  EXPECT_EQ(r10.GetDirect(0), 0.0f);
  EXPECT_EQ(r10.GetDirect(1), 0.0f);
  EXPECT_EQ(r11.x0(), 1.0f);
  EXPECT_EQ(r11.y0(), 2.0f);
  EXPECT_EQ(r11.GetDirect(0), 0.6f);
  EXPECT_EQ(r11.GetDirect(1), 0.8f);
}

TEST(test_ray, test_intersection)
{
  Ray2D r12(10.0f, 10.0f, -3.0*pi()/4.0f);
  cout<< r12.GetDirect(0)<< "    "<<r12.GetDirect(1)<<endl;
  Box2D b1(3.0f, 3.0f, 4.0f, 4.0f);
  Ray2D r13(6.0f, 6.0f, -3.0f*pi()/4.0f);
  Ray2D r14(1.0f, 1.0f, -pi()/4.0f);
  Ray2D r15(1.0f, 3.5f, 0.0f);
  Ray2D r16(3.5f, 10.0f, -pi()/2.0);
  EXPECT_EQ(r12.Intersection(b1, r12), 1);
  EXPECT_EQ(r13.Intersection(b1, r13), 1);
  EXPECT_EQ(r14.Intersection(b1, r14), 0);
  EXPECT_EQ(r15.Intersection(b1, r15), 1);
  EXPECT_EQ(r16.Intersection(b1, r16), 1);
}
