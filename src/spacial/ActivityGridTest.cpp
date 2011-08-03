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
	s.push_back(CUTE( ActivityGridTest::testApplyGridActivityModifier));
	s.push_back(CUTE( ActivityGridTest::testGetSetNearestGripPointActivity));
	s.push_back(CUTE( ActivityGridTest::testApplyPointActivity));
	s.push_back(CUTE( ActivityGridTest::testGetByActivity));
	s.push_back(CUTE( ActivityGridTest::testApplyPointActivityToGrid));
	//s.push_back(CUTE( ActivityGridTest::testApplyPointActivityToGrid2));
	//s.push_back(CUTE( ActivityGridTest::testApplyPointActivityToGrid3));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "ActivityGridTest");
}

void ActivityGridTest::testCreation() {
	//const int UNIT_SCALE = 1.0;
	const int GRID_X = 10;
	const int GRID_Y = 11;
	const int GRID_Z = 12;

	// forall in all_vals
	{

		ActivityGrid grid(GRID_X, GRID_Y, GRID_Z);
		ASSERT(grid.checkGridPointCount( Coordinates<int>(GRID_X, GRID_Y, GRID_Z)));
		ASSERT(grid.checkGridPointValues(0.0, 0.0));
		const std::map<Coordinates<int> , double> & all_vals = grid.getActivityGrid();
		std::map<Coordinates<int> , double>::const_iterator it_all_vals = all_vals.begin();
		const std::map<Coordinates<int> , double>::const_iterator it_all_vals_end = all_vals.end();
		while (it_all_vals != it_all_vals_end) {
			ASSERT_EQUAL_DELTA(0, it_all_vals->second, 0.00001);
			++it_all_vals;
		}
	}

	// check creation at scale
	{
		//1:1
		{
			int SCALE = 1;
			ActivityGrid grid(GRID_X, GRID_Y, GRID_Z, SCALE);
			ASSERT(grid.checkGridPointCount(Coordinates<int>(GRID_X, GRID_Y, GRID_Z)));
			ASSERT(grid.checkGridPointValues(0.0, 0.0));
		}

		//10:1
		{
			int SCALE = 3;
			ActivityGrid grid(GRID_X, GRID_Y, GRID_Z, SCALE);
			ASSERT(grid.checkGridPointCount(Coordinates<int>( (GRID_X) , (GRID_Y) ,(GRID_Z) )));
			ASSERT(grid.checkGridPointValues(0.0, 0.0));
		}

	}
}

void ActivityGridTest::testReScaling() {
	const double DISTANCE1D = sqrt((0.5 * 0.5) + (0.5 * 0.5) + (0.5 * 0.5));
	//const double DISTANCE2D = sqrt((1.5 * 1.5) + (1.5 * 1.5) + (1.5 * 1.5));
	//const double DISTANCE3D = sqrt((2.5 * 2.5) + (2.5 * 2.5) + (2.5 * 2.5));
	const double EQUAL_ACTIVITY = 2;
	const int GRID_X = 11;
	const int GRID_Y = 11;
	const int GRID_Z = 11;

	boost::shared_ptr<ActivityGrid> grid(new ActivityGrid(GRID_X, GRID_Y, GRID_Z));
	grid->clearGrid(EQUAL_ACTIVITY);

	// standard 1:1 scale ( 1 grid point per 1 unit )
	{
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

		// get interpolation
		{
			boost::shared_ptr<Point> test_point(new Point(5.5, 5.5, 5.5));

			double level1_act = 8 * (EQUAL_ACTIVITY - DISTANCE1D);
			double exp_total = level1_act;
			double activity = grid->getInterpolatedActivity(*test_point, 1);
			//std::cout << "ActivityGridTest::testInterpolation: " << activity << std::endl;
			ASSERT_EQUAL_DELTA(exp_total, activity, 0.0001);
		}
	}

	// rescale to 10:1 (10 grid points per 1 unit)
	{
		grid->setScale(10);
		// get interpolation
		{
			boost::shared_ptr<Point> test_point1(new Point(0.5, 0.5, 0.5));
			boost::shared_ptr<Point> test_point2(new Point(50, 550, 550));

			double level1_act = 8 * (EQUAL_ACTIVITY - DISTANCE1D);
			double exp_total = level1_act;
			double activity1 = grid->getInterpolatedActivity(*test_point1, 1);
			double activity2 = grid->getInterpolatedActivity(*test_point2, 1);
			//std::cout << "ActivityGridTest::testInterpolation: " << activity << std::endl;
			ASSERT_EQUAL_DELTA(exp_total, activity1, 0.0001);
			ASSERT_EQUAL_DELTA(0, activity2, 0.0001);
		}
	}
}

