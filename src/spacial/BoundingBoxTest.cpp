/*
 * BoundingBoxTest.cpp
 *
 *  Created on: 27 May 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#include "BoundingBoxTest.h"
#include "spacial/BoundingBox.h"
#include "spacial/ActivityGrid.h"

namespace cryomesh {

namespace spacial {

void BoundingBoxTest::runSuite() {
	cute::suite s;
	s.push_back(CUTE(BoundingBoxTest::testBoxCorners1));
	s.push_back(CUTE(BoundingBoxTest::testBoxCorners2));
	s.push_back(CUTE(BoundingBoxTest::testBoxCorners3));
	s.push_back(CUTE(BoundingBoxTest::testGetInterpolatedActivity1));
	s.push_back(CUTE(BoundingBoxTest::testGetInterpolatedActivity2));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "BoundingBoxTest");
}

void BoundingBoxTest::testBoxCorners1() {
	const double MIN_BOX_ACTIVITY = 0.2;
	const double MAX_BOX_ACTIVITY = 0.8;
	const int GRID_X = 10;
	const int GRID_Y = 10;
	const int GRID_Z = 10;

	const int REF_X = 5;
	const int REF_Y = 5;
	const int REF_Z = 5;

	boost::shared_ptr<ActivityGrid> grid(new ActivityGrid(GRID_X, GRID_Y, GRID_Z));
	grid->randomise(MIN_BOX_ACTIVITY, MAX_BOX_ACTIVITY);

	// put point in dead centre of grid
	boost::shared_ptr<Point> test_point(new Point(5.5, 5.5, 5.5));

	BoundingBox box(*grid, *test_point);

	// test set up
	{
		for (int i = 0; i < GRID_X; i++) {
			for (int j = 0; j < GRID_Y; j++) {
				for (int k = 0; k < GRID_Z; k++) {
					double act = grid->getGridPointActivity(i, j, k);
					//std::cout<<"BoundingBoxTest::testBoxCorners1: "<<"("<<i<<", "<<j<<", "<<k<<") = "<<act<<std::endl;
					ASSERT(act>MIN_BOX_ACTIVITY);
					ASSERT(act<MAX_BOX_ACTIVITY);
				}
			}
		}
	}
	// test point
	{
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X, REF_Y, REF_Z),
				box.getBoxElement(BoundingBox::BoxOrientation::FrontBottomLeft)->getActivity(), 0.00001);
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X+1, REF_Y, REF_Z),
				box.getBoxElement(BoundingBox::BoxOrientation::FrontBottomRight)->getActivity(), 0.00001);
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X, REF_Y, REF_Z+1),
				box.getBoxElement(BoundingBox::BoxOrientation::FrontTopLeft)->getActivity(), 0.00001);
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X+1, REF_Y, REF_Z+1),
				box.getBoxElement(BoundingBox::BoxOrientation::FrontTopRight)->getActivity(), 0.00001);
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X, REF_Y+1, REF_Z),
				box.getBoxElement(BoundingBox::BoxOrientation::BackBottomLeft)->getActivity(), 0.00001);
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X+1, REF_Y+1, REF_Z),
				box.getBoxElement(BoundingBox::BoxOrientation::BackBottomRight)->getActivity(), 0.00001);
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X, REF_Y+1, REF_Z+1),
				box.getBoxElement(BoundingBox::BoxOrientation::BackTopLeft)->getActivity(), 0.00001);
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X+1, REF_Y+1, REF_Z+1),
				box.getBoxElement(BoundingBox::BoxOrientation::BackTopRight)->getActivity(), 0.00001);
	}
}

void BoundingBoxTest::testBoxCorners2() {
	const double MIN_BOX_ACTIVITY = -10;
	const double MAX_BOX_ACTIVITY = 0.438;
	const int GRID_X = 12;
	const int GRID_Y = 12;
	const int GRID_Z = 12;

	const int REF_X = 1;
	const int REF_Y = 4;
	const int REF_Z = 9;

	boost::shared_ptr<ActivityGrid> grid(new ActivityGrid(GRID_X, GRID_Y, GRID_Z));
	grid->randomise(MIN_BOX_ACTIVITY, MAX_BOX_ACTIVITY);

	// put point in dead centre of grid
	boost::shared_ptr<Point> test_point(new Point(1.1, 4.79, 9.0003));

	BoundingBox box(*grid, *test_point);

	// test set up
	{
		for (int i = 0; i < GRID_X; i++) {
			for (int j = 0; j < GRID_Y; j++) {
				for (int k = 0; k < GRID_Z; k++) {
					double act = grid->getGridPointActivity(i, j, k);
					//	std::cout << "BoundingBoxTest::testBoxCorners1: " << "(" << i << ", " << j << ", " << k << ") = "
					//		<< act << std::endl;
					ASSERT(act>MIN_BOX_ACTIVITY);
					ASSERT(act<MAX_BOX_ACTIVITY);
				}
			}
		}
	}
	// test point
	{
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X, REF_Y, REF_Z),
				box.getBoxElement(BoundingBox::BoxOrientation::FrontBottomLeft)->getActivity(), 0.00001);
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X+1, REF_Y, REF_Z),
				box.getBoxElement(BoundingBox::BoxOrientation::FrontBottomRight)->getActivity(), 0.00001);
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X, REF_Y, REF_Z+1),
				box.getBoxElement(BoundingBox::BoxOrientation::FrontTopLeft)->getActivity(), 0.00001);
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X+1, REF_Y, REF_Z+1),
				box.getBoxElement(BoundingBox::BoxOrientation::FrontTopRight)->getActivity(), 0.00001);
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X, REF_Y+1, REF_Z),
				box.getBoxElement(BoundingBox::BoxOrientation::BackBottomLeft)->getActivity(), 0.00001);
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X+1, REF_Y+1, REF_Z),
				box.getBoxElement(BoundingBox::BoxOrientation::BackBottomRight)->getActivity(), 0.00001);
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X, REF_Y+1, REF_Z+1),
				box.getBoxElement(BoundingBox::BoxOrientation::BackTopLeft)->getActivity(), 0.00001);
		ASSERT_EQUAL_DELTA(grid->getGridPointActivity(REF_X+1, REF_Y+1, REF_Z+1),
				box.getBoxElement(BoundingBox::BoxOrientation::BackTopRight)->getActivity(), 0.00001);
	}
}

void BoundingBoxTest::testGetInterpolatedActivity1() {
	const double MIN_BOX_ACTIVITY = 0;
	const double MAX_BOX_ACTIVITY = 1;
	const int GRID_X = 12;
	const int GRID_Y = 12;
	const int GRID_Z = 12;

	const int REF_X = 1;
	const int REF_Y = 4;
	const int REF_Z = 9;
	boost::shared_ptr<ActivityGrid> grid(new ActivityGrid(GRID_X, GRID_Y, GRID_Z));
	grid->randomise(MIN_BOX_ACTIVITY, MAX_BOX_ACTIVITY);

	// put point in dead centre of grid
	boost::shared_ptr<Point> test_point_close(new Point(1.1, 4.79, 9.0003));
	boost::shared_ptr<Point> test_point_mid(new Point(1.4, 4.7, 9.1));
	boost::shared_ptr<Point> test_point_far(new Point(1.8, 4.79, 9.02));
	boost::shared_ptr<Point> test_point_on_corner(new Point(REF_X, REF_Y, REF_Z));
	boost::shared_ptr<Point> test_point_on_opposite_side(new Point(REF_X + 1, REF_Y, REF_Z));
	boost::shared_ptr<Point> test_point_on_opposite_corner(new Point(REF_X + 1, REF_Y + 1, REF_Z + 1));

	BoundingBox box_close(*grid, *test_point_close);
	BoundingBox box_mid(*grid, *test_point_mid);
	BoundingBox box_far(*grid, *test_point_far);
	BoundingBox box_corner(*grid, *test_point_on_corner);
	BoundingBox box_opposite_side(*grid, *test_point_on_opposite_side);
	BoundingBox box_opposite_corner(*grid, *test_point_on_opposite_corner);

	//double interpolated_act_close = box_close.getInterpolatedActivity();
	//double interpolated_act_mid = box_mid.getInterpolatedActivity();
	//double interpolated_act_far = box_far.getInterpolatedActivity();
	double interpolated_act_corner = box_corner.getInterpolatedActivity();
	double interpolated_act_opposite_side = box_opposite_side.getInterpolatedActivity();
	double interpolated_act_opposite_corner = box_opposite_corner.getInterpolatedActivity();

	double grid_corner = grid->getGridPointActivity(REF_X, REF_Y, REF_Z);
	double grid_opposite_side = grid->getGridPointActivity(REF_X + 1, REF_Y, REF_Z);
	double grid_opposite_corner = grid->getGridPointActivity(REF_X + 1, REF_Y + 1, REF_Z + 1);

	ASSERT_EQUAL_DELTA(interpolated_act_corner, grid_corner, 0.00001);
	ASSERT_EQUAL_DELTA(interpolated_act_opposite_side, grid_opposite_side, 0.00001);
	ASSERT_EQUAL_DELTA(interpolated_act_opposite_corner, grid_opposite_corner, 0.00001);

	/**
	 std::cout << "BoundingBoxTest::testGetInterpolatedActivity: " << "" << std::endl;
	 std::cout << "\t interpolated_act_close: " << interpolated_act_close << std::endl;
	 std::cout << "\t interpolated_act_mid: " << interpolated_act_mid << std::endl;
	 std::cout << "\t interpolated_act_far: " << interpolated_act_far << std::endl;
	 std::cout << "\t interpolated_act_corner: " << interpolated_act_corner << std::endl;
	 std::cout << "\t interpolated_act_opposite_side: " << interpolated_act_opposite_side << std::endl;
	 std::cout << "\t interpolated_act_opposite_corner: " << interpolated_act_opposite_corner << std::endl;
	 std::cout << "\t grid_corner: " << grid_corner << std::endl;
	 std::cout << "\t grid_opposite_side: " << grid_opposite_side << std::endl;
	 std::cout << "\t grid_opposite_corner: " << grid_opposite_corner << std::endl;
	 **/
}

