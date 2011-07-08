/*
 * GridContainerTest.cpp
 *
 *  Created on: 22 Jun 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#include "GridContainerTest.h"
#include "ICuteSuite.h"
#include "spacial/GridContainer.h"

namespace cryomesh {

namespace spacial {

void GridContainerTest::runSuite(){
	cute::suite s;
	s.push_back(CUTE(GridContainerTest::testCreation));
	s.push_back(CUTE(GridContainerTest::testGetSet));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "GridContainerTest");
}

void GridContainerTest::testCreation(){
	const int X = 9;
	const int Y = 4;
	const int Z = 7;
	const int TOTAL_VALS = (X+1) * (Y+1) * (Z+1);
	Point point(X, Y, Z);
	GridContainer gc(point);
	ASSERT_EQUAL(TOTAL_VALS, gc.getValues().size() );
}

void GridContainerTest::testGetSet(){
	const int X = 9;
		const int Y = 4;
		const int Z = 7;
		const int TOTAL_VALS = (X+1) * (Y+1) * (Z+1);
		const double TEST_VAL = 1.3;
		Point point(X, Y, Z);
		GridContainer gc(point);

		gc.clear(TEST_VAL);

		ASSERT_EQUAL_DELTA(TEST_VAL, gc.getValue(Coordinates<int>(0,0,0)), 0.00001);
		ASSERT_EQUAL_DELTA(TEST_VAL, gc.getValue(Coordinates<int>(X-4,Y-1,Z-2)), 0.00001);
		ASSERT_EQUAL_DELTA(TEST_VAL, gc.getValue(Coordinates<int>(X,Y,Z)), 0.00001);

}
}//NAMESPACE

}//NAMESPACE