void ActivityGridTest::testInterpolation() {

	const double DISTANCE1D = sqrt((0.5 * 0.5) + (0.5 * 0.5) + (0.5 * 0.5));
	const double DISTANCE2D = sqrt((1.5 * 1.5) + (1.5 * 1.5) + (1.5 * 1.5));
	const double DISTANCE3D = sqrt((2.5 * 2.5) + (2.5 * 2.5) + (2.5 * 2.5));

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
	// get an interpolation of levels
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
		//double exp_total = level1_act + level2_act + ;
		double activity1 = grid->getInterpolatedActivity(*test_point, 1);
		ASSERT_EQUAL_DELTA(level1_act, activity1, 0.0001);
		double activity2 = grid->getInterpolatedActivity(*test_point, 2);
		ASSERT_EQUAL_DELTA(level2_act, activity2, 0.0001);
		double activity3 = grid->getInterpolatedActivity(*test_point, 3);
		ASSERT_EQUAL_DELTA(level3_act, activity3, 0.0001);
		//std::cout << "ActivityGridTest::testInterpolation: " << activity << std::endl;
	}
}

void ActivityGridTest::testApplyGridActivityModifier() {
	// test addition
	{
		const double EQUAL_ACTIVITY = 6;
		const int GRID_X = 11;
		const int GRID_Y = 11;
		const int GRID_Z = 11;
		const double ADDITION_VAL = -0.3;

		boost::shared_ptr<ActivityGrid> grid(new ActivityGrid(GRID_X, GRID_Y, GRID_Z));
		grid->clearGrid(EQUAL_ACTIVITY);

		grid->applyGridActivityModifier(ADDITION_VAL, ActivityGrid::ACTIVITY_MODIFIER_ADDITION);
		// test set up
		{
			for (int i = 0; i < GRID_X; i++) {
				for (int j = 0; j < GRID_Y; j++) {
					for (int k = 0; k < GRID_Z; k++) {
						double act = grid->getGridPointActivity(i, j, k);
						//	std::cout << "BoundingBoxTest::testBoxCorners1: " << "(" << i << ", " << j << ", " << k << ") = "
						//		<< act << std::endl;
						ASSERT_EQUAL_DELTA(act, EQUAL_ACTIVITY + ADDITION_VAL, 0.00001);
					}
				}
			}
		}
	}

	// test multiplication
	{
		const double EQUAL_ACTIVITY = 6;
		const int GRID_X = 11;
		const int GRID_Y = 11;
		const int GRID_Z = 11;
		const double MULT_VAL = -0.3;

		boost::shared_ptr<ActivityGrid> grid(new ActivityGrid(GRID_X, GRID_Y, GRID_Z));
		grid->clearGrid(EQUAL_ACTIVITY);

		grid->applyGridActivityModifier(MULT_VAL, ActivityGrid::ACTIVITY_MODIFIER_MULTIPLY);
		// test set up
		{
			for (int i = 0; i < GRID_X; i++) {
				for (int j = 0; j < GRID_Y; j++) {
					for (int k = 0; k < GRID_Z; k++) {
						double act = grid->getGridPointActivity(i, j, k);
						//	std::cout << "BoundingBoxTest::testBoxCorners1: " << "(" << i << ", " << j << ", " << k << ") = "
						//		<< act << std::endl;
						ASSERT_EQUAL_DELTA(act, EQUAL_ACTIVITY *MULT_VAL, 0.00001);
					}
				}
			}
		}
	}

	// test invert
	{
		const double EQUAL_ACTIVITY = 6;
		const int GRID_X = 11;
		const int GRID_Y = 11;
		const int GRID_Z = 11;
		const double ADDITION_VAL = -0.3;

		boost::shared_ptr<ActivityGrid> grid(new ActivityGrid(GRID_X, GRID_Y, GRID_Z));
		grid->clearGrid(EQUAL_ACTIVITY);

		grid->applyGridActivityModifier(ADDITION_VAL, ActivityGrid::ACTIVITY_MODIFIER_INVERT);
		// test set up
		{
			for (int i = 0; i < GRID_X; i++) {
				for (int j = 0; j < GRID_Y; j++) {
					for (int k = 0; k < GRID_Z; k++) {
						double act = grid->getGridPointActivity(i, j, k);
						//	std::cout << "BoundingBoxTest::testBoxCorners1: " << "(" << i << ", " << j << ", " << k << ") = "
						//		<< act << std::endl;
						ASSERT_EQUAL_DELTA(act, -EQUAL_ACTIVITY, 0.00001);
					}
				}
			}
		}
	}

	// test compound
	{
		const double EQUAL_ACTIVITY = 6;
		const int GRID_X = 11;
		const int GRID_Y = 11;
		const int GRID_Z = 11;
		const double ADDITION_VAL = -0.3;

		boost::shared_ptr<ActivityGrid> grid(new ActivityGrid(GRID_X, GRID_Y, GRID_Z));
		grid->clearGrid(EQUAL_ACTIVITY);

		grid->applyGridActivityModifier(
				ADDITION_VAL,
				ActivityGrid::ACTIVITY_MODIFIER_ADDITION | ActivityGrid::ACTIVITY_MODIFIER_MULTIPLY
						| ActivityGrid::ACTIVITY_MODIFIER_INVERT);
		// test set up
		{
			for (int i = 0; i < GRID_X; i++) {
				for (int j = 0; j < GRID_Y; j++) {
					for (int k = 0; k < GRID_Z; k++) {
						double act = grid->getGridPointActivity(i, j, k);
						//	std::cout << "BoundingBoxTest::testBoxCorners1: " << "(" << i << ", " << j << ", " << k << ") = "
						//		<< act << std::endl;
						ASSERT_EQUAL_DELTA(act, ((EQUAL_ACTIVITY+ADDITION_VAL)*ADDITION_VAL * -1), 0.00001);
					}
				}
			}
		}
	}

}