void BoundingBoxTest::testGetInterpolatedActivity2() {
	const double MIN_BOX_ACTIVITY = 0;
	const double MAX_BOX_ACTIVITY = 5;
	const int GRID_X = 12;
	const int GRID_Y = 12;
	const int GRID_Z = 12;

	const int REF_X = 1;
	const int REF_Y = 4;
	const int REF_Z = 9;
	boost::shared_ptr<ActivityGrid> grid(new ActivityGrid(GRID_X, GRID_Y, GRID_Z, 1));
	grid->randomise(MIN_BOX_ACTIVITY, MAX_BOX_ACTIVITY);

	// put point in dead centre of grid
	boost::shared_ptr<Point> test_point_close(new Point(1.1, 4.79, 9.0003));
	boost::shared_ptr<Point> test_point_mid(new Point(1.4, 4.7, 9.1));
	boost::shared_ptr<Point> test_point_far(new Point(1.8, 4.79, 9.02));
	boost::shared_ptr<Point> test_point_on_corner(new Point(REF_X, REF_Y, REF_Z));
	boost::shared_ptr<Point> test_point_on_opposite_side(new Point(REF_X + 1, REF_Y, REF_Z));
	boost::shared_ptr<Point> test_point_on_opposite_corner(new Point(REF_X + 1, REF_Y + 1, REF_Z + 1));

	BoundingBox box_close(*grid, *test_point_close);
	BoundingBox box_mid(*grid, *test_point_mid);
	BoundingBox box_far(*grid, *test_point_far);
	BoundingBox box_corner(*grid, *test_point_on_corner);
	BoundingBox box_opposite_side(*grid, *test_point_on_opposite_side);
	BoundingBox box_opposite_corner(*grid, *test_point_on_opposite_corner);

	//double interpolated_act_close = box_close.getInterpolatedActivity();
	//double interpolated_act_mid = box_mid.getInterpolatedActivity();
	//double interpolated_act_far = box_far.getInterpolatedActivity();
	double interpolated_act_corner = box_corner.getInterpolatedActivity();
	double interpolated_act_opposite_side = box_opposite_side.getInterpolatedActivity();
	double interpolated_act_opposite_corner = box_opposite_corner.getInterpolatedActivity();

	double grid_corner = grid->getGridPointActivity(REF_X, REF_Y, REF_Z);
	double grid_opposite_side = grid->getGridPointActivity(REF_X + 1, REF_Y, REF_Z);
	double grid_opposite_corner = grid->getGridPointActivity(REF_X + 1, REF_Y + 1, REF_Z + 1);

	ASSERT(interpolated_act_corner> grid_corner);
	ASSERT(interpolated_act_opposite_side> grid_opposite_side);
	ASSERT(interpolated_act_opposite_corner> grid_opposite_corner);

	/**
	 std::cout << "BoundingBoxTest::testGetInterpolatedActivity: " << "" << std::endl;
	 std::cout << "\t interpolated_act_close: " << interpolated_act_close << std::endl;
	 std::cout << "\t interpolated_act_mid: " << interpolated_act_mid << std::endl;
	 std::cout << "\t interpolated_act_far: " << interpolated_act_far << std::endl;
	 std::cout << "\t interpolated_act_corner: " << interpolated_act_corner << std::endl;
	 std::cout << "\t interpolated_act_opposite_side: " << interpolated_act_opposite_side << std::endl;
	 std::cout << "\t interpolated_act_opposite_corner: " << interpolated_act_opposite_corner << std::endl;
	 std::cout << "\t grid_corner: " << grid_corner << std::endl;
	 std::cout << "\t grid_opposite_side: " << grid_opposite_side << std::endl;
	 std::cout << "\t grid_opposite_corner: " << grid_opposite_corner << std::endl;
	 **/
}

