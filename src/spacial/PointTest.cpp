#include "PointTest.h"

namespace cryomesh {
namespace spacial {

void PointTest::runSuite() {
	cute::suite s;
	s.push_back(CUTE(PointTest::testPoint_SphericalPoint));
	s.push_back(CUTE(PointTest::testPoint_CC));
	s.push_back(CUTE(PointTest::testgetDistance));
	s.push_back(CUTE(PointTest::testoperators));
	s.push_back(CUTE(PointTest::testgetNormalisedVector));
	s.push_back(CUTE(PointTest::testScale));
	s.push_back(CUTE(PointTest::testRounded));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "PointTest");
}
void PointTest::testPoint_SphericalPoint() {
	// good point
	{
		SphericalPoint sp(2.3, Radian(0.8), Radian(1.2));
		Point p(sp);
		double x = 0.597860947;
		double y = 1.537789005;
		double z = 1.602425431;
		ASSERT_EQUAL_DELTA(x, p.getX(), 0.0001);
		ASSERT_EQUAL_DELTA(y, p.getY(), 0.0001);
		ASSERT_EQUAL_DELTA(z, p.getZ(), 0.0001);
	}

}
void PointTest::testPoint_CC() {
	// good point
	{
		Point sp1(2.3, 0.8, 1.2);
		Point sp2(sp1);
		bool equal = sp1 == sp2;

		ASSERT(equal);
	}
}
void PointTest::testgetDistance() {
	Point p1(1, 2, 3);
	Point p2(3, 2, 1);
	double dist1 = p2.getDistance(p1);
	double dist2 = p1.getDistance(p2);
	ASSERT_EQUAL_DELTA(2.828427125, dist1, 0.00001);
	ASSERT_EQUAL_DELTA(dist1, dist2, 0.00001);

}
void PointTest::testoperators() {
	Point p1(1, 1, 1);
	Point p2(2, 2, 2);
	Point p3(3, 3, 3);

	bool plus = p1 + p2 == p3;
	bool minus = p3 - p2 == p1;
	ASSERT(plus);
	ASSERT(minus);

	//operator*
	{
		double mult = 2;
		Point p(1, 1, 1);
		Point pm = p * mult;
		bool eq = pm == Point(2, 2, 2);
		ASSERT(eq);
	}
}
void PointTest::testgetNormalisedVector() {
	Point p(3.232, 14.344, 66.34);
	Point norm_vector = p.getNormalisedVector();
	double dist = norm_vector.getDistance(Point(0, 0, 0));
	//std::cout<<"testgetNormalisedVector: dist: "<<dist<<std::endl;
	//std::cout << norm_vector<<std::endl;
	ASSERT_EQUAL_DELTA(1, dist, 0.0001);
}

void PointTest::testScale() {
	//
	{
		double X = 2.2;
		double Y = 3.3;
		double Z = 4.4;
		double factor1 = 2.2;
		double factor2 = -3.3;
		double factor3 = -(3.3 * 2.2);
		Point p1 = Point(X, Y, Z).getScaled(factor1);
		ASSERT_EQUAL_DELTA(factor1*X, p1.getX(), 0.00001);
		ASSERT_EQUAL_DELTA(factor1*Y, p1.getY(), 0.00001);
		ASSERT_EQUAL_DELTA(factor1*Z, p1.getZ(), 0.00001);

		Point p2 = p1.getScaled(factor2);
		ASSERT_EQUAL_DELTA(factor1*factor2*X, p2.getX(), 0.00001);
		ASSERT_EQUAL_DELTA(factor1*factor2*Y, p2.getY(), 0.00001);
		ASSERT_EQUAL_DELTA(factor1*factor2*Z, p2.getZ(), 0.00001);

		Point p3 = p2.getScaled(factor3);
		ASSERT_EQUAL_DELTA(factor1*factor2*factor3*X, p3.getX(), 0.00001);
		ASSERT_EQUAL_DELTA(factor1*factor2*factor3*Y, p3.getY(), 0.00001);
		ASSERT_EQUAL_DELTA(factor1*factor2*factor3*Z, p3.getZ(), 0.00001);

		Point p4 = p3.getScaled(1.0 / (factor1 * factor2 * factor3));
		ASSERT_EQUAL_DELTA(X, p4.getX(), 0.00001);
		ASSERT_EQUAL_DELTA(Y, p4.getY(), 0.00001);
		ASSERT_EQUAL_DELTA(Z, p4.getZ(), 0.00001);
	}

}

void PointTest::testRounded() {
	Point p(1.5, 1.2, 1.8);
	Point q = p.getRounded();
	ASSERT_EQUAL(Point(2, 1, 2), q);
}
}//NAMESPACE
}//NAMESPACE