void ActivityGridTest::testGetSetNearestGripPointActivity() {
	const int GRID_X = 9;
	const int GRID_Y = 9;
	const int GRID_Z = 9;
	//const int GRID_TOTAL = GRID_X * GRID_Y * GRID_Z;
	const int SCALE = 1;
	double MIN_ACT = 0.0;
	double MAX_ACT = 10;
	ActivityGrid grid(GRID_X * SCALE, GRID_Y * SCALE, GRID_Z * SCALE, SCALE);
	grid.setScale(SCALE);
	grid.randomise(MIN_ACT, MAX_ACT);

	// test
	{
		Coordinates<int> coords1_1 = grid.getNearestGridPoint(Point(GRID_X - 1.5, GRID_Y - 1, GRID_Z - 1))->first;
		Coordinates<int> coords1_2 = grid.getNearestGridPoint(Point(GRID_X - 1.6, GRID_Y - 1, GRID_Z - 1))->first;
		Coordinates<int> coords1_3 = grid.getNearestGridPoint(Point(GRID_X - 1.5, GRID_Y - 1.5, GRID_Z - 1))->first;
		Coordinates<int> coords1_4 = grid.getNearestGridPoint(Point(GRID_X - 1.6, GRID_Y - 1.6, GRID_Z - 1))->first;
		Coordinates<int> coords1_5 = grid.getNearestGridPoint(Point(GRID_X - 1.5, GRID_Y - 1.5, GRID_Z - 1.5))->first;
		Coordinates<int> coords1_6 = grid.getNearestGridPoint(Point(GRID_X - 1.6, GRID_Y - 1.6, GRID_Z - 1.6))->first;

		ASSERT_EQUAL(coords1_1, Coordinates<int>(GRID_X - 1, GRID_Y - 1, GRID_Z - 1));
		ASSERT_EQUAL(coords1_2, Coordinates<int>(GRID_X - 2, GRID_Y - 1, GRID_Z - 1));
		ASSERT_EQUAL(coords1_3, Coordinates<int>(GRID_X - 1, GRID_Y - 1, GRID_Z - 1));
		ASSERT_EQUAL(coords1_4, Coordinates<int>(GRID_X - 2, GRID_Y - 2, GRID_Z - 1));
		ASSERT_EQUAL(coords1_5, Coordinates<int>(GRID_X - 1, GRID_Y - 1, GRID_Z - 1));
		ASSERT_EQUAL(coords1_6, Coordinates<int>(GRID_X - 2, GRID_Y - 2, GRID_Z - 2));
	}

	// test
	{
		Coordinates<int> coords1_1 = grid.getNearestGridPoint(Point(GRID_X + 34, GRID_Y - 1, GRID_Z - 1))->first;
		Coordinates<int> coords1_2 = grid.getNearestGridPoint(Point(GRID_X - 1, -34, GRID_Z - 1.5))->first;
		Coordinates<int> coords1_3 = grid.getNearestGridPoint(Point(GRID_X - 1.1, GRID_Y - 1.3, GRID_Z))->first;

		ASSERT_EQUAL(coords1_1, Coordinates<int>(GRID_X - 1, GRID_Y - 1, GRID_Z - 1));
		ASSERT_EQUAL(coords1_2, Coordinates<int>(GRID_X - 1, 0, GRID_Z - 1));
		ASSERT_EQUAL(coords1_3, Coordinates<int>(GRID_X - 1, GRID_Y - 1, GRID_Z - 1));
	}

	// test set
	{
		double TEST_ACT = -4.0;
		grid.setNearestGridPointActivity(Point(GRID_X - 3.2, GRID_Y - 2.8, GRID_Z - 4.2), TEST_ACT);
		double got_act = grid.getNearestGridPointActivity(Point(GRID_X - 3.2, GRID_Y - 2.8, GRID_Z - 4.2)).second;

		ASSERT_EQUAL(TEST_ACT, got_act);
	}

}