void BoundingBoxTest::testBoxCorners3() {
	const double DISTANCE1D = sqrt((0.5 * 0.5) + (0.5 * 0.5) + (0.5 * 0.5));
	const double DISTANCE2D = sqrt((1.5 * 1.5) + (1.5 * 1.5) + (1.5 * 1.5));
	const double DISTANCE3D = sqrt((2.5 * 2.5) + (2.5 * 2.5) + (2.5 * 2.5));

	const double EQUAL_ACTIVITY = 17;
	const int GRID_X = 10;
	const int GRID_Y = 10;
	const int GRID_Z = 10;

	//	const int REF_X = 5;
	//const int REF_Y = 5;
	//	const int REF_Z = 5;

	boost::shared_ptr<ActivityGrid> grid(new ActivityGrid(GRID_X, GRID_Y, GRID_Z));
	grid->clearGrid(EQUAL_ACTIVITY);

	// put point in dead centre of grid
	boost::shared_ptr<Point> test_point(new Point(5.5, 5.5, 5.5));

	// 1d
	{
		BoundingBox box(*grid, *test_point);

		double level1_act = 8 * (EQUAL_ACTIVITY - (DISTANCE1D));
		double exp_total = level1_act;
		double activity = box.getInterpolatedActivity();
		ASSERT_EQUAL_DELTA(exp_total, activity, 0.00001);
	}

	// 2d
	{
		BoundingBox box(*grid, *test_point, 2);

		double level1_act = std::max(0.0, 8 * (EQUAL_ACTIVITY - (DISTANCE2D)));
		double exp_total = level1_act;
		double activity = box.getInterpolatedActivity();
		ASSERT_EQUAL_DELTA(exp_total, activity, 0.00001);
	}

	// 3d
	{
		BoundingBox box(*grid, *test_point, 3);

		double level1_act = std::max(0.0, 8 * (EQUAL_ACTIVITY - (DISTANCE3D)));
		double exp_total = level1_act;
		double activity = box.getInterpolatedActivity();
		ASSERT_EQUAL_DELTA(exp_total, activity, 0.00001);
	}

}
} //NAMESPACE

} //NAMESPACE
