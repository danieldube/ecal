/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2019 Continental Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ========================= eCAL LICENSE =================================
 */

#include <cstring>
#include <string>

#include <gtest/gtest.h>

#include <ecal/ecal_payload.h>

namespace eCAL {

class TestPayload : eCAL::CPayload {
public:
  virtual bool WriteComplete(void *buf_, size_t len_) {
    size_t length = std::min(len_, data.size());
    std::memcpy(buf_, data.data(), length);
    return true;
  }

  virtual bool WritePartial(void *buf_, size_t len_) {
    return WriteComplete(buf_, len_);
  };

  size_t GetSize() { return data.size(); }

  const std::string data = "test data";
};

TEST(Core, CPayload) {
  TestPayload payload;
  std::string destination(" ", payload.GetSize());
  payload.WriteComplete(destination.data(), destination.size());
  EXPECT_EQ(destination, payload.data);
}

} // namespace eCAL