void ActivityGridTest::testApplyPointActivity() {
	const int GRID_X = 10;
	const int GRID_Y = 11;
	const int GRID_Z = 12;
	const double ACTIVITY_DECAY = 2.3;
	const double ACTIVITY = 5;
	const int SCALE = 3;
	ActivityGrid grid(GRID_X, GRID_Y, GRID_Z, SCALE);
	grid.setActivityDecay(ACTIVITY_DECAY);

	Point p_ref(5, 5, 5);
	Point p_dest(6, 5, 5);
	ActivityGrid::CoordinatesIntegers p_dest_coords(6, 5, 5);
	std::pair<ActivityGrid::CoordinatesIntegers, double> grid_coords(p_dest_coords, 3);
	// distance is 1 but scale is 3 and decay is 2.3 per unit so...
	// dist ref to dest is unit 1 but 1/3 in reality
	double actual_distance = (p_ref.getDistance(p_dest));
	double exp_activity_mod = ACTIVITY - ((2.3 / grid.getScale()) * actual_distance);
	double exp_activity = grid_coords.second + exp_activity_mod;
	grid.applyPointActivityToGridPoint(p_ref, ACTIVITY, grid_coords);
	ASSERT_EQUAL_DELTA(exp_activity, grid_coords.second, 0.00001);
}

