/***
 *  Software License Agreement: BSD 3-Clause License
 *
 *  Copyright (c) 2016-2021, qbrobotics®
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 *  following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this list of conditions and the
 *    following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *    following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *  * Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote
 *    products derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// Google Testing Framework
#include <gtest/gtest.h>
//#include <gmock/gmock.h>
// qb robotics libraries
#include <qb_device_hardware_interface/qb_device_hardware_interface.h>

TEST(Resources, Constructors) {
  // positive tests
  qb_device_hardware_interface::qbDeviceResources default_constructor;
  EXPECT_EQ(1, default_constructor.id);
  EXPECT_EQ(+1, default_constructor.motor_axis_direction);

  std::vector<int> right_ids = {0, 1, -1, 255, -255};
  for (auto const id : right_ids) {
    qb_device_hardware_interface::qbDeviceResources constructor(id);
    EXPECT_EQ(std::abs(id), constructor.id);
    if (id > 0) {
      EXPECT_EQ(+1, constructor.motor_axis_direction);
    } else if (id < 0) {
      EXPECT_EQ(-1, constructor.motor_axis_direction);
    } else {
      EXPECT_EQ(0, constructor.motor_axis_direction);  // zero is the broadcast id (i.e. no motor is controlled)
    }
  }

  // negative tests
  std::vector<int> wrong_ids = {256, -256};
  for (auto const id : wrong_ids) {
    qb_device_hardware_interface::qbDeviceResources constructor(id);
    //FIXME
  }
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
//  testing::InitGoogleMock(&argc, argv);
//  testing::FLAGS_gmock_verbose = "info";
  ros::init(argc, argv, "unit_tests");
  return RUN_ALL_TESTS();
}