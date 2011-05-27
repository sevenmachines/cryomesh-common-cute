/*
 * ActivityGridTest.cpp
 *
 *  Created on: 26 May 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#include "ActivityGridTest.h"
#include "spacial/ActivityGrid.h"
#include <map>

namespace cryomesh {

namespace spacial {

void ActivityGridTest::runSuite() {
	cute::suite s;
	s.push_back(CUTE( ActivityGridTest::testCreation));
	s.push_back(CUTE( ActivityGridTest::testReScaling));
	s.push_back(CUTE( ActivityGridTest::testInterpolation));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "ActivityGridTest");
}

void ActivityGridTest::testCreation() {
	const int GRID_X = 10;
	const int GRID_Y = 11;
	const int GRID_Z = 12;

	ActivityGrid grid(GRID_X, GRID_Y, GRID_Z);
	const std::map<ActivityGrid::Coordinates, double> & all_vals = grid.getActivityGrid();
	// forall in all_vals
	{
		std::map<ActivityGrid::Coordinates, double>::const_iterator it_all_vals = all_vals.begin();
		const std::map<ActivityGrid::Coordinates, double>::const_iterator it_all_vals_end = all_vals.end();
		while (it_all_vals != it_all_vals_end) {
			ASSERT_EQUAL_DELTA(0, it_all_vals->second, 0.00001);
			++it_all_vals;
		}
	}
}

void ActivityGridTest::testReScaling() {
	ASSERTM("TODO", false);
}

void ActivityGridTest::testInterpolation() {

	const double DISTANCE1D =sqrt ( ( 0.5  * 0.5 )  + ( 0.5  * 0.5 ) + ( 0.5  * 0.5 ));
	const double DISTANCE2D =sqrt ( ( 1.5  * 1.5 )  + ( 1.5  * 1.5 ) + ( 1.5  * 1.5 ));
	const double DISTANCE3D =sqrt ( ( 2.5  *2.5 )  + ( 2.5  * 2.5 ) + ( 2.5  * 2.5 ));

	// get interpolation
	{
		const double EQUAL_ACTIVITY = 6;
		const int GRID_X = 11;
		const int GRID_Y = 11;
		const int GRID_Z = 11;

		boost::shared_ptr<ActivityGrid> grid(new ActivityGrid(GRID_X, GRID_Y, GRID_Z));
		grid->clearGrid(EQUAL_ACTIVITY);

		// test set up
		{
			for (int i = 0; i < GRID_X; i++) {
				for (int j = 0; j < GRID_Y; j++) {
					for (int k = 0; k < GRID_Z; k++) {
						double act = grid->getGridPointActivity(i, j, k);
						//	std::cout << "BoundingBoxTest::testBoxCorners1: " << "(" << i << ", " << j << ", " << k << ") = "
						//		<< act << std::endl;
						ASSERT_EQUAL_DELTA(EQUAL_ACTIVITY, act, 0.00001);
					}
				}
			}
		}

		boost::shared_ptr<Point> test_point(new Point(5.5, 5.5, 5.5));
		{
			double level1_act = 8 * (EQUAL_ACTIVITY - DISTANCE1D);
			double exp_total = level1_act;
			double activity = grid->getInterpolatedActivity(*test_point, 1);
			//std::cout << "ActivityGridTest::testInterpolation: " << activity << std::endl;
			ASSERT_EQUAL_DELTA(exp_total, activity, 0.0001);
		}
	}
	// get an interpolation of 3 levels
	{
		const double EQUAL_ACTIVITY = 6;
		const int GRID_X = 11;
		const int GRID_Y = 11;
		const int GRID_Z = 11;

		boost::shared_ptr<ActivityGrid> grid(new ActivityGrid(GRID_X, GRID_Y, GRID_Z));
		grid->clearGrid(EQUAL_ACTIVITY);

		// test set up
		{
			for (int i = 0; i < GRID_X; i++) {
				for (int j = 0; j < GRID_Y; j++) {
					for (int k = 0; k < GRID_Z; k++) {
						double act = grid->getGridPointActivity(i, j, k);
						//	std::cout << "BoundingBoxTest::testBoxCorners1: " << "(" << i << ", " << j << ", " << k << ") = "
						//		<< act << std::endl;
						ASSERT_EQUAL_DELTA(EQUAL_ACTIVITY, act, 0.00001);
					}
				}
			}
		}

		boost::shared_ptr<Point> test_point(new Point(5.5, 5.5, 5.5));

		double level1_act = 8 * (EQUAL_ACTIVITY - (DISTANCE1D));
		double level2_act = 8 * (EQUAL_ACTIVITY - (DISTANCE2D));
		double level3_act = 8 * (EQUAL_ACTIVITY - (DISTANCE3D));
		double exp_total = level1_act + level2_act + level3_act;
		double activity = grid->getInterpolatedActivity(*test_point, 3);
		//std::cout << "ActivityGridTest::testInterpolation: " << activity << std::endl;
		ASSERT_EQUAL_DELTA(exp_total, activity, 0.0001);
	}
}

}//NAMESPACE

}//NAMESPACE