void ActivityGridTest::testApplyPointActivityToGrid() {
	const bool SET_ASSERT_ON = false;
	// test1
	{
		const int GRID_X = 20;
		const int GRID_Y = 20;
		const int GRID_Z = 20;
		const int GRID_TOTAL = GRID_X * GRID_Y * GRID_Z;
		const double ACTIVITY_DECAY = 1;
		const int SCALE = 1;
		ActivityGrid grid_orig(GRID_X * SCALE, GRID_Y * SCALE, GRID_Z * SCALE, SCALE);
		grid_orig.setScale(SCALE);
		ActivityGrid grid(GRID_X * SCALE, GRID_Y * SCALE, GRID_Z * SCALE, SCALE);
		grid.setScale(SCALE);
		grid.setActivityDecay(ACTIVITY_DECAY);

		for (int i = 1; i < 3; i++) {
			const double ACTIVITY = i;

			// centred point
			{
				double temp_x = GRID_X / 2;
				double temp_y = GRID_Y / 2;
				double temp_z = GRID_Z / 2;

				Point p_ref_unscaled(temp_x, temp_y, temp_z);
				Point p_ref_scaled = p_ref_unscaled / SCALE;
				grid.applyPointActivityToGrid(p_ref_scaled, ACTIVITY);

				int equal_to = 0;
				int greater_than = 0;
				int less_than = 0;
				int not_found = 0;
				grid_orig.compareGridPoints(grid, equal_to, greater_than, less_than, not_found);
#ifdef ACTIVITYGRIDTEST_DEBUG
				std::cout << "ActivityGridTest::testApplyPointActivityToGrid: " << i << "  " << "equal_to: "
				<< equal_to << " " << "greater_than: " << greater_than << " " << "less_than: " << less_than
				<< " " << "not_found: " << not_found << std::endl << grid << std::endl;
#endif
				if (SET_ASSERT_ON == true) {
					ASSERT_EQUAL(0,less_than);
					ASSERT_EQUAL(0,not_found);
					ASSERT_EQUAL(27, greater_than);
					ASSERT_EQUAL(equal_to, (GRID_TOTAL *SCALE*SCALE*SCALE) - greater_than);
				}
			}

			// off-centred point
			{
				grid.clearGrid();
				double temp_x = (GRID_X / 2) - 0.1;
				double temp_y = GRID_Y / 2;
				double temp_z = GRID_Z / 2;

				Point p_ref_unscaled(temp_x, temp_y, temp_z);
				Point p_ref_scaled = p_ref_unscaled / SCALE;
				grid.applyPointActivityToGrid(p_ref_scaled, ACTIVITY);

				int equal_to = 0;
				int greater_than = 0;
				int less_than = 0;
				int not_found = 0;
				grid_orig.compareGridPoints(grid, equal_to, greater_than, less_than, not_found);
#ifdef ACTIVITYGRIDTEST_DEBUG
				std::cout << "ActivityGridTest::testApplyPointActivityToGrid: " << i << "  " << "equal_to: "
				<< equal_to << " " << "greater_than: " << greater_than << " " << "less_than: " << less_than
				<< " " << "not_found: " << not_found << std::endl << grid << std::endl;
#endif
				if (SET_ASSERT_ON == true) {
					ASSERT_EQUAL(0,less_than);
					ASSERT_EQUAL(0,not_found);
					ASSERT_EQUAL(28, greater_than);
					ASSERT_EQUAL(equal_to, (GRID_TOTAL *SCALE*SCALE*SCALE) - greater_than);
				}
			}

			// extreme off-centred point
			{
				grid.clearGrid();
				double temp_x = (GRID_X / 2) - 0.1;
				double temp_y = (GRID_Y / 2) - 0.1;
				double temp_z = (GRID_Z / 2) - 0.1;

				Point p_ref_unscaled(temp_x, temp_y, temp_z);
				Point p_ref_scaled = p_ref_unscaled / SCALE;
				grid.applyPointActivityToGrid(p_ref_scaled, ACTIVITY);

				int equal_to = 0;
				int greater_than = 0;
				int less_than = 0;
				int not_found = 0;
				grid_orig.compareGridPoints(grid, equal_to, greater_than, less_than, not_found);
#ifdef ACTIVITYGRIDTEST_DEBUG
				std::cout << "ActivityGridTest::testApplyPointActivityToGrid: " << i << "  " << "equal_to: "
						<< equal_to << " " << "greater_than: " << greater_than << " " << "less_than: " << less_than
						<< " " << "not_found: " << not_found << std::endl << grid << std::endl;
#endif
				if (SET_ASSERT_ON == true) {
					ASSERT_EQUAL(0,less_than);
					ASSERT_EQUAL(0,not_found);
					ASSERT_EQUAL(27+3, greater_than);
					ASSERT_EQUAL(equal_to, (GRID_TOTAL *SCALE*SCALE*SCALE) - greater_than);
				}
			}
		}
	}
}

