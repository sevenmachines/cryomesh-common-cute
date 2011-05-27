/*
 * BoundingBoxTest.h
 *
 *  Created on: 27 May 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#ifndef BOUNDINGBOXTEST_H_
#define BOUNDINGBOXTEST_H_

#include "ICuteSuite.h"
namespace cryomesh {

namespace spacial {

class BoundingBoxTest {
public:
	BoundingBoxTest(){}
	virtual ~BoundingBoxTest(){}

	static void runSuite();
	static void testBoxCorners1();
	static void testBoxCorners2();
	static void testBoxCorners3();
	static void testGetInterpolatedActivity1();
	static void testGetInterpolatedActivity2();

};

}//NAMESPACE

}//NAMESPACE

#endif /* BOUNDINGBOXTEST_H_ */