void ActivityGridTest::testApplyPointActivityToGrid2() {

	// calculate maximum affect
	{
		const int GRID_X = 19;
		const int GRID_Y = 19;
		const int GRID_Z = 19;
		const int POINT_X = 9;
		const int POINT_Y = 9;
		//const int POINT_Z = 9;

		//const int GRID_TOTAL = GRID_X * GRID_Y * GRID_Z;

		for (int i = 1; i < 6; i++) {
			const double ACTIVITY_DECAY = 1;
			const double ACTIVITY = i;
			const int SCALE = 1;
			ActivityGrid grid_orig(GRID_X * SCALE, GRID_Y * SCALE, GRID_Z * SCALE, SCALE);
			grid_orig.setScale(SCALE);
			ActivityGrid grid(GRID_X * SCALE, GRID_Y * SCALE, GRID_Z * SCALE, SCALE);
			grid.setScale(SCALE);
			grid.setActivityDecay(ACTIVITY_DECAY);
			//centre poiint
			{
				grid.clearGrid();
				Point p_ref_unscaled1(POINT_X, POINT_Y, POINT_Y);
				Point p_ref_scaled1 = p_ref_unscaled1 / SCALE;
				grid.applyPointActivityToGrid(p_ref_scaled1, ACTIVITY);
				int equal_to = 0;
				int greater_than = 0;
				int less_than = 0;
				int not_found = 0;
				grid_orig.compareGridPoints(grid, equal_to, greater_than, less_than, not_found);
#ifdef ACTIVITYGRIDTEST_DEBUG
				std::cout << "ActivityGridTest::testApplyPointActivityToGrid: 0: " << i << ": " << "equal_to: "
						<< equal_to << " " << "greater_than: " << greater_than << " " << "less_than: " << less_than
						<< " " << "not_found: " << not_found << std::endl << grid << std::endl;
#endif
			}

			//slightly less poiint
			{
				grid.clearGrid();
				Point p_ref_unscaled1(POINT_X - 0.01, POINT_Y - 0.01, POINT_Y - 0.01);
				Point p_ref_scaled1 = p_ref_unscaled1 / SCALE;
				grid.applyPointActivityToGrid(p_ref_scaled1, ACTIVITY);
				int equal_to = 0;
				int greater_than = 0;
				int less_than = 0;
				int not_found = 0;
				grid_orig.compareGridPoints(grid, equal_to, greater_than, less_than, not_found);
#ifdef ACTIVITYGRIDTEST_DEBUG
std::cout << "ActivityGridTest::testApplyPointActivityToGrid: - 0.01: " << i << ": " << "equal_to: "
						<< equal_to << " " << "greater_than: " << greater_than << " " << "less_than: " << less_than
						<< " " << "not_found: " << not_found << std::endl << grid << std::endl;
#endif
			}

			//mostly less poiint
			{
				grid.clearGrid();
				Point p_ref_unscaled1(POINT_X - 0.99, POINT_Y - 0.99, POINT_Y - 0.99);
				Point p_ref_scaled1 = p_ref_unscaled1 / SCALE;
				grid.applyPointActivityToGrid(p_ref_scaled1, ACTIVITY);
				int equal_to = 0;
				int greater_than = 0;
				int less_than = 0;
				int not_found = 0;
				grid_orig.compareGridPoints(grid, equal_to, greater_than, less_than, not_found);
#ifdef ACTIVITYGRIDTEST_DEBUG
std::cout << "ActivityGridTest::testApplyPointActivityToGrid: - 0.99: " << i << ": " << "equal_to: "
						<< equal_to << " " << "greater_than: " << greater_than << " " << "less_than: " << less_than
						<< " " << "not_found: " << not_found << std::endl << grid << std::endl;
#endif
			}

		}

		// test1
		{
			const int GRID_X = 9;
			const int GRID_Y = 9;
			const int GRID_Z = 9;
			const int GRID_TOTAL = GRID_X * GRID_Y * GRID_Z;
			const double ACTIVITY_DECAY = 0.9;
			const double ACTIVITY = 2;
			const int SCALE = 1;
			ActivityGrid grid_orig(GRID_X * SCALE, GRID_Y * SCALE, GRID_Z * SCALE, SCALE);
			grid_orig.setScale(SCALE);
			ActivityGrid grid(GRID_X * SCALE, GRID_Y * SCALE, GRID_Z * SCALE, SCALE);
			grid.setScale(SCALE);
			grid.setActivityDecay(ACTIVITY_DECAY);
			for (int i = 0; i < 10; i++) {
				grid.clearGrid();
				//double random_x = common::Maths::getRandomDouble(2, GRID_X - 2);
				//double random_y = common::Maths::getRandomDouble(2, GRID_Y - 2);
				//double random_z = common::Maths::getRandomDouble(2, GRID_Z - 2);
				double temp_x = 5 - (i * 0.1);
				double temp_y = 5 - (i * 0.1);
				double temp_z = 5 - (i * 0.1);

				Point p_ref_unscaled(temp_x, temp_y, temp_z);
				Point p_ref_scaled = p_ref_unscaled / SCALE;
				grid.applyPointActivityToGrid(p_ref_scaled, ACTIVITY);

				int equal_to = 0;
				int greater_than = 0;
				int less_than = 0;
				int not_found = 0;
				grid_orig.compareGridPoints(grid, equal_to, greater_than, less_than, not_found);
#ifdef ACTIVITYGRIDTEST_DEBUG
	std::cout << "ActivityGridTest::testApplyPointActivityToGrid: " << "equal_to: " << equal_to << " "
						<< "greater_than: " << greater_than << " " << "less_than: " << less_than << " "
						<< "not_found: " << not_found << std::endl << grid << std::endl;
#endif
				ASSERT_EQUAL(0,less_than);
				ASSERT_EQUAL(0,not_found);
				ASSERT(greater_than <=22);
				ASSERT(greater_than >=9);
				ASSERT_EQUAL(equal_to, (GRID_TOTAL *SCALE*SCALE*SCALE) - greater_than);
			}
		}
	}
	// test2
	{
		const int GRID_X = 9;
		const int GRID_Y = 9;
		const int GRID_Z = 9;
		const int GRID_TOTAL = GRID_X * GRID_Y * GRID_Z;
		const double ACTIVITY_DECAY = 1.8;
		const double ACTIVITY = 1;
		const int SCALE = 3;
		ActivityGrid grid_orig(GRID_X * SCALE, GRID_Y * SCALE, GRID_Z * SCALE, SCALE);
		grid_orig.setScale(SCALE);
		ActivityGrid grid(GRID_X * SCALE, GRID_Y * SCALE, GRID_Z * SCALE, SCALE);
		grid.setScale(SCALE);
		grid.setActivityDecay(ACTIVITY_DECAY);
		for (int i = 0; i < 10; i++) {
			grid.clearGrid();
			double random_x = common::Maths::getRandomDouble(2, GRID_X - 2);
			double random_y = common::Maths::getRandomDouble(2, GRID_Y - 2);
			double random_z = common::Maths::getRandomDouble(2, GRID_Z - 2);

			Point p_ref_unscaled(random_x, random_y, random_z);
			Point p_ref_scaled = p_ref_unscaled / SCALE;
			grid.applyPointActivityToGrid(p_ref_scaled, ACTIVITY);

			int equal_to = 0;
			int greater_than = 0;
			int less_than = 0;
			int not_found = 0;
			grid_orig.compareGridPoints(grid, equal_to, greater_than, less_than, not_found);
#ifdef ACTIVITYGRIDTEST_DEBUG
std::cout << "ActivityGridTest::testApplyPointActivityToGrid: " << "equal_to: " << equal_to << " "
					<< "greater_than: " << greater_than << " " << "less_than: " << less_than << " " << "not_found: "
					<< not_found << std::endl << grid << std::endl;
#endif
ASSERT_EQUAL(0,less_than);
			ASSERT_EQUAL(0,not_found);
			ASSERT(greater_than <=22);
			ASSERT(greater_than >=9);
			ASSERT_EQUAL(equal_to, (GRID_TOTAL *SCALE*SCALE*SCALE) - greater_than);
		}
	}
}

void ActivityGridTest::testGetByActivity() {
	const int GRID_X = 9;
	const int GRID_Y = 9;
	const int GRID_Z = 9;
	const int GRID_TOTAL = GRID_X * GRID_Y * GRID_Z;
	const int SCALE = 3;
	ActivityGrid grid_zero(GRID_X, GRID_Y, GRID_Z, SCALE);

	//
	{
		const double GRID1_VAL = 0.076;

		ActivityGrid grid1(GRID_X, GRID_Y, GRID_Z, SCALE);
		grid1.clearGrid(GRID1_VAL);

		// test compare
		{
			int equal_to = 0;
			int greater_than = 0;
			int less_than = 0;
			int not_found = 0;
			grid_zero.compareGridPoints(grid1, equal_to, greater_than, less_than, not_found);
			ASSERT_EQUAL(0,less_than);
			ASSERT_EQUAL(0,not_found);
			ASSERT_EQUAL(GRID_TOTAL,greater_than);
			ASSERT_EQUAL(0, equal_to);
		}

		//test get by activity
		{
			int act0 = grid1.getGridPointsByActivity(0).size();
			int act_clear = grid1.getGridPointsByActivity(GRID1_VAL).size();
			int act_other = grid1.getGridPointsByActivity(GRID1_VAL + 2.32).size();

			ASSERT_EQUAL(0, act0);
			ASSERT_EQUAL(GRID_TOTAL, act_clear);
			ASSERT_EQUAL(0, act_other);
		}
	}

	//grid2
	{
		const double GRID2_VAL1 = 0.376;
		const double GRID2_VAL2 = -0.2076;
		const double GRID2_VAL3 = 0.076;

		ActivityGrid grid2(GRID_X, GRID_Y, GRID_Z, SCALE);
		grid2.clearGrid(0);
		grid2.setGridPointActivity(ActivityGrid::CoordinatesIntegers(GRID_X - 1, GRID_Y - 1, GRID_Z - 1), GRID2_VAL1);
		grid2.setGridPointActivity(ActivityGrid::CoordinatesIntegers(GRID_X - 2, GRID_Y - 1, GRID_Z - 1), GRID2_VAL1);

		grid2.setGridPointActivity(ActivityGrid::CoordinatesIntegers(GRID_X - 2, GRID_Y - 2, GRID_Z - 1), GRID2_VAL2);
		grid2.setGridPointActivity(ActivityGrid::CoordinatesIntegers(GRID_X - 2, GRID_Y - 3, GRID_Z - 1), GRID2_VAL2);

		grid2.setGridPointActivity(ActivityGrid::CoordinatesIntegers(GRID_X - 2, GRID_Y - 2, GRID_Z - 2), GRID2_VAL3);
		grid2.setGridPointActivity(ActivityGrid::CoordinatesIntegers(GRID_X - 2, GRID_Y - 2, GRID_Z - 3), GRID2_VAL3);

		// test compare
		{
			int equal_to = 0;
			int greater_than = 0;
			int less_than = 0;
			int not_found = 0;
			grid_zero.compareGridPoints(grid2, equal_to, greater_than, less_than, not_found);
			ASSERT_EQUAL(2,less_than);
			ASSERT_EQUAL(0,not_found);
			ASSERT_EQUAL(4,greater_than);
			ASSERT_EQUAL(GRID_TOTAL-6, equal_to);
		}

		//test get by activity
		{
			int act0 = grid2.getGridPointsByActivity(0).size();
			int act_val1 = grid2.getGridPointsByActivity(GRID2_VAL1).size();
			int act_val2 = grid2.getGridPointsByActivity(GRID2_VAL2).size();
			int act_val3 = grid2.getGridPointsByActivity(GRID2_VAL3).size();

			ASSERT_EQUAL(GRID_TOTAL -6, act0);
			ASSERT_EQUAL(2, act_val1);
			ASSERT_EQUAL(2, act_val2);
			ASSERT_EQUAL(2, act_val3);
		}

	}

}

void ActivityGridTest::testApplyPointActivityToGrid3() {
	const bool SET_ASSERT_ON = false;
	// test1
	{
		const int GRID_X = 20;
		const int GRID_Y = 20;
		const int GRID_Z = 20;
		//const int GRID_TOTAL = GRID_X * GRID_Y * GRID_Z;
		const double ACTIVITY_DECAY = 1.75;
		const double ACTIVITY = 3.2;

		for (int i = 1; i < 5; i++) {
			const int SCALE = i;
			ActivityGrid grid(GRID_X * SCALE, GRID_Y * SCALE, GRID_Z * SCALE, SCALE);
			grid.setScale(SCALE);
			grid.setActivityDecay(ACTIVITY_DECAY);
			// centred point
			{
				grid.clearGrid();
				double temp_x = GRID_X / 2;
				double temp_y = GRID_Y / 2;
				double temp_z = GRID_Z / 2;

				Point p_ref_unscaled(temp_x, temp_y, temp_z);
				Point p_ref_scaled = p_ref_unscaled / SCALE;
				grid.applyPointActivityToGrid(p_ref_scaled, ACTIVITY);

				double sum = grid.getActivitySummation() / (double) grid.getScale();
				std::cout << "ActivityGridTest::testApplyPointActivityToGrid: " << i << "  sum = " << sum << std::endl;

				if (SET_ASSERT_ON == true) {
				}
			}

			// off-centred point
			{
				grid.clearGrid();
				double temp_x = (GRID_X / 2) - 0.1;
				double temp_y = GRID_Y / 2;
				double temp_z = GRID_Z / 2;

				Point p_ref_unscaled(temp_x, temp_y, temp_z);
				Point p_ref_scaled = p_ref_unscaled / SCALE;
				grid.applyPointActivityToGrid(p_ref_scaled, ACTIVITY);

				double sum = grid.getActivitySummation() / (double) grid.getScale();
				std::cout << "ActivityGridTest::testApplyPointActivityToGrid: " << i << "  sum = " << sum << std::endl;

				if (SET_ASSERT_ON == true) {
				}
			}

			// extreme off-centred point
			{
				grid.clearGrid();
				double temp_x = (GRID_X / 2) - 0.1;
				double temp_y = (GRID_Y / 2) - 0.1;
				double temp_z = (GRID_Z / 2) - 0.1;

				Point p_ref_unscaled(temp_x, temp_y, temp_z);
				Point p_ref_scaled = p_ref_unscaled / SCALE;
				grid.applyPointActivityToGrid(p_ref_scaled, ACTIVITY);

				double sum = grid.getActivitySummation() / (double) grid.getScale();
				std::cout << "ActivityGridTest::testApplyPointActivityToGrid: " << i << "  sum = " << sum << std::endl;

				if (SET_ASSERT_ON == true) {
				}
			}
		}
	}
}

}//NAMESPACE

}//NAMESPACE
